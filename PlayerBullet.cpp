#include "Player.h"
#include "PlayerBullet.h"
#include<cassert>

PlayerBullet::PlayerBullet() {

}


PlayerBullet::~PlayerBullet() {
	delete vectorMove_;
}

void PlayerBullet::Initialize(Model* model, const Vector3& position) {
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

}

void PlayerBullet::Update() {
	vectorMove_->MyUpdate(worldTransform_);
}
void PlayerBullet::Draw(const ViewProjection& viewProjection) {
//���f���̕`��
	model_->Draw(worldTransform_, viewProjection, textureHandle_);
}