#pragma once

#ifndef __BOSS00BULLET1_H__
#define __BOSS00BULLET1_H__

#include "Bullet.h"
class CBoss00Bullet1 :
	public CBullet
{
public:
	CBoss00Bullet1();
	virtual ~CBoss00Bullet1();

public:
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;
};

#endif // !__BOSS00BULLET1_H__