#include "GameOver.h"
#include "Novice.h"

GameOver::GameOver() {
	scoreArray_[2] = {};
	numGraphs_[0] = Novice::LoadTexture("./Resources/0.png");
	numGraphs_[1] = Novice::LoadTexture("./Resources/1.png");
	numGraphs_[2] = Novice::LoadTexture("./Resources/2.png");
	numGraphs_[3] = Novice::LoadTexture("./Resources/3.png");
	numGraphs_[4] = Novice::LoadTexture("./Resources/4.png");
	numGraphs_[5] = Novice::LoadTexture("./Resources/5.png");
	numGraphs_[6] = Novice::LoadTexture("./Resources/6.png");
	numGraphs_[7] = Novice::LoadTexture("./Resources/7.png");
	numGraphs_[8] = Novice::LoadTexture("./Resources/8.png");
	numGraphs_[9] = Novice::LoadTexture("./Resources/9.png");

	background_ = Novice::LoadTexture("./Resources/gameover.png");
}

void GameOver::DrawScene(int score) {
	Novice::DrawSprite(0, 0, background_, 1.0f, 1.0f, 0.0f, WHITE);

	scoreArray_[0] = score / 10;
	score %= 10;
	scoreArray_[1] = score;
	for (int i = 0; i < 2; i++) {
		Novice::DrawSprite(660 + i * 18, 416, numGraphs_[scoreArray_[i]], 1.0f, 1.0f, 0.0f, WHITE);
	}
}
