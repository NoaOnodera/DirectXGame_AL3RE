#pragma once
#include "Model.h"
#include "DebugText.h"
#include "EnemyBullet.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include "MyMath.h"
#include "Vector3.h"
#include "player.h"
//���@�N���X�̑O���錾
class Player;
//�Q�[���V�[���N���X�̑O���錾
class GameScene;

enum class Phase {
	Approch,//�ڋ߂���
	Leave,//���E����
};

class Enemy {
public:
	 Enemy();//�G�̃R���X�g���N�^�[

	 ~Enemy();//�G�̃f�X�g�X�g���N�^�[

	void Initialize(Model* model, uint32_t textureHandle,const Vector3& position);//������

	void Update();//�X�V

	void Draw(ViewProjection& viewProjection);//�`��

	void ApprochMove();//�ڋ߃t�F�[�Y

	void LeaveMove();//�ޔ��t�F�[�Y

	void Fire();//�e�̔���

	void SetPlayer(Player* player) { player_ = player; }//�v���C���[�̃Z�b�^�[
	
	void OnCollision();//�Փ˂����o������Ăяo�������R�[���o�b�N�֐�

	Vector3 GetWorldPosition();//���[���h���W�̎擾

	Vector3 GetRadius();//���[���h���W���a�̎擾

	void SetGameScene(GameScene* gameScene) { gameScene_ = gameScene; };//�Q�[���V�[���̃Z�b�^�[

	bool IsDead() const { return isDead_; };//�f�X�t���O�̃Q�b�^�[
	
	static const int kFireInterval = 60;//���ˊ��o

private:
	//���[���h�ϊ��f�[�^
	WorldTransform worldTransform_;
	//���f��
	Model* model_ = nullptr;
	//�e�N�X�`���n���h��
	uint32_t textureHandle_ = 0u;
	
	//�f�o�b�O�e�L�X�g
	DebugText* debugText_ = nullptr;

	MyMath* myMath_ = nullptr;//�N�����v�֐�

	
	
	int32_t eFireTime = 60;//�G�̔��˃^�C�}�[

	VectorMove* vectorMove_ = nullptr;//�s��̌v�Z

	Player* player_ = nullptr;//���L����

	std::list<std::unique_ptr<EnemyBullet>>bullets_;
	
	GameScene* gameScene_ = nullptr;//�Q�[���V�[��
	//�t�F�[�Y
	Phase phase_ = Phase::Approch;

	bool isDead_ = false;//�f�X�t���O

	
};