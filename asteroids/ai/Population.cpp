#include "Population.h"

Population::Population(int size, sf::RenderWindow* window, int asteroidsAmount)
{
	this->asteroidsAmount = asteroidsAmount;
	generations = std::make_shared<std::vector<std::shared_ptr<Generation>>>();
	for (int i = 0; i < size; i++) {
		auto gen = std::make_shared<Generation>(window, asteroidsAmount);
		generations->push_back(gen);
	}
}

void Population::updateAlive()
{
	int deads = 0;
	for (int i = 0; i < generations->size(); i++) {
		if (!(*generations)[i]->isPlayerDead()) {
			(*generations)[i]->scan();
			(*generations)[i]->actualizeOutput();
			(*generations)[i]->update();
			(*generations)[i]->render();
		}
		else
			deads++;
	}
	if (deads == generations->size())
		allDead = true;
}

void Population::naturalSelection()
{
	auto newGenerations = std::make_shared<std::vector<std::shared_ptr<Generation>>>(generations->size());

	(*newGenerations)[0] = (*generations)[bestGenerationNo]->clone(asteroidsAmount);

	for (int i = 1; i < generations->size(); i++) {
		if (i < generations->size()/2) {
			int genNo = getRandomGenByFitness();
			(*newGenerations)[i] = (*generations)[genNo]->clone(asteroidsAmount);
		}
		else {
			int genNo1 = getRandomGenByFitness();
			int genNo2 = getRandomGenByFitness();
			(*newGenerations)[i] = (*generations)[genNo1]->crossover((*generations)[genNo2], asteroidsAmount);
		}
		(*newGenerations)[i]->mutate();
	}
	
	for (int i = 0; i < generations->size(); i++)
		(*generations)[i] = (*newGenerations)[i]->clone(asteroidsAmount);

	allDead = false;
	std::cout << genCounter << std::endl;
	genCounter++;
}

int Population::getRandomGenByFitness()
{
	long fitnessSum = 0;
	for (int i = 0; i < generations->size(); i++)
		fitnessSum += (*generations)[i]->getFitness();

	int r = StaticRandom::getRangeRandomInt(0, fitnessSum);

	int runningSum = 0;

	for (int i = 0; i < generations->size(); i++) {
		runningSum += int((*generations)[i]->getFitness());
		if (runningSum > r)
			return i;
	}
	return 0;
}

void Population::calculateFitness()
{
	float maxFitness = 0;
	int genNo = 0;
	for (int i = 0; i < generations->size(); i++) {
		(*generations)[i]->calculateFitness();
		float fitness = (*generations)[i]->getFitness();
		if ( fitness > maxFitness) {
			maxFitness = fitness;
			genNo = i;
		}
	}
	bestGenerationNo = genNo;
}

bool Population::areAllDead()
{
	return allDead;
}
