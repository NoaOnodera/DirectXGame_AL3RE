#pragma once
#include"Matrix4.h"
#include "WorldTransform.h"
class VectorMove {
public:
	VectorMove();
	~VectorMove();


	Matrix4 MyScale(WorldTransform& worldTransform_);
	Matrix4 MyRotX(WorldTransform& worldTransform_);
	Matrix4 MyRotY(WorldTransform& worldTransform_);
	Matrix4 MyRotZ(WorldTransform& worldTransform_);
	Matrix4 MyUpdate(WorldTransform& worldTransform_);
	Matrix4 MyTrans(WorldTransform& worldTransform_);
};