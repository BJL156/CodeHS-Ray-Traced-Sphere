#ifndef UTILS_H
#define UTILS_H

#include <random>
#include <cmath>

// std::clamp is C++17
double clamp(double d, double min, double max);

double randomDouble();
double randomDouble(double min, double max);

#endif