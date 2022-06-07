#include "GameScene.h"
#include "TextureManager.h"
#include "AxisIndicator.h"
#include <cassert>
#include <random>
#include <DirectXMath.h>
#include "MyMath.h"
#include "Matrix4.h"

#pragma region スケーリング

Matrix4 MyScale(WorldTransform& worldTransform_)
{
	//スケーリング

	Matrix4 matScale;//スケーリング行列を宣言

	matScale.IndentityMatrix();
	//スケーリング倍率を行列に設定する
	matScale.m[0][0] = worldTransform_.scale_.x;
	matScale.m[1][1] = worldTransform_.scale_.y;
	matScale.m[2][2] = worldTransform_.scale_.z;
	matScale.m[3][3] = 1;

	return matScale;
}
#pragma endregion

#pragma region 回転角

Matrix4 MyRotZ(WorldTransform& worldTransform_)
{
	Matrix4 matRotZ;



	matRotZ.IndentityMatrix();
	//Z軸回転行列の各要素を設定する
	matRotZ.m[0][0] = cosf(worldTransform_.rotation_.z);
	matRotZ.m[0][1] = sinf(worldTransform_.rotation_.z);
	matRotZ.m[1][0] = -sinf(worldTransform_.rotation_.z);
	matRotZ.m[1][1] = cosf(worldTransform_.rotation_.z);
	matRotZ.m[2][2] = 1;
	matRotZ.m[3][3] = 1;

	return matRotZ;
}

Matrix4 MyRotX(WorldTransform& worldTransform_)
{


	Matrix4 matRotX;

	matRotX.IndentityMatrix();
	//X軸回転行列の各要素を設定する
	matRotX.m[0][0] = 1;
	matRotX.m[1][1] = cosf(worldTransform_.rotation_.x);
	matRotX.m[1][2] = sinf(worldTransform_.rotation_.x);
	matRotX.m[2][1] = -sinf(worldTransform_.rotation_.x);
	matRotX.m[2][2] = cosf(worldTransform_.rotation_.x);
	matRotX.m[3][3] = 1;

	
	return matRotX;

}

Matrix4 MyRotY(WorldTransform& worldTransform_)
{
	Matrix4 matRotY;

	matRotY.IndentityMatrix();
	//Y軸回転行列の各要素を設定する
	matRotY.m[0][0] = cosf(worldTransform_.rotation_.y);
	matRotY.m[1][1] = 1;
	matRotY.m[0][2] = -sinf(worldTransform_.rotation_.y);
	matRotY.m[2][0] = sinf(worldTransform_.rotation_.y);
	matRotY.m[2][2] = cosf(worldTransform_.rotation_.y);
	matRotY.m[3][3] = 1;



	return matRotY;
}



#pragma endregion 	


#pragma region 平行移動

Matrix4 MyTrans(WorldTransform& worldTransform_)
{
	//平行移動行列を宣言
	Matrix4 matTrans;

	matTrans.IndentityMatrix();

	//移動量を行列に設定する
	matTrans.m[0][0] = 1;
	matTrans.m[1][1] = 1;
	matTrans.m[2][2] = 1;
	matTrans.m[3][3] = 1;
	matTrans.m[3][0] = worldTransform_.translation_.x;
	matTrans.m[3][1] = worldTransform_.translation_.y;
	matTrans.m[3][2] = worldTransform_.translation_.z;


	return matTrans;

}
#pragma endregion


namespace My
{
	Matrix4 MyUpdate(WorldTransform& worldTransform_)
	{


		Matrix4 mat;
		mat.IndentityMatrix();
		worldTransform_.matWorld_ = mat;

	    //スケーリング
		Matrix4 matScale = MyScale(worldTransform_);
		Matrix4 matRotZ = MyRotZ(worldTransform_);
		Matrix4 matRotX = MyRotX(worldTransform_);
		Matrix4 matRotY = MyRotY(worldTransform_);
		Matrix4 matTrans = MyTrans(worldTransform_);
			//スケーリング・回転・平行移動を合成した行列を計算してワールドトランスフォームに代入zz

			worldTransform_.matWorld_ *= matScale;//掛け算


		worldTransform_.matWorld_ *= matRotZ;//掛け算


		worldTransform_.matWorld_ *= matRotX;//掛け算


		worldTransform_.matWorld_ *= matRotY;//掛け算



		worldTransform_.matWorld_ *= matTrans;//掛け算

			//行列の転送
		worldTransform_.TransferMatrix();
		
		return worldTransform_.matWorld_;
	}

}

GameScene::GameScene() {}

GameScene::~GameScene() {
	
	delete debugCamera_;
}

