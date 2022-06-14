#pragma once
#include"Player.h"
#include "Model.h"
#include "Input.h" 
#include "WorldTransform.h"
#include "ViewProjection.h"
#include"TextureManager.h"
#include "VectorMove.h"
#include "MyMath.h"

class PlayerBullet {
public:
	PlayerBullet();
	~PlayerBullet();
	void Initialize(Model*model,const Vector3& position);
	void Update();
	void Draw(const ViewProjection& viewProjection);
private:
	//���[���h�ϊ��f�[�^
	 WorldTransform worldTransform_;
	//���f���̃|�C���^(�؂�Ă���)
	Model* model_ = nullptr;
	//�e�N�X�`���n���h��
	uint32_t textureHandle_ = 0u;


	VectorMove* vectorMove_ = nullptr;


};