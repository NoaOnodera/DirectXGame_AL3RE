#pragma once
#include "GameScene.h"
#include "WorldTransform.h"
#include "Model.h"
#include "Input.h" 
#include "WorldTransform.h"
#include "ViewProjection.h"
#include"TextureManager.h"
#include "VectorMove.h"
#include "MyMath.h"
#include "PlayerBullet.h"

class Player {
public:


	 Player();
    ~Player();
	void Rotate();
	void Initialize(Model*model,uint32_t textureHandle);
	void Update();
	void Draw(ViewProjection&viewProjection);
	void Attack();
private:
	//���[���h�ϊ��f�[�^
	WorldTransform worldTransform_;
	//���f��
	Model* model_ = nullptr;
	//�e�N�X�`���n���h��
	uint32_t textureHandle_ = 0u;
	//���͏��������邽��
	Input* input_ = nullptr;
	//�f�o�b�O�e�L�X�g
	DebugText* debugText_ = nullptr;
	
	MyMath* myMath_ = nullptr;
    
	VectorMove* vectorMove_ = nullptr;

	//�e
	PlayerBullet* bullet_ = nullptr;


	
};