#pragma once

#ifndef __BOSS00BULLET2_H__
#define __BOSS00BULLET2_H__

#include "Bullet.h"
class CBoss00Bullet2 :
	public CBullet
{
private:
	D3DXVECTOR3		m_vPoint[8]; // Q
	D3DXVECTOR3		m_vOrigin[8]; // P

	int				m_iRand;

public:
	CBoss00Bullet2();
	virtual ~CBoss00Bullet2();

public:
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;
};

#endif // !__BOSS00BULLET2_H__
