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

	PrimitiveDrawer::GetInstance()->SetViewProjection(&debugCamera_->GetViewProjection());//ライン描画が参照するビュープロジェクションを指定する(アドレス渡し
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
	PrimitiveDrawer::GetInstance()->DrawLine3d(Vector3(0,10,0),Vector3(0,-10,0),Vector4(0,0,100,100));//ライン描画が参照するビュープロジェクションを指定する(アドレス渡し)
	PrimitiveDrawer::GetInstance()->DrawLine3d(Vector3(-10, 10, 0), Vector3(-10, -10, 0), Vector4(0, 0, 100, 100));
	PrimitiveDrawer::GetInstance()->DrawLine3d(Vector3(10, 10, 0), Vector3(10, -10, 0), Vector4(0, 0, 100, 100));
	PrimitiveDrawer::GetInstance()->DrawLine3d(Vector3(5, 10, 0), Vector3(5, -10, 0), Vector4(0, 0, 100, 100));
	PrimitiveDrawer::GetInstance()->DrawLine3d(Vector3(-5, 10, 0), Vector3(-5, -10, 0), Vector4(0, 0, 100, 100));
	PrimitiveDrawer::GetInstance()->DrawLine3d(Vector3(10, 0, 0), Vector3(-10, 0, 0), Vector4(100, 0, 0, 100));
	PrimitiveDrawer::GetInstance()->DrawLine3d(Vector3(10, 10, 0), Vector3(-10, 10, 0), Vector4(100, 0, 0, 100));



	PrimitiveDrawer::GetInstance()->DrawLine3d(Vector3(10, -10, 0), Vector3(-10, -10, 0), Vector4(100, 0, 0, 100));
	PrimitiveDrawer::GetInstance()->DrawLine3d(Vector3(10, 5, 0), Vector3(-10, 5, 0), Vector4(100, 0, 0, 100));
	PrimitiveDrawer::GetInstance()->DrawLine3d(Vector3(10, -5, 0), Vector3(-10, -5, 0), Vector4(100, 0, 0, 100));
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
