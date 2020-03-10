#pragma once
#include "Boss.h"
class CBoss02 :
	public CBoss
{
public:
	CBoss02();
	virtual ~CBoss02();

	// CBoss을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;
};

