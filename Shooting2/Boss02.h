#pragma once
#include "Boss.h"
class CBoss02 :
	public CBoss
{
public:
	CBoss02();
	virtual ~CBoss02();

private:
	enum STATE { IDLE, START, ATTACK, ATTACK1, ATTACK2, ATTACK3, END };

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

private:
	D3DXVECTOR3 m_vPoint[6]; // Q
	D3DXVECTOR3 m_vOrigin[6]; // P
	//D3DXVECTOR3		m_vPosin[6];
	//D3DXVECTOR3		m_vOriginPosin[6];
	STATE			m_eState;

	DWORD			m_dwLastAttTime;
	DWORD			m_dwAttDelay;
	DWORD			m_dwAttTime;
	DWORD			m_dwBulletTime;

	int				iPattern;
};

