#pragma once

class GameOver{
public: 
	GameOver();
	~GameOver() = default;
	void DrawScene(int score);
private:
	int scoreArray_[3];
	int numGraphs_[11];
	int background_;
};

