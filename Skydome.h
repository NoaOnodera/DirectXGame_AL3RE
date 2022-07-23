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

	void Draw(ViewProjection& viewProjection);

	void Update();
private:
	WorldTransform worldTransform_;

	Model* model_ = nullptr;

	VectorMove* vectorMove_ = nullptr;
	//�f�o�b�O�e�L�X�g
	DebugText* debugText_ = nullptr;
};
