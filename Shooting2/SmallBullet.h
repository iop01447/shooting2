#pragma once

#ifndef __SMALLBULLET_H__
#define __SMALLBULLET_H__

#include "Bullet.h"
class CSmallBullet :
	public CBullet
{
private:
	D3DXVECTOR3		m_vCenter;
	float			m_fRotDis;

public:
	CSmallBullet();
	virtual ~CSmallBullet();

	// CObj을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;
};

#endif // !__SMALLBULLET_H__
