#pragma once
#include "Bullet.h"
class CPlayerBullet :
	public CBullet
{
public:
	CPlayerBullet();
	virtual ~CPlayerBullet();

	virtual void Initialize() override;
};

