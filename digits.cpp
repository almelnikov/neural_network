#include "nnetwork.h"
#include <fstream>

using namespace std;

const size_t train_cnt = 13;

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

vector <double> read_digit(int &digit, const char *filename)
{
	ifstream input;
	vector <double> res;
	int cnt;

	input.open(filename);
	input >> digit >> cnt;
	res.resize(cnt);
	for (int i = 0; i < cnt; i++)
		input >> res[i];
	return res;
}

vector <double> train_digit(NeuralNetwork &dignet, vector <double> &vec,
	int digit, double alpha, double nu)
{
	vector <double> testvec(train_cnt, 0.1);
	
	if ((digit >= 0) && (digit < train_cnt))
		testvec[digit] = 0.9;
	return dignet.train(vec, testvec, alpha, nu);
}

int main()
{
	const unsigned int dig_layers[3] = {25, 25, 10};
	NeuralNetwork dignet(2, dig_layers);
	vector <double> res;
	vector <vector <double> > digit_vec(train_cnt);
	vector <int> digit_n(train_cnt);

	digit_vec[0] = read_digit(digit_n[0], "digits_train/0");
	digit_vec[1] = read_digit(digit_n[1], "digits_train/1");
	digit_vec[2] = read_digit(digit_n[2], "digits_train/2");
	digit_vec[3] = read_digit(digit_n[3], "digits_train/notadigit1");
	digit_vec[4] = read_digit(digit_n[4], "digits_train/3");
	digit_vec[5] = read_digit(digit_n[5], "digits_train/4");
	digit_vec[6] = read_digit(digit_n[6], "digits_train/5");
	digit_vec[7] = read_digit(digit_n[7], "digits_train/6");
	digit_vec[8] = read_digit(digit_n[8], "digits_train/notadigit2");
	digit_vec[9] = read_digit(digit_n[9], "digits_train/7");
	digit_vec[10] = read_digit(digit_n[10], "digits_train/8");
	digit_vec[11] = read_digit(digit_n[11], "digits_train/9");
	digit_vec[12] = read_digit(digit_n[12], "digits_train/notadigit3");	


	for (int i = 0; i < 10000; i++) {
		int num = i % train_cnt;
		
		train_digit(dignet, digit_vec[num], digit_n[num], 0.1, 0.3);
	}
	
	res = dignet.evaluate(digit_vec[0]);
	cout << endl << "0" << endl;
	vector_print(res);
	
/*
	for (int i = 0; i < 1000; i++) {
		dignet.train(v_dig1, r_dig1, 0.1, 0.3);
		dignet.train(v_dig2, r_dig2, 0.1, 0.3);
		dignet.train(v_nad1, r_nad1, 0.1, 0.3);
		dignet.train(v_dig0, r_dig0, 0.1, 0.3);
	}

	res = dignet.evaluate(v_dig0);
	cout << endl << "0" << endl;
	vector_print(res);

	res = dignet.evaluate(v_dig1);
	cout << endl << "1" << endl;
	vector_print(res);

	res = dignet.evaluate(v_dig2);
	cout << endl << "2" << endl;
	vector_print(res);
	
	res = dignet.evaluate(v_deformed0);
	cout << endl << "deformed 0" << endl;
	vector_print(res);

	res = dignet.evaluate(v_deformed1);
	cout << endl << "deformed 1" << endl;
	vector_print(res);
	
	res = dignet.evaluate(v_nad1);
	cout << endl << "Not a digit" << endl;
	vector_print(res);
*/
	return 0;
}