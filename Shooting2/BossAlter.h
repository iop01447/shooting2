#pragma once
#include "Obj.h"

class CBossAlter :
	public CObj
{
public:
	CBossAlter();
	virtual ~CBossAlter();

	// CObj을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;

	virtual void Set_Damage(int _iAtt) { if (!m_bGrayMode) m_tStatus.iHp -= _iAtt; }

	void Move();
	void Attack();

public:
	void Set_GoalPos(float _fX, float _fY);
	bool Get_GrayMode(){ return m_bGrayMode; }
	bool Get_Finish() { return m_bFinish; }

private:
	void Check_GrayMode();

private:
	bool m_bTransition{ false };
	bool m_bGrayMode{ false };
	bool m_bFinish{ false };

	DWORD		m_dwLastAttTime;
	DWORD		m_dwAttDelay;
	DWORD		m_dwLastGrayOnTime;
	DWORD		m_dwGrayTime{ 5000 };

	D3DXVECTOR3 m_vGoalPos;
	D3DXVECTOR3 m_vLookOrigin;
	D3DXVECTOR3 m_vPosin;

	D3DXVECTOR3 m_vPoint[4]; // Q
	D3DXVECTOR3 m_vOrigin[4];// P

	float		m_fAddAngle{ 3 };

};

