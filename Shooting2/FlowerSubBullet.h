#pragma once
#include "Bullet.h"
class CFlowerSubBullet :
	public CBullet
{
public:
	CFlowerSubBullet();
	virtual ~CFlowerSubBullet();

	virtual int Update() override;
	virtual void Late_Update() override;

public:
	void Set_UnDead(bool _bUnDead) { m_bUnDead = _bUnDead; }
	void Set_ParentErase(bool _bool) { m_bParentErase = _bool; }

private:
	bool m_bUnDead{ true };
	bool m_bParentErase{ false };
};

