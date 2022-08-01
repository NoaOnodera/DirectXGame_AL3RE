
#include "EnemyBullet.h"
#include<cassert>
//コンストラクター
EnemyBullet::EnemyBullet() {

}
//デストラクター
EnemyBullet::~EnemyBullet() {
	delete vectorMove_;
}
//初期化
void EnemyBullet::Initialize(Model* model, const Vector3& position, const Vector3& velocity) {
	//NULLポインタチェック
	assert(model);
    //引数で受け取ったデータをメンバ変数に記録する
	model_ = model;
	//引数で受け取った速度をメンバ変数に代入
	velocity_ = velocity;
	//テクスチャ読み込み
	textureHandle_ = TextureManager::Load("player_bullet.jpg");
	//引数で受け取った初期座標をセット
	worldTransform_.translation_ = position;

	vectorMove_ = new VectorMove();
	//ワールドトランスフォームの初期化
	worldTransform_.Initialize();
}
//更新
void EnemyBullet::Update() {
	vectorMove_->MyUpdate(worldTransform_);
	//座標を移動させる(1フレーム分の移動力を足し込む)
	worldTransform_.translation_ += velocity_;
	//時間経過でdeath
	if (--deathTimer_ <= 0) {
		isDead_ = true;
	}

}
//描画
void EnemyBullet::Draw(const ViewProjection& viewProjection) {
	//モデルの描画
	model_->Draw(worldTransform_, viewProjection, textureHandle_);
}
//あたり判定
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
