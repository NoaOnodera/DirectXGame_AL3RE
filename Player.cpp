#include <cassert>
#include"Player.h"


using namespace std;
Player::Player() {

}


Player::~Player() {
	delete vectorMove_;
	delete myMath_;
}
void Player::Initialize(Model* model, uint32_t textureHandle) {

	//NULL�|�C���^�`�F�b�N
	assert(model);
	//�����Ƃ��Ď󂯎�����f�[�^�������o�ϐ��ɋL�^����
	model_ = model;
	//�V���O���g���C���X�^���X���擾����

	textureHandle_ = TextureManager::Load("mario.jpg");
	input_ = Input::GetInstance();
	debugText_ = DebugText::GetInstance();
	

	
	worldTransform_.Initialize();

	myMath_ = new MyMath();



}


void Player::Rotate() {

	const float kRotateSpeed = 0.05f;
	if (input_->PushKey(DIK_U)) {
		worldTransform_.rotation_.y -= kRotateSpeed;
	}
	else if (input_->PushKey(DIK_I)) {
		worldTransform_.rotation_.y += kRotateSpeed;
	}
}


void Player::Update() {
	{

		//�f�X�t���O�̗������e���폜
		bullets_.remove_if([](std::unique_ptr<PlayerBullet>& bullet) 
			{
			return bullet->IsDead();
			});
		Vector3 move = { 0, 0, 0 };

		const float kCharacterSpeed = 0.2f;

		if (input_->PushKey(DIK_LEFT)) {
			move = { -kCharacterSpeed, 0, 0 };

		}
		else if (input_->PushKey(DIK_RIGHT)) {
			move = { kCharacterSpeed, 0, 0 };
		}
		else if (input_->PushKey(DIK_UP)) {
			move = { 0, kCharacterSpeed, 0 };
		}
		else if (input_->PushKey(DIK_DOWN)) {
			move = {0, -kCharacterSpeed, 0 };
		}



		



		//���W�ړ�(�x�N�g���̉��Z)
		worldTransform_.translation_ += move;
		
		//�ړ����E���W
		const float kMoveLimitX =35;
		const float kMoveLimitY = 20;
		//�͈͂𒴂��Ȃ�����worldTransform_.translation_�l�ɐ�����������
		worldTransform_.translation_.x = myMath_->MaxNum(worldTransform_.translation_.x ,- kMoveLimitX);
		worldTransform_.translation_.x = myMath_->MinNum(worldTransform_.translation_.x ,+ kMoveLimitX);
		worldTransform_.translation_.y = myMath_->MaxNum(worldTransform_.translation_.y ,- kMoveLimitY);
		worldTransform_.translation_.y = myMath_->MinNum(worldTransform_.translation_.y, + kMoveLimitY);



		


		//�L�����N�^�[�̍��W����ʕ\�����鏈��


		vectorMove_->MyUpdate(worldTransform_);
		Rotate();

		//�L�����N�^�@�U������
		Attack();

		for (std::unique_ptr<PlayerBullet>& bullet : bullets_) {
			bullet->Update();
		}
	}
	worldTransform_.TransferMatrix();


}



void Player::Draw(ViewProjection&viewProjection) {
	model_->Draw(worldTransform_, viewProjection, textureHandle_);

	//�e�`��
	for (std::unique_ptr<PlayerBullet>& bullet : bullets_) {
		bullet->Draw(viewProjection);
	}
}


void Player::Attack() {
	if (input_->PushKey(DIK_SPACE)) 
	{
       //�e�̑��x
		const float kBulletSpeed = 1.0f;
		Vector3 velocity(0,0,kBulletSpeed);
		//�e�𐶐����A������
		//PlayerBullet* newBullet = new PlayerBullet();
        Vector3 position = worldTransform_.translation_;
		//���x�x�N�g�������@�̌����ɍ��킹�ĉ�]������
		velocity = MathUtility::Vector3TransformNormal(velocity, worldTransform_.matWorld_);
		//�e�𐶐����A������
		std::unique_ptr<PlayerBullet> newBullet = std::make_unique<PlayerBullet>();
		newBullet->Initialize(model_, worldTransform_.translation_,velocity);
	
	//�e��o�^����
		//bullets_.push_back(std::move(newBullet));
		bullets_.push_back(std::move(newBullet));
	}
}

	