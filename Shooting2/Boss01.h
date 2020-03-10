#pragma once
#include "Boss.h"
class CBoss01 :
	public CBoss
{
public:
	CBoss01();
	virtual ~CBoss01();

	// CBoss��(��) ���� ��ӵ�
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;

public:
	int wrap(int x, int low, int high);

private:
	void Update_Matrix();

	void Pattern();
	void Change_Pattern();
	void Pattern00();
	void Pattern01();

private:
	D3DXVECTOR3 m_vPoint[4]; // Q
	D3DXVECTOR3 m_vOrigin[4];// P
	D3DXVECTOR3 m_vPosin;

	D3DXVECTOR3 m_vLookOrigin;

	DWORD		m_dwLastAttTime;
	DWORD		m_dwAttDelay;

	DWORD		m_dwLastPatternChangeTime;
	DWORD		m_dwPatternTime;

	int			m_iPattern{ 1 };
	int			m_iMaxPattern{ 2 };
};

