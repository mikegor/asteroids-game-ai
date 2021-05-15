#include "NeuralNet.h"

NeuralNet::NeuralNet(int inputs, int hiddenNo, int outputNo)
{
	iNodes = inputs;
	oNodes = outputNo;
	hNodes = hiddenNo;

	whi = std::make_shared<Matrix>(Matrix(hNodes, iNodes + 1));
	whh = std::make_shared<Matrix>(Matrix(hNodes, hNodes + 1));
	woh = std::make_shared<Matrix>(Matrix(oNodes, hNodes + 1));
}

void NeuralNet::mutate(float mutationRate)
{
	whi->mutate(mutationRate);
	whh->mutate(mutationRate);
	woh->mutate(mutationRate);
}

std::vector<float> NeuralNet::output(std::vector<float> inputArray)
{
	auto inputs = woh->get1ColumnMatrix(inputArray);

	auto inputsBias = inputs->addBias();

	auto hiddenInputs = whi->multiplyMatrices(inputsBias);
	auto hiddenOutputs = hiddenInputs->activate();
	auto hiddenOutputBias = hiddenOutputs->addBias();


	auto hiddenInputs2 = whh->multiplyMatrices(hiddenOutputBias);
	auto hiddenOutputs2 = hiddenInputs2->activate();
	auto hiddenOutputsBias2 = hiddenOutputs2->addBias();

	auto outputInputs = woh->multiplyMatrices(hiddenOutputsBias2);
	auto outputs = outputInputs->activate();


	return outputs->toVec();
}

std::shared_ptr<NeuralNet> NeuralNet::crossover(std::shared_ptr<NeuralNet> pair)
{
	auto child = std::make_shared<NeuralNet>(iNodes, hNodes, oNodes);
	child->whi = whi->crossover(pair->whi);
	child->whh = whh->crossover(pair->whh);
	child->woh = woh->crossover(pair->woh);
	return child;
}

std::shared_ptr<NeuralNet> NeuralNet::clone()
{
	auto c = std::make_shared<NeuralNet>(iNodes, hNodes, oNodes);
	c->whi = whi->clone();
	c->whh = whh->clone();
	c->woh = woh->clone();

	return c;
}
