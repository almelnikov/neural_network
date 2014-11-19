#ifndef _HOPFIELD_HEADER
#define _HOPFIELD_HEADER

#include <iostream>
#include <vector>

class Hopfield {
public:
	Hopfield(size_t size);
	std::vector <double> evaluate(std::vector <double> vec);
	void train(std::vector <std::vector <double> > data);
	void train_once(std::vector <double> vec);

private:
	std::vector <std::vector <double> > _mat;
	size_t _size;
};

#endif