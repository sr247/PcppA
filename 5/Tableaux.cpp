//~ Compilation: g++ -std=c++11 -Wall -Wextra -o Tableau Tableaux.cpp

#include <iostream>
#include <cassert>
#include <memory>
//~ #include <>


template <typename T, std::size_t N>
class small_array{
	
	T my_var_[N];	
	
public:

	//~ On pourait mettre toute ces fonctions à default
	small_array(){
	}
	
	small_array(const small_array& array){
		for(unsigned int i = 0; i < N; i++)
			my_var_[i] = array[i];
	}
	
	small_array(small_array<T,N>&& array){}
	
	small_array& operator=(const small_array<T,N>& array){
		for(unsigned int i = 0; i < N; i++)
			my_var_[i] = array[i];
		return *this;
	}
	
	small_array& operator=(small_array<T,N>&& array){
		my_var_ = std::move(array);
		return *this;		
	}
	
	
	T& operator[](std::size_t i) noexcept {
		assert( 0 <= i && i < N );
		return my_var_[i];
	}
		
	T const& operator[](std::size_t i) const noexcept{
		assert( 0 <= i && i < N );			
		return my_var_[i];		
	}

	T& index(std::size_t i) {
		if( !(0 <= i && i < N) )
			throw std::runtime_error("Index out of range");
		return my_var_[i];		
	}
	
	T const& index(std::size_t i) const {
		if( !(0 <= i && i < N) )
			throw std::runtime_error("Index out of range");
		return my_var_[i];		
	}		
	
	~small_array(){}
};


template <typename T, std::size_t N>
class large_array{
	std::unique_ptr<small_array<T, N>> p;
	
public:
	
	large_array() : p(new small_array<T,N>()) {};
	
	large_array(const large_array& array) : p(new small_array<T,N>(*array.p)) {};
		
	//~ large_array(const large_array& array)
	//~ STRONG
	//~ { 
	
		//~ p = std::unique_ptr<small_array<T,N>>(new small_array<T,N>(*array.p));	
	//~ }
	
	//~ large_array& operator=(const large_array& array){
		//~ *p = *(array.p);
		//~ return *this;
	//~ }
	
	large_array& operator=(const large_array& array){
		p = std::unique_ptr<small_array<T,N>>(new small_array<T,N>(*array.p));
		return *this;
	}
	
	large_array(large_array&& array) = default;
	~large_array() = default;
	large_array& operator=(large_array&& array) = default;
		
	T& operator[](std::size_t i) noexcept{
		assert( 0 <= i && i < N );
		return p->index(i);	
	}
		
	T const& operator[](std::size_t i) const noexcept{
		assert( 0 <= i && i < N );			
		return p->index(i);		
	}

	T& index(std::size_t i) {
		if( !(0 <= i && i < N) )
			throw std::runtime_error("Index out of range");
		return p->index(i);		
	}
	
	T const& index(std::size_t i) const {
		if( !(0 <= i && i < N) )
			throw std::runtime_error("Index out of range");
		return p->index(i);
	}
	
	void swap(large_array& array){
		p.swap(array.p);		
	}
	
};

template <bool, typename T1, typename T2> struct if_;
template <typename T1, typename T2> struct if_<true ,T1, T2> {typedef T1 type;};
template <typename T1, typename T2> struct if_<false ,T1, T2> {typedef T2 type;};

template <typename T, std::size_t N>
using smart_array = typename 
if_< (sizeof(small_array<T,N>) > 16), large_array<T,N>, small_array<T,N> >::type;

int main(){
	//~ Exercice 1
	//~ Q°1:
	//~ Je sais pas 
	
	//~ Q°2:
	//~ Non car l'operateur peut lever une exception sur les bornes de i
	
	//~ Q°3:
	//~ on a des valeur surprenante car le constructeur n'initialise pas les valeurs
	//~ Si le type T possede un constructeur celui ci sera appeler et
	//~ effectura eventuellement une initialisation.
	//~ small_array<int, 4> t;
	//~ t[2] = 42;
	
	//~ small_array<int, 4> const u = t;
	
	//~ for(std::size_t i = 0; i < 4; i++){
		//~ std::cout << "[ " << "] = " << u[i] << '\n';
	//~ }
	
	//~ Q°4
	//~ t[4] = 0;
	//~ t.index(4);
	
	//~ Exercice 2:
	large_array<int, 1000 * 1000 * 10> s;	
	s[2] = 42;
	
	//~ Q°3:
	//~ On a une utilisation plus dense de la mémoire 
	//~ ( allocation dynamique + construction par copie)
	
	
	//~ Exercice 3:
	smart_array<int, 4> y;
	y[2] = 42;
	
	smart_array<int, 1000*1000*10> z;
	z[2] = 42;
	return 0;
	
}
