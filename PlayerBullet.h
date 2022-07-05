#pragma once
#include "Model.h"
#include "WorldTransform.h"
#include"TextureManager.h"
#include "VectorMove.h"
#include "DebugText.h"

class PlayerBullet {
public:
	PlayerBullet();
	~PlayerBullet();
	void Initialize(Model* model, const Vector3& position, const Vector3& velocity);
	void Update();
	
	//衝突を検出したら呼び出しされるコールバック関数
	void OnCollision(); 
	void Draw(const ViewProjection& viewProjection);
	bool IsDead() const { return isDead_; }
private:
	//ワールド変換データ
	 WorldTransform worldTransform_;
	//モデルのポインタ(借りてくる)
	Model* model_ = nullptr;
	//テクスチャハンドル
	uint32_t textureHandle_ = 0u;
	//速度
	Vector3 velocity_;

	DebugText* debugText_ = nullptr;
	VectorMove* vectorMove_ = nullptr;
	//寿命<frm>
	static const int32_t kLifeTime = 60 * 5;
	//デスタイマー
	int32_t deathTimer_ = kLifeTime;
	//デスフラグ
	bool isDead_ = false;

	

	
};