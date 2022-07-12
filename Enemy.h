#pragma once
#include "Model.h"
#include "DebugText.h"
#include "EnemyBullet.h"

//���@�N���X�̑O���錾
class Player;

enum class Phase {
	Approch,//�ڋ߂���
	Leave,//���E����
};

class Enemy {
public:
	 Enemy();
	 ~Enemy();
	void Initialize(Model* model,uint32_t textureHandle);
	void Update();
	void Draw(ViewProjection& viewProjection);
	void ApprochMove();
	void LeaveMove();
	void Fire();
	void SetPlayer(Player* player) { player_ = player; }
	//�Փ˂����o������Ăяo�������R�[���o�b�N�֐�
	void OnCollision();
	Vector3 GetWorldPosition();
	//���ˊ��o
	static const int kFireInterval = 60;
	const std::list<std::unique_ptr<EnemyBullet>>& GetBullets() { return bullets_; }
private:
	//���[���h�ϊ��f�[�^
	WorldTransform worldTransform_;
	//���f��
	Model* model_ = nullptr;
	//�e�N�X�`���n���h��
	uint32_t textureHandle_ = 0u;
	
	//�f�o�b�O�e�L�X�g
	DebugText* debugText_ = nullptr;

	//MyMath* myMath_ = nullptr;

	int32_t eFireTime = 60;

	VectorMove* vectorMove_ = nullptr;
	Player* player_ = nullptr;
	std::list<std::unique_ptr<EnemyBullet>>bullets_;
	

	//�e���X�g���擾
	
	//�t�F�[�Y
	Phase phase_ = Phase::Approch;

	

	
};