#pragma once

#ifndef __BOSS_H__
#define __BOSS_H__

#include "Obj.h"
class CBoss : public CObj
{
public:
	CBoss();
	virtual ~CBoss();

	// CObj��(��) ���� ��ӵ�
	virtual void Initialize() override = 0;
	virtual int Update() override = 0;
	virtual void Late_Update() override = 0;
	virtual void Render(HDC hDC) override = 0;
	virtual void Release() override = 0;

protected:
	template <typename T>
	CObj* Create_Bullet(float _x, float _y, float _fAngle = 0.f)
	{
		CObj* pObj = CAbstractFactory<T>::Create(_x, _y, _fAngle);
		return pObj;
	}

	virtual void Move(){}
	virtual void Attack(){}
};


#endif