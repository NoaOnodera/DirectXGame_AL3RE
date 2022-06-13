#pragma once
#include "GameScene.h"


class Player {
public:
	void Initialize(Model*model,uint32_t textureHandle);
	void Update();
	void Draw();

private:
	//���[���h�ϊ��f�[�^
	WorldTransform worldTransform_;
	//���f��
	Model* model_ = nullptr;
	//�e�N�X�`���n���h��
	uint32_t textureHandle_ = 0u;

	Input* input_ = nullptr;
	DebugText* debugText_ = nullptr;
};