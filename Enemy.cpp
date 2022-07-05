
#include "Enemy.h"
#include"VectorMove.h"
#include"Player.h"
#include<cassert>

Enemy::Enemy() {

}
Enemy::~Enemy() {

}

void Enemy::Initialize(Model* model, uint32_t textureHandle)
{
	//���[���h�g�����X�t�H�[���̏�����
	worldTransform_.Initialize();
	//NULL�|�C���^�`�F�b�N
	assert(model);
	//�����Ƃ��Ď󂯎�����f�[�^�������o�ϐ��ɋL�^����
	this->model_ = model;

	textureHandle_ = TextureManager::Load("player_shade.jpg");
	debugText_ = DebugText::GetInstance();

	vectorMove_ = new VectorMove();


	//myMath_ = new MyMath();
	//ApprochMove();

	//debugText_ = DebugTxet::GetInstance();
	//�����Ŏ󂯎�����������W���Z�b�g
	//worldTransform_.Initialize();
	worldTransform_.translation_ = { 0,2,30 };
	worldTransform_.scale_ = { 1,1,1 };
	//vectorMove_ = new VectorMove();

}

void Enemy::LeaveMove() {
	//�L�����N�^�[�̈ړ��x�N�g��
	Vector3 move = { 0,0,0 };

	//�L�����N�^�[�̈ړ�����
	const float kCharacterSpeed = 0.1f;

	move = { -kCharacterSpeed,-kCharacterSpeed,0 };

	worldTransform_.translation_ += move;

	vectorMove_->MyUpdate(worldTransform_);

	//�s��X�V
	//�s��̓]��
	worldTransform_.TransferMatrix();
}

void Enemy::ApprochMove()
{
	bullets_.remove_if([](std::unique_ptr<EnemyBullet>& bullet)
		{
			return bullet->IsDead();
		});
	//�L�����N�^�[�̈ړ��x�N�g��
	Vector3 move = { 0,0,0 };

	//�L�����N�^�[�̈ړ�����
	const float kCharacterSpeed = 0.1f;

	move = { 0,0,-kCharacterSpeed };

	worldTransform_.translation_ += move;

	vectorMove_->MyUpdate(worldTransform_);

	//���˃^�C�}�[�J�E���g�_�E��
	eFireTime--;
	if (eFireTime <= 0)
	{
		//�e�𔭎�
		Fire();
		//���˃^�C�}�[��������
		eFireTime = kFireInterval;
	}

	for (std::unique_ptr<EnemyBullet>& bullet : bullets_) {
		if (bullet) {
			bullet->Update();
		}
	}

	if (worldTransform_.translation_.z < 0.0f) {
		phase_ = Phase::Leave;
	}

	//�s��X�V
	//�s��̓]��
	worldTransform_.TransferMatrix();

}

void Enemy::Update()
{
	switch (phase_) {
	case Phase::Approch:
	default:
		//�K��̈ʒu�ɓ��B�����痣�E
		ApprochMove();
		debugText_->SetPos(70, 170);
		debugText_->Printf("Phase:Approch");
		break;
	case Phase::Leave:
		LeaveMove();
		debugText_->SetPos(70, 170);
		debugText_->Printf("Phase:LeaveMove");
		break;
	}

	for (std::unique_ptr<EnemyBullet>& bullet : bullets_) {
		bullet->Update();
	}
	/*vectorMove_->MyUpdate(worldTransform_);

	�s��X�V
	�s��̓]��
	worldTransform_.TransferMatrix();*/



	debugText_->SetPos(70, 160);
	debugText_->Printf("Enemy Pos:(%f,%f,%f)", worldTransform_.translation_.x, worldTransform_.translation_.y, worldTransform_.translation_.z);
    

	
}

void Enemy::Draw(ViewProjection& viewProjection)
{
	model_->Draw(worldTransform_, viewProjection, textureHandle_);


	for (std::unique_ptr<EnemyBullet>& bullet : bullets_) {
		if (bullet) {
			bullet->Draw(viewProjection);
		}
	}
}

Vector3 Enemy::GetWorldPosition()
{
	Vector3 worldPos;

	worldPos.x = worldTransform_.translation_.x;
	worldPos.y = worldTransform_.translation_.y;
	worldPos.z = worldTransform_.translation_.z;

	return worldPos;

}
void Enemy::Fire()
{

	assert(player_);
	//�e�̑��x
	const float eBulletSpeed = 0.01f;

	////�e�𐶐����A������
	////PlayerBullet* newBullet = new PlayerBullet();
	//Vector3 position = worldTransform_.translation_;
	////���x�x�N�g�������@�̌����ɍ��킹�ĉ�]������
	//velocity = MathUtility::Vector3TransformNormal(velocity, worldTransform_.matWorld_);

	Vector3 playerVec = player_->GetWorldPosition();
	Vector3 enemyVec = GetWorldPosition();
	Vector3 Difference = playerVec;
	Difference -= enemyVec;
	Vector3 normalize(Difference);
	Difference *= eBulletSpeed;
	Vector3 velocity(Difference);

	//�e�𐶐����A������
	std::unique_ptr<EnemyBullet> newBullet = std::make_unique<EnemyBullet>();
	newBullet->Initialize(model_, worldTransform_.translation_, velocity);

	//�e��o�^����
		//bullets_.push_back(std::move(newBullet));
	bullets_.push_back(std::move(newBullet));
}


void Enemy::OnCollision()
{

}
