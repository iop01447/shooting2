#include "stdafx.h"
#include "MainGame.h"

#include "CollisionMgr.h"
#include "ObjMgr.h"
#include "KeyMgr.h"
#include "BmpMgr.h"

#include "Player.h"
#include "Boss00.h"
#include "Boss01.h"



CMainGame::CMainGame()
{
}

CMainGame::~CMainGame()
{
	Release(); 
}

void CMainGame::Initialize()
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Back.bmp", L"Back");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/BackBuffer.bmp", L"BackBuffer");

	m_hDC = GetDC(g_hWnd);

	CObjMgr::Get_Instance()->Add_Object(OBJID::PLAYER, CAbstractFactory<CPlayer>::Create(300.f, 700.f));
	CObjMgr::Get_Instance()->Add_Object(OBJID::BOSS, CAbstractFactory<CBoss00>::Create());
	//CObjMgr::Get_Instance()->Add_Object(OBJID::BOSS, CAbstractFactory<CBoss01>::Create());

}

void CMainGame::Update()
{
	CObjMgr::Get_Instance()->Update();
	CKeyMgr::Get_Instance()->Key_Update();
}

void CMainGame::LateUpdate()
{
	CObjMgr::Get_Instance()->Late_Update();
}

void CMainGame::Render()
{
	HDC hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"BackBuffer");
	HDC hBackBuffer = CBmpMgr::Get_Instance()->Find_Image(L"Back");
	BitBlt(hBackBuffer, 0, 0, WINCX, WINCY, hMemDC, 0, 0, SRCCOPY);

	CObjMgr::Get_Instance()->Render(hBackBuffer);

	BitBlt(m_hDC, 0, 0, WINCX, WINCY, hBackBuffer, 0, 0, SRCCOPY);

}

void CMainGame::Release()
{
	CObjMgr::Get_Instance()->Delete_ID(OBJID::BOSS);

	CObjMgr::Get_Instance()->Delete_ID(OBJID::PLAYER);

	CBmpMgr::Destroy_Instance();
	CKeyMgr::Destroy_Instance();
	CObjMgr::Destroy_Instance();

	ReleaseDC(g_hWnd, m_hDC); 
}
