#include "GameScene.h"
#include "Player.h"

void Player::Initialize(Model* model, uint32_t textureHandle) {

	//NULLポインタチェック
	assert(model);
	//引数として受け取ったデータをメンバ変数に記録する

	//シングルトンインスタンスを取得する
	input_ = Input::GetInstance();
	debugText_ = DebugText::GetInstance();
	//ワールド変換の初期化
}



void Player::Update() {
	//キャラクターの移動ベクトル
	Vector3 move = { 0,0,0 };
	//移動ベクトルを変更する処理
	const float Speed = 0.2f;

	if (input_->PushKey(DIK_W)) {
		move={ 0,0,Speed };
	}
	else if(input_->PushKey(DIK_S)) {
		move = { 0,0,-Speed };
	}
	//座標移動(ベクトルの加算)

	//行列更新

	//キャラクターの座標を画面表示する処理
}


void Player::Draw() {
	
}
