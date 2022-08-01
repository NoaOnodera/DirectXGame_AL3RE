#pragma once
#include "Model.h"
#include "WorldTransform.h"
#include "ViewProjection.h"
#include"TextureManager.h"
#include "VectorMove.h"
#include "DebugText.h"
#include "MyMath.h"
#include "Vector3.h"



class EnemyBullet {
public:
	EnemyBullet();//コンストラクター

	~EnemyBullet();//デストラクター

	void Initialize(Model* model, const Vector3& position, const Vector3& velocity);//初期化

	void Update();//更新

	void Draw(const ViewProjection& viewProjection);//描画

	bool IsDead() const { return isDead_; };//デスフラグのゲッター
	
	void OnCollision();//衝突を検出したら呼び出しされるコールバック関数

	Vector3 GetWorldPosition();//ワールド座標の取得
	Vector3 GetRadius();//ワールド座標の半径の取得

	
	
private:

	//ワールド変換データ
	WorldTransform worldTransform_;
	//モデルのポインタ(借りてくる)
	Model* model_ = nullptr;
	//テクスチャハンドル
	uint32_t textureHandle_ = 0u;
	//デバックテキスト
	DebugText* debugText_ = nullptr;
	//行列の計算
	VectorMove* vectorMove_ = nullptr;
	//速度
	Vector3 velocity_;
	//寿命<frm>
	static const int32_t eLifeTime = 60 * 5;
	//デスタイマー
	int32_t deathTimer_ = eLifeTime;
	//デスフラグ
	bool isDead_ = false;
};