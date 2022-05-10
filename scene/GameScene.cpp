#include "GameScene.h"
#include "TextureManager.h"
#include "AxisIndicator.h"
#include "PrimitiveDrawer.h"
#include <cassert>

GameScene::GameScene() {}

GameScene::~GameScene() {
	delete model_;
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
	AxisIndicator::GetInstance()->SetTargetViewProjection(&debugCamera_->GetViewProjection());//軸方向表示が参照するビュープロジェクションを指定する(アドレス渡し)
	//スケーリング
	worldTransform_.scale_ = {5,1,1};//x,y,z方向のスケーリングを設定
	worldTransform_.rotation_ = { 0.0f,0.0f,1.0f };//x,y,z軸の周りの回転角を設定
	worldTransform_.rotation_ = { 1.0f,0.0f,0.0f };
	worldTransform_.rotation_ = { 0.0f,1.0f,0.0f };
	Matrix4 matScale;//スケーリング行列を宣言
	Matrix4 matRotZ;//Z軸回転行列を宣言
	Matrix4 matRotX;//X軸回転行列を宣言
	Matrix4 matRotY;//Y軸回転行列を宣言
	//スケーリング倍率を行列に設定する
	matScale.m[0][0] =worldTransform_.scale_.x;
	matScale.m[0][1] = worldTransform_.scale_.y;
	matScale.m[1][1] = worldTransform_.scale_.z;
	//Z軸回転行列の各要素を設定する
	matRotZ.m[0][0] = worldTransform_.rotation_.x;
	matRotZ.m[0][1] = worldTransform_.rotation_.y;
	matRotZ.m[1][0] = worldTransform_.rotation_.z;
	
    //X軸回転行列の各要素を設定する
	matRotX.m[0][0] = worldTransform_.rotation_.x;
	matRotX.m[0][1] = worldTransform_.rotation_.y;
	matRotX.m[1][0] = worldTransform_.rotation_.z;

	//Y軸回転行列の各要素を設定する
	matRotY.m[0][0] = worldTransform_.rotation_.x;
	matRotY.m[0][1] = worldTransform_.rotation_.y;
	matRotY.m[1][0] = worldTransform_.rotation_.z;

	worldTransform_.matWorld_ = matScale;//単位行列を代入
    worldTransform_.matWorld_*=matScale;//掛け算

	worldTransform_.matWorld_ = matRotZ;//代入
	worldTransform_.matWorld_ *= matRotZ;//掛け算

	worldTransform_.matWorld_ = matRotX;//代入
	worldTransform_.matWorld_ *= matRotX;//掛け算

	worldTransform_.matWorld_ = matRotY;//代入
	worldTransform_.matWorld_ *= matRotY;//掛け算




	worldTransform_.TransferMatrix();
	worldTransform_.TransferMatrix();
	worldTransform_.TransferMatrix();
	worldTransform_.TransferMatrix();//行列の転送
	//PrimitiveDrawer::GetInstance()->SetViewProjection(&debugCamera_->GetViewProjection());//ライン描画が参照するビュープロジェクションを指定する(アドレス渡し
	worldTransform_.Initialize();//ワールドトランスフォームの初期化
	viewProjection_.Initialize();//ビュープロジェクションの初期化
}

void GameScene::Update() {
	debugCamera_->Update();//デバッグカメラの更新
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

	//model_->Draw(worldTransform_,viewProjection_,textureHandle_);//3Dモデル描画
	model_->Draw(worldTransform_, debugCamera_->GetViewProjection(), textureHandle_);
	//PrimitiveDrawer::GetInstance()->DrawLine3d(Vector3(0,10,0),Vector3(0,-10,0),Vector4(0,0,100,100));//ライン描画が参照するビュープロジェクションを指定する(アドレス渡し)
	//PrimitiveDrawer::GetInstance()->DrawLine3d(Vector3(-10, 10, 0), Vector3(-10, -10, 0), Vector4(0, 0, 100, 100));
	//PrimitiveDrawer::GetInstance()->DrawLine3d(Vector3(10, 10, 0), Vector3(10, -10, 0), Vector4(0, 0, 100, 100));
	//PrimitiveDrawer::GetInstance()->DrawLine3d(Vector3(5, 10, 0), Vector3(5, -10, 0), Vector4(0, 0, 100, 100));
	//PrimitiveDrawer::GetInstance()->DrawLine3d(Vector3(-5, 10, 0), Vector3(-5, -10, 0), Vector4(0, 0, 100, 100));
	//PrimitiveDrawer::GetInstance()->DrawLine3d(Vector3(10, 0, 0), Vector3(-10, 0, 0), Vector4(100, 0, 0, 100));
	//PrimitiveDrawer::GetInstance()->DrawLine3d(Vector3(10, 10, 0), Vector3(-10, 10, 0), Vector4(100, 0, 0, 100));
	//PrimitiveDrawer::GetInstance()->DrawLine3d(Vector3(10, -10, 0), Vector3(-10, -10, 0), Vector4(100, 0, 0, 100));
	//PrimitiveDrawer::GetInstance()->DrawLine3d(Vector3(10, 5, 0), Vector3(-10, 5, 0), Vector4(100, 0, 0, 100));
	//PrimitiveDrawer::GetInstance()->DrawLine3d(Vector3(10, -5, 0), Vector3(-10, -5, 0), Vector4(100, 0, 0, 100));
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
