
#include "PlayerBullet.h"
#include<cassert>

PlayerBullet::PlayerBullet() {

}


PlayerBullet::~PlayerBullet() {
	
}

void PlayerBullet::Initialize(Model* model, const Vector3& position, const Vector3& velocity) {
//NULL�|�C���^�`�F�b�N
	assert(model);

	model_ = model;
	//�e�N�X�`���ǂݍ���
	textureHandle_ = TextureManager::Load("black.jpg");


	//���[���h�g�����X�t�H�[���̏�����
	worldTransform_.Initialize();
	//�����Ŏ󂯎�����������W���Z�b�g
	worldTransform_.translation_ = position;

	vectorMove_ = new VectorMove();


	//�����Ŏ󂯎�������x�������o�ϐ��ɑ��
	velocity_ = velocity;
}

void PlayerBullet::Update() {
	vectorMove_->MyUpdate(worldTransform_);
	//���W���ړ�������(1�t���[�����̈ړ��͂𑫂�����)
	worldTransform_.translation_ += velocity_;
	//���Ԍo�߂�death
	if (--deathTimer_ <= 0) {
		isDead_ = true;
	}

}
void PlayerBullet::Draw(const ViewProjection& viewProjection) {
//���f���̕`��
	model_->Draw(worldTransform_, viewProjection, textureHandle_);
}

void PlayerBullet::OnCollision()
{
	isDead_ = TRUE;
}