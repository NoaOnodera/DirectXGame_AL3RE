
#include "Enemy.h"
#include<cassert>
Enemy::Enemy() {

}
Enemy::~Enemy() {
	
}

void Enemy::Initialize(Model* model, uint32_t textureHandle)
{
	//ワールドトランスフォームの初期化
	worldTransform_.Initialize();
	//NULLポインタチェック
	assert(model);
	//引数として受け取ったデータをメンバ変数に記録する
	this->model_ = model;

	textureHandle_ = TextureManager::Load("player_shade.jpg");

	

	//debugText_ = DebugTxet::GetInstance();
	//引数で受け取った初期座標をセット
	worldTransform_.translation_ = {0,2,30};
	worldTransform_.scale_ = { 1,1,1 };
	//vectorMove_ = new VectorMove();

}

void Enemy::Move()
{
	//キャラクターの移動ベクトル
	Vector3 move = { 0,0,0 };

	//キャラクターの移動速さ
	const float kCharacterSpeed = 0.1f;

	move = {0,0,-kCharacterSpeed};

	worldTransform_.translation_ += move;

	vectorMove_->MyUpdate(worldTransform_);

	//行列更新
	//行列の転送
	worldTransform_.TransferMatrix();

	//キャラクターの座標を画面表示する処理
	//debugText_->SetPos(50,90);
	//debugText_->Printf("EnemyPos:(%f,%f,%f)",worldTransform.translation_.x,
		//worldTransform_.translation_.y,worldTransform_.translation_.z);
}
void Enemy::Update()
	{
	switch (phase_) {
	case Phase::Approch:
	default:
			//移動ベクトル加算
		worldTransform_.translation_ += ;
    //規定の位置に到達したら離脱
		if (worldTransform_.translation_.z < 0.0f) {
			phase_ = Phase::Leave;
		}
		break;
	case Phase::Leave:
		//移動ベクトルを加算
		worldTransform_.translation_ += Phase::Leave;
		break;
	}

	Move();
	}

void Enemy::Draw(const ViewProjection& viewProjection)
{
	model_->Draw(worldTransform_, viewProjection, textureHandle_);
}