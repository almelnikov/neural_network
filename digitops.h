#ifndef _HEADER_DIGITOPS
#define _HEADER_DIGITOPS

#include <fstream>
#include <vector>
#include <cstdlib>

std::vector <double> read_digit(int &digit, const char *filename);
std::vector <double> generate_deformed(std::vector <double> vec, int n);

#endif
