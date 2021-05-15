#pragma once

#include<SFML/Graphics.hpp>

class Bullet
{
public:
	sf::RectangleShape shape;
	sf::Vector2f direction;

	Bullet(float posX, float posY, float dirX, float dirY, float deg);

	sf::FloatRect getBounds();

	void update();

	void render(sf::RenderTarget* target);
};