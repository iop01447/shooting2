#pragma once
#include "Boss.h"

class CObj;
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

	virtual const RECT& Get_Rect() const { return m_bVisible ? m_tRect : RECT{ 0,0,0,0 }; }

	virtual void Move() override;
	virtual void Attack() override;

public:
	int wrap(int x, int low, int high);

private:
	// Update
	void KeyCheck();

	void Change_Pattern(); // ���� ��ȯ ���� �˻�
	void InitPattern(); // ���� �ʱ�ȭ
	void Pattern00(); // ����ȹ� ���
	void Pattern01(); // �н��� ũ��������Ʈ�� ���
	void Pattern02(); // �Ѿ� ���� �� �÷��̾� ������ �̵�
	void Pattern03(); // ������
	void Pattern04(); // ��

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

	bool		m_bTest{ false };
	bool		m_bTransition{ false };
	bool		m_bAlterMode{ false };
	bool		m_bVisible{ true };

	CObj*		m_pAlter[2]{ nullptr };
	int			m_iAlterCnt{ 2 };
};

