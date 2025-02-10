#include "SceneManager.h"


SceneManager::SceneManager() {
	currentScene_ = TITLE;
	playScene_ = new PlayScene;
	gameOverScene_ = new GameOver;

	titleImage_ = Novice::LoadTexture("./Resources/title.png");
	
}


SceneManager::~SceneManager() {
	delete playScene_;
}


void SceneManager::Update(char* keys, char* preKeys) {
	switch (currentScene_) {
	case TITLE:
		if (keys[DIK_SPACE] && !preKeys[DIK_SPACE]) {
			currentScene_ = GAME;
		}
		playScene_->ResetPlayScene();
		break;
	case GAME:
		
		playScene_->Update(keys);

		if (playScene_->GetFadeTimer() >= 120) {
			currentScene_ = RESULT;
		}
		break;
	case RESULT:
		if (keys[DIK_SPACE] && !preKeys[DIK_SPACE]) {
			currentScene_ = TITLE;
		}
		
		break;
	}
}

void SceneManager::Draw() {
	switch (currentScene_) {
	case TITLE:
		Novice::DrawSprite(0, 0, titleImage_, 1.0f, 1.0f, 0.0f, WHITE);
		break;
	case GAME:
		playScene_->Draw();
		
		break;
	case RESULT:
		
		gameOverScene_->DrawScene(playScene_->GetScore());
		
		break;
	}
}
