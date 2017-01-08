#include <iostream>
#include <fstream>
#include <string>
#include <boost/foreach.hpp>
#include <boost/tokenizer.hpp>
#include <cstdlib>
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
	float get_conversion(int from, int to, float value);
	float temperature_to_C(string um, float value);
	float temperature_from_C(string um, float value);
	float convert_temepature(string from, string to, float value);
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

float Masura_fizica::get_conversion(int from, int to, float value) {
	if (this->nume == "Temperatura")
		return convert_temepature(um[from], um[to], value);

	return value * this->um_si[from] / this->um_si[to];
}


float Masura_fizica::temperature_to_C (string um, float value) {
	if (um == "C")
	       return value;
	if (um == "K")
	       return value - 273.15;
	if (um == "F")
	       return  (value - 32) / 1.8;
	if (um == "Ra")
	       return (value - 32 - 459.67) / 1.8;
	if (um == "Re")
	       return value * 1.25;
	return 0;
}

float Masura_fizica::temperature_from_C (string um, float value) {
	if (um == "C")
	       return value;
	if (um == "K")
	       return value + 273.15;
	if (um == "F")
	       return  value * 1.8 + 32;
	if (um == "Ra")
	       return  value * 1.8 + 32 + 459.67;
	if (um == "Re")
	       return value/1.25;
	return 0;
}
float Masura_fizica::convert_temepature(string from, string to, float value) {
	return temperature_from_C(to, temperature_to_C(from, value));
}


Masura_fizica* read_data(int* nr_marimi_fizice) {

	std::ifstream file(FILE_NAME);
	std::string str;
	Masura_fizica* marimi;
	int index = 0;


	std::getline(file, str);
	if ((*nr_marimi_fizice = stoi(str)) == 0) {
		cout << "Numarul de marimi fizice nu poate fi 0!\n";
		return NULL;
	}

	marimi = new Masura_fizica[*nr_marimi_fizice];

	while (true) {
		// se citeste numele marimii fizice
		getline(file, str);

		if (file.eof()) { break;}
		marimi[index].set_nume(str);

		// se citeste numarul unitatilor de masura
		getline(file, str);
		if (file.eof()) {
			cout << "Fisierul de date nu este valid!\n";
			return NULL;
		}

		marimi[index].set_nr_um(stoi(str));

		// se citesc unitatile de masura
		getline(file, str);
		if (file.eof()) {
			cout << "Fisierul de date nu este valid!\n";
			return NULL;
		}

		marimi[index].set_um(str);

		// se citeste vecgorul de conversii pentru unitatile de masura
		getline(file, str);
		if (file.eof()) {
			cout << "Fisierul de date nu este valid!\n";
			return NULL;
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
	if (marimi == NULL) {
		return 0;
	}
//	test_data(marimi, nr_marimi_fizice);
	int option;
	int from;
	int to;
	float value;
	int back;
	int quit;
	int end;
	float result;

	while(true) {
marime_fizica:
		cout << "\n------------------\n";
		cout << "Alege marimea fizica\n";
		for (int i = 0; i < nr_marimi_fizice; i++) {
			cout << i + 1 << "    " << marimi[i].nume << endl;
			if (i == nr_marimi_fizice - 1) {
				quit = i + 2;
				cout << quit  << "    " << "Quit\n";

			}
		}

		cout << "Marime fizica: ";
		if(!(cin >> option) || option <= 0 || option > nr_marimi_fizice + 1) {
			cout << "\nValoarea nu este valida!\n";
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			goto marime_fizica;
		}

		if (option == quit) {
			return 0;
		}
		option -= 1;

um_init:
		cout << "\n------------------\n";
		cout << "Alege unitatea de masura initiala!\n";
		for (int j = 0; j < marimi[option].nr_um; j++) {
			cout << j + 1 << "    " << marimi[option].um[j] << endl;
			if (j == marimi[option].nr_um - 1) {
				back = j + 2;
				cout << back  << "    " << "Back\n";

			}
		}


		cout << "Um initiala: ";
		if(!(cin >> from) || from <= 0 || from > marimi[option].nr_um + 1) {
			cout << "\nValoarea nu este valida!\n";
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			goto um_init;
		}

		if (from == back) {
			goto marime_fizica;
		}
um_final:

		cout << "\n------------------\n";
		cout << "Alege unitatea de masura finala!\n";
		for (int j = 0; j < marimi[option].nr_um; j++) {
			cout << j + 1<< "    " << marimi[option].um[j] << endl;
			if (j == marimi[option].nr_um - 1) {
				back = j + 2;
				cout << back  << "    " << "Back\n";
			}
		}

		cout << "Um finala: ";
		if(!(cin >> to) || to <= 0 || to > marimi[option].nr_um + 1) {
			cout << "\nValoarea nu este valida!\n";
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			goto um_final;
		}

		if (to == back) {
			goto um_init;
		}

		cout << "\n------------------\n";
		cout << "Valoarea de convertit: ";

		while(!(cin >> value))
		{
			cout << "\nValoarea nu este valida!\n";
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "\n------------------\n";
			cout << "Valoarea de convertit: ";
		}

		result = marimi[option].get_conversion(from - 1, to - 1, value);
		cout << value << " " << marimi[option].um[from - 1] <<
			" = " << result << " " << marimi[option].um[to - 1] << endl;

end:
		cout << "\n------------------\n";
		cout << "1    Executa o alta conversie\n";
		cout << "2    Quit\n";

		if(!(cin >> end) || end < 1 || end > 2) {
			cout << "\nValoarea nu este valida!\n";
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			goto end;
		}
		if (end == 2) {
			return 0;
		} else {
			goto marime_fizica;
		}
	}


	return 0;
}
