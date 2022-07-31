#include "EnemyBullet.h"
#include<cassert>
#include "DebugText.h"


EnemyBullet::EnemyBullet() {

}


EnemyBullet::~EnemyBullet() {
	
}

void EnemyBullet::Initialize(Model* model, const Vector3& position, const Vector3& velocity) {
	//NULL�|�C���^�`�F�b�N
	assert(model);

	model_ = model;
	//�e�N�X�`���ǂݍ���
	textureHandle_ = TextureManager::Load("player_bullet.jpg");


	//���[���h�g�����X�t�H�[���̏�����
	worldTransform_.Initialize();
	//�����Ŏ󂯎�����������W���Z�b�g
	worldTransform_.translation_ = position;

	vectorMove_ = new VectorMove();


	//�����Ŏ󂯎�������x�������o�ϐ��ɑ��
	velocity_ = velocity;
}

void EnemyBullet::Update() {
	vectorMove_->MyUpdate(worldTransform_);
	//���W���ړ�������(1�t���[�����̈ړ��͂𑫂�����)
	worldTransform_.translation_ += velocity_;
	//���Ԍo�߂�death
	if (--deathTimer_ <= 0) {
		isDead_ = TRUE;
	}

}
void EnemyBullet::Draw(const ViewProjection& viewProjection) {
	//���f���̕`��
	model_->Draw(worldTransform_, viewProjection, textureHandle_);
}

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
