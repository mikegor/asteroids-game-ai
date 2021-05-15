#pragma once

#include<math.h>
#include<random>
#include<iostream>



class StaticRandom {
public:
    static std::mt19937 s_RandomEngine;
    static std::uniform_int_distribution<std::mt19937::result_type> s_Distribution;

    static std::default_random_engine generator;

public:
    static float getRandomFloat() {
        return (float)s_Distribution(s_RandomEngine) / (float)std::numeric_limits<uint32_t>::max();
    }

    static float getRangeRandomFloat(float min, float max) {
        return getRandomFloat() * (max - min) + min;
    }

    static float getRandomFloatNormalDist(float mean, float std, float lborder, float rborder) {
        std::normal_distribution<float> distribution(mean, std);
        float number = distribution(generator);
        number = number > rborder ? rborder : number;
        number = number < lborder ? lborder : number;
        return number;
    }

    static int getRangeRandomInt(int min, int max) {
        return int(getRandomFloat() * (max - min) + min);
    }

    static float getSigmoid(float x) {
        float y = 1 / (1 + std::exp(-x));
        return y;
    }
};
