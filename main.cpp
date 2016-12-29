#include <iostream>
#include <fstream>
#include <string>
#include <boost/foreach.hpp>
#include <boost/tokenizer.hpp>

#define FILE_NAME "unitati_masura.txt"

using namespace std;
using namespace boost;

class Masura_fizica {
	public:
	string nume;
	string* um;
	float* um_si;
	int nr_um;

	void set_nume(string nume);
	void set_nr_um(int num);
	void set_um_si(string um_str);
	void set_um(string um_str);
	void get_conversion(int from, int to);
};

void Masura_fizica::set_nr_um(int num) {
	this->nr_um = num;

}
void Masura_fizica::set_nume(string nume) {
	this->nume = nume;

}
	
void Masura_fizica::set_um_si(string um_str) {
	this->um_si = new float[this->nr_um];
	int index = 0;

	char_separator<char> sep("\t");
	tokenizer< char_separator<char> > tokens(um_str, sep);
	BOOST_FOREACH (const string& t, tokens) {
		this->um_si[index] = stof(t);
		index++;
	}
}

void Masura_fizica::set_um(string um_str) {
	this->um = new string[this->nr_um];
	int index = 0;

	char_separator<char> sep("\t");
	tokenizer< char_separator<char> > tokens(um_str, sep);
	BOOST_FOREACH (const string& t, tokens) {
		this->um[index] = t;
		index++;
	}
}

void Masura_fizica::get_conversion(int from, int to) {


}



Masura_fizica* read_data(int* nr_marimi_fizice) {

	std::ifstream file(FILE_NAME);
	std::string str;
	Masura_fizica* marimi;
	int index = 0;


	std::getline(file, str);
	if ((*nr_marimi_fizice = stoi(str)) == 0) {
		cout << "Numarul de marimi fizice nu poate fi 0!\n";
		return 0;
	}

	marimi = new Masura_fizica[*nr_marimi_fizice];

	while (std::getline(file, str)) {

		marimi[index].set_nume(str);

		if (getline(file, str) == false) {
			cout << "Fisierul de date nu este valid!\n";
			return 0;
		}

		marimi[index].set_nr_um(stoi(str));

		if (getline(file, str) == false) {
			cout << "Fisierul de date nu este valid!\n";
			return 0;
		}

		marimi[index].set_um(str);

		if (getline(file, str) == false) {
			cout << "Fisierul de date nu este valid!\n";
			return 0;
		}
		marimi[index].set_um_si(str);
		index++;
	}

	return marimi;
}

void test_data(Masura_fizica* marimi, int nr_marimi_fizice) {

	for (int i = 0; i < nr_marimi_fizice; i++) {
		cout << marimi[i].nume << endl;
		for (int j = 0; j < marimi[i].nr_um; j++) {
			cout << marimi[i].um[j] << " ";
		}
		cout << endl;
		for (int j = 0; j < marimi[i].nr_um; j++) {
			cout << marimi[i].um_si[j] << " ";
		}
		cout << endl;
	}
} 

int main() 
{ 
	int nr_marimi_fizice;
	Masura_fizica* marimi = read_data(&nr_marimi_fizice);
	test_data(marimi, nr_marimi_fizice);

	return 0;
}
