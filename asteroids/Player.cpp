#include "Player.h"

void Player::initVariables()
{
	this->attackCooldownMax = 10.f;
	this->attackCooldown = this->attackCooldownMax;
}

Player::Player()
{
	this->initVariables();
	this->shape = sf::RectangleShape(sf::Vector2f(60.f, 60.f));
	this->shape.setFillColor(sf::Color(1,255,255,128));
	this->shape.setOrigin(30.f, 30.f);
	this->shape.setPosition(sf::Vector2f(640, 360));
	this->shape.rotate(180.f);

	//ai
}

sf::FloatRect Player::getBounds()
{
	return this->shape.getGlobalBounds();
}

sf::Vector2f Player::getPosition()
{
	return this->shape.getPosition();
}

float Player::getRotation()
{
	return this->shape.getRotation();
}

void Player::setPosition(const float x, const float y)
{
	this->shape.setPosition(x, y);
}

void Player::move()
{
	
	float deg = this->shape.getRotation();
	float dirX = Helpers::getDirX(deg);
	float dirY = Helpers::getDirY(deg);
	
	this->shape.move(dirX, dirY);
}

void Player::rotate(float deg)
{
	this->shape.rotate(deg);
}

bool Player::canAttack()
{
	if (this->attackCooldown >= this->attackCooldownMax)
	{
		this->attackCooldown = 0.f;
		return true;
	}

	return false;
}

bool Player::isDead()
{
	return this->dead;
}

void Player::updateAttack()
{
	if (this->attackCooldown < this->attackCooldownMax)
		this->attackCooldown += 0.5f;
}

void Player::setDead()
{
	this->dead = true;
}

void Player::update()
{
	this->updateAttack();
}

void Player::render(sf::RenderTarget* target)
{
	target->draw(this->shape);
}
//show points
//void Player::render(sf::RenderTarget* target)
//{
//	target->draw(this->shape);
//
//	float dir = shape.getRotation();
//	for (int i = 0; i < input.size(); i++) {
//		sf::CircleShape vertex(3.f, 3.f);
//		sf::Vector2f position = shape.getPosition();
//		vertex.setFillColor(sf::Color::Red);
//		vertex.setPosition(position);
//		position.x += 15 * Helpers::getDirX(int(dir) % 360);
//		position.y += 15 * Helpers::getDirY(int(dir) % 360);
//		for (int dist = 1; dist < 20; dist++) {
//			vertex.setFillColor(sf::Color::Red);
//			position.x += 15 * Helpers::getDirX(int(dir) % 360);
//			position.y += 15 * Helpers::getDirY(int(dir) % 360);
//			vertex.setPosition(position.x, position.y);
//			if (Collisions::pointAsteroidsCollision(position))
//				vertex.setFillColor(sf::Color::Green);
//
//			target->draw(vertex);
//
//			//std::cout << "XD";
//			sf::Vector2f xd = Collisions::pointWorldCollision(position);
//			position = xd;
//		}
//		dir += 45;
//	}
//}
