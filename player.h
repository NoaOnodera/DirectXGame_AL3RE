#pragma once
#include "Model.h"
#include "WorldTransform.h"
#include "DebugText.h"
#include "Input.h"
#include "WorldTransform.h"
#include "ViewProjection.h"
#include "TextureManager.h"
#include "VectorMove.h"
#include "MyMath.h"
#include "PlayerBullet.h"
#include <memory>
#include <list>


class Player {
public:


	 Player();
    ~Player();
	void Rotate();
	void Initialize(Model*model,uint32_t textureHandle);
	void Update();
	void Draw(ViewProjection&viewProjection);
	void Attack();

	//衝突を検出したら呼び出しされるコールバック関数
	void OnCollision();
	Vector3 GetWorldPosition();
	Vector3 GetRadius();
	//弾リストを取得
	const std::list<std::unique_ptr<PlayerBullet>>& GetBullets() { return bullets_; }

private:

	
	//ワールド変換データ
	WorldTransform worldTransform_;
	//モデル
	Model* model_ = nullptr;
	//テクスチャハンドル
	uint32_t textureHandle_ = 0u;
	//入力処理をするため
	Input* input_ = nullptr;
	//デバッグテキスト
	DebugText* debugText_ = nullptr;
	
	MyMath* myMath_ = nullptr;
    

	
	VectorMove* vectorMove_ = nullptr;

	
	std::list<std::unique_ptr<PlayerBullet>>bullets_;
	
	
	
	
};