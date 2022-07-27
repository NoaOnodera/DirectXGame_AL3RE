#include "RailCamera.h"
void RailCamera::Initialize(const Vector3& position,const Vector3& rotation)
{
	//ワールドトランスフォームの初期化

	//worldTransform_.Initialize();
	worldTransform_.translation_ = position;
	worldTransform_.rotation_ = rotation;
	//ビュープロジェクションの初期化
	viewProjection_.farZ = 2000.0f;
	viewProjection_.Initialize();
	worldTransform_.Initialize();
}

void RailCamera::Update()
{


	
//ワールドトランスフォームの座標の数値ヲ加算したりする(移動)
	worldTransform_.translation_ += Vector3(0, 0, 0.1f);

	//ワールドトランスフォームの角度の数値を加算したりする(回転)
	 //woldTransform_.rotation_+=Vector3(0,0.1f,0);
	//ワールドトランスフォームのワールド行列の再計算

	//worldTransform_.translation_ += MoveTrans;
	//worldTransform_.rotation_ += MoveRota;



	//worldTransform_.matWorld_.MatrixUpdate(worldTransform_.scale_,worldTransform_.rotation_,worldTransform_.translation_);

	//worldTransform_.MatrixUpdate();
	vectorMove_->MyUpdate(worldTransform_);

	//viewProjection_.eye = worldTransform_.translation_;
	//ワールド行列の平行移動成分を取得
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

	//ビュープロジェクションの更新と定数バッファへの転送
	viewProjection_.UpdateMatrix();


	DebugText* debugText_ = DebugText::GetInstance();

	debugText_->SetPos(70, 300);
	debugText_->Printf("RailCamera Pos:(%f,%f,%f)",viewProjection_.eye.x,viewProjection_.eye.y,viewProjection_.eye.z );
}

