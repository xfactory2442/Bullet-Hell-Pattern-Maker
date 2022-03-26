#pragma once
#include <SFML/Graphics.hpp>
#include "Pattern.h"
#include "Button.h"
class TimeChooser : public sf::RectangleShape
{
public:
	TimeChooser();
	~TimeChooser();
	void Update();
	void SetPattern(Pattern* pattern);
	void ResetPattern();
	void RunPattern(float dt);
	void RenderPattern();
	void RenderRun();

private:
	void UpdateButtons();

	Pattern* current_pattern_ = nullptr;
	Button* down_button_ = nullptr;
	Button* up_button_ = nullptr;
};
