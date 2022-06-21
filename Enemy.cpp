
#include "Enemy.h"
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

	

	//debugText_ = DebugTxet::GetInstance();
	//�����Ŏ󂯎�����������W���Z�b�g
	worldTransform_.translation_ = {0,2,30};
	worldTransform_.scale_ = { 1,1,1 };
	//vectorMove_ = new VectorMove();

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
			//�ړ��x�N�g�����Z
		worldTransform_.translation_ += ;
    //�K��̈ʒu�ɓ��B�����痣�E
		if (worldTransform_.translation_.z < 0.0f) {
			phase_ = Phase::Leave;
		}
		break;
	case Phase::Leave:
		//�ړ��x�N�g�������Z
		worldTransform_.translation_ += Phase::Leave;
		break;
	}

	Move();
	}

void Enemy::Draw(const ViewProjection& viewProjection)
{
	model_->Draw(worldTransform_, viewProjection, textureHandle_);
}