#pragma once
#include "Model.h"
#include "WorldTransform.h"
#include"TextureManager.h"
#include "VectorMove.h"
#include "DebugText.h"



class EnemyBullet {
public:
	EnemyBullet();
	~EnemyBullet();
	void Initialize(Model* model, const Vector3& position, const Vector3& velocity);
	void Update();
	//�Փ˂����o������Ăяo�������R�[���o�b�N�֐�
	void OnCollision();
	Vector3 GetWorldPosition();
	Vector3 GetRadius();
	void Draw(const ViewProjection& viewProjection);
	bool IsDead() const { return isDead_; }
private:

	//���[���h�ϊ��f�[�^
	WorldTransform worldTransform_;
	//���f���̃|�C���^(�؂�Ă���)
	Model* model_ = nullptr;
	//�e�N�X�`���n���h��
	uint32_t textureHandle_ = 0u;
	//���x
	Vector3 velocity_;

	DebugText* debugText_ = nullptr;
	VectorMove* vectorMove_ = nullptr;
	//����<frm>
	static const int32_t eLifeTime = 60 * 5;
	//�f�X�^�C�}�[
	int32_t deathTimer_ = eLifeTime;
	//�f�X�t���O
	bool isDead_ = false;
};