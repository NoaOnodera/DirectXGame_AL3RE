
#include "Enemy.h"
#include"VectorMove.h"
#include"Player.h"
#include<cassert>
#include "GameScene.h"

Enemy::Enemy() {

}
Enemy::~Enemy() {

}

void Enemy::Initialize(Model* model, WorldTransform worldTransform)
{
	//ワールドトランスフォームの初期化
	worldTransform_.Initialize();
	//NULLポインタチェック
	assert(model);
	//引数として受け取ったデータをメンバ変数に記録する
	this->model_ = model;


	
	textureHandle_ = TextureManager::Load("player_shade.jpg");
	debugText_ = DebugText::GetInstance();

	worldTransform_.translation_ = worldTransform_.translation_;
	vectorMove_ = new VectorMove();


	//myMath_ = new MyMath();
	//ApprochMove();

	//debugText_ = DebugTxet::GetInstance();
	//引数で受け取った初期座標をセット
	//worldTransform_.Initialize();
	worldTransform_.translation_ = { 0,2,30 };
	worldTransform_.scale_ = { 1,1,1 };
	//vectorMove_ = new VectorMove();

}

void Enemy::LeaveMove() {
	//キャラクターの移動ベクトル
	Vector3 move = { 0,0,0 };

	//キャラクターの移動速さ
	const float kCharacterSpeed = 0.1f;

	move = { -kCharacterSpeed,-kCharacterSpeed,0 };

	worldTransform_.translation_ += move;

	vectorMove_->MyUpdate(worldTransform_);

	//行列更新
	//行列の転送
	worldTransform_.TransferMatrix();
}

void Enemy::ApprochMove()
{
	bullets_.remove_if([](std::unique_ptr<EnemyBullet>& bullet)
		{
			return bullet->IsDead();
		});
	//キャラクターの移動ベクトル
	Vector3 move = { 0,0,0 };

	//キャラクターの移動速さ
	const float kCharacterSpeed = 0.1f;

	move = { 0,0,-kCharacterSpeed };

//worldTransform_.translation_ += move;

	vectorMove_->MyUpdate(worldTransform_);

	//発射タイマーカウントダウン
	eFireTime--;
	if (eFireTime <= 0)
	{
		//弾を発射
		Fire();
		//発射タイマーを初期化
		eFireTime = kFireInterval;
	}

	/*for (std::unique_ptr<EnemyBullet>& bullet : bullets_) {
		if (bullet) {
			bullet->Update();
		}
	}*/

	/*if (worldTransform_.translation_.z < 0.0f) {
		phase_ = Phase::Leave;
	}*/

	//行列更新
	//行列の転送
	worldTransform_.TransferMatrix();

}

void Enemy::Update()
{
	switch (phase_) {
	case Phase::Approch:
	default:
		//規定の位置に到達したら離脱
		ApprochMove();
		debugText_->SetPos(70, 170);
		debugText_->Printf("Phase:Approch");
		break;
	
	}

	//for (std::unique_ptr<EnemyBullet>& bullet : bullets_) {
	//	bullet->Update();
	//}
	vectorMove_->MyUpdate(worldTransform_);

	//行列更新
	//行列の転送
	worldTransform_.TransferMatrix();



	debugText_->SetPos(70, 160);
	debugText_->Printf("Enemy Pos:(%f,%f,%f)", worldTransform_.translation_.x, worldTransform_.translation_.y, worldTransform_.translation_.z);
    

	
}

void Enemy::Draw(ViewProjection& viewProjection)
{
	model_->Draw(worldTransform_, viewProjection, textureHandle_);


}



void Enemy::Fire()
{

	//assert(player_);
	//弾の速度
	const float eBulletSpeed = 0.01f;

	
	////弾を生成し、初期化
	////PlayerBullet* newBullet = new PlayerBullet();
	//Vector3 position = worldTransform_.translation_;
	////速度ベクトルを自機の向きに合わせて回転させる
	

	Vector3 playerVec = player_->GetWorldPosition();
	Vector3 enemyVec = GetWorldPosition();
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
	gameScene_->AddEnemyBullet(move(newBullet));
}


void Enemy::OnCollision()
{
	isDead_ = TRUE;
}

Vector3 Enemy::GetWorldPosition()
{
	Vector3 worldPos;

	worldPos.x = worldTransform_.translation_.x;
	worldPos.y = worldTransform_.translation_.y;
	worldPos.z = worldTransform_.translation_.z;

	return worldPos;
}
Vector3 Enemy::GetRadius()
{
	Vector3 enemyRadius;

	enemyRadius.x = worldTransform_.scale_.x / 2;
	enemyRadius.y = worldTransform_.scale_.y / 2;
	enemyRadius.z = worldTransform_.scale_.z / 2;

	return enemyRadius;
}
