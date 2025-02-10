#pragma once

#include "Player.h"
#include "Enemy.h"

class PlayScene{
public:
	Player* player_;
	Enemy* enemy_;

	PlayScene();
	~PlayScene();

	void Update(char* keys);
	void Draw();

	int GetFadeTimer() const  { return fadeTimer_; }
	int GetScore() const  { return score_; }

	/// <summary>
	/// スコアとFadeTimerのリセット関数
	/// </summary>
	void ResetPlayScene();
private:
	int score_;
	int fadeTimer_; ///　ゲームオーバーシーンまでのタイマー
public:
	bool isGameLoad_;
};

