
#include "Enemy.h"
#include "VectorMove.h"
#include <cassert>
#include "GameScene.h"

//�R���X�g���N�^�[
Enemy::Enemy() {

}
//�f�X�g���N�^�[
Enemy::~Enemy() {
	delete vectorMove_;
	delete myMath_;
}
//������
void Enemy::Initialize(Model* model, uint32_t textureHandle,const Vector3& position)
{
	
	//NULL�|�C���^�`�F�b�N
	assert(model);
	//�����Ƃ��Ď󂯎�����f�[�^�������o�ϐ��ɋL�^����
	this->model_ = model;
	textureHandle_ = textureHandle;

	//�e�N�X�`���n���h��
	textureHandle_ = TextureManager::Load("player_shade.jpg");
	//�f�o�b�O�e�L�X�g
	debugText_ = DebugText::GetInstance();
	//�s��̌v�Z
	vectorMove_ = new VectorMove();

	myMath_ = new MyMath();

	//�����Ŏ󂯎�����������W���Z�b�g
	//worldTransform_.translation_ = position;

	worldTransform_.translation_ = { 0,2,30 };
	worldTransform_.scale_ = { 1,1,1 };
	//���[���h�g�����X�t�H�[���̏�����
	worldTransform_.Initialize();

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

//worldTransform_.translation_ += move;

	
	//���˃^�C�}�[�J�E���g�_�E��
	eFireTime--;
	if (eFireTime <= 0)
	{
		//�e�𔭎�
		Fire();
		//���˃^�C�}�[��������
		eFireTime = kFireInterval;
	}
	//�s��X�V
	vectorMove_->MyUpdate(worldTransform_);
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
	
	}

	for (std::unique_ptr<EnemyBullet>& bullet :bullets_) {
		bullet->Update();
	}

	vectorMove_->MyUpdate(worldTransform_);

	//�s��X�V
	//�s��̓]��
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
	assert(player_);
	//�e�̑��x
	const float eBulletSpeed = 0.01f;

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
	gameScene_->AddEnemyBullet(newBullet);
}


Vector3 Enemy::GetWorldPosition()
{
	Vector3 worldPos;

	worldPos.x = worldTransform_.translation_.x;
	worldPos.y = worldTransform_.translation_.y;
	worldPos.z = worldTransform_.translation_.z;

	return worldPos;

}


void Enemy::OnCollision()
{
	isDead_ = TRUE;
}
Vector3 Enemy::GetRadius()
{
	Vector3 enemyRadius;

	enemyRadius.x = worldTransform_.scale_.x / 2;
	enemyRadius.y = worldTransform_.scale_.y / 2;
	enemyRadius.z = worldTransform_.scale_.z / 2;

	return enemyRadius;
}
