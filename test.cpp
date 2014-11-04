#include "nnetwork.h"

using namespace std;

int main() {
	vector <double> v_1_1;
	v_1_1.push_back(2);
	v_1_1.push_back(-3);

	vector <double> v_1_2;
	v_1_2.push_back(3);
	v_1_2.push_back(-1);

	vector <double> v_2_1;
	v_2_1.push_back(4);
	v_2_1.push_back(2);

	vector <double> v_2_2;
	v_2_2.push_back(2);
	v_2_2.push_back(2);

	vector <double> v_3_1;
	v_3_1.push_back(5);
	v_3_1.push_back(1);

	vector <vector <double> > l1;
	l1.push_back(v_1_1);
	l1.push_back(v_1_2);

	vector <vector <double> > l2;
	l2.push_back(v_2_1);
	l2.push_back(v_2_2);

	vector <vector <double> > l3;
	l3.push_back(v_3_1);

	vector <vector <vector <double> > > neu;
	neu.push_back(l1);
	neu.push_back(l2);
	neu.push_back(l3);

	vector <double> testvec;
	testvec.push_back(0.3);
	testvec.push_back(0.8);
	NeuralNetwork net(neu);
	vector <double> res = net.evaluate(testvec);
	cout << res[0] << endl << endl;

	const unsigned int lay[5] = {2, 2, 3, 5, 1};
	NeuralNetwork net2(4, lay);
	res = net2.evaluate(testvec);
	cout << res[0] << endl << endl;

	//-------------------------------------------
	vector <double> desired;
	desired.push_back(0.1);
	net.train(testvec, desired, 0, 0.3);

	cout << endl;
	res = net.evaluate(testvec);
	cout << res[0] << endl;;

	return 0;
}