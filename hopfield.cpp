#include "hopfield.h"

using namespace std;

Hopfield::Hopfield(size_t size)
{
	_size = size;
	_mat.resize(size);
	for (size_t i = 0; i < size; i++)
		_mat[i].resize(size);
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
	
	for (size_t i = 0; i < vec.size(); i++) {
		
	}
}

vector <double> Hopfield::evaluate(vector <double> vec)
{
	return vec;
}