#include "Asteroid.h"

 Asteroid Asteroid::create(int size, float posX, float posY, float velX, float velY)
{
	switch (size) {
	case 1:
		return SmallAsteroid(posX, posY, velX, velY);
	case 2:
		return MediumAsteroid(posX, posY, velX, velY);
	case 3:
		return BigAsteroid(posX, posY, velX, velY);
	}
}

void Asteroid::setPosition(const float x, const float y)
{
	this->shape.setPosition(x, y);
}

sf::FloatRect Asteroid::getBounds() {
	return this->shape.getGlobalBounds();
}

void Asteroid::update() {
	this->shape.move(this->vel);
}

void Asteroid::render(std::shared_ptr<sf::RenderTarget> target) {
	target->draw(this->shape);
}