//~ g++ -Wall -Wextra -o Pointeur Pointeur.cpp
#include <iostream>
#include <iomanip>
#include <memory>
#include <string>
#include <vector>



using namespace std;
//~ using enable_shared_from_this = esft;



class node;

//~ Exercice 1
//~ typedef node *node_ptr;

//~ Exercice 2 
//~ struct node_ptr: shared_ptr<node> {
	//~ node_ptr(node *n): shared_ptr<node>(n) {}
 //~ node_ptr(node_ptr const &) = default;
  //~ ~node_ptr() { /*std::cout << this << '\n';*/ }
//~ };

typedef shared_ptr<node> node_ptr;
class node : public std::enable_shared_from_this<node>{	
	public:
	string tag;
	//~ Ici cette solution permet de libérer toute les mémoire concerné 
	//~ meme en présence de cycles car les pointeurs existent encore sur la pile.
	//~ Mais en contre partie les seul pointeurs réels sont ceux sur la pile, 
	//~ donc en sortie d'une fonction ces pointeurs n'existerons plus.
	//~ vector<weak_ptr<node>> children;
	vector<node_ptr> children;
	vector<weak_ptr<node>> parents;
	
	node(string s) : tag(s){}
	~node(){
		cout << "Desctructeur de " << this << " " << tag << endl;
	}
	
	void add_child(node_ptr &child){
		children.push_back(child);
		child->parents.push_back(this->shared_from_this());
	}
	
	vector<node_ptr> get_parents() const {
		vector<node_ptr> tmp;
		for(weak_ptr<node> n : parents){
			if(!n.expired()){
				tmp.push_back(n.lock());
			}
		}
		return tmp;
	}
	
};



int main(int argc, char** argv){
	
	node_ptr a (new node("a'"));
	node_ptr b (new node("b'"));
	node_ptr c (new node("c'"));
	node_ptr d (new node("d'"));
	
	a->add_child(b);
	a->add_child(c);
	d->add_child(b);
	b->add_child(a);
	a.reset();
	cout << b->get_parents().size() << endl;
	return 0;
}


//~ Exercice 1
//~ Q°1 : Ce sont des pointeurs type C, qui n'appelle pas les destructeurs des objects qu'ils contiennent.
//~ Q°2 :
//~ Q°3 : parce qu'il est possible que l'un des noeuds contenu dans "children" soit aussi utilisé par un autre "node"

//~ Exercice 2
//~ Q°1 : - le destructeur du pointeur <d> est appelé. Il cause la destruction 
//~         de la valeur "d" qui n'utilise que "c", et personne d'autre de l'utilise "d". 
//        - le destructeur du pointeur <a> est appeler et cause en cascade la destruction de l'objet "a" 
//~         puis des objets contenu dans son vecteur children
//        - "b" et "c" ensuite dans l'ordre d'apparition 
//~ Q°2 : Il y a maintenant 2 shared_ptr qui point l'un vers l'autre :
//~       on est dans le cas où il en se libère jamais car l'incrément de pointeur partagé n'atteint jamais 0.

//~ Exercice 3
//~ Q°1 :
//~ Q°2 : 
//~ Q°3 : 
