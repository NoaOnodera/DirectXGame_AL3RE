#include "Player.h"
#include "PlayerBullet.h"
#include<cassert>

PlayerBullet::PlayerBullet() {

}


PlayerBullet::~PlayerBullet() {
	delete vectorMove_;
}

void PlayerBullet::Initialize(Model* model, const Vector3& position) {
//NULLポインタチェック
	assert(model);

	model_ = model;
	//テクスチャ読み込み
	textureHandle_ = TextureManager::Load("black.jpg");


	//ワールドトランスフォームの初期化
	worldTransform_.Initialize();
	//引数で受け取った初期座標をセット
	worldTransform_.translation_ = position;

	vectorMove_ = new VectorMove();

}

void PlayerBullet::Update() {
	vectorMove_->MyUpdate(worldTransform_);
}
void PlayerBullet::Draw(const ViewProjection& viewProjection) {
//モデルの描画
	model_->Draw(worldTransform_, viewProjection, textureHandle_);
}