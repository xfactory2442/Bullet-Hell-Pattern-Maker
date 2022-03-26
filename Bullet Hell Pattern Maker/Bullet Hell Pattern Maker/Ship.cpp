#include "Ship.h"
#include "GeneralVariables.h"

Ship::Ship(float health, 
	sf::Vector2f size, sf::Vector2f initial_position,
	sf::Color colour, sf::Texture* texture)
{
	setSize(size);
	setOrigin(size / 2.0f);
	setPosition(initial_position);
	if (texture) {
		setTexture(texture);
	}
	setFillColor(colour);

	max_health_ = health;
	ResetHealth();

	sf::Vector2f hitbox_size = size - sf::Vector2f(50.0f, 50.0f);
	hitbox_.hitbox_.left = initial_position.x - hitbox_size.x / 2.0f;
	hitbox_.hitbox_.top = initial_position.y - hitbox_size.y / 2.0f;
	hitbox_.hitbox_.width = hitbox_size.x;
	hitbox_.hitbox_.height = hitbox_size.y;

	hitbox_.hitbox_indicator_.setSize(hitbox_size);
	hitbox_.hitbox_indicator_.setOrigin(hitbox_size / 2.0f);
	hitbox_.hitbox_indicator_.setPosition(initial_position);
	hitbox_.hitbox_indicator_.setFillColor(sf::Color::Green);
}

void Ship::Update(float dt)
{
	for (int i = 0; i < Bullets_.size(); i++) {
		if (Bullets_[i]->MoveBullet(dt)) {
			delete Bullets_[i];
			Bullets_.erase(Bullets_.begin() + i);
		}
	}
}

void Ship::Render()
{
	GeneralVariables::window_->draw(*this);
	GeneralVariables::window_->draw(hitbox_.hitbox_indicator_);
	for (int i = 0; i < Bullets_.size(); i++) {
		GeneralVariables::window_->draw(*Bullets_[i]);
	}
}

bool Ship::HitboxOnHitboxCollision(sf::FloatRect other_hitbox)
{
	float left = other_hitbox.left;
	float top = other_hitbox.top;
	float right = other_hitbox.left + other_hitbox.width;
	float bottom = other_hitbox.top + other_hitbox.height;

	if (PointOnHitboxCollision(sf::Vector2f(left, top))
		|| PointOnHitboxCollision(sf::Vector2f(right, top))
		|| PointOnHitboxCollision(sf::Vector2f(left, bottom))
		|| PointOnHitboxCollision(sf::Vector2f(right, bottom))) {
		return true;
	}

	return false;
}

bool Ship::PointOnHitboxCollision(sf::Vector2f point)
{
	if (hitbox_.hitbox_.contains(point)) {
		return true;
	}
	return false;
}

int Ship::NumberOfHits(Ship* ship)
{
	int num_hits = 0;
	for (int i = 0; i < Bullets_.size(); i++) {
		if (ship->HitboxOnHitboxCollision(Bullets_[i]->GetHitbox())) {
			num_hits++;
			delete Bullets_[i];
			Bullets_.erase(Bullets_.begin() + i);
			i--;
		}
	}
	return num_hits;
}

void Ship::MoveShip(sf::Vector2f distance)
{
	setPosition(getPosition() + distance);
	hitbox_.hitbox_indicator_.setPosition(getPosition());
	hitbox_.hitbox_.left = getPosition().x - hitbox_.hitbox_.width / 2.0f;
	hitbox_.hitbox_.top = getPosition().y - hitbox_.hitbox_.height / 2.0f;
}

void Ship::ResetHealth()
{
	health_ = max_health_;
}

void Ship::AddHealth(float change)
{
	health_ += change;
	CheckHealth();
}

void Ship::SetHealth(float health)
{
	health_ = health;
	CheckHealth();
}

bool Ship::CheckHealth()
{
	if (health_ <= 0.0f) {
		alive_ = false;
	}
	health_ = health_ >= max_health_ ? max_health_ : health_;

	return alive_;
}
