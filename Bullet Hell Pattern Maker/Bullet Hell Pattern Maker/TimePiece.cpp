#include "TimePiece.h"
#include "GeneralVariables.h"
#include <imgui.h>
#include <imgui-SFML.h>
#include <imgui_stdlib.h>
#include <imgui_internal.h>
#include <iomanip>
#include "Input.h"

TimePiece::TimePiece(float time, sf::Vector2f position)
{
	time_ = time;
	setFillColor(sf::Color::Red);
	setPosition(0.0f, 0.0f);
	setSize(GeneralVariables::play_area_size_);

	choose_time_piece_button_ = new Button("Choose", sf::Vector2f(0.0f, 0.0f),
		sf::Vector2f(100.0f, 25.0f), &GeneralVariables::font_, 15,
		sf::Vector2f(2.0f, 5.0f), sf::Color::Black, sf::Color::White);

	sf::Vector2f window_size = (sf::Vector2f)GeneralVariables::window_->getSize();

	SetViewPosition(position);
}

TimePiece::~TimePiece()
{
	for (int i = 0; i < Bullets_.size(); i++) {
		delete Bullets_.back();
		Bullets_.back() = nullptr;
		Bullets_.pop_back();
		i--;
	}
}

void TimePiece::MoveView(sf::Vector2f movement)
{
	view_position += movement;
	SetViewPort();
}

void TimePiece::SetViewPosition(sf::Vector2f position)
{
	view_position = position;
	SetViewPort();
}

void TimePiece::SetViewPositionY(float y_position)
{
	view_position.y = y_position;
	SetViewPortTop();
}

void TimePiece::MoveViewPositionY(float y_position)
{
	view_position.y += y_position;
	SetViewPortTop();
}

void TimePiece::MoveBullets()
{
	if (Input::GetMouseLeftDown()) {
		if (chosen_bullet_) {
			if (Input::GetKeyDown(sf::Keyboard::LShift)) {
				Input::SetKeyUp(sf::Keyboard::LShift);
				chosen_bullet_->SetVelocity(temp_velocity_);
				chosen_bullet_ = nullptr;
				return;
			}
			else if (Input::GetKeyDown(sf::Keyboard::R)) {
				Input::SetKeyUp(sf::Keyboard::R);
				chosen_bullet_->SetOriginalSize(temp_size_);
				chosen_bullet_ = nullptr;
				return;
			}
			else {
				Input::SetMouseLeftDown(false);
				chosen_bullet_->SetOriginalPosition(GeneralVariables::window_->mapPixelToCoords(Input::GetMouse()));
				chosen_bullet_ = nullptr;
				return;
			}
		}
		for (auto bullet : Bullets_) {
			if (bullet->GetHitbox().contains(
				GeneralVariables::window_->mapPixelToCoords(Input::GetMouse()))) {
				chosen_bullet_ = bullet;
				Input::SetMouseLeftDown(false);
				break;
			}
		}
	}

	if (chosen_bullet_) {
		chosen_bullet_->Reset();
		if (Input::GetMouseRightDown()) {
			chosen_bullet_ = nullptr;
			Input::SetKeyUp(sf::Keyboard::LShift);
			Input::SetKeyUp(sf::Keyboard::R);
		}
		else if (Input::GetKeyDown(sf::Keyboard::LShift)) {
			temp_velocity_ = GeneralVariables::window_->mapPixelToCoords(Input::GetMouse()) - chosen_bullet_->getPosition();
		}
		else if (Input::GetKeyDown(sf::Keyboard::R)) {
			temp_size_ = GeneralVariables::window_->mapPixelToCoords(Input::GetMouse()) - chosen_bullet_->getPosition();
			chosen_bullet_->setSize(sf::Vector2f(abs(temp_size_.x), abs(temp_size_.y)));
		}
		else {
			chosen_bullet_->setPosition(GeneralVariables::window_->mapPixelToCoords(Input::GetMouse()));
		}
	}
}

void TimePiece::Run(float dt)
{
	for (int i = 0; i < Bullets_.size(); i++) {
		Bullets_[i]->MoveBullet(dt);
	}
}

void TimePiece::Reset()
{
	for (int i = 0; i < Bullets_.size(); i++) {
		Bullets_[i]->Reset();
	}
}

