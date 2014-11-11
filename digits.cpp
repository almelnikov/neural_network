#include "nnetwork.h"
#include <fstream>
#include <string>

using namespace std;

const size_t train_cnt = 13;
const size_t test_cnt = 4;

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

void print_mostsimilar(vector <double> &vec)
{
	double max = vec[0];
	int maxi = 0;
	string ret;

	for (int i = 1; i < vec.size(); i++) {
		if (max < vec[i]) {
			max = vec[i];
			maxi = i;
		}
	}
	if (max > 0.5)
		cout << maxi << " Out is " << max << endl;
	else
		cout << "Not a digit! Most similar digit is " << maxi << " Out is " <<
		 max << endl;
}

int main()
{
	const unsigned int dig_layers[3] = {25, 25, 10};
	NeuralNetwork dignet(2, dig_layers);
	vector <double> res;
	vector <vector <double> > digit_vec(train_cnt);
	vector <vector <double> > test_vec(test_cnt);
	vector <int> digit_n(train_cnt);
	vector <int> digit_test(test_cnt);

	// Для обучения
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

	// Для проверки работы на искаженных цифрах
	test_vec[0] = read_digit(digit_test[0], "digits_test/0_1");
	test_vec[1] = read_digit(digit_test[1], "digits_test/1_1");
	test_vec[2] = read_digit(digit_test[2], "digits_test/7_1");
	test_vec[3] = read_digit(digit_test[3], "digits_test/8_1");

	for (int i = 0; i < 10000; i++) {
		int num = i % train_cnt;
		
		train_digit(dignet, digit_vec[num], digit_n[num], 0.1, 0.3);
	}
	cout << "Training data:" << endl;
	for (int i = 0; i < train_cnt; i++) {
		res = dignet.evaluate(digit_vec[i]);
		if (digit_n[i] >= 0)
			cout << digit_n[i] << endl;
		else
			cout << "Not a digit" << endl;
		vector_print(res);
		print_mostsimilar(res);
		cout << endl;
	}

	cout << "Test data:" << endl;
	for (int i = 0; i < test_cnt; i++) {
		res = dignet.evaluate(test_vec[i]);
		cout << endl << digit_test[i] << endl;
		vector_print(res);
		print_mostsimilar(res);
		cout << endl;
	}

	return 0;
}