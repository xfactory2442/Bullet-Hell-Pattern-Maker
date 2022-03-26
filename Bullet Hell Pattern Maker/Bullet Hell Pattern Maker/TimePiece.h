#pragma once
#include <SFML/Graphics.hpp>
#include "Bullet.h"
#include "Button.h"
#include <iostream>
#include <fstream>

class TimePiece : public sf::RectangleShape
{
public:
	TimePiece(float time, sf::Vector2f position);
	~TimePiece();
	void MoveView(sf::Vector2f movement);
	void SetViewPosition(sf::Vector2f position);
	void SetViewPositionY(float y_position);
	void MoveViewPositionY(float y_position);

	void MoveBullets();
	void Run(float dt);
	void Reset();

	void ShowBulletsWindow();
	void RenderTimePiece();
	void RenderFullSize();

	float GetTime();
	void SetTime(float new_time);
	float GetViewPortTop();
	float GetViewPositionY();

	void SaveTimePiece(std::ofstream* pattern_file);
	void LoadBullet(sf::Vector2f size, sf::Vector2f position, sf::Vector2f velocity);

	static float view_size_;

private:
	void SetViewPort();
	void SetViewPortTop();
	void SetButtonPosition();
	Button* choose_time_piece_button_ = nullptr;
	std::vector<Bullet*> Bullets_;
	Bullet* chosen_bullet_ = nullptr;
	const sf::Vector2f standard_bullet_size = sf::Vector2f(30.0f, 30.0f);

	float time_ = 0.0f;
	sf::View view_;
	sf::Vector2f view_position = sf::Vector2f(0.0f, 0.0f);

	sf::Vector2f temp_velocity_ = sf::Vector2f(0.0f, 0.0f);
	sf::Vector2f temp_size_ = sf::Vector2f(0.0f, 0.0f);
};

