#pragma once
#include "Model.h"
#include "DebugText.h"
#include "EnemyBullet.h"
#include "WorldTransform.h"
#include "ViewProjection.h"
#include "GameScene.h"
//自機クラスの前方宣言
class Player;
class GameScene;


enum class Phase {
	Approch,//接近する
	Leave,//離脱する
};

class Enemy {
public:
	 Enemy();
	 ~Enemy();
	void Initialize(Model* model,WorldTransform worldTransform);
	void Update();
	void Draw(ViewProjection& viewProjection);
	void ApprochMove();
	void LeaveMove();
	void Fire();
	void SetPlayer(Player* player) { player_ = player; }
	
	bool IsDead()const { return isDead_; }
	//衝突を検出したら呼び出しされるコールバック関数
	void OnCollision();
	Vector3 GetWorldPosition();
	Vector3 GetRadius();
	//発射感覚
	static const int kFireInterval = 60;
	const std::list<std::unique_ptr<EnemyBullet>>& GetBullets() { return bullets_; };
	void SetGameScene(GameScene* gameScene) { gameScene_ = gameScene; };

	
private:
	//ワールド変換データ
	WorldTransform worldTransform_;
	//モデル
	Model* model_ = nullptr;
	//テクスチャハンドル
	uint32_t textureHandle_ = 0u;
	



	std::list<std::unique_ptr<EnemyBullet>>bullets_;


	//デバッグテキスト
	DebugText* debugText_ = nullptr;


	//MyMath* myMath_ = nullptr;

	int32_t eFireTime = 60;

	VectorMove* vectorMove_ = nullptr;
	
	

	Player* player_ = nullptr;

	bool isDead_ = false;

	
	//弾リストを取得
	
	//フェーズ
	Phase phase_ = Phase::Approch;

	
	GameScene* gameScene_ = nullptr;
	
};