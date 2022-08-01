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
#include "Vector3.h"


class Player {
public:


	 Player();//�R���X�g���N�^�[

    ~Player();//�f�X�g���N�^�[

	void Rotate();//�v���C���[��]����

	void Initialize(Model*model,uint32_t textureHandle,WorldTransform worldTransform_,const Vector3& position);//������

	void Update();//�X�V

	void Draw(ViewProjection&viewProjection);//�`��

	void Attack();//�U��

	//�Փ˂����o������Ăяo�������R�[���o�b�N�֐�
	void OnCollision();

	Vector3 direction(const Vector3& velocity, const Matrix4& matWorld);
	Vector3 GetWorldPosition();
	Vector3 GetRadius();

	//�e���X�g���擾
	const std::list<std::unique_ptr<PlayerBullet>>& GetBullets() { return bullets_; }

	void setRailCamera(const WorldTransform& worldTransform) 
	{ worldTransform_.parent_ = &worldTransform; }//���[���J�����e�q�֌W

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

	std::list<std::unique_ptr<PlayerBullet>>bullets_;
	
	MyMath* myMath_ = nullptr;
    
	VectorMove* vectorMove_ = nullptr;
};