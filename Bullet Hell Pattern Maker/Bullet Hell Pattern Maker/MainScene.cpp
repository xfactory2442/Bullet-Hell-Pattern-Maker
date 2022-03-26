#include "MainScene.h"
#include <filesystem>
#include <iostream>
#include "SaveAndLoadPatterns.h"
#include "GeneralVariables.h"
namespace fs = std::filesystem;

MainScene::MainScene()
{
	/*Set up view port so that parts that aren't used in the pattern maker
	but were copied from the main game don't crash this program*/
	float bullet_delete_space_ = 800.0f;
	auto view = GeneralVariables::window_->getView();
	auto view_port_ = GeneralVariables::window_->getViewport(view);
	GeneralVariables::bullet_view_port_ = view_port_;

	//Initialise imgui
	ImGui::SFML::Init(*GeneralVariables::window_, false);

	ImGuiIO& imgui_io = ImGui::GetIO();

	imgui_io.Fonts->AddFontFromFileTTF("fonts/consola.ttf", 16.f);
	ImGui::SFML::UpdateFontTexture();

	std::string path = "patterns/";
	for (const auto& entry : fs::directory_iterator(path)) {
		std::string filename = entry.path().string();
		std::cout << "Loading pattern " << filename << std::endl;
		Pattern_.push_back(SaveAndLoadPatterns::LoadPattern(filename));
	}
}

MainScene::~MainScene()
{
	ImGui::SFML::Shutdown();
}

void MainScene::ProcessEvent(sf::Event& event)
{
	ImGui::SFML::ProcessEvent(event);
}

void MainScene::Update(float dt)
{
	time_chooser_.Update();

	ImGui::SFML::Update(*GeneralVariables::window_, sf::seconds(dt));
	ImGui::Begin("Pattern Menu", 0,
		ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse);
	ImGui::SetWindowSize(ImVec2(GeneralVariables::view_displacement_, 200.0f));
	ImGui::SetWindowPos(ImVec2(0.0f, 0.0f));
	ImGui::InputText("New Pattern Name", pattern_name_buffer_, 20);
	std::string name(pattern_name_buffer_);
	if (ImGui::Button("Create New Pattern") && name != "") {
		bool create = true;
		for (int i = 0; i < Pattern_.size(); i++) {
			if (Pattern_[i]->GetName() == name) {
				create = false;
				pattern_name_buffer_ = new char();
				break;
			}
		}
		if (create) {
			Pattern_.push_back(new Pattern(name));
			time_chooser_.SetPattern(Pattern_.back());
		}
	}
	for (int i = 0; i < Pattern_.size(); i++) {
		if (Pattern_[i]->CheckIfFocus()) {
			time_chooser_.SetPattern(Pattern_[i]);
		}
	}
	ImGui::End();

	ImGui::Begin("Controls", 0,
		ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse);
	sf::Vector2f window_size = sf::Vector2f(100.0f, 60.0f);
	ImGui::SetWindowSize(ImVec2(window_size.x, window_size.y));
	ImGui::SetWindowPos(ImVec2(
		GeneralVariables::window_->getSize().x / 2.0f - window_size.x / 2.0f,
		GeneralVariables::window_->getSize().y - window_size.y));
	if (ImGui::Button(run_ ? "Stop" : "Run")) {
		run_ = !run_;
		time_chooser_.ResetPattern();
	}
	ImGui::End();

	if (run_) {
		time_chooser_.RunPattern(dt);
	}
}

void MainScene::Render()
{
	StartDraw();
	if (!run_) {
		time_chooser_.RenderPattern();
	}
	else {
		time_chooser_.RenderRun();
	}
	ImGui::SFML::Render(*GeneralVariables::window_);
	EndDraw();
}
