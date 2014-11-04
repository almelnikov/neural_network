#include "nnetwork.h"

using namespace std;

double dig1[25] = {0, 0, 0, 1, 0,
				   0, 0, 0, 1, 0,
				   0, 0, 0, 1, 0,
				   0, 0, 0, 1, 0,
				   0, 0, 1, 1, 1
				};
vector <double> v_dig1(dig1, dig1 + 25);
double rdig1[3] = {0.1, 0.9, 0.1};
vector <double> r_dig1(rdig1, rdig1 + 3);

double nad1[25] = {0, 0, 0, 0, 0,
				   0, 0, 0, 0, 0,
				   0, 0, 0, 0, 0,
				   0, 0, 0, 0, 0,
				   0, 0, 0, 0, 0
				};
vector <double> v_nad1(nad1, nad1 + 25);
double rnad1[3] = {0.1, 0.1, 0.1};
vector <double> r_nad1(rnad1, rnad1 + 3);

double dig2[25] = {1, 1, 1, 1, 1,
				   0, 0, 0, 0, 1,
				   1, 1, 1, 1, 1,
				   1, 0, 0, 0, 0,
				   1, 1, 1, 1, 1
				};
vector <double> v_dig2(dig2, dig2 + 25);
double rdig2[3] = {0.1, 0.1, 0.9};
vector <double> r_dig2(rdig2, rdig2 + 3);

double dig0[25] = {0, 1, 1, 1, 1,
				   0, 1, 0, 0, 1,
				   0, 1, 0, 0, 1,
				   0, 1, 0, 0, 1,
				   0, 1, 1, 1, 1
				};
vector <double> v_dig0(dig0, dig0 + 25);
double rdig0[3] = {0.9, 0.1, 0.1};
vector <double> r_dig0(rdig0, rdig0 + 3);

double deformed0[25] = {0, 1, 1, 1, 1,
					    0, 0, 0, 0, 1,
					    0, 1, 0, 0, 1,
					    1, 1, 0, 0, 1,
					    0, 1, 1, 1, 1
					   };
vector <double> v_deformed0(deformed0, deformed0 + 25);


double deformed1[25] = {0, 0, 1, 1, 0,
					    0, 0, 1, 1, 0,
					    0, 0, 0, 1, 0,
					    0, 0, 0, 1, 0,
					    0, 0, 1, 1, 1
					   };
vector <double> v_deformed1(deformed1, deformed1 + 25);

template <typename T>
void vector_print(const vector <T> &v)
{
	for (size_t i = 0; i < v.size(); i++)
		cout << v[i] << ' ';
	cout << endl;
}

int main()
{
	const unsigned int xor_layers[3] = {25, 25, 3};
	NeuralNetwork xornet(2, xor_layers);
	vector <double> res;

	for (int i = 0; i < 1000; i++) {
		xornet.train(v_dig1, r_dig1, 0.1, 0.3);
		xornet.train(v_dig2, r_dig2, 0.1, 0.3);
		xornet.train(v_nad1, r_nad1, 0.1, 0.3);
		xornet.train(v_dig0, r_dig0, 0.1, 0.3);
	}

	res = xornet.evaluate(v_dig0);
	cout << endl << "0" << endl;
	vector_print(res);

	res = xornet.evaluate(v_dig1);
	cout << endl << "1" << endl;
	vector_print(res);

	res = xornet.evaluate(v_dig2);
	cout << endl << "2" << endl;
	vector_print(res);
	
	res = xornet.evaluate(v_deformed0);
	cout << endl << "deformed 0" << endl;
	vector_print(res);

	res = xornet.evaluate(v_deformed1);
	cout << endl << "deformed 1" << endl;
	vector_print(res);
	
	res = xornet.evaluate(v_nad1);
	cout << endl << "Not a digit" << endl;
	vector_print(res);

	return 0;
}