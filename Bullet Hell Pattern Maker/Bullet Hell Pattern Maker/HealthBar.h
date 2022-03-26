#pragma once
#include <SFML/Graphics.hpp>

class HealthBar : public sf::RectangleShape
{
public:
	HealthBar(sf::Vector2f enemy_size, sf::Vector2f enemy_middle_position,
		sf::Color bar_colour, sf::Texture* outline_texture);
	void MoveHealthBar(sf::Vector2f movement);
	void RenderHealthBar();

	void SetHealthBar(float max, float amount);
private:
	sf::RectangleShape outline_;
};

