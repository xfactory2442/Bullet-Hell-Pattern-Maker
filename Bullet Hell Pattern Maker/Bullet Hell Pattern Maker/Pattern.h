#pragma once
#include <SFML/Graphics.hpp>
#include "TimePiece.h"

class Pattern
{
public:
	Pattern(std::string pattern_name);
	bool CheckIfFocus();
	void Update();
	void ShowPatternWindow();
	void RenderPattern();
	void RenderCurrentTimePiece();
	void RenderAllActiveTimePieces();

	void AddTimePiece(float time);
	void MoveTimePiecesDown(float amount);
	void Run(float dt);
	void Reset();

	std::string GetName();
	void SetName(std::string name);

	std::vector<TimePiece*> Time_Pieces_;
private:
	float time_ = 0.0f;
	std::string name_;
	TimePiece* current_time_piece_ = nullptr;
	float* timeBuffer = new float(0.0f);
	float time_piece_view_port_size = 0.0f;
};

