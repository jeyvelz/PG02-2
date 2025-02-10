#pragma once
#include "Vector2.h"
#include "Bullet.h"

class Enemy {
public:
	/// <summary>
	/// 敵のコンストラクタ
	/// </summary>
	Enemy();

	/// <summary>
	/// 敵のデストラクタ
	/// </summary>
	~Enemy() = default;

	/// <summary>
	/// 移動処理
	/// </summary>
	void Move();

	void SpawnEnemy(Vector2 spawnPos);

	/// <summary>
	/// プレイヤーの弾の当たり判定関数
	/// </summary>
	/// <param name="pos">弾の位置</param>
	/// <param name="radius">弾の半径</param>
	/// <returns>true/false</returns>
	bool CollisionCheck(Vector2 const pos, float const radius);

	//描画処理
	void Draw();

	/// アクセッサ
	Vector2 GetPos() const { return pos_; }
	float GetRadius() const { return radius_; }


public:
	bool isSpawn_;
private:
	Vector2 spawnPos_;
	Vector2 pos_;
	Vector2 speed_;
	float radius_;
	int spawnCooldown_;

	int deadSFX_;
};


