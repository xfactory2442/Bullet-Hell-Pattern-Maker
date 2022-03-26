#pragma once
#include "Scene.h"
#include <imgui.h>
#include <imgui-SFML.h>
#include <imgui_stdlib.h>
#include <imgui_internal.h>
#include "Pattern.h"
#include "TimeChooser.h"

class MainScene : public Scene
{
public:
	MainScene();
	~MainScene();
	void ProcessEvent(sf::Event& event);
	void Update(float dt);
	void Render();
private:
	std::vector<Pattern*> Pattern_;
	bool run_ = false;

	TimeChooser time_chooser_;
	char* pattern_name_buffer_ = new char();
};

