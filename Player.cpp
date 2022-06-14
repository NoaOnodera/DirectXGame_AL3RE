#include "GameScene.h"
#include <cassert>
#include"Player.h"
#include"MyMath.h"

Player::Player() {

}


Player::~Player() {
	delete vectorMove_;
	delete myMath_;
}
void Player::Initialize(Model* model, uint32_t textureHandle) {

	//NULLポインタチェック
	assert(model);
	//引数として受け取ったデータをメンバ変数に記録する
	model_ = model;
	//シングルトンインスタンスを取得する

	textureHandle_ = TextureManager::Load("mario.jpg");
	input_ = Input::GetInstance();
	debugText_ = DebugText::GetInstance();
	//ワールド変換の初期化
	worldTransform_.Initialize();

	myMath_ = new MyMath();

}



void Player::Update() {
	{
		Vector3 move = { 0, 0, 0 };

		const float kCharacterSpeed = 0.2f;

		if (input_->PushKey(DIK_LEFT)) {
			move = { -kCharacterSpeed, 0, 0 };

		}
		else if (input_->PushKey(DIK_RIGHT)) {
			move = { kCharacterSpeed, 0, 0 };
		}
		else if (input_->PushKey(DIK_UP)) {
			move = { 0, kCharacterSpeed, 0 };
		}
		else if (input_->PushKey(DIK_DOWN)) {
			move = {0, -kCharacterSpeed, 0 };
		}





		//座標移動(ベクトルの加算)
		worldTransform_.translation_ += move;
		/*worldTransform_.translation_.z += move.z;
		worldTransform_.translation_.x += move.x;
		worldTransform_.translation_.y += move.y;*/
		//移動限界座標
		const float kMoveLimitX =35;
		const float kMoveLimitY = 20;
		//範囲を超えない処理worldTransform_.translation_値に制限をかける
		worldTransform_.translation_.x = myMath_->MaxNum(worldTransform_.translation_.x ,- kMoveLimitX);
		worldTransform_.translation_.x = myMath_->MinNum(worldTransform_.translation_.x ,+ kMoveLimitX);
		worldTransform_.translation_.y = myMath_->MaxNum(worldTransform_.translation_.y ,- kMoveLimitY);
		worldTransform_.translation_.y = myMath_->MinNum(worldTransform_.translation_.y, + kMoveLimitY);




		//キャラクターの座標を画面表示する処理


		vectorMove_->MyUpdate(worldTransform_);
	}
	worldTransform_.TransferMatrix();


}



void Player::Draw(ViewProjection&viewProjection) {
	model_->Draw(worldTransform_, viewProjection, textureHandle_);
}


	