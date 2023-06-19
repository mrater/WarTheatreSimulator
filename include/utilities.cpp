#include "utilities.h"

std::vector<int> generateRandomPermutation(const size_t &size)
{
    std::vector<int> turnOrderPermutation(size);
    std::iota(turnOrderPermutation.begin(), turnOrderPermutation.end(), 1);
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(turnOrderPermutation.begin(), turnOrderPermutation.end(), g);
    return turnOrderPermutation;
}