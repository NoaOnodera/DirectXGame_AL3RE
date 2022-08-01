
#include "PlayerBullet.h"
#include<cassert>

PlayerBullet::PlayerBullet() {

}

PlayerBullet::~PlayerBullet() {
	delete vectorMove_;
}

void PlayerBullet::Initialize(Model* model, const Vector3& position, const Vector3& velocity) {
//NULL�|�C���^�`�F�b�N
	assert(model);

	model_ = model;
	//�����Ŏ󂯎�������x�������o�ϐ��ɑ��
	velocity_ = velocity;
	//�e�N�X�`���ǂݍ���
	textureHandle_ = TextureManager::Load("black.jpg");

	Vector3 pos = { 0,0,3 };
	//�����Ŏ󂯎�����������W���Z�b�g
	worldTransform_.translation_ = position+pos;

	vectorMove_ = new VectorMove();
	//���[���h�g�����X�t�H�[���̏�����
	worldTransform_.Initialize();
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

Vector3 PlayerBullet::GetRadius()
{
	Vector3 playerRadius;

	playerRadius.x = worldTransform_.scale_.x / 2;
    playerRadius.y = worldTransform_.scale_.y / 2;
	playerRadius.z = worldTransform_.scale_.z / 2;

	return playerRadius;
}

Vector3 PlayerBullet::GetWorldPosition()
{
	Vector3 worldPos;

	worldPos.x = worldTransform_.translation_.x;
	worldPos.y = worldTransform_.translation_.y;
	worldPos.z = worldTransform_.translation_.z;

	return worldPos;

}