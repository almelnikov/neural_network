#include "hopfield.h"

using namespace std;

Hopfield::Hopfield(size_t size)
{
	_size = size;
	_mat.resize(size);
	for (size_t i = 0; i < size; i++)
		_mat[i].resize(size);
}

double Hopfield::sgn(double d)
{
	if (d >= 0)
		return 1;
	else
		return -1;
}

void Hopfield::train(vector <vector <double> > data)
{
	for (size_t i = 0; i < data.size(); i++) {
		train_once(data[i]);
	}
}

void Hopfield::train_once(vector <double> vec)
{
	vector <double> compl_vec = vec;
	compl_vec.resize(_size, 1);
	
	for (size_t i = 0; i < _size; i++) {
		for (size_t j = 0; j < _size; j++) {
			if (i != j)
				_mat[i][j] += compl_vec[i] * compl_vec[j] / _size;
		}
	}
}

vector <double> Hopfield::evaluate(vector <double> vec)
{
	vector <double> prevvec;
	vector <double> newvec = vec;
	newvec.resize(_size, 1);

	for (int k = 0; k < 1000; k++) { // TBD условие цикла
		prevvec = newvec;
		for (size_t i = 0; i < _size; i++) {
			double sum = 0;
			for (size_t j = 0; j < _size; j++) {
				sum += _mat[i][j] * newvec[i];
			}
			newvec[i] = sgn(sum);
		}
	}
	return newvec;
}
