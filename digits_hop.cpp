#include "digitops.h"
#include "hopfield.h"
#include <fstream>
#include <string>

using namespace std;

const size_t train_cnt = 3;
const size_t test_cnt = 4;
const size_t net_size = 30;

template <typename T>
void vector_print(const vector <T> &v)
{
	for (size_t i = 0; i < v.size(); i++)
		cout << v[i] << ' ';
	cout << endl;
}

vector <double> &print_digit(vector <double> &vec) {
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++)
			if (vec[i*5 + j] > 0)
				cout << '*';
			else
				cout << ' ';
		cout << endl;
	}
	return vec;
}

vector <double> &null_tominusone(vector <double> &vec)
{
	for (size_t i = 0; i < vec.size(); i++) {
		if (vec[i] == 0)
			vec[i] = -1;
	}
	return vec;
}

int main()
{
	Hopfield dignet(net_size);
	vector <double> res, deformed_vec;
	vector <vector <double> > digit_vec(train_cnt);
	vector <vector <double> > test_vec(test_cnt);
	vector <int> digit_test(test_cnt);

	// Для обучения
	int emptyint;
	digit_vec[0] = read_digit(emptyint, "digits_train/0");
	digit_vec[1] = read_digit(emptyint, "digits_train/1");
	digit_vec[2] = read_digit(emptyint, "digits_train/2");
	/*
	digit_vec[3] = read_digit(emptyint, "digits_train/3");
	digit_vec[4] = read_digit(emptyint, "digits_train/4");
	digit_vec[5] = read_digit(emptyint, "digits_train/5");
	digit_vec[6] = read_digit(emptyint, "digits_train/6");
	digit_vec[7] = read_digit(emptyint, "digits_train/7");
	digit_vec[8] = read_digit(emptyint, "digits_train/8");
	digit_vec[9] = read_digit(emptyint, "digits_train/9");
	*/

	// Для проверки работы на искаженных цифрах
	test_vec[0] = read_digit(digit_test[0], "digits_test/0_1");
	test_vec[1] = read_digit(digit_test[1], "digits_test/1_1");
	test_vec[2] = read_digit(digit_test[2], "digits_test/2_1");
	test_vec[3] = read_digit(digit_test[3], "digits_test/8_1");


	for (int i = 0; i < train_cnt; i++) {
		null_tominusone(digit_vec[i]);
	}
	dignet.train(digit_vec);
	for (int i = 0; i < train_cnt; i++) {
		res = dignet.evaluate(digit_vec[i]);
		cout << i << endl;
		print_digit(res);
		cout << endl;
	}

	cout << "Test data:" << endl;
	for (int i = 0; i < test_cnt; i++) {
		res = dignet.evaluate(test_vec[i]);
		cout << endl << digit_test[i] << endl;
		print_digit(test_vec[i]);
		cout << "Restored:" << endl;
		print_digit(res);
		cout << endl;
	}
	// Проверка на искаженных цифрах
	/*
	for (int i = 0; i < train_cnt; i++) {
		if (digit_n[i] >= 0) {
			for (int j = 1; j <= 5; j++) {
				int right_cnt = 0, right_g05 = 0;
			
				for (int rep_i = 0; rep_i < 100; ++rep_i) {
					int maxi = 0;
					double max;
					
					deformed_vec = generate_deformed(digit_vec[i], j);
					res = dignet.evaluate(deformed_vec);
					max = res[0];
					for (int k = 1; k < res.size(); k++) {
						if (max < res[k]) {
							max = res[k];
							maxi = k;
						}
					}
					if (maxi == digit_n[i]) {
						if (max > 0.5)
							++right_g05;
						++right_cnt;
					}
				}
				cout << digit_n[i] << " changed bits "  << j << " right ";
				cout << right_cnt << " right and greater then 0.5 " <<
					 right_g05 << endl;
			}
		}
	}
	*/
	return 0;
}
