#include "nnetwork.h"

using namespace std;

NeuralNetwork::NeuralNetwork()
{
	_weights.resize(1);
	_prevwt.resize(1);
}

// neurons_cnt содержит число входов в нулевом элементе
NeuralNetwork::NeuralNetwork(unsigned int n, const unsigned int *neurons_cnt)
{
	_weights.resize(n);
	for (unsigned int i = 1; i <= n; i++) {
		_weights[i-1].resize(neurons_cnt[i]);
		for (unsigned int j = 0; j < neurons_cnt[i]; j++) {
			_weights[i-1][j].resize(neurons_cnt[i - 1]);
			for (unsigned int k = 0; k < neurons_cnt[i - 1]; k++)
				_weights[i-1][j][k] = wrand();
		}
	}
	_prevwt = _weights;
	clear_prevwt();
}

NeuralNetwork::NeuralNetwork(vector<vector<vector<double> > > &weights)
{
	_weights = weights;
	_prevwt = _weights;
	clear_prevwt();
}

NeuralNetwork::~NeuralNetwork()
{
}

void NeuralNetwork::clear_prevwt()
{
	for (unsigned int i = 0; i < _weights.size(); i++)
		for (unsigned int j = 0; j < _weights[i].size(); j++)
			for (unsigned int k = 0; k < _weights[i][j].size(); k++)
				_prevwt[i][j][k] = 0;
}

double NeuralNetwork::wrand()
{
	double d = (double)rand() / RAND_MAX;
	return (-0.3 + d * 0.6);
}

void NeuralNetwork::change_layer(vector<vector<double> > vec, unsigned int layer)
{
	_weights[layer] = vec;
}

void NeuralNetwork::change_layer_number(unsigned int n)
{
	_weights.resize(n);
}

unsigned int NeuralNetwork::layers()
{
	return _weights.size();
}

double NeuralNetwork::activation(double v)
{
	return (1.0 / (1 + exp(-v)));
}

vector <double> NeuralNetwork::evaluate(vector <double> &input)
{
	unsigned int layers = _weights.size();
	vector <double> prev = input;
	vector <double> newout;

	_eval.clear();
	for (unsigned int i = 0; i < layers; i++) {
		newout.clear();
		for (unsigned int j = 0; j < _weights[i].size(); j++) {
			double sum = 0;
			for (unsigned int k = 0; k < prev.size(); k++) {
				sum += _weights[i][j][k] * prev[k];
			}
			newout.push_back(activation(sum));
			//cout << i << ' ' << j << ' ' << activation(sum) << endl;
		}
		_eval.push_back(newout);
		prev = newout;
	}

	return newout;
}

vector <double> NeuralNetwork::train(vector <double> &input,
	 vector <double> &tvec, double alpha, double nu)
{
	unsigned int layers = _weights.size();
	vector <double> newout = evaluate(input);

	vector <vector<double> > delta = _eval;
	// Погрешность выходного слоя
	unsigned int out_size = newout.size();
	vector <double> out_error(out_size);
	for (unsigned int i = 0; i < out_size; i++) {
		out_error[i] = newout[i] * (tvec[i] - newout[i]) * (1 - newout[i]);
	}
	delta[layers - 1] = out_error;
	// Погрешность остальных слоев
	for (int i = (delta.size() - 2); i >= 0 ; i--) {
		for (unsigned int j = 0; j < delta[i].size(); j++) {
			double sum = 0;
			for (unsigned int k = 0; k < delta[i+1].size(); k++)
				sum += delta[i+1][k] * _weights[i+1][k][j];
			delta[i][j] = sum * _eval[i][j] * (1 - _eval[i][j]);
		}
	}
	// Alpha
	for (unsigned int i = 0; i < _weights.size(); i++) {
		for (unsigned int j = 0; j < _weights[i].size(); j++) {
			for (unsigned int k = 0; k < _weights[i][j].size(); k++) {
				_weights[i][j][k] += alpha * _prevwt[i][j][k];
			}
		}
	}
	// Nu
	for (unsigned int i = 1; i < _weights.size(); i++) {
		for (unsigned int j = 0; j < _weights[i].size(); j++) {
			for (unsigned int k = 0; k < _weights[i][j].size(); k++) {
				_prevwt[i][j][k] = nu * _eval[i-1][k] * delta[i][j];
				_weights[i][j][k] += _prevwt[i][j][k];
				//cout << i << ' ' << j << ' ' << _weights[i][j][k] << endl;
			}
		}
	}
	// Для входного слоя
	for (unsigned int j = 0; j < _weights[0].size(); j++) {
		for (unsigned int k = 0; k < _weights[0][j].size(); k++) {
			_prevwt[0][j][k] = nu * input[k] * delta[0][j];
			_weights[0][j][k] += _prevwt[0][j][k];
		}
	}
	//cout << endl;
	return newout;
}
