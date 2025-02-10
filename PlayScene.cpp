#include "PlayScene.h"
#include "Novice.h"

PlayScene::PlayScene() {
	player_ = new Player();
	enemy_ = new Enemy();
	score_ = 0;
	fadeTimer_ = 0;
	isGameLoad_ = false;
}

PlayScene::~PlayScene() {
	delete player_;
	delete enemy_;
}

void PlayScene::Update(char* keys) {
	if (isGameLoad_ == false) {
		player_->SpawnPlayer();
		isGameLoad_ = true;
	}

	player_->Update(keys);
	enemy_->SpawnEnemy({ 200.0f, 100.0f });
	enemy_->Move();

	for (int i = 0; i < 12; i++) {
		if (enemy_->isSpawn_ == true) {
			if (player_->bullet_[i]->isShot_ == true) {
				if (enemy_->CollisionCheck(player_->bullet_[i]->GetPos(),
					player_->bullet_[i]->GetRadius())) {
					score_++;
				}
			}
		}
	}	

	if (enemy_->isSpawn_ == true) {
		if (player_->CollisionCheck(enemy_->GetPos(), enemy_->GetRadius())) {

		}
	}

	if (player_->GetState() == DEAD) {
		fadeTimer_++;
		player_->isSpawn_ = false;
	}
}

void PlayScene::ResetPlayScene() {
	fadeTimer_ = 0;
	score_ = 0;
	isGameLoad_ = false;
	enemy_->isSpawn_ = false;
}


void PlayScene::Draw() {
	Novice::DrawBox(0, 0, 1280, 720, 0.0f, BLACK, kFillModeSolid);

	enemy_->Draw();
	player_->Draw();
}