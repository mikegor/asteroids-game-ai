#pragma once

#include<memory>

#include"Matrix.h"


class NeuralNet{
public:
	int iNodes = 0;
	int hNodes = 0;
	int oNodes = 0;

	std::shared_ptr<Matrix> whi;
	std::shared_ptr<Matrix> whh;
	std::shared_ptr<Matrix> woh;

	NeuralNet() {};
	NeuralNet(int inputs, int hiddenNo, int outputNo);

	void mutate(float mutationRate);

	std::vector<float> output(std::vector<float> inputArray);

	std::shared_ptr<NeuralNet> crossover(std::shared_ptr<NeuralNet> pair);

	std::shared_ptr<NeuralNet> clone();
};