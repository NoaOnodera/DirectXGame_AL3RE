#pragma once
///<summary>
///���삵�����w�N���X
/// </summary>

class MyMath {
public:
	//�R���X�g���N�^
	MyMath();
	//�f�X�g���N�^�[
	~MyMath();

	//�����o�֐�

	///<summary>
	///�ŏ��l
	/// </summary>

	float MinNum(float min, float num);
	float MaxNum(float min, float num);
	float Clamp(float min, float max, float num);
};