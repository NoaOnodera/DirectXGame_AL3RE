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

		debugText_->SetPos(70, 100);
		debugText_->Printf("Player Pos:(%f,%f,%f)", worldTransform_.translation_.x, worldTransform_.translation_.y, worldTransform_.translation_.z);
		debugText_->SetPos(70, 130);
		debugText_->Printf("Player Rot:(%f)", worldTransform_.rotation_.y);
		
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

		worldTransform_.MatrixUpdate();
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
void Player::OnCollision()
{

}

Vector3 Player::GetRadius()
{
	Vector3 playerRadius;

	playerRadius.x = worldTransform_.scale_.x / 2;
	playerRadius.y = worldTransform_.scale_.y / 2;
	playerRadius.z = worldTransform_.scale_.z / 2;

	return playerRadius;
}

Vector3 Player::GetWorldPosition()
{
	Vector3 worldPos;

	worldPos.x = worldTransform_.matWorld_.m[3][0];
	worldPos.y = worldTransform_.matWorld_.m[3][1];
	worldPos.z = worldTransform_.matWorld_.m[3][2];

	return worldPos;
}

Vector3 Player::direction(const Vector3& velocity, const Matrix4& matWorld)
{
	Vector3 puts;

	puts.x = velocity.x * matWorld.m[0][0] + velocity.y * matWorld.m[1][0] + velocity.z * matWorld.m[2][0];
	puts.y = velocity.x * matWorld.m[0][1] + velocity.y * matWorld.m[1][1] + velocity.z * matWorld.m[2][1];
	puts.z = velocity.x * matWorld.m[0][2] + velocity.y * matWorld.m[1][2] + velocity.z * matWorld.m[2][3];

	return puts;

}