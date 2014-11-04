#include "nnetwork.h"

using namespace std;

double xor1[2] = {0, 0};
vector <double> v_xor1(xor1, xor1 + 2);
vector <double> r_xor1(1, 0.01);

double xor2[2] = {1, 0};
vector <double> v_xor2(xor2, xor2 + 2);
vector <double> r_xor2(1, 0.99);

double xor3[2] = {1, 1};
vector <double> v_xor3(xor3, xor3 + 2);
vector <double> r_xor3(1, 0.01);

double xor4[2] = {0, 1};
vector <double> v_xor4(xor4, xor4 + 2);
vector <double> r_xor4(1, 0.99);

int main()
{
	const unsigned int xor_layers[4] = {2, 3, 3, 1};
	NeuralNetwork xornet(3, xor_layers);
	vector <double> res;

	for (int i = 0; i < 100000; i++) {
		xornet.train(v_xor1, r_xor1, 0, 0.2);
		xornet.train(v_xor2, r_xor2, 0, 0.2);
		xornet.train(v_xor3, r_xor3, 0, 0.2);
		xornet.train(v_xor4, r_xor4, 0, 0.2);
	}
	res = xornet.evaluate(v_xor1);
	cout << "0 0" << endl;
	cout << res[0] << endl << endl;
	res = xornet.evaluate(v_xor2);
	cout << "1 0" << endl;
	cout << res[0] << endl << endl;
	res = xornet.evaluate(v_xor3);
	cout << "1 1" << endl;
	cout << res[0] << endl << endl;
	res = xornet.evaluate(v_xor4);
	cout << "0 1" << endl;
	cout << res[0] << endl << endl;
	return 0;
}