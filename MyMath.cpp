#include "MyMath.h"

//コンストラクタ
MyMath::MyMath() {}

//デストラクタ-
MyMath::~MyMath() {
}


//メンバ関数
float MyMath::MinNum(float min, float num)
{
	//もし最小値より大きいなら
	if (min < num)
	{
		//最小値を返す
		return min;

	}
	//もし最小値により小さいなら
	//最小値を返す
	return num;
}

float MyMath::MaxNum(float max, float num)
{
	//もし最大値より小さいなら
	if (num < max)
	{
		//最大値を返す
		return max;

	}
	//もし最大値より大きいなら
	//最大値を返す
	return num;
}

float Clamp(float min, float max, float num)
{
	//もし最小値より大きい
	if (min < num)
	{
		//最小値を返す
		return min;
	}
	//もし最大値より小さいから
	if (num < max)
	{
		//最大値を返す
		return max;
	}
	//これらの条件に当てはまらなければ
	//値を返す
	return num;

}