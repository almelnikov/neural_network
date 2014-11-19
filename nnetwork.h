#ifndef _NNETWORK_HEADER
#define _NNETWORK_HEADER

#include <iostream>
#include <cmath>
#include <vector>
#include <cstdlib>

class NeuralNetwork {
public:
	NeuralNetwork();
	NeuralNetwork(unsigned int n, const unsigned int *neurons_cnt);
	NeuralNetwork(std::vector<std::vector<std::vector<double> > > &weights);
	~NeuralNetwork();
	void change_layer(std::vector<std::vector<double > > vec, unsigned int layer);
	void change_layer_number(unsigned int n);
	unsigned int layers();
	std::vector <double> evaluate(std::vector <double> &input);
	std::vector <double> train(std::vector <double> &input,
		std::vector <double> &tvec, double alpha, double nu);

private:
	std::vector<std::vector<std::vector<double> > > _weights;
	std::vector<std::vector<std::vector<double> > > _prevwt;
	std::vector<std::vector<double> > _eval;
	double activation(double v);
	double wrand();
	void clear_prevwt();
};

#endif
