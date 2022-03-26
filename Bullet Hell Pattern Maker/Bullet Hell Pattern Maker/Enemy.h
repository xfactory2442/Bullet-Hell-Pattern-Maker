#pragma once
#include "Ship.h"
#include "HealthBar.h"

class Enemy : public Ship
{
public:
	Enemy(float health, sf::Vector2f size, sf::Vector2f initial_position,
		sf::Texture* bar_outline,
		sf::Color colour = sf::Color::Red, sf::Texture* texture = nullptr);
	void Render();

	void ResetHealth();
	void AddHealth(float change);
	void SetHealth(float health);

protected:
	HealthBar* health_bar_;
};

