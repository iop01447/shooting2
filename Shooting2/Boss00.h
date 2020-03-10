#pragma once

#ifndef __BOSS00_H__
#define __BOSS00_H__

#include "Boss.h"
class CBoss00 :
	public CBoss
{
private:
	enum STATE { IDLE, START, ATTACK, ATTACK1, ATTACK2, ATTACK3, STATE_END };
	enum DIR { LEFT, RIGHT, DIR_END };

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
	void Attack1();
	void Attack2();
	void Attack3();

	void BackStartPos();

private:
	STATE			m_eState;
	DIR				m_eDir;

	D3DXVECTOR3		m_vStart;
	D3DXVECTOR3		m_vPoint[4]; // Q
	D3DXVECTOR3		m_vOrigin[4]; // P
	D3DXVECTOR3		m_vPosin[3];
	D3DXVECTOR3		m_vOriginPosin[3];

	DWORD			m_dwLastAttTime;
	DWORD			m_dwAttDelay;
	DWORD			m_dwAttTime;

	int				m_iCount;

	list<CObj*>*	m_listBullet;
};

#endif // !__BOSS00_H__
