#pragma once

#include <vector>
#include <random>
#include<iostream>
#include<memory>
#include<time.h>

#include"Helpers.h"
#include"StaticRandom.h"


class Matrix {
	int rows;
	int cols;
	std::vector<std::vector<float>> matrix;
public:
	Matrix() {};
	Matrix(std::vector<float>);
	Matrix(int r, int c);


	std::shared_ptr<Matrix> get1ColumnMatrix(std::vector<float> vec);
	std::shared_ptr<Matrix> addBias();
	std::shared_ptr<Matrix> activate();

	std::shared_ptr<Matrix> multiplyMatrices(std::shared_ptr<Matrix> n);
	std::vector<float> toVec();
	std::shared_ptr<Matrix> clone();
#pragma region GeneticAlg
	void mutate(float mutationRate);
	std::shared_ptr<Matrix> crossover(std::shared_ptr<Matrix> pair);
#pragma endregion

};