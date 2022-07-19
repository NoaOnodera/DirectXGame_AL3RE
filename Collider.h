#pragma once

class Collider {
public:
	Collider() ;
	~Collider() ;


	bool OnBulletCollision(int a_PosX, int a_PosY, int a_PosZ, int a_PosR, int b_PosX, int b_PosY, int b_PosZ, int b_PosR);
};