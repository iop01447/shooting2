#pragma once
#include "Boss.h"

class CObj;
class CBoss01 :
	public CBoss
{
public:
	CBoss01();
	virtual ~CBoss01();

	// CBoss을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;

public:
	int wrap(int x, int low, int high);

private:
	// Update
	void KeyCheck();

	void Pattern();
	void Set_Pattern(int _iPatter);
	void Pattern00(); // 사방팔방 쏘기
	void Pattern01(); // 분신이 크리스마스트리 쏘기
	void Pattern02(); // 총알 지진 후 플레이어 쪽으로 이동
	void Pattern03(); // 레이저
	void Pattern04(); // 꽃

private:
	void AlterMode_On();
	void AlterMode_Off();

private:
	D3DXVECTOR3 m_vPoint[4]; // Q
	D3DXVECTOR3 m_vOrigin[4];// P
	D3DXVECTOR3 m_vPosin;

	D3DXVECTOR3 m_vLookOrigin;

	DWORD		m_dwLastAttTime;
	DWORD		m_dwAttDelay;

	DWORD		m_dwLastPatternChangeTime;
	DWORD		m_dwPatternTime;

	int			m_iPattern;
	const int	m_iMaxPattern{ 3 };

	//bool		m_bTest{ false };
	bool		m_bTransition{ false };
	bool		m_bAlterMode{ false };
	bool		m_bFirst{ true };

	CObj*		m_pAlter[2]{ nullptr };
	int			m_iAlterCnt{ 2 };

	int			m_iPhase{ 0 };
};

