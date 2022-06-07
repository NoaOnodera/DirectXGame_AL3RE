#pragma once
///<summary>
///自作した数学クラス
/// </summary>

class MyMath {
public:
	//コンストラクタ
	MyMath();
	//デストラクター
	~MyMath();

	//メンバ関数

	///<summary>
	///最小値
	/// </summary>

	float MinNum(float min, float num);
	float MaxNum(float min, float num);
	float Clamp(float min, float max, float num);
};