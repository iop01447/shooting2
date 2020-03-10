#pragma once
#ifndef __STRUCT_H__
#define __STRUCT_H__


typedef struct tagInfo
{
	D3DXVECTOR3 vPos; 
	D3DXVECTOR3 vDir; 
	D3DXVECTOR3 vSize; 
	D3DXVECTOR3 vLook; 

	D3DXMATRIX matWorld; 

}INFO;

typedef struct tagStatus
{
	int		iPower;
	int		iExp;
	int		iMaxExp;
	int		iHp;
	int		iMaxHp;
	int		iLevel;
}STATUS;

#endif