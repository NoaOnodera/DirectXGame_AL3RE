#include "RailCamera.h"
void RailCamera::Initialize(const Vector3& position,const Vector3& rotation)
{
	//���[���h�g�����X�t�H�[���̏�����

	//worldTransform_.Initialize();
	worldTransform_.translation_ = position;
	worldTransform_.rotation_ = rotation;
	//�r���[�v���W�F�N�V�����̏�����
	viewProjection_.farZ = 2000.0f;
	viewProjection_.Initialize();
	worldTransform_.Initialize();
}

void RailCamera::Update()
{


	
//���[���h�g�����X�t�H�[���̍��W�̐��l�����Z�����肷��(�ړ�)
	worldTransform_.translation_ += Vector3(0, 0, 0.1f);

	//���[���h�g�����X�t�H�[���̊p�x�̐��l�����Z�����肷��(��])
	 //woldTransform_.rotation_+=Vector3(0,0.1f,0);
	//���[���h�g�����X�t�H�[���̃��[���h�s��̍Čv�Z

	//worldTransform_.translation_ += MoveTrans;
	//worldTransform_.rotation_ += MoveRota;



	//worldTransform_.matWorld_.MatrixUpdate(worldTransform_.scale_,worldTransform_.rotation_,worldTransform_.translation_);

	//worldTransform_.MatrixUpdate();
	vectorMove_->MyUpdate(worldTransform_);

	//viewProjection_.eye = worldTransform_.translation_;
	//���[���h�s��̕��s�ړ��������擾
	viewProjection_.eye.x = worldTransform_.matWorld_.m[3][0];
	viewProjection_.eye.y = worldTransform_.matWorld_.m[3][1];
	viewProjection_.eye.z = worldTransform_.matWorld_.m[3][2];

	Vector3 forward(0, 0, 1);
	forward = MathUtility::Vector3TransformNormal(forward,worldTransform_.matWorld_);

	//forward = worldTransform_.matWorld_.direction(forward, worldTransform_.matWorld_);
	viewProjection_.target =viewProjection_.eye+forward;

	Vector3 up(0, 1, 0);

	viewProjection_.up = MathUtility::Vector3TransformNormal(up,worldTransform_.matWorld_);
	//viewProjection_.up = worldTransform_.matWorld_.direction(up, worldTransform_.matWorld_);

	//�r���[�v���W�F�N�V�����̍X�V�ƒ萔�o�b�t�@�ւ̓]��
	viewProjection_.UpdateMatrix();


	DebugText* debugText_ = DebugText::GetInstance();

	debugText_->SetPos(70, 300);
	debugText_->Printf("RailCamera Pos:(%f,%f,%f)",viewProjection_.eye.x,viewProjection_.eye.y,viewProjection_.eye.z );
}

