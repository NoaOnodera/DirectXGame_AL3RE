#include "VectorMove.h"
#include <DirectXMath.h>

VectorMove::VectorMove() {

};

VectorMove::~VectorMove() {
}




#pragma region �X�P�[�����O





Matrix4 VectorMove::MyScale(WorldTransform& worldTransform_)
{
	//�X�P�[�����O

	Matrix4 matScale;//�X�P�[�����O�s���錾

	matScale.IdentityMatrix();
	//�X�P�[�����O�{�����s��ɐݒ肷��
	matScale.m[0][0] = worldTransform_.scale_.x;
	matScale.m[1][1] = worldTransform_.scale_.y;
	matScale.m[2][2] = worldTransform_.scale_.z;
	matScale.m[3][3] = 1;

	return matScale;
}
#pragma endregion

#pragma region ��]�p

Matrix4 VectorMove::MyRotZ(WorldTransform& worldTransform_)
{
	Matrix4 matRotZ;



	matRotZ.IdentityMatrix();
	//Z����]�s��̊e�v�f��ݒ肷��
	matRotZ.m[0][0] = cosf(worldTransform_.rotation_.z);
	matRotZ.m[0][1] = sinf(worldTransform_.rotation_.z);
	matRotZ.m[1][0] = -sinf(worldTransform_.rotation_.z);
	matRotZ.m[1][1] = cosf(worldTransform_.rotation_.z);
	matRotZ.m[2][2] = 1;
	matRotZ.m[3][3] = 1;

	return matRotZ;
}

Matrix4 VectorMove::MyRotX(WorldTransform& worldTransform_)
{


	Matrix4 matRotX;

	matRotX.IdentityMatrix();
	//X����]�s��̊e�v�f��ݒ肷��
	matRotX.m[0][0] = 1;
	matRotX.m[1][1] = cosf(worldTransform_.rotation_.x);
	matRotX.m[1][2] = sinf(worldTransform_.rotation_.x);
	matRotX.m[2][1] = -sinf(worldTransform_.rotation_.x);
	matRotX.m[2][2] = cosf(worldTransform_.rotation_.x);
	matRotX.m[3][3] = 1;


	return matRotX;

}

Matrix4 VectorMove::MyRotY(WorldTransform& worldTransform_)
{
	Matrix4 matRotY;

	matRotY.IdentityMatrix();
	//Y����]�s��̊e�v�f��ݒ肷��
	matRotY.m[0][0] = cosf(worldTransform_.rotation_.y);
	matRotY.m[1][1] = 1;
	matRotY.m[0][2] = -sinf(worldTransform_.rotation_.y);
	matRotY.m[2][0] = sinf(worldTransform_.rotation_.y);
	matRotY.m[2][2] = cosf(worldTransform_.rotation_.y);
	matRotY.m[3][3] = 1;



	return matRotY;
}



#pragma endregion 	


#pragma region ���s�ړ�

Matrix4 VectorMove::MyTrans(WorldTransform& worldTransform_)
{
	//���s�ړ��s���錾
	Matrix4 matTrans;

	matTrans.IdentityMatrix();

	//�ړ��ʂ��s��ɐݒ肷��
	matTrans.m[0][0] = 1;
	matTrans.m[1][1] = 1;
	matTrans.m[2][2] = 1;
	matTrans.m[3][3] = 1;
	matTrans.m[3][0] = worldTransform_.translation_.x;
	matTrans.m[3][1] = worldTransform_.translation_.y;
	matTrans.m[3][2] = worldTransform_.translation_.z;


	return matTrans;

}
#pragma endregion



Matrix4 VectorMove::MyUpdate(WorldTransform& worldTransform_)
{


	Matrix4 mat;
	mat.IdentityMatrix();
	worldTransform_.matWorld_ = mat;

	//�X�P�[�����O
	Matrix4 matScale = VectorMove::MyScale(worldTransform_);
	Matrix4 matRotZ = VectorMove::MyRotZ(worldTransform_);
	Matrix4 matRotX = VectorMove::MyRotX(worldTransform_);
	Matrix4 matRotY = VectorMove::MyRotY(worldTransform_);
	Matrix4 matTrans = VectorMove::MyTrans(worldTransform_);
	//�X�P�[�����O�E��]�E���s�ړ������������s����v�Z���ă��[���h�g�����X�t�H�[���ɑ��zz

	worldTransform_.matWorld_ *= matScale;//�|���Z


	worldTransform_.matWorld_ *= matRotZ;//�|���Z


	worldTransform_.matWorld_ *= matRotX;//�|���Z


	worldTransform_.matWorld_ *= matRotY;//�|���Z



	worldTransform_.matWorld_ *= matTrans;//�|���Z

		//�s��̓]��
	worldTransform_.TransferMatrix();

	return worldTransform_.matWorld_;
}




