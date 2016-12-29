#include <iostream>


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


int main() 
{ 

	return 0;
}
