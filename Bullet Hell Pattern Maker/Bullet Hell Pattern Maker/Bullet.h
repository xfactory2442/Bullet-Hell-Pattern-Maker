#pragma once
#include "SFML/Graphics.hpp"
#include <fstream>
#include <iostream>
class Bullet : public sf::RectangleShape
{
public:
	Bullet(sf::Vector2f size, sf::Vector2f position, sf::Vector2f velocity);
	virtual bool MoveBullet(float dt);
	void RenderInOriginalConfiguration();
	void Reset();
	void SaveBullet(std::ofstream* pattern_file);


	void setPosition(sf::Vector2f position);
	void SetOriginalPosition(sf::Vector2f positon);
	void setSize(sf::Vector2f size);
	void SetOriginalSize(sf::Vector2f size);
	sf::FloatRect GetHitbox();
	void SetVelocity(sf::Vector2f velocity);
	sf::Vector2f GetVelocity();

private:
	bool alive_ = true;
	sf::Vector2f velocity_;
	sf::FloatRect hitbox_;

	sf::Vector2f original_position_;
	sf::Vector2f original_size_;
};