void GameScene::Initialize() {

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();
	debugText_ = DebugText::GetInstance();
	textureHandle_ = TextureManager::Load("mario.jpg");//ファイル名を指定してテクスチャを読み込む
	model_ = Model::Create();//3Dモデルの生成
	debugCamera_ = new DebugCamera(1280, 720);
	AxisIndicator::GetInstance()->SetVisible(true);//軸方向表示の表示を有効にする
	//AxisIndicator::GetInstance()->SetTargetViewProjection(&debugCamera_->GetViewProjection());//軸方向表示が参照するビュープロジェクションを指定する(アドレス渡し)
	AxisIndicator::GetInstance()->SetTargetViewProjection(&viewProjection_);
	//数学を生成
	myMath_ = new MyMath();

	Matrix4 matRotX, matRotY, matRotZ;

	for (WorldTransform& worldTransform_ : worldTransforms_)
	{
		//ワールドトランスフォームの初期化
		worldTransform_.Initialize();

		//行列の転送
		worldTransform_.TransferMatrix();

	}
	viewProjection_.Initialize();
	


	////親
	//worldTransforms_[0].Initialize();
	////子
	//worldTransforms_[1].Initialize();
	//worldTransforms_[1].translation_ = { 0,4.5f,0 };
	//worldTransforms_[1].parent_ = &worldTransforms_[0];
	//
		

	//キャラクターの大元
	worldTransforms_[PartId::kRoot].Initialize();


	//脊髄
worldTransforms_[PartId::kSpine].translation_ = { 0.0f,0.0f,0.0f };
worldTransforms_[PartId::kSpine].parent_ = &worldTransforms_[PartId::kRoot];
worldTransforms_[PartId::kSpine].Initialize();

//上半身
worldTransforms_[PartId::kChest].translation_ = { 0.0f,5.0f,0.0f };
worldTransforms_[PartId::kChest].parent_ = &worldTransforms_[PartId::kSpine];
worldTransforms_[PartId::kChest].Initialize();

worldTransforms_[PartId::kHead].translation_ = { 0.0f, 3.0f, 0.0f };
worldTransforms_[PartId::kHead].parent_ = &worldTransforms_[PartId::kChest];
worldTransforms_[PartId::kHead].Initialize();

worldTransforms_[PartId::kArmL].translation_ = { -3.0f,0.0f,0.0f };
worldTransforms_[PartId::kArmL].parent_ = &worldTransforms_[PartId::kChest];
worldTransforms_[PartId::kArmL].Initialize();

worldTransforms_[PartId::kArmR].translation_ = { 3.0f, 0.0f, 0.0f };
worldTransforms_[PartId::kArmR].parent_ = &worldTransforms_[PartId::kChest];
worldTransforms_[PartId::kArmR].Initialize();


//下半身

worldTransforms_[PartId::kHip].translation_ = { 0.0f,2.0f,0.0f };
worldTransforms_[PartId::kHip].parent_ = &worldTransforms_[PartId::kSpine];
worldTransforms_[PartId::kHip].Initialize();

worldTransforms_[PartId::kLegL].translation_ = { -3.0f, -3.0f, 0.0f };
worldTransforms_[PartId::kLegL].parent_ = &worldTransforms_[PartId::kHip];
worldTransforms_[PartId::kLegL].Initialize();

worldTransforms_[PartId::kLegR].translation_ = { 3.0f, -3.0f, 0.0f };
worldTransforms_[PartId::kLegR].parent_ = &worldTransforms_[PartId::kHip];
worldTransforms_[PartId::kLegR].Initialize();



for (int i = 0; i < kNumPartId; i++)
{
	My::MyUpdate(worldTransforms_[i]);
}
}


	///*viewProjection_.up = { 0.0f,1.0f,0.0f };
	//viewProjection_.target = { 0,0,0 };
	//viewProjection_.eye = { 0.0f,0.0f,-50 };*/

