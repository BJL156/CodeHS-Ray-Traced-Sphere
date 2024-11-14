#include "Utils.h"

double clamp(double d, double min, double max) {
    return std::max(min, std::min(d, max));
}

double randomDouble() {
    static std::uniform_real_distribution<double> distribution(0.0, 1.0);
    static std::mt19937 generator;
    return distribution(generator);
}

double randomDouble(double min, double max) {
    return min + (max - min) * randomDouble();
}