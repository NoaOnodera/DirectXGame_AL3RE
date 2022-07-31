#include "GameScene.h"
#include "TextureManager.h"
#include <cassert>
#include"AxisIndicator.h"
#include"Collider.h"
#include "Matrix4.h"
#include <fstream>

GameScene::GameScene() {
}

GameScene::~GameScene() {
	delete modelSkydome_;
	delete skydome_;
	delete debugCamera_;
}

void GameScene::Initialize() {

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();
	debugText_ = DebugText::GetInstance();
	textureHandle_ = TextureManager::Load("mario.jpg");//ファイル名を指定してテクスチャを読み込む
	model_ = Model::Create();//3Dモデルの生成
	modelSkydome_ = Model::CreateFromOBJ("skydome", true);
	//debugCamera_ = new DebugCamera(1280, 720);
	debugCamera_ = new DebugCamera(WinApp::kWindowWidth, WinApp::kWindowHeight);

	//軸方向表示の表示を有効にする
	AxisIndicator::GetInstance()->SetVisible(true);
	//軸方向表示が参照するビュープロジェクションを指定する
	AxisIndicator::GetInstance()->SetTargetViewProjection(&debugCamera_->GetViewProjection());
	collider_ = new Collider;
	worldTransform_.Initialize();//ワールドトランスフォームの初期化
	viewProjection_.Initialize();//ビュープロジェクションの初期化
	viewProjection_.eye = { 0,0,-50 };
	


	//Vector3 position = { 10.0f,2.0f,50.0f };

	Vector3 cameraPosisition = {0,0,-10.0f};
	Vector3 cameraRotation = { 0,0,0 };
	
	skydome_ = new Skydome();//天球
	skydome_->Initialize(modelSkydome_);//天球の初期化
	player_ = std::make_unique<Player>();
	railCamera_ = std::make_unique<RailCamera>();//レールカメラの生成
	/*enemy_ = std::make_unique<Enemy>();
	enemy_->SetPlayer(player_.get());*/


	player_->Initialize(model_, textureHandle_);
	//enemy_->Initialize(model_, textureHandle_);
	railCamera_->Initialize(Vector3(0,0,-50),Vector3(0,0,0));


	player_->setRailCamera(railCamera_->GetWorldMatrix());


	LoadEnemyPopData();
}

