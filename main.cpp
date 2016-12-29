#include <iostream>
#include <fstream>
#include <string>
#define FILE_NAME "unitati_masura.txt"


using namespace std;

class Masura_fizica {
	public:
	string nume;
	string* um;
	int* um_si;

	void set_nume(string nume);
	void set_um_si(string um_str);
	void set_um(string um_str);
	void get_conversion(int from, int to);
};

void Masura_fizica::set_nume(string nume) {
	this->nume = nume;

}
	
void Masura_fizica::set_um_si(string um_str) {


}

void Masura_fizica::set_um(string um_str) {

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
		marimi[index].set_um(str);

		if (getline(file, str) == false) {
			cout << "Fisierul de date nu este valid!\n";
			return 0;
		}
		marimi[index].set_um_si(str);
	}

	return marimi;
}

int main() 
{

	return 0;
}
