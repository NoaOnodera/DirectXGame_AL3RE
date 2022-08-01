
#include "EnemyBullet.h"
#include<cassert>
//�R���X�g���N�^�[
EnemyBullet::EnemyBullet() {

}
//�f�X�g���N�^�[
EnemyBullet::~EnemyBullet() {
	delete vectorMove_;
}
//������
void EnemyBullet::Initialize(Model* model, const Vector3& position, const Vector3& velocity) {
	//NULL�|�C���^�`�F�b�N
	assert(model);
    //�����Ŏ󂯎�����f�[�^�������o�ϐ��ɋL�^����
	model_ = model;
	//�����Ŏ󂯎�������x�������o�ϐ��ɑ��
	velocity_ = velocity;
	//�e�N�X�`���ǂݍ���
	textureHandle_ = TextureManager::Load("player_bullet.jpg");
	//�����Ŏ󂯎�����������W���Z�b�g
	worldTransform_.translation_ = position;

	vectorMove_ = new VectorMove();
	//���[���h�g�����X�t�H�[���̏�����
	worldTransform_.Initialize();
}
//�X�V
void EnemyBullet::Update() {
	vectorMove_->MyUpdate(worldTransform_);
	//���W���ړ�������(1�t���[�����̈ړ��͂𑫂�����)
	worldTransform_.translation_ += velocity_;
	//���Ԍo�߂�death
	if (--deathTimer_ <= 0) {
		isDead_ = true;
	}

}
//�`��
void EnemyBullet::Draw(const ViewProjection& viewProjection) {
	//���f���̕`��
	model_->Draw(worldTransform_, viewProjection, textureHandle_);
}
//�����蔻��
void EnemyBullet::OnCollision()
{
	isDead_ = TRUE;
}

Vector3 EnemyBullet::GetWorldPosition()
{
	Vector3 worldPos;

	worldPos.x = worldTransform_.translation_.x;
	worldPos.y = worldTransform_.translation_.y;
	worldPos.z = worldTransform_.translation_.z;

	return worldPos;

}

Vector3 EnemyBullet::GetRadius()
{
	Vector3 enemyRadius;

	enemyRadius.x = worldTransform_.scale_.x / 2;
	enemyRadius.y = worldTransform_.scale_.y / 2;
	enemyRadius.z = worldTransform_.scale_.z / 2;

	return enemyRadius;
}
