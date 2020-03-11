#pragma once
#include "Boss.h"
class CBoss02 :
	public CBoss
{
public:
	CBoss02();
	virtual ~CBoss02();

private:
	enum STATE { IDLE, START, ATTACK, ATTACK1, ATTACK2, ATTACK3, ATTACK4, ATTACK5, END };
	enum PHASE { PHASE1, PHASE2, PHASE3, PHASE4, PHASE5, PHASE_END };
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
	void Attack4();
	void Attack5();


private:
	D3DXVECTOR3 m_vPoint[6]; // Q
	D3DXVECTOR3 m_vOrigin[6]; // P
							  //D3DXVECTOR3		m_vPosin[6];
							  //D3DXVECTOR3		m_vOriginPosin[6];
	STATE			m_eState;
	PHASE			m_ePhase;
	DWORD			m_dwLastAttTime;
	DWORD			m_dwAttDelay;
	DWORD			m_dwAttTime;
	DWORD			m_dwBulletTime;
	DWORD			m_dwBulletTime2;
	int				iPattern;
	float		m_fAngle2;
	bool			m_bDir;
};

