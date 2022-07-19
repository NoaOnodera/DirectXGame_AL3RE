#include "Collider.h"

Collider::Collider()
{

}

Collider::~Collider()
{

}



bool Collider::OnBulletCollision(int a_PosX, int a_PosY, int a_PosZ, int a_PosR, int b_PosX, int b_PosY, int b_PosZ, int b_PosR)
{
	if ((b_PosX - a_PosX) * (b_PosX - a_PosX) + (b_PosY - a_PosY) * (b_PosY - a_PosY) +
		(b_PosZ - a_PosZ) * (b_PosZ - a_PosZ) <= (a_PosR + b_PosR) * (a_PosR +b_PosR))
	{
		return true;
	}
	else
	{
		return false;
	}
}