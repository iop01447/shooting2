#pragma once
#include "Boss02Bullet.h"
class CRazerBullet :
	public CBoss02Bullet
{
public:
	CRazerBullet();
	virtual ~CRazerBullet();
public:
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;
};

