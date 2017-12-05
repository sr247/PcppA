//~ Compilation: g++ -Wall -Wextra -std=c++14 -o Matrices Matrices.cpp
#include <cassert>
#include <iostream>
#include <vector>
#include <string>
#include <ctime>

#include <iomanip>
#include <memory>
#include <utility>

using namespace std;
class full_matrix;
class diag_matrix;

class matrix{
	public:
	virtual pair<unsigned int, unsigned int> size() const = 0;
	virtual double get(unsigned int i, unsigned int j) const = 0;
	shared_ptr<matrix> slice(unsigned int i, unsigned int j, int h, int w) const {
		vector<double> tmp;
		for(int l = i; l < h; l++){
			for(int k = j; k < w ; k++){
				tmp.push_back(this->get(l, k));
			}
		}
		return shared_ptr<full_matrix>(tmp);
	}
	
	virtual ~matrix() = default;

};

class full_matrix : public matrix{
	
	unsigned int width_;
	unsigned int height_;
	vector<vector<double>> data_;
	
	public:
	full_matrix(unsigned int height, unsigned int width, vector<double> const& v) noexcept:
		width_ (width),
		height_(height)
		//~ Meme si le vecteur est plus grand que la taille totale de la 
		//~ matrice on ignore les éléments supérieure à width_ * height_
	{

		unsigned int k = 0;
		for(unsigned int i = 0; i < height; i++){
			data_.push_back(vector<double>(width, 0));
			for(unsigned int j = 0; j < width; j++){
				if(k < v.size()){
					data_[i][j] = v[k];
					k++;
				}
			}
		}
	}
	
	full_matrix(unsigned int height, unsigned int width, vector<double> &&v) noexcept(noexcept(move(v))):
		width_ (width),
		height_(height)
		// Basic
	{
		vector<double> tmp(move(v));
		unsigned int k = 0;
		for(unsigned int i = 0; i < height; i++){
			data_.push_back(vector<double>(width, 0));
			for(unsigned int j = 0; j < width; j++){
				if(k < tmp.size()){
					data_[i][j] = tmp[k];
					k++;
				}
			}
		}
	}
	
	pair<unsigned int, unsigned int> size() const noexcept	
	{
		return make_pair<int, int>(width_, height_);
	}
	
	double get(unsigned int i, unsigned int j) const
	// Strong
	// Si on accède à un indice supérieur à la taille -> segfault.
	// Néanmoins 	: pas de modification des données de l'objet.
	{ 
		return data_[i][j];
	}
	
};

class diag_matrix : public matrix{
	unsigned int width_;
	unsigned int height_;
	vector<double> data_;
	
	public:
	diag_matrix(vector<double> const& v) noexcept:
		width_ (v.size()),
		height_(v.size())
		//~ Meme si le vecteur est plus grand que la taille totale de la 
		//~ matrice on ignore les éléments supérieure à width_ * height_
	{
		data_ = v;
	}
	
	diag_matrix(vector<double> &&v) noexcept(noexcept(move(v))):
		width_ (v.size()),
		height_(v.size())
	{
		data_ = move(v);
	}
	
	pair<unsigned int, unsigned int> size() const noexcept	
	{
		return make_pair<int, int>(width_, height_);
	}
	
	double get(unsigned int i, unsigned int j) const
	// Strong
	// Si on accède à un indice supérieur à la taille -> segfault.
	// Néanmoins 	: pas de modification des données de l'objet.
	{ 
		if(i == j){ 
			return data_[i];
		}
		else{
			return 0.;
		}
		if(i > std::get<1>(size()) || j > std::get<0>(size())){
			throw runtime_error("Out of Matrix Bounds !");
		}
	}
	
		
};
	

	ostream &operator<<(ostream &os, matrix const &m)	
	{
		for(unsigned int i = 0; i < get<1>(m.size()); i++){
			for(unsigned int j = 0; j < get<0>(m.size()); j++){
				os << " " << m.get(i, j) << ""; 
			}
			os << endl;
		}
		return os;
	}

int main(){
	
	
	full_matrix m(2, 4, {1.,2.,3.,4.,5.,6.});
	cout << m << '\n';
	//~ Exercice 2:
	//~ Question 1
	// Doit aboutir à un seg fault: m.get(2,4);
	shared_ptr<matrix> d(new diag_matrix({1.,2.,3.,4.,5.,6.}));
	cout << *d << '\n';
	
	//~ Exercice 3:
	shared_ptr<matrix> s = d->slice(0,1, 3, 2)->slice(1,0,2,1);
	cout << *s << '\n';
	//~ Question
	return 0;
}
