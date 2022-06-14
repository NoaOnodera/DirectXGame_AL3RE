#pragma once
#include "GameScene.h"
#include "WorldTransform.h"
#include "Model.h"
#include "Input.h" 
#include "WorldTransform.h"
#include "ViewProjection.h"
#include"TextureManager.h"
#include "VectorMove.h"
#include "MyMath.h"
#include "PlayerBullet.h"

class Player {
public:


	 Player();
    ~Player();
	void Rotate();
	void Initialize(Model*model,uint32_t textureHandle);
	void Update();
	void Draw(ViewProjection&viewProjection);
	void Attack();
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

	//弾
	PlayerBullet* bullet_ = nullptr;


	
};