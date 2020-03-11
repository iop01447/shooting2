#pragma once
#include "Bullet.h"
class CFlowerBullet :
	public CBullet
{
public:
	CFlowerBullet();
	virtual ~CFlowerBullet();

	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;

private:
	map<CObj*, D3DXVECTOR3> m_mapBullet;
};

