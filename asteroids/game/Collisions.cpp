#include "Collisions.h"

void Collisions::playerCollisions()
{
	playerWorldCollision();
}

void Collisions::asteroidCollisions(int counter)
{
	asteroidWorldCollision(counter);
	asteroidPlayerCollision(counter);
}

bool Collisions::bulletCollisions(int bulletCounter)
{
	if (bulletWorldCollision(bulletCounter)) 
		bullets->erase(bullets->begin() + bulletCounter);
	else {
		unsigned int asteroidCounter = 0;
		for (int i = 0; i < (*asteroids).size(); i++) {
			if (bulletAsteroidCollision(bulletCounter, asteroidCounter)) {
				(*asteroids).erase((*asteroids).begin() + asteroidCounter);
				bullets->erase((*bullets).begin() + bulletCounter);
				return true;
			}
			asteroidCounter++;
		}
	}
	return false;
}

bool Collisions::pointAsteroidsCollision(sf::Vector2f point)
{
	for (auto& asteroid : *asteroids) {
		if ((point.x > asteroid->getBounds().left && point.x < (asteroid->getBounds().left + asteroid->getBounds().width))
			&& (point.y > asteroid->getBounds().top && point.y < (asteroid->getBounds().top + asteroid->getBounds().height)))
			return true;
	}
	return false;
}

sf::Vector2f Collisions::pointWorldCollision(sf::Vector2f point)
{
	if (point.x < 0.f)
	{
		return sf::Vector2f(window->getSize().x, point.y);
	}
	//Right world collison
	else if (point.x > window->getSize().x)
	{
		return sf::Vector2f(0.f, point.y);
	}

	//Top world collision
	if (point.y < 0.f)
	{
		return sf::Vector2f(point.x, window->getSize().y);
	}
	//Bottom world collision
	else if (point.y > window->getSize().y)
	{
		return sf::Vector2f(point.x, 0.f);
	}
	else
		return point;
}

void Collisions::playerWorldCollision()
{
	if (player->getBounds().left < 0.f - player->getBounds().width/2)
	{
		player->setPosition(window->getSize().x, player->getPosition().y);
	}
	//Right world collison
	else if (player->getBounds().left > window->getSize().x - player->getBounds().width/2)
	{
		player->setPosition(0.f, player->getPosition().y);
	}

	//Top world collision
	if (player->getBounds().top < 0.f - player->getBounds().height/2)
	{
		player->setPosition(player->getPosition().x, window->getSize().y);
	}
	//Bottom world collision
	else if (player->getBounds().top > window->getSize().y - player->getBounds().height/2)
	{
		player->setPosition(player->getPosition().x, 0.f);
	}
}

void Collisions::asteroidWorldCollision(int asteroidCounter)
{
	auto& asteroid = (*asteroids)[asteroidCounter];
	if (asteroid->getBounds().left < 0.f - asteroid->getBounds().width/2)
	{
		asteroid->setPosition(window->getSize().x, asteroid->shape.getPosition().y);
	}
	//Right world collison
	else if (asteroid->getBounds().left > window->getSize().x -asteroid->getBounds().width/2)
	{
		asteroid->setPosition(0.f, asteroid->shape.getPosition().y);
	}

	//Top world collision
	if (asteroid->getBounds().top < 0.f - asteroid->getBounds().height/2)
	{
		asteroid->setPosition(asteroid->shape.getPosition().x, window->getSize().y);
	}
	//Bottom world collision
	else if (asteroid->getBounds().top > window->getSize().y - asteroid->getBounds().height/2)
	{
		asteroid->setPosition(asteroid->shape.getPosition().x, 0.f);
	}
}

void Collisions::asteroidPlayerCollision(int asteroidCounter)
{
	auto& asteroid = (*asteroids)[asteroidCounter];
	if (asteroid->getBounds().intersects(player->getBounds()))
	{
		player->setDead();
	}
}

bool Collisions::bulletWorldCollision(int bulletCounter)
{
	auto& bullet = (*bullets)[bulletCounter];
	if (bullet->getBounds().top + bullet->getBounds().height < 0.f)
	{
		return true;
	}
	else
		return false;
}

bool Collisions::bulletAsteroidCollision(int bulletCounter, int asteroidCounter)
{
	auto& bullet = (*bullets)[bulletCounter];
	auto& asteroid = (*asteroids)[asteroidCounter];

	if (bullet->getBounds().intersects(asteroid->getBounds())) {
		return true;
	}
	return false;
}