void GameScene::Update() {
	debugCamera_->Update();//デバッグカメラの更新

	UpdateEnemyPopComands();

	//railCameraをゲームシーンのカメラに適応する
	viewProjection_.matView = railCamera_->GetViewProjection().matView;
	viewProjection_.matProjection = railCamera_->GetViewProjection().matProjection;
	//ビュープロジェクションの転送
	viewProjection_.TransferMatrix();
	railCamera_->Update();

	enemys_.remove_if([](std::unique_ptr<Enemy>& enemy)
		{
			return enemy->IsDead();
		}
	);
	enemyBullets_.remove_if([](std::unique_ptr<EnemyBullet>& bullet)
		{
			return bullet->IsDead();
		}
	);
	//自キャラの更新
	player_->Update();
	skydome_->Update();
	for (std::unique_ptr<Enemy>& enemy : enemys_)
	{
		enemy->Update();
	}
	for (std::unique_ptr<EnemyBullet>& enemyBullet : enemyBullets_)
	{
		enemyBullet->Update();
	}
	CheckAllCollisions();
	Vector3 v = player_->GetWorldPosition();

#ifdef _DEBUG
	/*if (input_->TriggerKey(DIK_P)) {
		isDebugCameraActive_ = !isDebugCameraActive_;
	}

	if (isDebugCameraActive_) {

		AxisIndicator::GetInstance()->SetVisible(true);

		AxisIndicator::GetInstance()->SetTargetViewProjection(&debugCamera_->GetViewProjection());


		debugCamera_->Update();
		viewProjection_.matView = debugCamera_->GetViewProjection().matView;
		viewProjection_.matProjection = debugCamera_->GetViewProjection().matProjection;
		viewProjection_.TransferMatrix();
	}
	else
	{
		AxisIndicator::GetInstance()->SetVisible(false);
		AxisIndicator::GetInstance()->SetTargetViewProjection(&debugCamera_->GetViewProjection());
		viewProjection_.UpdateMatrix();
		viewProjection_.TransferMatrix();
	}*/
#endif
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
	skydome_->Draw(viewProjection_);
	player_->Draw(viewProjection_);
	
	for (std::unique_ptr<Enemy>& enemy : enemys_)
	{
		enemy->Draw(viewProjection_);
	}
	for (std::unique_ptr<EnemyBullet>& bullet : enemyBullets_)
	{
		bullet->Draw(viewProjection_);
	}

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
	Vector3 p_Pos,e_Pos,pb_Pos,eb_Pos;

	Vector3 p_radius, e_radius, pb_radius, eb_radius;

	////自弾リストの取得
	//const std::list<std::unique_ptr<PlayerBullet>>& playerBullets = player_->GetBullets();
	////敵弾リストの取得
	//const std::list<std::unique_ptr<EnemyBullet>>& enemyBullets = enemy->GetBullets();
#pragma 自キャラと敵弾の当たり判定
	//自キャラの座標
	p_Pos = player_->GetWorldPosition();
	
	//自キャラの半径
	p_radius = player_->GetRadius();

	for (const std::unique_ptr<Enemy>& enemy : enemys_)
	{

		const std::list<std::unique_ptr<EnemyBullet>>& enemuBullets = enemyBullets_;
		//自キャラと敵弾全てのあたり判定
		for (const std::unique_ptr<EnemyBullet>& bullet : enemyBullets_) {


			//敵弾の座標
			e_Pos = bullet->GetWorldPosition();
			e_radius = bullet->GetRadius();



			//球と球の交差判定
			if (collider_->OnBulletCollision(p_Pos.x, p_Pos.y, p_Pos.z, p_radius.x, e_Pos.x, e_Pos.y, e_Pos.z, e_radius.x) == true) {
				//自キャラの衝突時コールバックを呼び出す
				player_->OnCollision();
				//敵弾の衝突時コールバックを呼び出す
				bullet->OnCollision();
			}
		}
	}
#pragma endregion

#pragma 自弾と敵キャラのあたり判定
	

	
	
	//自弾のリスト生成
	const std::list<std::unique_ptr<PlayerBullet>>& playerbullets = player_->GetBullets();
	
	for (const std::unique_ptr<PlayerBullet>& bullet : playerbullets) {

		//自キャラの座標
		pb_Pos = bullet->GetWorldPosition();

		//自キャラの半径
		pb_radius = bullet->GetRadius();
		for (const std::unique_ptr<Enemy>& enemy : enemys_)
		{
			e_Pos = enemy->GetWorldPosition();
			e_radius = enemy->GetRadius();

			//球と球の交差判定
			if (collider_->OnBulletCollision(pb_Pos.x, pb_Pos.y, pb_Pos.z, pb_radius.x, e_Pos.x, e_Pos.y, e_Pos.z, e_radius.x) == true) {

				enemy->OnCollision();

				bullet->OnCollision();
			}
		}
	}


#pragma endregion

#pragma 自弾と敵弾のあたり判定

	const std::list<std::unique_ptr<PlayerBullet>>& playerBullets = player_->GetBullets();

	for (const std::unique_ptr<PlayerBullet>& playerbullet : playerBullets) {
		//自キャラの座標
		pb_Pos = playerbullet->GetWorldPosition();

		//自キャラの半径
		pb_radius = playerbullet->GetRadius();

		for (const std::unique_ptr<Enemy>& enemy : enemys_)
		{
			const std::list < std::unique_ptr < EnemyBullet>>& enemyBullets = enemyBullets_;
			for (const std::unique_ptr<EnemyBullet>& enemybullet : enemyBullets) {


				//敵弾の座標
				eb_Pos = enemybullet->GetWorldPosition();
				eb_radius = enemybullet->GetRadius();



				//球と球の交差判定
				if (collider_->OnBulletCollision(pb_Pos.x, pb_Pos.y, pb_Pos.z, pb_radius.x, eb_Pos.x, eb_Pos.y, eb_Pos.z, eb_radius.x) == true) {
					enemybullet->OnCollision();
					//敵弾の衝突時コールバックを呼び出す
					playerbullet->OnCollision();
				}
			}
		}
	}
#pragma endregion	
}


