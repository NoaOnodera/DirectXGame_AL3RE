#include "VectorMove.h"
#include <DirectXMath.h>

VectorMove::VectorMove() {

};

VectorMove::~VectorMove() {
}




#pragma region スケーリング





Matrix4 VectorMove::MyScale(WorldTransform& worldTransform_)
{
	//スケーリング

	Matrix4 matScale;//スケーリング行列を宣言

	matScale.IdentityMatrix();
	//スケーリング倍率を行列に設定する
	matScale.m[0][0] = worldTransform_.scale_.x;
	matScale.m[1][1] = worldTransform_.scale_.y;
	matScale.m[2][2] = worldTransform_.scale_.z;
	matScale.m[3][3] = 1;

	return matScale;
}
#pragma endregion

#pragma region 回転角

Matrix4 VectorMove::MyRotZ(WorldTransform& worldTransform_)
{
	Matrix4 matRotZ;



	matRotZ.IdentityMatrix();
	//Z軸回転行列の各要素を設定する
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
	//X軸回転行列の各要素を設定する
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
	//Y軸回転行列の各要素を設定する
	matRotY.m[0][0] = cosf(worldTransform_.rotation_.y);
	matRotY.m[1][1] = 1;
	matRotY.m[0][2] = -sinf(worldTransform_.rotation_.y);
	matRotY.m[2][0] = sinf(worldTransform_.rotation_.y);
	matRotY.m[2][2] = cosf(worldTransform_.rotation_.y);
	matRotY.m[3][3] = 1;



	return matRotY;
}



#pragma endregion 	


#pragma region 平行移動

Matrix4 VectorMove::MyTrans(WorldTransform& worldTransform_)
{
	//平行移動行列を宣言
	Matrix4 matTrans;

	matTrans.IdentityMatrix();

	//移動量を行列に設定する
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

	//スケーリング
	Matrix4 matScale = VectorMove::MyScale(worldTransform_);
	Matrix4 matRotZ = VectorMove::MyRotZ(worldTransform_);
	Matrix4 matRotX = VectorMove::MyRotX(worldTransform_);
	Matrix4 matRotY = VectorMove::MyRotY(worldTransform_);
	Matrix4 matTrans = VectorMove::MyTrans(worldTransform_);
	//スケーリング・回転・平行移動を合成した行列を計算してワールドトランスフォームに代入zz

	worldTransform_.matWorld_ *= matScale;//掛け算


	worldTransform_.matWorld_ *= matRotZ;//掛け算


	worldTransform_.matWorld_ *= matRotX;//掛け算


	worldTransform_.matWorld_ *= matRotY;//掛け算



	worldTransform_.matWorld_ *= matTrans;//掛け算

		//行列の転送
	worldTransform_.TransferMatrix();

	return worldTransform_.matWorld_;
}




