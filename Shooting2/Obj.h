#pragma once

#ifndef __OBJ_H__
#define __OBJ_H__

class CObj
{
public:
	CObj();
	virtual ~CObj();

public:
	virtual void Initialize() = 0;
	virtual int Update() = 0;
	virtual void Late_Update() = 0;
	virtual void Render(HDC hDC) = 0;
	virtual void Release() = 0;

protected:
	void Update_Rect();

public:
	const INFO& Get_Info() const { return m_tInfo; }
	const RECT& Get_Rect() const { return m_tRect; }
	const bool& Get_Dead() const { return m_bDead; }
	const float& Get_Angle() const { return m_fAngle; }
	const int& Get_HP() const { return m_tStatus.iHp; }
	const int& Get_MaxHP() const { return m_tStatus.iMaxHp; }
	const int& Get_Power() const { return m_tStatus.iPower; }


public:
	void Set_Dead() { m_bDead = true; }
	void Set_Damage(int _iAtt) { m_tStatus.iHp -= _iAtt; }
	void Set_Pos(float _x, float _y) { m_tInfo.vPos = { _x, _y, 0.f }; };
	void Set_Angle(float _fAngle) { m_fAngle = _fAngle; }
	void Set_Target(CObj* _pTarget) { m_pTarget = _pTarget; }
	void Set_Size(int _iCX, int _iCY) { m_tInfo.vSize = { float(_iCX), float(_iCY), 0.f };}


protected:
	INFO		m_tInfo;		// 객체들의 좌표와 크기를 저장한다.
	RECT		m_tRect;

	STATUS		m_tStatus;
	CObj*		m_pTarget;

	float		m_fSpeed;
	bool		m_bDead;

	float		m_fAngle;
};

#endif // !__OBJ_H__