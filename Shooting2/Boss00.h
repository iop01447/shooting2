#pragma once

#ifndef __BOSS00_H__
#define __BOSS00_H__

#include "Boss.h"
class CBoss00 :
	public CBoss
{
public:
	CBoss00();
	virtual ~CBoss00();

public:
	// CBoss을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;

	// CBoss을(를) 통해 상속됨
	virtual void Move() override;
	virtual void Attack() override;

private:
	D3DXVECTOR3 m_vPoint[4]; // Q
	D3DXVECTOR3 m_vOrigin[4]; // P
	D3DXVECTOR3 m_vPosin;
	D3DXVECTOR3 m_vOriginPosin;

	DWORD		m_dwLastAttTime;
	DWORD		m_dwAttDelay;
};

#endif // !__BOSS00_H__
