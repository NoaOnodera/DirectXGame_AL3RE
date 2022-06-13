#include "GameScene.h"
#include "Player.h"

void Player::Initialize(Model* model, uint32_t textureHandle) {

	//NULL�|�C���^�`�F�b�N
	assert(model);
	//�����Ƃ��Ď󂯎�����f�[�^�������o�ϐ��ɋL�^����

	//�V���O���g���C���X�^���X���擾����
	input_ = Input::GetInstance();
	debugText_ = DebugText::GetInstance();
	//���[���h�ϊ��̏�����
}



void Player::Update() {
	//�L�����N�^�[�̈ړ��x�N�g��
	Vector3 move = { 0,0,0 };
	//�ړ��x�N�g����ύX���鏈��
	const float Speed = 0.2f;

	if (input_->PushKey(DIK_W)) {
		move={ 0,0,Speed };
	}
	else if(input_->PushKey(DIK_S)) {
		move = { 0,0,-Speed };
	}
	//���W�ړ�(�x�N�g���̉��Z)

	//�s��X�V

	//�L�����N�^�[�̍��W����ʕ\�����鏈��
}


void Player::Draw() {
	
}
