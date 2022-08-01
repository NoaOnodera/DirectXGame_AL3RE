
#include "PlayerBullet.h"
#include<cassert>

PlayerBullet::PlayerBullet() {

}

PlayerBullet::~PlayerBullet() {
	delete vectorMove_;
}

void PlayerBullet::Initialize(Model* model, const Vector3& position, const Vector3& velocity) {
//NULLポインタチェック
	assert(model);

	model_ = model;
	//引数で受け取った速度をメンバ変数に代入
	velocity_ = velocity;
	//テクスチャ読み込み
	textureHandle_ = TextureManager::Load("black.jpg");

	Vector3 pos = { 0,0,3 };
	//引数で受け取った初期座標をセット
	worldTransform_.translation_ = position+pos;

	vectorMove_ = new VectorMove();
	//ワールドトランスフォームの初期化
	worldTransform_.Initialize();
}

void PlayerBullet::Update() {
	vectorMove_->MyUpdate(worldTransform_);
	//座標を移動させる(1フレーム分の移動力を足し込む)
	worldTransform_.translation_ += velocity_;
	//時間経過でdeath
	if (--deathTimer_ <= 0) {
		isDead_ = true;
	}
}

void PlayerBullet::Draw(const ViewProjection& viewProjection) {
//モデルの描画
	model_->Draw(worldTransform_, viewProjection, textureHandle_);
}

void PlayerBullet::OnCollision()
{
	isDead_ = TRUE;
}

Vector3 PlayerBullet::GetRadius()
{
	Vector3 playerRadius;

	playerRadius.x = worldTransform_.scale_.x / 2;
    playerRadius.y = worldTransform_.scale_.y / 2;
	playerRadius.z = worldTransform_.scale_.z / 2;

	return playerRadius;
}

Vector3 PlayerBullet::GetWorldPosition()
{
	Vector3 worldPos;

	worldPos.x = worldTransform_.translation_.x;
	worldPos.y = worldTransform_.translation_.y;
	worldPos.z = worldTransform_.translation_.z;

	return worldPos;

}