#pragma once

#include<memory>
#include<iostream>

#include<SFML/Graphics.hpp>

#include"Asteroid.h"
#include"Player.h"
#include"Bullet.h"

class Player;
class Collisions {

public:
	sf::RenderWindow* window = nullptr;
	std::shared_ptr<std::vector<std::shared_ptr<Asteroid>>> asteroids;
	std::shared_ptr<std::vector<std::shared_ptr<Bullet>>> bullets;
	std::shared_ptr<Player> player;

	

	//static int points;

public:
	Collisions() {
	}
	void setWindow(sf::RenderWindow* window)
	{
		this->window = window;
	}
	void setAsteroids(std::shared_ptr<std::vector<std::shared_ptr<Asteroid>>> asteroids)
	{
		this->asteroids = asteroids;
	}
	void setBullets(std::shared_ptr<std::vector<std::shared_ptr<Bullet>>> bullets)
	{
		this->bullets = bullets;
	}
	void setPlayer(std::shared_ptr<Player> player)
	{
		this->player = player;
	}
	void playerCollisions();
	void asteroidCollisions(int counter);
	bool bulletCollisions(int counter);
	
	bool pointAsteroidsCollision(sf::Vector2f point);
	sf::Vector2f pointWorldCollision(sf::Vector2f point);
private:
	void playerWorldCollision();
	void asteroidWorldCollision(int asteroidCounter);
	void asteroidPlayerCollision(int asteroidCounter);
	bool bulletWorldCollision(int bulletCounter);
	bool bulletAsteroidCollision(int bulletCounter, int asteroidCounter);
};