#pragma once
#include <SFML/Graphics.hpp>

class GeneralVariables
{
public:
	static sf::RenderWindow* window_;
	static sf::View view_;
	static sf::Vector2f play_area_size_;
	static sf::IntRect bullet_view_port_;
	static sf::Font font_;
	static float time_piece_position_x;
	static const float view_displacement_;
};

