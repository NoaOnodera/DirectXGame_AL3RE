#include "GameScene.h"
#include "TextureManager.h"
#include <cassert>
#include"AxisIndicator.h"


GameScene::GameScene() {
}

GameScene::~GameScene() {
	
	
}

void GameScene::Initialize() {

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();
	debugText_ = DebugText::GetInstance();
	textureHandle_ = TextureManager::Load("mario.jpg");//ファイル名を指定してテクスチャを読み込む
	model_ = Model::Create();//3Dモデルの生成
	debugCamera_ = new DebugCamera(1280, 720);
	worldTransform_.Initialize();//ワールドトランスフォームの初期化
	viewProjection_.Initialize();//ビュープロジェクションの初期化
	viewProjection_.eye = { 0,0,-50 };
	
	player_ = std::make_unique<Player>();
	
	//自キャラの初期化
	//void Initialize(Model * model, uint32_t textureHandle);
	enemy_ = std::make_unique<Enemy>();
	enemy_->SetPlayer(player_.get());



	player_->Initialize(model_, textureHandle_);
	enemy_->Initialize(model_, textureHandle_);

	
}

void GameScene::Update() {
	debugCamera_->Update();//デバッグカメラの更新
	//自キャラの更新
	player_->Update();
	enemy_->Update();

	debugText_->SetPos(50, 70);
	debugText_->Printf("eye:(%f,%f,%f)", viewProjection_.eye.x, viewProjection_.eye.y, viewProjection_.eye.z);
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


	//自キャラの描画
	player_->Draw(viewProjection_);
	enemy_->Draw(viewProjection_);
	// 3Dオブジェクト描画後処理
	Model::PostDraw();
#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	/// </summary>

	// デバッグテキストの描画
	debugText_->DrawAll(commandList);
	
	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}


void GameScene::CheckAllCollisions()
{
	//判定対象AとBの座標
	Vector3 posA, posB;

	//自弾リストの取得
	const std::list<std::unique_ptr<PlayerBullet>>& playerBullets = player_->GetBullets();
	//敵弾リストの取得
	const std::list<std::unique_ptr<EnemyBullet>>& enemyBullets = enemy_->GetBullets();
#pragma 自キャラと敵弾の当たり判定
	//自キャラの座標
	posA =;


	//自キャラと敵弾全てのあたり判定
	for (const std::unique_ptr<EnemyBullet>& bullet : enemyBullets) {


		//敵弾の座標
		posB =worldTransform_.translation_;

		//座標AとBの距離を求める
			//球と球の交差判定
			if() {
				//自キャラの衝突時コールバックを呼び出す
				player_->OnCollision();
				//敵弾の衝突時コールバックを呼び出す
				bullet->OnCollision();


			}
	}
#pragma endregion

#pragma 自弾と敵キャラのあたり判定



#pragma endregion

#pragma 自弾と敵弾のあたり判定


#pragma endregion
	
	
}
