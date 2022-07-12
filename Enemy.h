#pragma once
#include "Model.h"
#include "DebugText.h"
#include "EnemyBullet.h"

//自機クラスの前方宣言
class Player;

enum class Phase {
	Approch,//接近する
	Leave,//離脱する
};

class Enemy {
public:
	 Enemy();
	 ~Enemy();
	void Initialize(Model* model,uint32_t textureHandle);
	void Update();
	void Draw(ViewProjection& viewProjection);
	void ApprochMove();
	void LeaveMove();
	void Fire();
	void SetPlayer(Player* player) { player_ = player; }
	//衝突を検出したら呼び出しされるコールバック関数
	void OnCollision();
	Vector3 GetWorldPosition();
	//発射感覚
	static const int kFireInterval = 60;
	const std::list<std::unique_ptr<EnemyBullet>>& GetBullets() { return bullets_; }
private:
	//ワールド変換データ
	WorldTransform worldTransform_;
	//モデル
	Model* model_ = nullptr;
	//テクスチャハンドル
	uint32_t textureHandle_ = 0u;
	
	//デバッグテキスト
	DebugText* debugText_ = nullptr;

	//MyMath* myMath_ = nullptr;

	int32_t eFireTime = 60;

	VectorMove* vectorMove_ = nullptr;
	Player* player_ = nullptr;
	std::list<std::unique_ptr<EnemyBullet>>bullets_;
	

	//弾リストを取得
	
	//フェーズ
	Phase phase_ = Phase::Approch;

	

	
};