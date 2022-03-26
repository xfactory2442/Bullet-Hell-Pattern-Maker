#include "Enemy.h"

Enemy::Enemy(float health, sf::Vector2f size, sf::Vector2f initial_position, 
	sf::Texture* bar_outline,
	sf::Color colour, sf::Texture* texture) :
	Ship(health, size, initial_position, colour, texture)
{
	health_bar_ = new HealthBar(size, initial_position, sf::Color::Red, bar_outline);
}

void Enemy::Render()
{
	Ship::Render();
	health_bar_->RenderHealthBar();
}

void Enemy::ResetHealth()
{
	Ship::ResetHealth();
	health_bar_->SetHealthBar(max_health_, health_);
}

void Enemy::AddHealth(float change)
{
	Ship::AddHealth(change);
	health_bar_->SetHealthBar(max_health_, health_);
}

void Enemy::SetHealth(float health)
{
	Ship::SetHealth(health);
	health_bar_->SetHealthBar(max_health_, health_);
}
