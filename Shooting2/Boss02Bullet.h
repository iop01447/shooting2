#pragma once
#include "Bullet.h"
class CBoss02Bullet :
	public CBullet
{
public:
	CBoss02Bullet();
	virtual ~CBoss02Bullet();

	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;
};

