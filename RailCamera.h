#pragma once
#include "WorldTransform.h"
#include "ViewProjection.h"
#include "DebugText.h"
#include "VectorMove.h"
#include "player.h"
class RailCamera {
public:
	RailCamera();
	~RailCamera();
	void Initialize(const Vector3&position,const Vector3&rotation);

	void Update();



	//ビュープロジェクションを取得
	const ViewProjection& GetViewProjection() { return viewProjection_; }

	//ワールド行列の取得
	const WorldTransform& GetWorldMatrix()const { return worldTransform_; }

	WorldTransform* GetWorldTransform() { return &worldTransform_; }
private:
//ワールド変換データ
	WorldTransform worldTransform_;
//ビュープロジェクション
	ViewProjection viewProjection_;

	//デバッグテキスト
	DebugText* debugText_ = nullptr;

	VectorMove* vectorMove_ = nullptr;
};
