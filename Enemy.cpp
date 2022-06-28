
#include "Enemy.h"
#include<cassert>
Enemy::Enemy() {

}
Enemy::~Enemy() {
	delete vectorMove_;
	delete myMath_;
}

void Enemy::Initialize(Model* model, uint32_t textureHandle)
{
	
	//NULL�|�C���^�`�F�b�N
	assert(model);
	//�����Ƃ��Ď󂯎�����f�[�^�������o�ϐ��ɋL�^����
	this->model_ = model;

	textureHandle_ = TextureManager::Load("player_shade.jpg");
	debugText_ = DebugText::GetInstance();

	//���[���h�g�����X�t�H�[���̏�����
	worldTransform_.Initialize();


	myMath_ = new MyMath();
	//ApprochMove();

	//debugText_ = DebugTxet::GetInstance();
	//�����Ŏ󂯎�����������W���Z�b�g
	worldTransform_.translation_ = {0,2,30};
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
	if (eFireTime ==0)
	{
		//�e�𔭎�
		Fire();
		//���˃^�C�}�[��������
		eFireTime = kFireInterval;
	}

	for (std::unique_ptr<EnemyBullet>& bullet : bullets_) {
		bullet->Update();
	}
	//�s��X�V
	//�s��̓]��
	worldTransform_.TransferMatrix();

	if (worldTransform_.translation_.z < 0.0f) {
		phase_ = Phase::Leave;
	}
}

void Enemy::Move()
{
	//�L�����N�^�[�̈ړ��x�N�g��
	Vector3 move = { 0,0,0 };

	//�L�����N�^�[�̈ړ�����
	const float kCharacterSpeed = 0.1f;

	move = {0,0,-kCharacterSpeed};

	worldTransform_.translation_ += move;

	vectorMove_->MyUpdate(worldTransform_);

	//�s��X�V
	//�s��̓]��
	worldTransform_.TransferMatrix();

	//�L�����N�^�[�̍��W����ʕ\�����鏈��
	//debugText_->SetPos(50,90);
	//debugText_->Printf("EnemyPos:(%f,%f,%f)",worldTransform.translation_.x,
		//worldTransform_.translation_.y,worldTransform_.translation_.z);
}


void Enemy::Update()
	{
	switch (phase_) {
	case Phase::Approch:
	default:
    //�K��̈ʒu�ɓ��B�����痣�E
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

	/*if (bullet_)
	{
		bullet_->Draw(viewProjection);
    }*/

	for (std::unique_ptr<EnemyBullet>& bullet : bullets_) {
		bullet->Draw(viewProjection);
	}
}

void Enemy::Fire()
{
	//�e�̑��x
	const float eBulletSpeed = 1.0f;
	Vector3 velocity(0, 0, -eBulletSpeed);
	//�e�𐶐����A������
	//PlayerBullet* newBullet = new PlayerBullet();
	Vector3 position = worldTransform_.translation_;
	//���x�x�N�g�������@�̌����ɍ��킹�ĉ�]������
	velocity = MathUtility::Vector3TransformNormal(velocity, worldTransform_.matWorld_);
	//�e�𐶐����A������
	std::unique_ptr<EnemyBullet> newBullet = std::make_unique<EnemyBullet>();
	newBullet->Initialize(model_, worldTransform_.translation_, velocity);

	//�e��o�^����
		//bullets_.push_back(std::move(newBullet));
	bullets_.push_back(std::move(newBullet));
}