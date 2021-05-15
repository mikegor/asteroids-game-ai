#pragma once

#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>
#include <vector>

#include"Helpers.h"
#include"NeuralNet.h"
#include"Collisions.h"

#include<windows.h>

class Player
{
public:
	sf::RectangleShape shape;

	float attackCooldown;
	float attackCooldownMax;

	bool dead = false;
	int score = 0;

	void initVariables();

	Player();

	sf::FloatRect getBounds();
	sf::Vector2f getPosition();
	float getRotation();

	void setPosition(const float x, const float y);
	void move();
	void rotate(float deg);

	bool canAttack();
	bool isDead();

	void updateAttack();
	void setDead();

	void update();
	void render(sf::RenderTarget* target);

	
};