void TimePiece::ShowBulletsWindow()
{
	ImGui::Begin("Chosen Time Window", 0, 
		ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse);
	ImGui::SetWindowSize(ImVec2(GeneralVariables::view_displacement_,
		GeneralVariables::window_->getSize().y - 400.0f));
	ImGui::SetWindowPos(ImVec2(0.0f, 400.0f));
	ImGui::Text(("Time: " + std::to_string(time_)).c_str());
	if (chosen_bullet_) {
		if (Input::GetKeyDown(sf::Keyboard::LShift)) {
			ImGui::Text(("New Velocity: ("
				+ std::to_string(temp_velocity_.x)
				+ ", "
				+ std::to_string(temp_velocity_.y)
				+ ")").c_str());
		}
		else if (Input::GetKeyDown(sf::Keyboard::R)) {
			ImGui::Text(("New Size: ("
				+ std::to_string(temp_size_.x)
				+ ", "
				+ std::to_string(temp_size_.y)
				+ ")").c_str());
		}
	}
	if (ImGui::Button("Create Bullet")) {
		Bullets_.push_back(new Bullet(
			standard_bullet_size,
			sf::Vector2f(50.0f, 50.0f),
			sf::Vector2f(0.0f, 100.0f)
		));
	}
	for (int i = 0; i < Bullets_.size(); i++) {
		ImGui::Text(("Bullet " + std::to_string(i) + ":").c_str());
		sf::Vector2f position = Bullets_[i]->getPosition();
		ImGui::Text(("	Position: ("
			+ std::to_string(position.x)
			+ ", "
			+ std::to_string(position.y)
			+ ")").c_str()
		);
		float velocity[2] = {Bullets_[i]->GetVelocity().x, Bullets_[i]->GetVelocity().y};
		ImGui::InputFloat2("Velocity: ", velocity);
		Bullets_[i]->SetVelocity(sf::Vector2f(velocity[0], velocity[1]));
	}
	ImGui::End();
}

void TimePiece::SetButtonPosition()
{
	choose_time_piece_button_->SetPosition(
		view_position - sf::Vector2f(0.0f, 30.0f)
	);
}

void TimePiece::RenderTimePiece()
{
	if (view_.getViewport().top - view_.getViewport().height > 1.0f
		|| view_.getViewport().top + view_.getViewport().height < 0.0f) {
		return;
	}
	sf::RenderWindow* window = GeneralVariables::window_;
	window->setView(view_);
	window->draw(*this);
	for (auto bullet : Bullets_) {
		bullet->RenderInOriginalConfiguration();
	}
	window->setView(GeneralVariables::view_);

	if (choose_time_piece_button_) {
		window->draw(*choose_time_piece_button_);
		choose_time_piece_button_->RenderButtonText();
	}
}

void TimePiece::RenderFullSize()
{
	for (auto bullet : Bullets_) {
		if (bullet) {
			GeneralVariables::window_->draw(*bullet);
		}
	}
}

float TimePiece::GetTime()
{
	return time_;
}

void TimePiece::SetTime(float new_time)
{
	time_ = new_time;
}

float TimePiece::GetViewPortTop()
{
	return view_.getViewport().top;
}

float TimePiece::GetViewPositionY()
{
	return view_position.y;
}

void TimePiece::SaveTimePiece(std::ofstream* pattern_file)
{
	*pattern_file << "Time" << "," <<  std::fixed<< std::setprecision(2) << time_ << "\n" ;
	for (int i = 0; i < Bullets_.size(); i++) {
		Bullets_[i]->SaveBullet(pattern_file);
	}
}

void TimePiece::LoadBullet(sf::Vector2f size, sf::Vector2f position, sf::Vector2f velocity)
{
	Bullets_.push_back(new Bullet(size, position, velocity));
}

void TimePiece::SetViewPort()
{
	sf::Vector2f window_size = (sf::Vector2f)GeneralVariables::window_->getSize();
	float left_side = (view_position.x  + GeneralVariables::view_displacement_) / window_size.x;
	float width = 0.25f;
	float top_side = view_position.y / window_size.y;
	view_.setViewport(sf::FloatRect(left_side, top_side, width, view_size_ / window_size.y));
	SetButtonPosition();
}

void TimePiece::SetViewPortTop()
{
	sf::Vector2f window_size = (sf::Vector2f)GeneralVariables::window_->getSize();
	sf::FloatRect view_port = view_.getViewport();
	view_port.top = view_position.y / window_size.y;
	view_.setViewport(view_port);
	SetButtonPosition();
}
