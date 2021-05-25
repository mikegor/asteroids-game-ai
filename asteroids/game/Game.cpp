#include "Game.h"

void Game::initWindow()
{
	this->window = std::make_shared<sf::RenderWindow>(sf::VideoMode(this->windowX, this->windowY), "Asteroids");
}

void Game::initAsteroids()
{
	for (int i = 0; i < 20; i++) {
		this->spawnAsteroid();
	}
}

void Game::initPlayer()
{
		this->player = std::make_shared<Player>();
}

void Game::spawnAsteroid()
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

Game::Game()
{
	this->initWindow();
	this->initAsteroids();
	this->initPlayer();

	collisions.setAsteroids(asteroids);
	collisions.setBullets(bullets);
	collisions.setWindow(window);
	collisions.setPlayer(player);
	std::srand(1);
}

Game::~Game()
{
	//delete this->window;
}

void Game::run()
{
	while (this->window->isOpen() && !(player->isDead()))
	{
		this->updatePollEvents();
		if (this->asteroidTimer == 200) {
			this->spawnAsteroid();
			asteroidTimer = 0;
		}
		asteroidTimer++;
		this->update();
		this->render();
	}
}

void Game::updatePollEvents()
{
	sf::Event e;
	while (this->window->pollEvent(e))
	{
		if (e.Event::type == sf::Event::Closed)
			this->window->close();
	}
}

void Game::updateInput()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		player->rotate(-1.f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		player->rotate(1.f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		player->move();

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && player->canAttack())
	{
		
		float posX = player->getPosition().x;
		float posY = player->getPosition().y;
		float deg = player->getRotation();
		float dirX = Helpers::getDirX(deg);
		float dirY = Helpers::getDirY(deg);

		bullets->push_back(std::make_shared<Bullet>(Bullet(posX, posY, dirX, dirY, deg)));
	}
}

void Game::updateAsteroids()
{
	for (int i = 0; i < (*asteroids).size(); i++)
	{
		(*asteroids)[i]->update();
		collisions.asteroidCollisions(i);
	}
}

void Game::updateBullets()
{
	for (int i = 0; i < (*bullets).size(); i++)
	{
		(*bullets)[i]->update();
		collisions.bulletCollisions(i);
	}
}

void Game::updatePlayer()
{
	
	player->update();
	collisions.playerCollisions();
	//    player->scan();
}

void Game::update()
{
	this->updateInput();
	this->updateAsteroids();
	this->updateBullets();
	this->updatePlayer();
}

void Game::render()
{
	this->window->clear();

	for (auto asteroid : *asteroids)
	{
		asteroid->render(this->window);
	}

	for (auto bullet : *bullets)
	{
		bullet->render(this->window);
	}
	player->render(this->window);
	window->display();
}
//show points
//void Game::render()
//{
//	this->window->clear();
//
//	for (auto& asteroid : this->asteroids)
//	{
//		asteroid->render(this->window);
//		sf::CircleShape center(3.f, 3.f);
//		center.setPosition(asteroid->shape.getPosition());
//		center.setFillColor(sf::Color::Yellow);
//		window->draw(center);
//	}
//
//	for (auto& bullet : bullets)
//	{
//		bullet->render(this->window);
//	}
//	this->player->render(this->window);
//
//	player->getBounds().left;
//	player->getBounds().top;
//	sf::CircleShape left(4.f, 4.f);
//	sf::CircleShape top(4.f, 4.f);
//	sf::CircleShape center(4.f, 4.f);
//	left.setPosition(player->getBounds().left, player->getBounds().top + ((player->getBounds().height) / 2));
//	top.setPosition(player->getBounds().left + (player->getBounds().width) / 2, player->getBounds().top);
//	center.setPosition(player->getPosition());
//	left.setFillColor(sf::Color::Blue);
//	top.setFillColor(sf::Color::Green);
//	center.setFillColor(sf::Color::Yellow);
//	window->draw(left);
//	window->draw(top);
//	window->draw(center);
//	this->window->display();
//}
