#pragma once

#ifndef __RAZER_H__
#define __RAZER_H__

#include "Bullet.h"
class CRazer : public CBullet
{
private:
	DWORD		m_dwDeltaTime;
	DWORD		m_dwAttTime;

public:
	CRazer();
	virtual ~CRazer();

	// CObj을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;

	void Set_PosX(float _x) { m_tInfo.vPos.x = _x; }

private:
	template <typename T>
	CObj* Create_Bullet(float _x, float _y, float _fAngle = 0.f)
	{
		CObj* pObj = CAbstractFactory<T>::Create(_x, _y, _fAngle);
		return pObj;
	}
};

#endif // !__RAZER_H__
