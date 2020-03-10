#pragma once

#ifndef __BOSS_H__
#define __BOSS_H__

#include "Obj.h"
class CBoss : public CObj
{
public:
	CBoss();
	virtual ~CBoss();

	// CObj을(를) 통해 상속됨
	virtual void Initialize() override = 0;
	virtual int Update() override = 0;
	virtual void Late_Update() override = 0;
	virtual void Render(HDC hDC) override = 0;
	virtual void Release() override = 0;

protected:
	//RECT m_tRect; 
	D3DXVECTOR3 m_vPoint[4]; // Q
	D3DXVECTOR3 m_vOrigin[4]; // P

	float m_fAngle;
	float m_fSpeed;
};


#endif