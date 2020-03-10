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

	//static CObj* Create(int _Weapon)
	//{
	//	CObj* pObj = new T;

	//	pObj->Set_Gold(-_Weapon);
	//	pObj->Initialize();

	//	return pObj;
	//}

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
		pObj->Initialize();
		pObj->Set_Pos(_x, _y);
		pObj->Set_Angle(_fAngle);

		return pObj;
	}
	static CObj* Create(float _x, float _y, int _Weapon)
	{
		CObj* pObj = new T;
		
		pObj->Set_Pos(_x, _y);
		pObj->Set_Gold(-_Weapon);
		pObj->Initialize();

		return pObj;
	}
};

#endif // !__AbstractFactory_H__