void GameScene::Update() {
	
	Vector3 move = { 0, 0, 0 };

	const float kCharacterSpeed = 0.2f;

	if (input_->PushKey(DIK_LEFT)) {
		move = { -kCharacterSpeed, 0, 0 };

	}
	else if (input_->PushKey(DIK_RIGHT)) {
		move = { kCharacterSpeed, 0, 0 };
	}

	worldTransforms_[PartId::kRoot].translation_ += move;


	worldTransforms_[PartId::kRoot].translation_.z += move.z;
	worldTransforms_[PartId::kRoot].translation_.x += move.x;
	worldTransforms_[PartId::kRoot].translation_.y += move.y;

	My::MyUpdate(worldTransforms_[PartId::kRoot]);

	
	for (int i = 0; i < kNumPartId; i++)
	{

		worldTransforms_[i].matWorld_ = My::MyUpdate(worldTransforms_[i]);
		if (worldTransforms_[i].parent_!=nullptr) {
			worldTransforms_[i].matWorld_ *= worldTransforms_[i].parent_->matWorld_;
			

		}

		worldTransforms_[i].TransferMatrix();
    }
	



	//上半身の回転速さ[ラジアン/frame]
	const float kChestRotSpeed = 0.05f;

	//押した方向で移動べくトルを変更
	if (input_->PushKey(DIK_U)) {
		worldTransforms_[PartId::kChest].rotation_.y -= kChestRotSpeed;
	}
	else if (input_->PushKey(DIK_I)) {
		worldTransforms_[PartId::kChest].rotation_.y += kChestRotSpeed;
	}

	const float kHipRotSpeed = 0.05f;

	if (input_->PushKey(DIK_J)) {
		worldTransforms_[PartId::kHip].rotation_.y -= kHipRotSpeed;
	}
	else if (input_->PushKey(DIK_K)) {
		worldTransforms_[PartId::kHip].rotation_.y += kHipRotSpeed;
	}


	for (WorldTransform& worldTransform_ : worldTransforms_) {
		
		worldTransform_.TransferMatrix();
	}
	 
	
	 
	
	

	////デバッグ用表示
	debugText_->SetPos(50, 150);
	debugText_->Printf(
		"Root::(%f,%f,%f", worldTransforms_[PartId::kRoot].translation_.x,
		worldTransforms_[PartId::kRoot].translation_.y, worldTransforms_[PartId::kRoot].translation_.z);

	debugText_->SetPos(50, 50);
	debugText_->Printf(
		"eye:(%f,%f,%f)", viewProjection_.eye.x, viewProjection_.eye.y, viewProjection_.eye.z);

	debugText_->SetPos(50, 70);
	debugText_->Printf(
		"target:(%f,%f,%f)", viewProjection_.target.x, viewProjection_.target.y,
		viewProjection_.target.z);

	debugText_->SetPos(50, 90);
	debugText_->Printf(
		"up:(% f, % f,% f) ", viewProjection_.up.x, viewProjection_.up.y, viewProjection_.up.z);


	debugText_->SetPos(50, 110);
	debugText_->Printf("fovAngleY(Degree):%f", DirectX::XMConvertToDegrees(viewProjection_.fovAngleY));

	debugText_->SetPos(50, 130);
	debugText_->Printf("nearZ:%f", DirectX::XMConvertToDegrees(viewProjection_.nearZ));



	

}

void GameScene::Draw() {

	// コマンドリストの取得								
	ID3D12GraphicsCommandList* commandList = dxCommon_->GetCommandList();

#pragma region 背景スプライト描画
	// 背景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに背景スプライトの描画処理を追加できる
	/// </summary>

	// スプライト描画後処理
	Sprite::PostDraw();
	// 深度バッファクリア
	dxCommon_->ClearDepthBuffer();
#pragma endregion

#pragma region 3Dオブジェクト描画
	// 3Dオブジェクト描画前処理
	Model::PreDraw(commandList);

	/// <summary>
	/// ここに3Dオブジェクトの描画処理を追加できる
	/// </summary>

	//model_->Draw(worldTransform__,viewProjection_,textureHandle_);//3Dモデル描画
	//範囲forで全てのワールドトランスフォームを順に処理する
	//for (WorldTransform& worldTransform_ : worldTransforms_) {

	//	//model_->Draw(worldTransform_, debugCamera_->GetViewProjection(), textureHandle_);
	//	//model_->Draw(worldTransforms_[0], viewProjection_, textureHandle_);
	//	//model_->Draw(worldTransforms_[1], viewProjection_, textureHandle_);
	//	/*model_->Draw(worldTransforms_[PartId::kChest], viewProjection_, textureHandle_);
	//	model_->Draw(worldTransforms_[PartId::kHead], viewProjection_, textureHandle_);
	//	model_->Draw(worldTransforms_[PartId::kArmL], viewProjection_, textureHandle_);
	//	model_->Draw(worldTransforms_[PartId::kArmR], viewProjection_, textureHandle_);
	//	model_->Draw(worldTransforms_[PartId::kHip], viewProjection_, textureHandle_);
	//	model_->Draw(worldTransforms_[PartId::kLegL], viewProjection_, textureHandle_);
	//	model_->Draw(worldTransforms_[PartId::kLegR], viewProjection_, textureHandle_);*/
	//}


	for (int i = 2; i < kNumPartId; i++)
	{
		model_->Draw(worldTransforms_[i], viewProjection_, textureHandle_);
		//model_->Draw(worldTransforms_[1], viewProjection_, textureHandle_);
	}


	Model::PostDraw();// 3Dオブジェクト描画後処理																									
#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	/// </summary>

	// デバッグテキストの描画
	debugText_->DrawAll(commandList);
	//
	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}
