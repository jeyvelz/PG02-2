#include "Enemy.h"
#include "Novice.h"
#define _USE_MATH_DEFINES
#include <math.h>

const int maxSpawnCooldown_ = 120;

Enemy::Enemy() {
	spawnPos_ = { 200.0f, 200.0f };
	pos_ = spawnPos_;
	speed_ = { 10.0f, 10.0f };
	radius_ = 20.0f;
	isSpawn_ = false;
	spawnCooldown_ = 0;

	deadSFX_ = Novice::LoadAudio("./Resources/audio/enemyDead.mp3");
}

void Enemy::SpawnEnemy(Vector2 pos) {
	if (isSpawn_ == false) {
		if (spawnCooldown_ <= 0) {
			isSpawn_ = true;
			spawnPos_ = pos;
			pos_ = spawnPos_;
		} else {
			spawnCooldown_--;
		}
	}
}

bool Enemy::CollisionCheck(Vector2 const pos, float const radius) {
	float x = pos_.x - pos.x;
	float y = pos_.y - pos.y;

	float distance = sqrtf(x * x + y * y);
	float minDistance = radius_ + radius;

	if (minDistance >= distance) {
		Novice::PlayAudio(deadSFX_, 0, 1.0f);
		isSpawn_ = false;
		spawnCooldown_ = maxSpawnCooldown_;
		return true;
	}
	return false;
}

void Enemy::Move() {
	if (isSpawn_ == true) {
		pos_.x += speed_.x;
		pos_.y += speed_.y;
		if (pos_.x + radius_ >= 1280.0f || pos_.x - radius_ <= 0.0f) {
			speed_.x = -speed_.x;
		}
		if (pos_.y + radius_ >= 720.0f || pos_.y - radius_ <= 0.0f) {
			speed_.y = -speed_.y;
		}
	} 
}

void Enemy::Draw() {
	if (isSpawn_ == true) {
		Novice::DrawEllipse(static_cast<int>(pos_.x), static_cast<int>(pos_.y),
			static_cast<int>(radius_), static_cast<int>(radius_), 0.0f, RED, kFillModeSolid);
	}

}