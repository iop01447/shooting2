#pragma once
#include "Boss.h"
class CBoss02 :
	public CBoss
{
public:
	CBoss02();
	virtual ~CBoss02();

	// CBoss��(��) ���� ��ӵ�
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;

	// CBoss��(��) ���� ��ӵ�
	virtual void Move() override;
	virtual void Attack() override;

private:
	D3DXVECTOR3 m_vPoint[6]; // Q
	D3DXVECTOR3 m_vOrigin[6]; // P
};

