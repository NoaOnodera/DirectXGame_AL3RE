#include "EnemyBullet.h"
#include<cassert>
#include "DebugText.h"


EnemyBullet::EnemyBullet() {

}


EnemyBullet::~EnemyBullet() {
	
}

void EnemyBullet::Initialize(Model* model, const Vector3& position, const Vector3& velocity) {
	//NULLポインタチェック
	assert(model);

	model_ = model;
	//テクスチャ読み込み
	textureHandle_ = TextureManager::Load("player_bullet.jpg");


	//ワールドトランスフォームの初期化
	worldTransform_.Initialize();
	//引数で受け取った初期座標をセット
	worldTransform_.translation_ = position;

	vectorMove_ = new VectorMove();


	//引数で受け取った速度をメンバ変数に代入
	velocity_ = velocity;
}

void EnemyBullet::Update() {
	vectorMove_->MyUpdate(worldTransform_);
	//座標を移動させる(1フレーム分の移動力を足し込む)
	worldTransform_.translation_ += velocity_;
	//時間経過でdeath
	if (--deathTimer_ <= 0) {
		isDead_ = TRUE;
	}

}
void EnemyBullet::Draw(const ViewProjection& viewProjection) {
	//モデルの描画
	model_->Draw(worldTransform_, viewProjection, textureHandle_);
}

void EnemyBullet::OnCollision()
{
	isDead_ = TRUE;
}

Vector3 EnemyBullet::GetWorldPosition()
{
	Vector3 worldPos;

	worldPos.x = worldTransform_.translation_.x;
	worldPos.y = worldTransform_.translation_.y;
	worldPos.z = worldTransform_.translation_.z;

	return worldPos;

}

Vector3 EnemyBullet::GetRadius()
{
	Vector3 enemyRadius;

	enemyRadius.x = worldTransform_.scale_.x / 2;
	enemyRadius.y = worldTransform_.scale_.y / 2;
	enemyRadius.z = worldTransform_.scale_.z / 2;

	return enemyRadius;
}
