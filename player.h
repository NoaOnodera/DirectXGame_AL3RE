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
#include "Vector3.h"


class Player {
public:


	 Player();//コンストラクター

    ~Player();//デストラクター

	void Rotate();//プレイヤー回転処理

	void Initialize(Model*model,uint32_t textureHandle,WorldTransform worldTransform_,const Vector3& position);//初期化

	void Update();//更新

	void Draw(ViewProjection&viewProjection);//描画

	void Attack();//攻撃

	//衝突を検出したら呼び出しされるコールバック関数
	void OnCollision();

	Vector3 direction(const Vector3& velocity, const Matrix4& matWorld);
	Vector3 GetWorldPosition();
	Vector3 GetRadius();

	//弾リストを取得
	const std::list<std::unique_ptr<PlayerBullet>>& GetBullets() { return bullets_; }

	void setRailCamera(const WorldTransform& worldTransform) 
	{ worldTransform_.parent_ = &worldTransform; }//レールカメラ親子関係

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

	std::list<std::unique_ptr<PlayerBullet>>bullets_;
	
	MyMath* myMath_ = nullptr;
    
	VectorMove* vectorMove_ = nullptr;
};