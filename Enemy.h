#pragma once
#include "Model.h"
#include "DebugText.h"
#include "EnemyBullet.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include "MyMath.h"
#include "Vector3.h"
#include "player.h"
//自機クラスの前方宣言
class Player;
//ゲームシーンクラスの前方宣言
class GameScene;

enum class Phase {
	Approch,//接近する
	Leave,//離脱する
};

class Enemy {
public:
	 Enemy();//敵のコンストラクター

	 ~Enemy();//敵のデストストラクター

	void Initialize(Model* model, uint32_t textureHandle,const Vector3& position);//初期化

	void Update();//更新

	void Draw(ViewProjection& viewProjection);//描画

	void ApprochMove();//接近フェーズ

	void LeaveMove();//退避フェーズ

	void Fire();//弾の発射

	void SetPlayer(Player* player) { player_ = player; }//プレイヤーのセッター
	
	void OnCollision();//衝突を検出したら呼び出しされるコールバック関数

	Vector3 GetWorldPosition();//ワールド座標の取得

	Vector3 GetRadius();//ワールド座標半径の取得

	void SetGameScene(GameScene* gameScene) { gameScene_ = gameScene; };//ゲームシーンのセッター

	bool IsDead() const { return isDead_; };//デスフラグのゲッター
	
	static const int kFireInterval = 60;//発射感覚

private:
	//ワールド変換データ
	WorldTransform worldTransform_;
	//モデル
	Model* model_ = nullptr;
	//テクスチャハンドル
	uint32_t textureHandle_ = 0u;
	
	//デバッグテキスト
	DebugText* debugText_ = nullptr;

	MyMath* myMath_ = nullptr;//クランプ関数

	
	
	int32_t eFireTime = 60;//敵の発射タイマー

	VectorMove* vectorMove_ = nullptr;//行列の計算

	Player* player_ = nullptr;//自キャラ

	std::list<std::unique_ptr<EnemyBullet>>bullets_;
	
	GameScene* gameScene_ = nullptr;//ゲームシーン
	//フェーズ
	Phase phase_ = Phase::Approch;

	bool isDead_ = false;//デスフラグ

	
};