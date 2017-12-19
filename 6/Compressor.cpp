//~ Compilation : g++ -Wall -Wextra -std=c++14 -O2 -o Compressor Compressor.cpp
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <map>
#include <algorithm>

using namespace std;
typedef map < string , int > occs;
typedef multimap < int ,codes > partial_codes;
typedef map < string , string > codes;

template<typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& vec)
{
    for (auto& el : vec)
    {
        os << el << ' ';
    }
    os << '\n';
    return os;
}

template<typename T, typename U>
std::ostream& operator<<(std::ostream& os, const std::map<T, U>& M)
{
    for (auto& el : M)
    {
        os << "<" << el->fst << ", " << el->snd << '>' << '\n';
    }
    os << '\n';
    return os;
}

std::vector<string> load(string filename) {
	ifstream file(filename);
	std::vector<string> tmp;
	string s;
	
	while(std::getline(file, s)) { 
		tmp.push_back(s);
	}
	return tmp;
}

occs count(const vector<string>& v){
	occs M;
	
	auto nb_occurences = [&M](const string s)
	{
		++M[s];
	};
	
	std::for_each(v.begin(), v.end(), nb_occurences);
	return M;
}

codes merge(const codes& A, const codes& B){
	codes C;
	
	for(auto const &e: A){
		//~ C[e1.first] = "0" + e1.second;               // Cout de création de la clé vide
		C.insert(make_pair(e.first, "0" + e.second));
		
	}
	
	for(auto const& e: B){
		//~ C[e2.first] = "1" + e2.second;
		C.insert(make_pair(e.first, "1" + e.second));
	}
	return codes();
}

void reduce(partial_codes &p){
	auto x = *p.begin();
	p.erase(p.begin());
	auto y = *p.begin();
	p.erase(p.begin());

	p.insert(make_pair<int, codes>(x.first + y.first, merge(x.second, y.second)));	
}

codes create(occs const& occ){
	partial_codes res;
	for(auto const& v : occ){
		codes c;
		c.insert(make_pair<>);
		res.ins
	}
}
int main()
{    
    // lambda fonction
    auto f = [](auto &x){x *= 10;};
    auto g = [](auto x) {return x * 10;};
    
    std::vector<float> v{1,2,3,4,5,6,7,8,9};
    std::vector<float> w(v.size());
    
    std::for_each(v.begin(), v.end(), f);
    std::cout << v << std::endl;   
    
    std::transform(v.begin(), v.end(), w.begin(), g);
    std::cout << w << std::endl;    
    
    
    
    vector<string> data(load("macbeth.txt"));    
    std::cout << data.size() << '\n';
    std::cout << "last word: " << *(data.cend() - 1) << '\n';
    
    occs oMap = count(data);
    
    std::cout << oMap.size() << '\n';
    std::cout << oMap["the"] << '\n';
    std::cout << oMap["macbeth"] << '\n';
    std::cout << oMap["chesnuts"] << '\n';
    
    
}

