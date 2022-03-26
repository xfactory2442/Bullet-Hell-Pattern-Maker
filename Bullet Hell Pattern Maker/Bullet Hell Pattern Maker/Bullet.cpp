#include "Bullet.h"
#include "GeneralVariables.h"
#include <iomanip >

Bullet::Bullet(sf::Vector2f size, sf::Vector2f position, sf::Vector2f velocity)
{
	velocity_ = velocity;
	setSize(size);
	setOrigin(size / 2.0f);
	setPosition(position);
	setFillColor(sf::Color::White);
	original_position_ = position;
	original_size_ = size;

	hitbox_.left = position.x - size.x / 2.0f;
	hitbox_.top = position.y - size.y / 2.0f;
	hitbox_.width = size.x;
	hitbox_.height = size.y;
}

bool Bullet::MoveBullet(float dt)
{
	setPosition(getPosition() + velocity_ * dt);

	hitbox_.left = getPosition().x - getSize().x / 2.0f;
	hitbox_.top = getPosition().y - getSize().y / 2.0f;

	if (!GeneralVariables::bullet_view_port_.contains((sf::Vector2i)getPosition())) {
		alive_ = false;
		return true;
	}

	return false;
}

void Bullet::RenderInOriginalConfiguration()
{
	sf::Vector2f current_position = getPosition();
	sf::Vector2f current_size = getSize();
	setPosition(original_position_);
	setSize(original_size_);
	GeneralVariables::window_->draw(*this);
	setPosition(current_position);
	setSize(current_size);
}

void Bullet::Reset()
{
	setPosition(original_position_);
	setSize(original_size_);
}

void Bullet::SaveBullet(std::ofstream* pattern_file)
{
	*pattern_file << std::fixed << std::setprecision(2) << 
		original_size_.x << "," << original_size_.y << "," <<
		original_position_.x << "," << original_position_.y << "," <<
		velocity_.x << "," << velocity_.y << "\n";
}

void Bullet::setPosition(sf::Vector2f position)
{
	sf::RectangleShape::setPosition(position);
	hitbox_.left = position.x - getSize().x / 2.0f;
	hitbox_.top = position.y - getSize().y / 2.0f;
}

void Bullet::SetOriginalPosition(sf::Vector2f position)
{
	original_position_ = position;
	setPosition(position);
}

void Bullet::setSize(sf::Vector2f size)
{
	sf::RectangleShape::setSize(size);
	hitbox_.left = getPosition().x - getSize().x / 2.0f;
	hitbox_.top = getPosition().y - getSize().y / 2.0f;
	hitbox_.height = size.y;
	hitbox_.width = size.x;
	setOrigin(size / 2.0f);
}

void Bullet::SetOriginalSize(sf::Vector2f size)
{
	original_size_ = size;
	setSize(size);
}

sf::FloatRect Bullet::GetHitbox()
{
	return hitbox_;
}

void Bullet::SetVelocity(sf::Vector2f velocity)
{
	velocity_ = velocity;
}

sf::Vector2f Bullet::GetVelocity()
{
	return velocity_;
}
