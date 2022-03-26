#include "Pattern.h"
#include <imgui.h>
#include <imgui-SFML.h>
#include <imgui_stdlib.h>
#include <imgui_internal.h>
#include "GeneralVariables.h"
#include "SaveAndLoadPatterns.h"

Pattern::Pattern(std::string pattern_name)
{
	name_ = pattern_name;
}

bool Pattern::CheckIfFocus()
{
	return ImGui::Button(name_.c_str());
}

void Pattern::Update()
{
	if (current_time_piece_) {
		current_time_piece_->MoveBullets();
	}
}

void Pattern::ShowPatternWindow()
{
	ImGui::Begin(name_.c_str(), 0,
		ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse);
	ImGui::SetWindowSize(ImVec2(GeneralVariables::view_displacement_, 
		200.0f));
	ImGui::SetWindowPos(ImVec2(0.0f, 200.0f));
	if (ImGui::Button("Save Pattern")) {
		SaveAndLoadPatterns::SavePattern(this);
	}
	ImGui::InputFloat("New Time", timeBuffer);
	if (ImGui::Button("Add New Time")) {
		AddTimePiece(*timeBuffer);
	}
	for (unsigned int i = 0; i < Time_Pieces_.size(); i++) {
		ImGui::Text(("Time: " + std::to_string(Time_Pieces_[i]->GetTime())).c_str());
		if (ImGui::Button(("Time Piece " + std::to_string(i)).c_str())) {
			current_time_piece_ = Time_Pieces_[i];
		}
	}
	ImGui::End();

	if (current_time_piece_) {
		current_time_piece_->ShowBulletsWindow();
	}
}

void Pattern::RenderPattern()
{
	for (auto time_piece : Time_Pieces_) {
		time_piece->RenderTimePiece();
	}
}

void Pattern::RenderCurrentTimePiece()
{
	if (current_time_piece_) {
		current_time_piece_->RenderFullSize();
	}
}

void Pattern::RenderAllActiveTimePieces()
{
	for (int i = 0; i < Time_Pieces_.size(); i++) {
		if (Time_Pieces_[i]->GetTime() <= time_) {
			Time_Pieces_[i]->RenderFullSize();
		}
	}
}

void Pattern::AddTimePiece(float time)
{
	float position = 0;
	for (int i = 0; i < Time_Pieces_.size(); i++) {
		if (Time_Pieces_[i]->GetTime() > time) {
			break;
		}
		position++;
	}
	Time_Pieces_.insert(Time_Pieces_.begin() + position, new TimePiece(time, sf::Vector2f(GeneralVariables::time_piece_position_x, 0.0f)));
	current_time_piece_ = Time_Pieces_[position];

	for (int i = position; i < Time_Pieces_.size(); i++) {
		Time_Pieces_[i]->SetViewPositionY(TimePiece::view_size_ * i);
	}
}

void Pattern::MoveTimePiecesDown(float amount)
{
	for (int i = 0; i < Time_Pieces_.size(); i++) {
		Time_Pieces_[i]->MoveViewPositionY(amount);
	}
}

void Pattern::Run(float dt)
{
	time_ += dt;
	for (int i = 0; i < Time_Pieces_.size(); i++) {
		if (Time_Pieces_[i]->GetTime() <= time_) {
			Time_Pieces_[i]->Run(dt);
		}
	}
}

void Pattern::Reset()
{
	for (int i = 0; i < Time_Pieces_.size(); i++) {
		Time_Pieces_[i]->Reset();
	}
	time_ = 0.0f;
}

std::string Pattern::GetName()
{
	return name_;
}

void Pattern::SetName(std::string name)
{
	name_ = name;
}
