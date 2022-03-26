#include "Scene.h"

void Scene::StartDraw()
{
	GeneralVariables::window_->clear(sf::Color::Black);
}

void Scene::EndDraw()
{
	GeneralVariables::window_->display();
}
