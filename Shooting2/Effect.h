#pragma once

#ifndef __EFFECT_H__
#define __EFFECT_H__

#include "Obj.h"
class CEffect :
	public CObj
{
private:
	DWORD		m_dwDeltaTime;
	DWORD		m_dwDeadTime;

public:
	CEffect();
	virtual ~CEffect();

public:
	// CObj을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;
};

#endif // !__EFFECT_H__