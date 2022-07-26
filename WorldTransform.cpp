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

	

	TransferMatrix();
}