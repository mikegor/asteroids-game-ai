#include "Generation.h"

void Generation::initWindow(std::shared_ptr<sf::RenderWindow> window)
{
	this->window = window;
}

void Generation::initAsteroids(int asteroidsAmount)
{
	for (int i = 0; i < asteroidsAmount;i++) {
		spawnAsteroid();
	}
}

void Generation::initPlayer()
{
	this->player = std::make_shared<Player>();
}

void Generation::spawnAsteroid()
{
	int sizeA = random.getRangeRandomInt(1, 4);
	int xA = random.getRangeRandomInt(1, 3);
	int yA = random.getRangeRandomInt(1, 3);
	switch (xA)
	{
	case 1:
		xA = 0;
		break;
	case 2:
		xA = this->windowX;
		break;
	default:
		break;
	}
	switch (yA)
	{
	case 1:
		yA = 0;
		break;
	case 2:
		yA = this->windowY;
		break;
	default:
		break;
	}
	float deg = random.getRangeRandomFloat(0, 360);
	float velXA = Helpers::getDirX(deg);
	float velYA = Helpers::getDirY(deg);

	std::shared_ptr<Asteroid> asteroid = std::make_shared<Asteroid>(Asteroid::create(sizeA, xA - 100, yA - 100, velXA, velYA));
	asteroids->push_back(asteroid);
}

Generation::Generation(std::shared_ptr<sf::RenderWindow> window, int asteroidsAmount) : input(8), output(4)
{
	initWindow(window);
	initAsteroids(asteroidsAmount);
	initPlayer();
	ai = std::make_shared<NeuralNet>(9, 16, 4);
	collisions = std::make_shared<Collisions>();
	collisions->setAsteroids(asteroids);
	collisions->setWindow(window);
	collisions->setBullets(bullets);
	collisions->setPlayer(player);
}

void Generation::updateAsteroids()
{
	for (int i = 0; i < asteroids->size(); i++)
	{
		(*asteroids)[i]->update();
		collisions->asteroidCollisions(i);
	}
}

void Generation::updateBullets()
{
	for (int i = 0; i < bullets->size(); i++)
	{
		(*bullets)[i]->update();
		if (collisions->bulletCollisions(i)) {
			shotsHit++;
		}
	}
}

void Generation::updatePlayer()
{
	player->update();
	collisions->playerCollisions();
}

void Generation::updatePlayerAction()
{
	if (output[0] > 0.8) {
		player->move();
	}
	if (output[1] > 0.8)
		player->rotate(-1.f);
	else if (output[2] > 0.8)
		player->rotate(1.f);
	if (output[3] > 0.8 && player->canAttack()) {
		float posX = player->getPosition().x;
		float posY = player->getPosition().y;
		float deg = player->getRotation();
		float dirX = Helpers::getDirX(deg);
		float dirY = Helpers::getDirY(deg);

		bullets->push_back(std::make_shared<Bullet>(Bullet(posX, posY, dirX, dirY, deg)));
		shotsFired++;
	}
}

void Generation::updateTimers()
{
	if (asteroidTimer <= 0)
	{
		spawnAsteroid();
		asteroidTimer = 200;
	}
		
	lifeSpan++;
	asteroidTimer--;
}

void Generation::update()
{
	updateTimers();
	updateAsteroids();
	updateBullets();
	updatePlayerAction();
	updatePlayer();
	if (player->isDead())
		playerDead = true;
}

bool Generation::isPlayerDead()
{
	return playerDead;
}

void Generation::calculateFitness()
{
	fitness = lifeSpan;
	fitness *= shotsHit * shotsHit / shotsFired;
}

float Generation::getFitness()
{
	return fitness;
}

void Generation::mutate()
{
	ai->mutate(mutationRate);
}

std::shared_ptr<Generation> Generation::clone(int asteroidsAmount)
{
	auto clone = std::make_shared<Generation>(window, asteroidsAmount);
	clone->ai = ai->clone();
	return clone;
}

std::shared_ptr<Generation> Generation::crossover(std::shared_ptr<Generation> pair, int asteroidsAmount)
{
	auto child = std::make_shared<Generation>(window, asteroidsAmount);
	child->ai = ai->crossover(pair->ai);
	return child;
}

void Generation::scan()
{
	float dir = player->getRotation();
		for (int i = 0; i < input.size(); i++) {
			sf::Vector2f position = player->getPosition();
			position.x += 15 * Helpers::getDirX(int(dir) % 360);
			position.y += 15 * Helpers::getDirY(int(dir) % 360);
			input[i] = scanDir(dir, position);
			dir += 45;
		}
}

float Generation::scanDir(float dir, sf::Vector2f position)
{
	for (int dist = 1; dist < 20; dist++) {
			position.x += 15 * Helpers::getDirX(int(dir) % 360);
			position.y += 15 * Helpers::getDirY(int(dir) % 360);
			if (collisions->pointAsteroidsCollision(position))
				return 1 / dist;
			position = collisions->pointWorldCollision(position);
		}
	return 0;
}

void Generation::actualizeOutput()
{
	output = ai->output(input);
}

void Generation::render()
{
	for (auto asteroid : *asteroids)
	{
		asteroid->render(this->window);
	}

	for (auto bullet : *bullets)
	{
		bullet->render(this->window);
	}
	player->render(this->window);
}
