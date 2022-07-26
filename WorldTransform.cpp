#include "WorldTransform.h"

void WorldTransform::MatrixUpdate()
{
	Initialize();

	matWorld_.MatrixUpdate
	(
		scale_,
		rotation_,
		translation_
	);

	if (parent_)
	{
		matWorld_ *= parent_->matWorld_;


	}

	TransferMatrix();
}