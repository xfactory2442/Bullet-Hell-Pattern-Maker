#include "HealthBar.h"
#include "GeneralVariables.h"

HealthBar::HealthBar(sf::Vector2f enemy_size, sf::Vector2f enemy_middle_position,
	sf::Color bar_color, sf::Texture* outline_texture)
{
	setSize(sf::Vector2f(enemy_size.x / 5.0f * 4.0f, enemy_size.y / 5.0f));
	setOrigin(getSize() / 2.0f);
	setPosition(enemy_middle_position - sf::Vector2f(0.0f, enemy_size.y / 2.0f + getSize().y / 4.0f));
	setFillColor(bar_color);

	outline_.setSize(sf::Vector2f(enemy_size.x / 5.0f * 4.0f, enemy_size.y / 5.0f));
	outline_.setOrigin(getSize() / 2.0f);
	outline_.setPosition(getPosition());
	outline_.setTexture(outline_texture);
}

void HealthBar::MoveHealthBar(sf::Vector2f movement)
{
	setPosition(getPosition() + movement);
	outline_.setPosition(getPosition());
}

void HealthBar::RenderHealthBar()
{
	GeneralVariables::window_->draw(*this);
	GeneralVariables::window_->draw(outline_);
}

void HealthBar::SetHealthBar(float max, float amount)
{
	setSize(sf::Vector2f(amount / max * outline_.getSize().x, getSize().y));
}
