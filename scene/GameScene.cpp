#include "GameScene.h"
#include "TextureManager.h"
#include "AxisIndicator.h"
#include <cassert>
#include <random>
#include <DirectXMath.h>
//#include "MyMath.h"


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
	//AxisIndicator::GetInstance()->SetTargetViewProjection(&debugCamera_->GetViewProjection());//軸方向表示が参照するビュープロジェクションを指定する(アドレス渡し)
	AxisIndicator::GetInstance()->SetTargetViewProjection(&viewProjection_);
	
	//乱数シード生成器
	std::random_device seed_gen;
	//メルセンヌ・ツイスターの乱数エンジン
	std::mt19937_64 engine(seed_gen());
	//乱数範囲の指定
	std::uniform_real_distribution<float>dist(0.0f, MathUtility::PI);
	//乱数範囲の指定(回転)
	std::uniform_real_distribution<float>rotDist(0.0f, MathUtility::PI);
	//乱数範囲の指定(座標)
	std::uniform_real_distribution<float>posDist(-10.0f, 10.0f);

	//乱数エンジンを渡し、指定範囲からランダムな数値を得る
	float value = dist(engine);
	
	for (WorldTransform& worldTransform : worldTransforms_) {

		

		
		//ワールドトランスフォームの初期化
		worldTransform.Initialize();
		
#pragma region スケーリング
	//スケーリング
		worldTransform.scale_ = { 1,1,1 };//x,y,z方向のスケーリングを設定
		Matrix4 matScale;//スケーリング行列を宣言
		//スケーリング倍率を行列に設定する
		matScale.m[0][0] = worldTransform.scale_.x;
		matScale.m[1][1] = worldTransform.scale_.y;
		matScale.m[2][2] = worldTransform.scale_.z;
		matScale.m[3][3] = 1;

#pragma endregion

#pragma region 回転角

		//worldTransform.rotation_ = { MathUtility::PI / 4.0f,MathUtility::PI / 4.0f,0.0f };//回転角を設定
		worldTransform.rotation_ = { rotDist(engine),rotDist(engine),rotDist(engine) };
		Matrix4 matRotZ, matRotX, matRotY;
		//Z軸回転行列の各要素を設定する
		matRotZ.m[0][0] = cosf(worldTransform.rotation_.z);
		matRotZ.m[0][1] = sinf(worldTransform.rotation_.z);
		matRotZ.m[1][0] = -sinf(worldTransform.rotation_.z);
		matRotZ.m[1][1] = cosf(worldTransform.rotation_.z);
		matRotZ.m[2][2] = 1;
		matRotZ.m[3][3] = 1;


		//X軸回転行列の各要素を設定する
		matRotX.m[0][0] = 1;
		matRotX.m[1][1] = cosf(worldTransform.rotation_.x);
		matRotX.m[1][2] = sinf(worldTransform.rotation_.x);
		matRotX.m[2][1] = -sinf(worldTransform.rotation_.x);
		matRotX.m[2][2] = cosf(worldTransform.rotation_.x);
		matRotX.m[3][3] = 1;

		//Y軸回転行列の各要素を設定する
		matRotY.m[0][0] = cosf(worldTransform.rotation_.y);
		matRotY.m[1][1] = 1;
		matRotY.m[0][2] = -sinf(worldTransform.rotation_.y);
		matRotY.m[2][0] = sinf(worldTransform.rotation_.y);
		matRotY.m[2][2] = cosf(worldTransform.rotation_.y);
		matRotY.m[3][3] = 1;




#pragma endregion 	

#pragma region 平行移動

		//x,y,z軸周りの平行移動を設定
		//worldTransform.translation_ = { 5,5,5};
		worldTransform.translation_ = { posDist(engine),posDist(engine),posDist(engine)};
		//平行移動行列を宣言
		Matrix4 matTrans = MathUtility::Matrix4Identity();

		//移動量を行列に設定する
		matTrans.m[0][0] = 1;
		matTrans.m[1][1] = 1;
		matTrans.m[2][2] = 1;
		matTrans.m[3][3] = 1;
		matTrans.m[3][0] = worldTransform.translation_.x;
		matTrans.m[3][1] = worldTransform.translation_.y;
		matTrans.m[3][2] = worldTransform.translation_.z;


#pragma endregion


		worldTransform.matWorld_ = Matrix4(
			1, 0, 0, 0,
			0, 1, 0, 0,
			0, 0, 1, 0,
			0, 0, 0, 1
		);

		//スケーリング・回転・平行移動を合成した行列を計算してワールドトランスフォームに代入zz

		worldTransform.matWorld_ *= matScale;//掛け算


		worldTransform.matWorld_ *= matRotZ;//掛け算


		worldTransform.matWorld_ *= matRotX;//掛け算


		worldTransform.matWorld_ *= matRotY;//掛け算



		worldTransform.matWorld_ *= matTrans;//掛け算



		worldTransform.TransferMatrix();//行列の転送
		


			//行列の転送
		worldTransform.TransferMatrix();


		worldTransforms_[PartId::kRoot].scale_ = { 0.6f,1.0f,1.0f };

		worldTransforms_[PartId::kRoot].Initialize();
		//脊髄
		worldTransforms_[PartId::kSpine].translation_ = { 0.0f,0.0f,0.0f };
		worldTransforms_[PartId::kSpine].parent_ = &worldTransforms_[PartId::kRoot];
		worldTransforms_[PartId::kSpine].Initialize();

		//上半身
		worldTransforms_[kChest].translation_ = { 0.0f,5.0f,0.0f };
		worldTransforms_[kChest].parent_ = &worldTransforms_[kSpine];
		worldTransforms_[kChest].Initialize();

		worldTransforms_[kHead].translation_ = { 0.0f, 3.0f, 0.0f };
		worldTransforms_[kHead].parent_=&worldTransforms_[kChest];
		worldTransforms_[kHead].Initialize();

		worldTransforms_[kArmL].translation_ = { -3.0f,0.0f,0.0f };
		worldTransforms_[kArmL].parent_ = &worldTransforms_[kChest];
		worldTransforms_[kArmL].Initialize();

		worldTransforms_[kArmR].translation_ = { 3.0f, 0.0f, 0.0f };
		worldTransforms_[kArmR].parent_ = &worldTransforms_[kChest];
		worldTransforms_[kArmR].Initialize();


		//下半身

		worldTransforms_[kHip].translation_ = { 0.0f,2.0f,0.0f };
		worldTransforms_[kHip].parent_ = &worldTransforms_[kSpine];
		worldTransforms_[kHip].Initialize();

		worldTransforms_[kLegL].translation_ = { -3.0f, -3.0f, 0.0f };
		worldTransforms_[kLegL].parent_ = &worldTransforms_[kHip];
		worldTransforms_[kLegL].Initialize();

		worldTransforms_[kLegR].translation_ = { 3.0f, -3.0f, 0.0f };
		worldTransforms_[kLegR].parent_ = &worldTransforms_[kHip];
		worldTransforms_[kLegR].Initialize();


		viewProjection_.up = { 0.0f,1.0f,0.0f };
		viewProjection_.target = { 0,0,0 };
		viewProjection_.eye = { 0.0f,0.0f,- 50 };


	}

