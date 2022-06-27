#pragma once
#include "Model.h"
#include "DebugText.h"
#include "VectorMove.h"
#include "EnemyBullet.h"
enum class Phase {
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
	void ApprochMove();
	void LeaveMove();
	void Fire();

	//���ˊ��o
	static const int kFireInterval = 60;
private:
	//���[���h�ϊ��f�[�^
	WorldTransform worldTransform_;
	//���f��
	Model* model_ = nullptr;
	//�e�N�X�`���n���h��
	uint32_t textureHandle_ = 0u;
	
	int32_t eFireTime = 0;
	VectorMove* vectorMove_ = nullptr;
	
	//�t�F�[�Y
	Phase phase_ = Phase::Approch;

	std::list<std::unique_ptr<EnemyBullet>>bullets_;
	EnemyBullet* bullet_ = nullptr;
};