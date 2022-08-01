#pragma once
#include "Model.h"
#include "WorldTransform.h"
#include "ViewProjection.h"
#include"TextureManager.h"
#include "VectorMove.h"
#include "DebugText.h"
#include "MyMath.h"
#include "Vector3.h"



class EnemyBullet {
public:
	EnemyBullet();//�R���X�g���N�^�[

	~EnemyBullet();//�f�X�g���N�^�[

	void Initialize(Model* model, const Vector3& position, const Vector3& velocity);//������

	void Update();//�X�V

	void Draw(const ViewProjection& viewProjection);//�`��

	bool IsDead() const { return isDead_; };//�f�X�t���O�̃Q�b�^�[
	
	void OnCollision();//�Փ˂����o������Ăяo�������R�[���o�b�N�֐�

	Vector3 GetWorldPosition();//���[���h���W�̎擾
	Vector3 GetRadius();//���[���h���W�̔��a�̎擾

	
	
private:

	//���[���h�ϊ��f�[�^
	WorldTransform worldTransform_;
	//���f���̃|�C���^(�؂�Ă���)
	Model* model_ = nullptr;
	//�e�N�X�`���n���h��
	uint32_t textureHandle_ = 0u;
	//�f�o�b�N�e�L�X�g
	DebugText* debugText_ = nullptr;
	//�s��̌v�Z
	VectorMove* vectorMove_ = nullptr;
	//���x
	Vector3 velocity_;
	//����<frm>
	static const int32_t eLifeTime = 60 * 5;
	//�f�X�^�C�}�[
	int32_t deathTimer_ = eLifeTime;
	//�f�X�t���O
	bool isDead_ = false;
};