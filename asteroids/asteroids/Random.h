#pragma once

#include<math.h>
#include<random>
#include<iostream>

class Random {
public:
    std::mt19937 s_RandomEngine;
    std::uniform_int_distribution<std::mt19937::result_type> s_Distribution;

    std::default_random_engine generator;

public:
    Random(int seed1, int seed2) {
        this->s_RandomEngine = std::mt19937(seed1);
        this->generator = std::default_random_engine(seed2);
    }
    float getRandomFloat() {
        return (float)s_Distribution(s_RandomEngine) / (float)std::numeric_limits<uint32_t>::max();
    }

    float getRangeRandomFloat(float min, float max) {
        return getRandomFloat() * (max - min) + min;
    }

    float getRandomFloatNormalDist(float mean, float std, float lborder, float rborder) {
        std::normal_distribution<float> distribution(mean, std);
        float number = distribution(generator);
        number = number > rborder ? rborder : number;
        number = number < lborder ? lborder : number;
        return number;
    }
    int getRangeRandomInt(int min, int max) {
        return int(getRandomFloat() * (max - min) + min);
    }

    float getSigmoid(float x) {
        float y = 1 / (1 + std::exp(-x));
        return y;
    }
};