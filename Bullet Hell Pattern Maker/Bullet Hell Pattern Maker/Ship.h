#pragma once
#include "SFML/Graphics.hpp"
#include "Bullet.h"

class Ship : public sf::RectangleShape
{
public:
	Ship(float health,
		sf::Vector2f size, sf::Vector2f initial_position, 
		sf::Color colour = sf::Color::Red, sf::Texture* texture = nullptr);
	virtual void Update(float dt);
	virtual void Render();
	bool HitboxOnHitboxCollision(sf::FloatRect other_hitbox);
	bool PointOnHitboxCollision(sf::Vector2f point);
	int NumberOfHits(Ship* ship);


	void MoveShip(sf::Vector2f distance);
	virtual void ResetHealth();
	virtual void AddHealth(float change);
	virtual void SetHealth(float health);

	bool CheckHealth();

protected:
	struct Hitbox {
		sf::FloatRect hitbox_;
		sf::RectangleShape hitbox_indicator_;
	};

	Hitbox hitbox_;

	std::vector<Bullet*> Bullets_;

	bool alive_ = true;

	float speed_ = 100.0f;
	float health_ = 0.0f;
	float max_health_ = 10.0f;
};

