#include"player.h"
#include "Enemy.h"
#include<cassert>

Enemy::Enemy() {
	

}
Enemy::~Enemy() {
	
}

void Enemy::Initialize(Model* model, uint32_t textureHandle)
{
	//ワールドトランスフォームの初期化
	worldTransform_.Initialize();
	
	//NULLポインタチェック
	assert(model);
	//引数として受け取ったデータをメンバ変数に記録する
	this->model_ = model;

	textureHandle_ = TextureManager::Load("player_shade.jpg");
	debugText_ = DebugText::GetInstance();

	


	myMath_ = new MyMath();
	

	//debugText_ = DebugTxet::GetInstance();
	//引数で受け取った初期座標をセット
	worldTransform_.translation_ = {0,2,30};
	worldTransform_.scale_ = { 1,1,1 };
	vectorMove_ = new VectorMove();

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

	worldTransform_.translation_ += move;

	vectorMove_->MyUpdate(worldTransform_);

	//発射タイマーカウントダウン
	eFireTime--;
	if (eFireTime ==0)
	{
		//弾を発射
		Fire();
		//発射タイマーを初期化
		eFireTime = kFireInterval;
	}

	for (std::unique_ptr<EnemyBullet>& bullet : bullets_) {
		bullet->Update();
	}
	//行列更新
	//行列の転送
	worldTransform_.TransferMatrix();

	if (worldTransform_.translation_.z < 0.0f) {
		phase_ = Phase::Leave;
	}
}

void Enemy::Move()
{
	//キャラクターの移動ベクトル
	Vector3 move = { 0,0,0 };

	//キャラクターの移動速さ
	const float kCharacterSpeed = 0.1f;

	move = {0,0,-kCharacterSpeed};

	worldTransform_.translation_ += move;

	vectorMove_->MyUpdate(worldTransform_);

	//行列更新
	//行列の転送
	worldTransform_.TransferMatrix();

	//キャラクターの座標を画面表示する処理
	//debugText_->SetPos(50,90);
	//debugText_->Printf("EnemyPos:(%f,%f,%f)",worldTransform.translation_.x,
		//worldTransform_.translation_.y,worldTransform_.translation_.z);
}


void Enemy::Update()
	{
	switch (phase_) {
	case Phase::Approch:
	default:
    //規定の位置に到達したら離脱
		ApprochMove();
		break;
	case Phase::Leave:
		LeaveMove();
		break;
	}

	for (std::unique_ptr<EnemyBullet>& bullet : bullets_) {
		bullet->Update();
	}
	//Move();
	}

void Enemy::Draw(ViewProjection& viewProjection)
{
	model_->Draw(worldTransform_, viewProjection, textureHandle_);

	for (std::unique_ptr<EnemyBullet>& bullet : bullets_) {
		bullet->Draw(viewProjection);
	}
}

void Enemy::Fire()
{
	assert(player_);
	
	//弾の速度
	const float eBulletSpeed = 1.0f;
	Vector3 velocity(0, 0, -eBulletSpeed);
	


	


	//弾を生成し、初期化
	std::unique_ptr<EnemyBullet> newBullet = std::make_unique<EnemyBullet>();
	newBullet->Initialize(model_, worldTransform_.translation_, velocity);

	//弾を登録する
	bullets_.push_back(std::move(newBullet));
	
}

Vector3 Enemy::GetWorldPosition() {

	//ワールド座標を入れる変数
	Vector3 worldPos;

	//ワールド行列の平行移動成分を取得(ワールド座標)
	worldPos.x = worldTransform_.translation_.x;
	worldPos.y = worldTransform_.translation_.y;
	worldPos.z = worldTransform_.translation_.z;

	return worldPos;
}
