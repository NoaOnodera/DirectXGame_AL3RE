#pragma once
#include "Model.h"
#include "DebugText.h"
#include "EnemyBullet.h"
#include "WorldTransform.h"
#include "ViewProjection.h"
#include "GameScene.h"
//���@�N���X�̑O���錾
class Player;
class GameScene;


enum class Phase {
	Approch,//�ڋ߂���
	Leave,//���E����
};

class Enemy {
public:
	 Enemy();
	 ~Enemy();
	void Initialize(Model* model,WorldTransform worldTransform);
	void Update();
	void Draw(ViewProjection& viewProjection);
	void ApprochMove();
	void LeaveMove();
	void Fire();
	void SetPlayer(Player* player) { player_ = player; }
	
	bool IsDead()const { return isDead_; }
	//�Փ˂����o������Ăяo�������R�[���o�b�N�֐�
	void OnCollision();
	Vector3 GetWorldPosition();
	Vector3 GetRadius();
	//���ˊ��o
	static const int kFireInterval = 60;
	const std::list<std::unique_ptr<EnemyBullet>>& GetBullets() { return bullets_; };
	void SetGameScene(GameScene* gameScene) { gameScene_ = gameScene; };

	
private:
	//���[���h�ϊ��f�[�^
	WorldTransform worldTransform_;
	//���f��
	Model* model_ = nullptr;
	//�e�N�X�`���n���h��
	uint32_t textureHandle_ = 0u;
	



	std::list<std::unique_ptr<EnemyBullet>>bullets_;


	//�f�o�b�O�e�L�X�g
	DebugText* debugText_ = nullptr;


	//MyMath* myMath_ = nullptr;

	int32_t eFireTime = 60;

	VectorMove* vectorMove_ = nullptr;
	
	

	Player* player_ = nullptr;

	bool isDead_ = false;

	
	//�e���X�g���擾
	
	//�t�F�[�Y
	Phase phase_ = Phase::Approch;

	
	GameScene* gameScene_ = nullptr;
	
};