void GameScene::EnemyFire()
{
	
	//弾の速度
	const float eBulletSpeed = 0.01f;
	Vector3 velocity;
	////弾を生成し、初期化
	////PlayerBullet* newBullet = new PlayerBullet();
	//Vector3 position = worldTransform_.translation_;
	////速度ベクトルを自機の向きに合わせて回転させる
	

	Vector3 playerVec = player_->GetWorldPosition();
	for (const std::unique_ptr<Enemy>& enemy : enemys_)
	{
		Vector3 enemyVec = enemy->GetWorldPosition();
		Vector3 Difference = playerVec;
		Difference -= enemyVec;
		Vector3 normalize(Difference);
		Difference *= eBulletSpeed;
		Vector3 velocity(Difference);


		velocity = MathUtility::Vector3TransformNormal(velocity, worldTransform_.matWorld_);
		//弾を生成し、初期化
		std::unique_ptr<EnemyBullet> newBullet = std::make_unique<EnemyBullet>();
		newBullet->Initialize(model_, worldTransform_.translation_, velocity);

		//弾を登録する
			//bullets_.push_back(std::move(newBullet));
		enemyBullets_.push_back(std::move(newBullet));
	}
}

void GameScene::BulletUpdate()
{
	enemyBullets_.remove_if([](std::unique_ptr<EnemyBullet>& bullet)
		{
			return bullet->IsDead();
		}
	);

	for (std::unique_ptr<EnemyBullet>& bullet : enemyBullets_)
	{
		bullet->Update();
	}
}

void GameScene::PEnemy(Vector3 v)
{
	worldTransform_.translation_.x = v.x;
	worldTransform_.translation_.y = v.y;
	worldTransform_.translation_.z= v.z;

	std::unique_ptr<Enemy>newEnemy = std::make_unique<Enemy>();
	newEnemy->Initialize(model_, worldTransform_);
	newEnemy->SetPlayer(player_.get());
	newEnemy->SetGameScene(this);  
	enemys_.push_back(move(newEnemy));
}

void GameScene::LoadEnemyPopData()
{
	std::ifstream file;
	file.open("Resources/sheet.csv");
	assert(file.is_open());

	enemyPopComands << file.rdbuf();

	file.close();


}

void GameScene::UpdateEnemyPopComands()
{
	if (isWait)
	{
		waitTimer--;
		if (waitTimer <= 0)
		{
			isWait = false;
		}
		return;
	}
	std::string line;

	while (getline(enemyPopComands, line))
	{
		std::istringstream line_stream(line);

		std::string word;
		getline(line_stream, word, ',');

		if (word.find("//") == 0)
		{
			continue;
		}
		if (word.find("POP") == 0)
		{
			getline(line_stream, word, ',');
			float x = (float)atof(word.c_str());


			getline(line_stream, word, ',');
			float y = (float)atof(word.c_str());


			getline(line_stream, word, ',');
			float z = (float)atof(word.c_str());
			PEnemy(Vector3(x, y, z));
		}
		else if (word.find("WAIT") == 0)
		{
			getline(line_stream, word, ',');
			int32_t waitTime = atoi(word.c_str());

			isWait = TRUE;
			waitTimer = waitTime;

			break;
		}
	}
}