#pragma once

#include <SFML/Graphics.hpp>

#include<memory>

class SmallAsteroid;

class Asteroid
{
public:
	sf::Vector2f pos;
	sf::Vector2f vel;
	int size;
	float radius;
	sf::RectangleShape shape;

public:
	Asteroid(float posX, float posY, float velX, float velY)
	{
		this->vel = sf::Vector2f(velX, velY);
	}

	static Asteroid create(int size, float posX, float posY, float velX, float velY);

	sf::FloatRect getBounds();

	void setPosition(const float x, const float y);

	void update();
	void render(std::shared_ptr<sf::RenderTarget> target);
};

class SmallAsteroid : public Asteroid
{
public:
	SmallAsteroid(float posX, float posY, float velX, float velY) : Asteroid(posX, posY, velX, velY)
	{
		this->radius = 16;
		this->shape = sf::RectangleShape(sf::Vector2f(radius, radius));
		this->shape.setPosition(sf::Vector2f(posX, posY));
		this->shape.setOrigin(8.f, 8.f);
		this->shape.setFillColor(sf::Color(255, 255, 255, 128));
		this->vel *= 0.8f;
	}
};

class MediumAsteroid : public Asteroid
{
public:
	MediumAsteroid(float posX, float posY, float velX, float velY) : Asteroid(posX, posY, velX, velY)
	{
		this->radius = 30;
		this->shape = sf::RectangleShape(sf::Vector2f(radius, radius));
		this->shape.setPosition(sf::Vector2f(posX, posY));
		this->shape.setOrigin(15.f, 15.f);
		this->shape.setFillColor(sf::Color(255, 255, 255, 128));
		this->vel *= 0.6f;
	}
};

class BigAsteroid : public Asteroid
{
public:
	BigAsteroid(float posX, float posY, float velX, float velY) : Asteroid(posX, posY, velX, velY)
	{
		this->radius = 60;
		this->shape = sf::RectangleShape(sf::Vector2f(radius, radius));
		this->shape.setPosition(sf::Vector2f(posX, posY));
		this->shape.setOrigin(30.f, 30.f);
		this->shape.setFillColor(sf::Color(255, 255, 255, 128));
		this->vel *= 0.4f;
	}
};