#pragma once
#include "WorldTransform.h"
#include "ViewProjection.h"
#include "DebugText.h"
#include "VectorMove.h"
#include "player.h"
class RailCamera {
public:
	RailCamera();
	~RailCamera();
	void Initialize(const Vector3&position,const Vector3&rotation);

	void Update();



	//�r���[�v���W�F�N�V�������擾
	const ViewProjection& GetViewProjection() { return viewProjection_; }

	//���[���h�s��̎擾
	const WorldTransform& GetWorldMatrix()const { return worldTransform_; }

	WorldTransform* GetWorldTransform() { return &worldTransform_; }
private:
//���[���h�ϊ��f�[�^
	WorldTransform worldTransform_;
//�r���[�v���W�F�N�V����
	ViewProjection viewProjection_;

	//�f�o�b�O�e�L�X�g
	DebugText* debugText_ = nullptr;

	VectorMove* vectorMove_ = nullptr;
};
