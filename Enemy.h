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
#include "EnemyBullet.h"
#include <memory>
#include <list>
enum class Phase {
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
	void Draw(ViewProjection& viewProjection);
	void ApprochMove();
	void LeaveMove();
	void Fire();

	//発射感覚
	static const int kFireInterval = 60;
private:
	//ワールド変換データ
	WorldTransform worldTransform_;
	//モデル
	Model* model_ = nullptr;
	//テクスチャハンドル
	uint32_t textureHandle_ = 0u;
	
	//デバッグテキスト
	DebugText* debugText_ = nullptr;

	MyMath* myMath_ = nullptr;

	int32_t eFireTime = 60;

	VectorMove* vectorMove_ = nullptr;
	
	//フェーズ
	Phase phase_ = Phase::Approch;

	std::list<std::unique_ptr<EnemyBullet>>bullets_;
	EnemyBullet* bullet_ = nullptr;
};