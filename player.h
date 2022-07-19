#pragma once
#include "Model.h"
#include "WorldTransform.h"
#include "DebugText.h"
#include "Input.h"
#include "WorldTransform.h"
#include "ViewProjection.h"
#include "TextureManager.h"
#include "VectorMove.h"
#include "MyMath.h"
#include "PlayerBullet.h"
#include <memory>
#include <list>


class Player {
public:


	 Player();
    ~Player();
	void Rotate();
	void Initialize(Model*model,uint32_t textureHandle);
	void Update();
	void Draw(ViewProjection&viewProjection);
	void Attack();

	//�Փ˂����o������Ăяo�������R�[���o�b�N�֐�
	void OnCollision();
	Vector3 GetWorldPosition();
	Vector3 GetRadius();
	//�e���X�g���擾
	const std::list<std::unique_ptr<PlayerBullet>>& GetBullets() { return bullets_; }

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

	
	std::list<std::unique_ptr<PlayerBullet>>bullets_;
	
	
	
	
};