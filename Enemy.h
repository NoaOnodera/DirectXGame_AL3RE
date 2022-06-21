#pragma once
#include "Model.h"
#include "DebugText.h"
#include "VectorMove.h"

enum class Phase {
	Initial,//初期
	Approch,//接近する
	Leave,//離脱する
};

class Enemy {
public:
	 Enemy();
	 ~Enemy();
	void Initialize(Model* model,uint32_t textureHandle);
	void Move();
	void Update();
	void Draw(const ViewProjection& viewProjection);
private:
	//ワールド変換データ
	WorldTransform worldTransform_;
	//モデル
	Model* model_ = nullptr;
	//テクスチャハンドル
	uint32_t textureHandle_ = 0u;
	
	VectorMove* vectorMove_ = nullptr;
	
	//フェーズ
	Phase phase_ = Phase::Initial;
	
};