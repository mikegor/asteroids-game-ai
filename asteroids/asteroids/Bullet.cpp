#include "Bullet.h"

Bullet::Bullet(float posX, float posY, float dirX, float dirY, float deg)
{
    this->shape = sf::RectangleShape(sf::Vector2f(10.f, 6.f));
    this->shape.setPosition(posX, posY);
    this->shape.setOrigin(5.f, 3.f);
    this->shape.rotate(180.f + deg);
    
    this->direction.x = dirX*2;
    this->direction.y = dirY*2;

}

sf::FloatRect Bullet::getBounds()
{
    return this->shape.getGlobalBounds();
}

void Bullet::update()
{
    this->shape.move(direction);
}

void Bullet::render(sf::RenderTarget* target)
{
    target->draw(this->shape);
}
