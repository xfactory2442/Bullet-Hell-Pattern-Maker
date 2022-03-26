#include <SFML/Graphics.hpp>
#include <ctime>
#include <time.h>       /* time */
#include <stdio.h>      /* printf, scanf, puts, NULL */
#include "Input.h"
#include "SceneManager.h"
#include "GeneralVariables.h"
#include "TimePiece.h"

#include "MainScene.h"

//
//Declaring Static Members
//

//Input static members.
bool Input::keys[256];
Input::Mouse Input::mouse;

//SceneManager static members.
SceneManager::Scene SceneManager::scene;

//TimePiece static members.
float TimePiece::view_size_ = 0.0f;

//GeneralVariables static members.
sf::RenderWindow* GeneralVariables::window_;
sf::View GeneralVariables::view_;
sf::Vector2f GeneralVariables::play_area_size_ = sf::Vector2f(800.0f, 800.0f);
sf::IntRect GeneralVariables::bullet_view_port_;
sf::Font GeneralVariables::font_;
float GeneralVariables::time_piece_position_x;
const float GeneralVariables::view_displacement_ = 400.0f;

int main() {
	//Create the window.
	sf::RenderWindow window(sf::VideoMode(GeneralVariables::play_area_size_.x + 400.0f + GeneralVariables::view_displacement_, 800), "Pathfinding");
	GeneralVariables::view_.reset(
		sf::FloatRect(-GeneralVariables::view_displacement_, 0.0f,
			GeneralVariables::play_area_size_.x + 400.0f + GeneralVariables::view_displacement_, 800.0f)
		);
	window.setView(GeneralVariables::view_);
	GeneralVariables::window_ = &window;

	TimePiece::view_size_ = (window.getSize().y / 2.0f - 5.0f);

	srand((int)time(NULL));

	//Initialise Clock Object.
	sf::Clock clock;

	//Initialse SceneManager Object.
	SceneManager::ChangeScene(SceneManager::Scene::Main);

	//Initialise Input.
	Input::Init();

	//Initialise Font Object.
	GeneralVariables::font_.loadFromFile("fonts/consola.ttf");

	//Initialise Scene Objects.
	MainScene main_scene_;

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			main_scene_.ProcessEvent(event);
			switch (event.type)
			{
			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::Resized:
				window.setSize(sf::Vector2u(unsigned int(GeneralVariables::play_area_size_.x + 800.0f), unsigned int(800)));
				break;
			case sf::Event::KeyPressed:
				// update input class
				Input::SetKeyDown(event.key.code);
				break;
			case sf::Event::KeyReleased:
				//update input class
				Input::SetKeyUp(event.key.code);
				break;
			case sf::Event::MouseMoved:
				//update input class
				Input::SetMouseXPosition(event.mouseMove.x);
				Input::SetMouseYPosition(event.mouseMove.y);
				break;
			case sf::Event::MouseButtonPressed:
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					//update input class
					Input::SetMouseLeftDown(true);
				}
				if (event.mouseButton.button == sf::Mouse::Right)
				{
					//update input class
					Input::SetMouseRightDown(true);
				}
				break;
			case sf::Event::MouseButtonReleased:
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					//update input class
					Input::SetMouseLeftDown(false);
				}
				if (event.mouseButton.button == sf::Mouse::Right)
				{
					//update input class
					Input::SetMouseRightDown(false);
				}
				break;
			default:
				// don't handle other events
				break;
			}
		}
		float dt = clock.restart().asSeconds();

		switch (SceneManager::GetScene()) {
		case SceneManager::Scene::Main:
			main_scene_.Update(dt);
			main_scene_.Render();
			break;
		}
	}
}