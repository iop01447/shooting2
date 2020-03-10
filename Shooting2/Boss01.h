#pragma once
#include "Boss.h"
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

private:
	D3DXVECTOR3 m_vPoint[4]; // Q
	D3DXVECTOR3 m_vOrigin[4]; // P
};

