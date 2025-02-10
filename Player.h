#pragma once
#include "Bullet.h"

struct Color {
	int red;
	int green;
	int blue;
	int alpha;
	int rgba;
};

struct Particle {
	Vector2 pos;
	Vector2 speed;
	Color color;
	bool isVisible;
};

enum STATE {
	ALIVE,
	DEAD
};

class Player {
public:
	/// <summary>
	/// 弾クラスのポインター変数
	/// </summary>
	Bullet* bullet_[12];

	/// <summary>
	/// プレイヤーのコンストラクタ
	/// </summary>
	Player();
	/// <summary>
	/// プレイヤーのデストラクタ
	/// </summary>
	~Player();

	/// <summary>
	/// プレイヤーの更新処理
	/// </summary>
	/// <param name="keys">キー入力</param>
	/// <param name="preKeys">前キー入力</param>
	void Update(char* keys);

	/// <summary>
	/// 敵と当たり判定関数
	/// </summary>
	/// <param name="enemyPos">敵の位置</param>
	/// <param name="enemyRadius">敵の半径</param>
	/// <returns>true/false</returns>
	bool CollisionCheck(Vector2 const& enemyPos, float const& enemyRadius);

	/// <summary>
	/// プレイヤーと弾の描画処理
	/// </summary>
	void Draw();

	void SpawnPlayer();

	Vector2 GetPos() const { return pos_; }
	float GetRadius() const { return radius_; }
	int GetState() const { return state_; }

private:
	void Shot(char* keys);

	void DeadParticles();

public:
	bool isSpawn_;
private:
	Vector2 pos_;
	float speed_;
	float radius_;

	int shootCD_;
	int state_;

	Particle particle[32]; //死んだときのパーティクル
	int particleTimer_;

	int shootSFX_;
	int deadSFX_;
};

