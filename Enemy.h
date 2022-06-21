#pragma once
#include "Model.h"
#include "DebugText.h"
#include "VectorMove.h"

enum class Phase {
	Initial,//����
	Approch,//�ڋ߂���
	Leave,//���E����
};

class Enemy {
public:
	 Enemy();
	 ~Enemy();
	void Initialize(Model* model,uint32_t textureHandle);
	void Move();
	void Update();
	void Draw(const ViewProjection& viewProjection);
private:
	//���[���h�ϊ��f�[�^
	WorldTransform worldTransform_;
	//���f��
	Model* model_ = nullptr;
	//�e�N�X�`���n���h��
	uint32_t textureHandle_ = 0u;
	
	VectorMove* vectorMove_ = nullptr;
	
	//�t�F�[�Y
	Phase phase_ = Phase::Initial;
	
};