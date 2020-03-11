#pragma once

#ifndef __BOSS00BULLET2_H__
#define __BOSS00BULLET2_H__

#include "Bullet.h"
class CBoss00Bullet2 :
	public CBullet
{
public:
	CBoss00Bullet2();
	virtual ~CBoss00Bullet2();

public:
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;
};

#endif // !__BOSS00BULLET2_H__
