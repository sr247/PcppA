#include <iomanip>
#include <iostream>
#include <ctime>
#include <cstdio>
#include <string>
	
using namespace std;


struct file{
	
	
	file(const char* filename){ descr = fopen(filename, "w+"); }
	
	file(file const& f) = delete;
	
	file(file&& f){ 
		descr = f.descr;
		f.descr = NULL; 
	}
	
	file& operator=(file&& f){
		//~ if(descr) fclose(descr);
		//~ descr = f.descr;
		//~ f.descr = NULL; 
		
		//~ On récupere la rvalue dans une var temporele qu'on stock dans un nouvel objet de type file
		//~ On swap le contenu de l'objet courant avec ce nouvel objet
		//~ This contient maintenant le contenu de f par le biais de that
		
		file that(std::foward<file>(f));
		that.swap(*this);
		return *this;
	}
	void swap(file& other){
		std::swap(descr, other.descr);
	}
	file& operator=(file const& f) = delete;
	
	~file(){ if(descr)fclose(descr); }
	
	void write(string s){ fwrite(s.c_str(), s.size(), 1, descr);}
	
	private:
		FILE* descr;
};
	
class T{
public:
	T(){ std::cout << this << " : T Constructed from " << "None" << '\n'; }
	T(T const& t){ std::cout << this << " : T Constructed from " << &t << '\n'; }
	~T(){ std::cout << this << " : T Destroyed " << '\n'; }
	
	T& operator=(T const& t){ std :: cout << this << " : T Assigned with " << &t << '\n'; return *this; }
	T& operator=(T&& t){ std :: cout << this << " : T Moved from " << &t << '\n'; return *this; }
	
};


struct U {
	T v1, v2 ;
	U (T const &t) : v2(t) { std::cout << this << " : U Constructed from " << &t << '\n';
							v1 = t; }
};

void f1 ( T const & t ) {}
void f2 ( T t ) {}
T f3 () { return T (); }
T f4 () { T t; return t; }
void f5 (T &t) { t = T (); }

int main(int argc, char **argv){
	
	//~ Exercice 1 -----------------------------------------------------
	//~ T a;
	//~ f1 (a);
	//~ f2 (a);
	//~ T b = a;
	
	//~ Elision de copie : Le compilateur à le droit de checker la sortie
	//~ de la fonction pour simplifier le type du return doit etre le meme 
	//~ que celui de la variable avant l'opérateur égal
	//~ T c = f3();  
	
	//~ Named Return Value optimisation
	//~ T d = f4();
	
	//~ Passage par référence : t est déja construit alors on crée un temporaire et on affect t avec
	//~ f5 (d);
	//~ U e(a);
	//~ ----------------------------------------------------------------
	
	//~ Exercice 2 -----------------------------------------------------	
	file f ("test1.txt");
	f.write ("first string for test1\n");
	file g("test2.txt ");
	g.write("first string for test2\n");
	f.write("second string for test1\n");
	
	//~ Wrong : par sécurité on a interdit la création par défaut du 
	//~ constructeur par copie de la classe file
	//~ file h(f); file p = g;
	
	//~ Ici grace au constructeur par défaut avec rvalue on peut ré-exploiter 
	//~ la valeur de f en transferant le pointeur descr de f vers h;
	file h(std::move(f)); 
	//~ ----------------------------------------------------------------
	
	return 0;
}
