#pragma once
#include "Vector2.h"

class Bullet {
public:
	/// <summary>
	/// 弾のコンストラクタ
	/// </summary>
	Bullet();
	/// <summary>
	/// 弾のデストラクタ
	/// </summary>
	~Bullet() = default;

	/// <summary>
	/// 弾の更新処理
	/// </summary>
	void Update();

	/// <summary>
	/// 弾の描画処理
	/// </summary>
	void Draw();

	Vector2 GetPos() const { return pos_; }
	float GetRadius() const { return radius_; }

	void SetPosX(float posX);
	void SetPosY(float posY);

private:
	/// <summary>
	///  弾のメンバー変数
	/// </summary>
	Vector2 pos_;
	float speed_;
	float radius_;
public:
	bool isShot_;
};

