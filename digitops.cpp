#include "digitops.h"

using namespace std;

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

vector <double> generate_deformed(vector <double> vec, int n)
{
	int *rands = new int [n];
	int vec_pos;
	vector <double> res = vec;
	
	for (int i = 0; i < n; i++) {
		bool found_repeat;
		do {
			found_repeat = false;
			vec_pos = rand() % res.size();
		
			for (int j = 0; j < i; j++) {
				if (rands[j] == vec_pos) {
					found_repeat = true;
					break;
				} 
			}
		} while (found_repeat);
		
		rands[i] = vec_pos;
		if (res[vec_pos] == 0)
			res[vec_pos] = 1;
		else
			res[vec_pos] = 0;
	}
	delete [] rands;
	return res;
}
