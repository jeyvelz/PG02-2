#include "Novice.h"
#include "Bullet.h"

const int kMaxBullet = 24;

Bullet::Bullet() {
	pos_ = { -200.0f, -200.0f };
	speed_ = 12.0f;
	radius_ = 12.0f;
	isShot_ = false;
}

void Bullet::SetPosX(float posX) {
	pos_.x = posX;
}

void Bullet::SetPosY(float posY) {
	pos_.y = posY;
}

void Bullet::Update() {
	if (isShot_ == true) {
		pos_.y -= speed_;
	}
	if (pos_.y + radius_ <= 0.0f) {
		isShot_ = false;
	}
}

void Bullet::Draw() {
	if (isShot_ == true) {
		Novice::DrawEllipse(static_cast<int>(pos_.x), static_cast<int>(pos_.y),
			static_cast<int>(radius_), static_cast<int>(radius_), 0.0f, WHITE, kFillModeSolid);
	}
}