#pragma region 垂直 

	//カメラ垂直方向視野角を設定
	viewProjection_.fovAngleY = DirectX::XMConvertToRadians(45.0f);

	//aspectRation
	viewProjection_.aspectRatio = 1.0f;
	//ニアクリップ距離を設定
	viewProjection_.nearZ = 52.0f;
	//ファークリップ距離を設定
	viewProjection_.farZ = 53.0f;


#pragma endregion
	
	viewProjection_.Initialize();
}

void GameScene::Update() {
	
	Vector3 move = { 0, 0, 0 };

	const float kCharacterSpeed = 0.2f;

	if (input_->PushKey(DIK_LEFT)) {
		move = { -kCharacterSpeed, 0, 0 };

	}
	else if (input_->PushKey(DIK_RIGHT)) {
		move = { kCharacterSpeed, 0, 0 };
	}

	worldTransforms_[PartId::kRoot].translation_.x += move.x;

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


	for (WorldTransform& worldTransform : worldTransforms_) {
		

			worldTransform.TransferMatrix();
	}
	//worldTransforms_[PartId::kRoot].translation_.y += move.y;
	//orldTransforms_[PartId::kRoot].translation_.z += move.z;


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


	worldTransforms_[PartId::kRoot].UpdateMatrix();
	worldTransforms_[PartId::kSpine].UpdateMatrix();

	worldTransforms_[PartId::kChest].UpdateMatrix();
	worldTransforms_[PartId::kHead].UpdateMatrix();
	worldTransforms_[PartId::kArmL].UpdateMatrix();
	worldTransforms_[PartId::kArmR].UpdateMatrix();
	worldTransforms_[PartId::kHip].UpdateMatrix();
	worldTransforms_[PartId::kLegL].UpdateMatrix();
	worldTransforms_[PartId::kLegR].UpdateMatrix();

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
	//範囲forで全てのワールドトランスフォームを順に処理する
	for (WorldTransform& worldTransform : worldTransforms_) {

		//model_->Draw(worldTransform, debugCamera_->GetViewProjection(), textureHandle_);
		model_->Draw(worldTransforms_[PartId::kChest], viewProjection_, textureHandle_);
		model_->Draw(worldTransforms_[PartId::kHead], viewProjection_, textureHandle_);
		model_->Draw(worldTransforms_[PartId::kArmL], viewProjection_, textureHandle_);
		model_->Draw(worldTransforms_[PartId::kArmR], viewProjection_, textureHandle_);
		model_->Draw(worldTransforms_[PartId::kHip], viewProjection_, textureHandle_);
		model_->Draw(worldTransforms_[PartId::kLegL], viewProjection_, textureHandle_);
		model_->Draw(worldTransforms_[PartId::kLegR], viewProjection_, textureHandle_);
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
