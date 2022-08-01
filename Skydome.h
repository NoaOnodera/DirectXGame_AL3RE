#pragma once
#include "WorldTransform.h"
#include "ViewProjection.h"
#include "Model.h"
#include "VectorMove.h"
#include "DebugText.h"
class Skydome {

public:
	Skydome();

	~Skydome();

	void Initialize(Model* model);

	void Update();

	void Draw(ViewProjection& viewProjection);
private:
	WorldTransform worldTransform_;

	Model* model_ = nullptr;

	VectorMove* vectorMove_ = nullptr;
	//デバッグテキスト
	DebugText* debugText_ = nullptr;
};
