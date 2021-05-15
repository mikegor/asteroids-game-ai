#include"StaticRandom.h"

std::mt19937 StaticRandom::s_RandomEngine;
std::uniform_int_distribution<std::mt19937::result_type> StaticRandom::s_Distribution;

std::default_random_engine StaticRandom::generator;