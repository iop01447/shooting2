#pragma once
#include "Boss02Bullet.h"
class CRotBullet :
	public CBoss02Bullet
{
public:
	CRotBullet();
	virtual ~CRotBullet();

	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;
private:
	D3DXVECTOR3		m_tCenter;

	float		m_fRotAngle;
	float		m_fRotSpeed;
	float		m_fRotDis;
	bool		m_bDir;
};

