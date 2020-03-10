#pragma once
#include "Bullet.h"
class CDelayBullet :
	public CBullet
{
public:
	CDelayBullet();
	virtual ~CDelayBullet();

	virtual void Initialize() override;
	virtual int Update() override;

private:
	DWORD m_dwLastTime;
	DWORD m_dwDelay;

	bool m_bMove{ false };
};

