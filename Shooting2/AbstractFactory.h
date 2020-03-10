#pragma once

#ifndef __AbstractFactory_H__
#define __AbstractFactory_H__

// Ŭ������ �����ϴ� ����
// �����̶� ��ü ���⿡ ������ �ڵ带 �����ϱ� ���ؼ��̴�.
class CObj;
template <typename T>
class CAbstractFactory
{
public:
	// static ����ϴ� ����
	// static�� ����ϸ� ��ü ���� ���� ������ �����ڸ� ���� ������ �� �ִ�!
	static CObj* Create()
	{
		CObj* pObj = new T;
		pObj->Initialize();

		return pObj;
	}

	static CObj* Create(float _x, float _y)
	{
		CObj* pObj = new T;
		pObj->Initialize();
		pObj->Set_Pos(_x, _y);

		return pObj;
	}

	static CObj* Create(float _x, float _y, float _fAngle)
	{
		CObj* pObj = new T;
		pObj->Set_Pos(_x, _y);
		pObj->Initialize();
		pObj->Set_Angle(_fAngle);

		return pObj;
	}

	static CObj* Create(const D3DXVECTOR3& _vPos, const D3DXVECTOR3& _vDir)
	{
		CObj* pObj = new T;
		pObj->Set_Pos(_vPos.x, _vPos.y);
		pObj->Initialize();
		pObj->Set_Dir(_vDir);

		return pObj;
	}
};

#endif // !__AbstractFactory_H__
