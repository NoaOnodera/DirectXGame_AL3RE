#include "MyMath.h"

//�R���X�g���N�^
MyMath::MyMath() {}

//�f�X�g���N�^-
MyMath::~MyMath() {
}


//�����o�֐�
float MyMath::MinNum(float min, float num)
{
	//�����ŏ��l���傫���Ȃ�
	if (min < num)
	{
		//�ŏ��l��Ԃ�
		return min;

	}
	//�����ŏ��l�ɂ�菬�����Ȃ�
	//�ŏ��l��Ԃ�
	return num;
}

float MyMath::MaxNum(float max, float num)
{
	//�����ő�l��菬�����Ȃ�
	if (num < max)
	{
		//�ő�l��Ԃ�
		return max;

	}
	//�����ő�l���傫���Ȃ�
	//�ő�l��Ԃ�
	return num;
}

float Clamp(float min, float max, float num)
{
	//�����ŏ��l���傫��
	if (min < num)
	{
		//�ŏ��l��Ԃ�
		return min;
	}
	//�����ő�l��菬��������
	if (num < max)
	{
		//�ő�l��Ԃ�
		return max;
	}
	//�����̏����ɓ��Ă͂܂�Ȃ����
	//�l��Ԃ�
	return num;

}