#include "TimeChooser.h"
#include "GeneralVariables.h"
#include "Input.h"

TimeChooser::TimeChooser()
{
	setSize(sf::Vector2f(
		400.0f,
		GeneralVariables::window_->getSize().y
	));
	setPosition(
		GeneralVariables::play_area_size_.x,
		0.0f
	);
	setFillColor(sf::Color::White);
	GeneralVariables::time_piece_position_x = getPosition().x + 5.0f;

	sf::Vector2f window_size = (sf::Vector2f)GeneralVariables::window_->getSize();
	down_button_ = new Button("Down", 
		sf::Vector2f(window_size.x - 60.0f - GeneralVariables::view_displacement_, 
			window_size.y - 60.0f),
		sf::Vector2f(50.0f, 50.0f), &GeneralVariables::font_,
		15.0f, sf::Vector2f(2.0f, 5.0f), sf::Color::Black, sf::Color::White
	);
	up_button_ = new Button("Up",
		sf::Vector2f(window_size.x - 60.0f - GeneralVariables::view_displacement_, 
			10.0f),
		sf::Vector2f(50.0f, 50.0f), &GeneralVariables::font_,
		15.0f, sf::Vector2f(2.0f, 5.0f), sf::Color::Black, sf::Color::White
	);
}

TimeChooser::~TimeChooser()
{
	current_pattern_ = nullptr;
	delete down_button_;
	down_button_ = nullptr;
	delete up_button_;
	up_button_ = nullptr;
}

void TimeChooser::Update()
{
	UpdateButtons();
	if (current_pattern_) {
		current_pattern_->Update();
	}
}

void TimeChooser::UpdateButtons()
{
	sf::Vector2f mouse_position = GeneralVariables::window_->mapPixelToCoords(Input::GetMouse());
	if (Input::GetMouseLeftDown()) {
		if (down_button_->Collision(mouse_position)) {
			current_pattern_->MoveTimePiecesDown(-100.0f);
			Input::SetMouseLeftDown(false);
		}
		else if (up_button_->Collision(mouse_position)) {
			current_pattern_->MoveTimePiecesDown(100.0f);
			Input::SetMouseLeftDown(false);
		}
	}
}

void TimeChooser::SetPattern(Pattern* pattern)
{
	current_pattern_ = pattern;
	float y = 5.0f;
}

void TimeChooser::ResetPattern()
{
	if (current_pattern_) {
		current_pattern_->Reset();
	}
}

void TimeChooser::RunPattern(float dt)
{
	if (current_pattern_) {
		current_pattern_->Run(dt);
	}
}

void TimeChooser::RenderPattern()
{
	GeneralVariables::window_->draw(*this);
	if (current_pattern_) {
		current_pattern_->ShowPatternWindow();
		current_pattern_->RenderCurrentTimePiece();
		current_pattern_->RenderPattern();
		if (up_button_) {
			GeneralVariables::window_->draw(*up_button_);
			up_button_->RenderButtonText();
		}
		if (down_button_) {
			GeneralVariables::window_->draw(*down_button_);
			down_button_->RenderButtonText();
		}
	}
}

void TimeChooser::RenderRun()
{
	if (current_pattern_) {
		current_pattern_->RenderAllActiveTimePieces();
	}
}
