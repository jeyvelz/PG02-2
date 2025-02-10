#include "Novice.h"
#include "Player.h"
#include <iostream>
#include <time.h>

const float windowRight = 1280.0f;
const float windowLeft = 0.0f;
const float windowTop = 0.0f;
const float windowBottom = 720.0f;

const int kMaxBullet = 12;
const int kMaxParticles = 20;

Player::Player() {
	pos_ = { 640.f, 520.f };
	speed_ = 6.f;
	radius_ = 20.f;
	shootCD_ = 0;
	isSpawn_ = true;
	state_ = ALIVE;

	for (int i = 0; i < kMaxBullet; i++) {
		bullet_[i] = new Bullet;
	}

	for (int i = 0; i < kMaxParticles; i++) {
		particle[i].pos = { 0, 0 };
		particle[i].speed = { 0, 0 };
		particle[i].color.red = 0;
		particle[i].color.green = 0;
		particle[i].color.blue = 255;
		particle[i].color.alpha = 255;
		particle[i].color.rgba = (particle[i].color.red << 24) | (particle[i].color.green < 16) |
			(particle[i].color.blue << 8) | particle[i].color.alpha;

		particle[i].isVisible = false;
	}
	particleTimer_ = 0;

	deadSFX_ = Novice::LoadAudio("./Resources/audio/dead.mp3");
	shootSFX_ = Novice::LoadAudio("./Resources/audio/shoot.mp3");
}

Player::~Player() {
	for (int i = 0; i < kMaxBullet; i++) {
		delete bullet_[i];
	}
}

void Player::SpawnPlayer() {
	if (isSpawn_ == false) {
		isSpawn_ = true;
		state_ = ALIVE;
		pos_ = { 640.f, 520.f };
		particleTimer_ = 0;
		shootCD_ = 0;
		for (int i = 0; i < kMaxParticles; i++) {
			particle[i].pos = { 0, 0 };
			particle[i].speed = { 0, 0 };
			particle[i].color.red = 0;
			particle[i].color.green = 0;
			particle[i].color.blue = 255;
			particle[i].color.alpha = 255;
			particle[i].color.rgba = (particle[i].color.red << 24) | (particle[i].color.green < 16) |
				(particle[i].color.blue << 8) | particle[i].color.alpha;

			particle[i].isVisible = false;
		}
	}
}

void Player::Shot(char* keys) {
	if (shootCD_ == 0) {
		if (keys[DIK_Z]) {
			for (int i = 0; i < kMaxBullet; i++) {
				if (bullet_[i]->isShot_ == false) {
					Novice::PlayAudio(shootSFX_, 0, 1.0f);
					bullet_[i]->SetPosX(pos_.x);
					bullet_[i]->SetPosY(pos_.y);
					bullet_[i]->isShot_ = true;
					shootCD_ = 8;
					break;
				}
			}
		}
	}

	if (shootCD_ > 0) {
		shootCD_--;
	}

}

bool Player::CollisionCheck(Vector2 const& enemyPos, float const& enemyRadius) {
	float x = pos_.x - enemyPos.x;
	float y = pos_.y - enemyPos.y;

	float distance = sqrtf(x * x + y * y);
	float minDistance = radius_ + enemyRadius;

	if (minDistance >= distance) {
		Novice::PlayAudio(deadSFX_, 0, 1.0f);
		state_ = DEAD;
		return true;
	}
	return false;
}

void Player::DeadParticles() {
	
	if (state_ == DEAD) {
		particleTimer_++;
		if (particleTimer_ % 3 == 0) {
			for (int i = 0; i < kMaxParticles; i++) {
				if (particleTimer_ <= 60) {
					if (particle[i].isVisible == false) {
						particle[i].isVisible = true;
						particle[i].pos = { pos_.x, pos_.y };
						particle[i].speed.x = static_cast<float>(rand() % 5 - 2);
						particle[i].speed.y = static_cast<float>(rand() % 5 - 2);
						particle[i].color.alpha = 255;

						break;
					}
				}
			}
		}

		for (int i = 0; i < kMaxParticles; i++) {
			
			if (particle[i].isVisible == true) {
				particle[i].pos.x += particle[i].speed.x;
				particle[i].pos.y += particle[i].speed.y;
				particle[i].color.alpha -= 5;
			}

			/// パーティクルをリセット
			if (particle[i].color.alpha <= 0) {
				particle[i].isVisible = false;
			}

			particle[i].color.rgba = (particle[i].color.red << 24) | (particle[i].color.green << 16) |
				(particle[i].color.blue << 8) | particle[i].color.alpha;

		}

	}
	

}

void Player::Update(char* keys) {
	if (state_ == ALIVE) {
		/// プレイヤーの移動処理
		if (keys[DIK_UP]) {
			pos_.y -= speed_;
		}
		if (keys[DIK_DOWN]) {
			pos_.y += speed_;
		}
		if (keys[DIK_LEFT]) {
			pos_.x -= speed_;
		}
		if (keys[DIK_RIGHT]) {
			pos_.x += speed_;
		}


		/// プレイヤーは画面内に移動させる
		if (pos_.x - radius_ <= windowLeft) {
			pos_.x = windowLeft + radius_;
		}
		if (pos_.x + radius_ >= windowRight) {
			pos_.x = windowRight - radius_;
		}
		if (pos_.y - radius_ <= windowTop) {
			pos_.y = windowTop + radius_;
		}
		if (pos_.y + radius_ >= windowBottom) {
			pos_.y = windowBottom - radius_;
		}

		Shot(keys);
	} 
	/// 弾の更新処理
	for (int i = 0; i < kMaxBullet; i++) {
		bullet_[i]->Update();
	}

	DeadParticles();
	
}

void Player::Draw() {
	// 弾の描画
	for (int i = 0; i < kMaxBullet; i++) {
		bullet_[i]->Draw();
	}

	if (state_ == ALIVE) {
		// プレイヤーの描画
		Novice::DrawEllipse(static_cast<int>(pos_.x), static_cast<int>(pos_.y),
			static_cast<int>(radius_), static_cast<int>(radius_), 0.0f, BLUE, kFillModeSolid);
	} else {
		for (int i = 0; i < kMaxParticles; i++) {
			if (particle[i].isVisible == true) {
				Novice::DrawEllipse(static_cast<int>(particle[i].pos.x), static_cast<int>(particle[i].pos.y),
					8, 8, 0.0f, particle[i].color.rgba, kFillModeSolid);
			}
		}
	}
	
}