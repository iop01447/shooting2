#include "stdafx.h"
#include "MainGame.h"

#include "CollisionMgr.h"
#include "ObjMgr.h"
#include "KeyMgr.h"
#include "BmpMgr.h"

#include "Player.h"
#include "Boss00.h"
#include "Boss01.h"
#include "Boss02.h"


CMainGame::CMainGame()
{
}

CMainGame::~CMainGame()
{
	Release(); 
}

void CMainGame::Initialize()
{
	srand(unsigned(time(NULL)));

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Back.bmp", L"Back");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/BackBuffer.bmp", L"BackBuffer");

	m_hDC = GetDC(g_hWnd);

	CObjMgr::Get_Instance()->Add_Object(OBJID::PLAYER, CAbstractFactory<CPlayer>::Create(300.f, 700.f));

	//m_pBoss = CAbstractFactory<CBoss00>::Create();
	//m_pBoss->Set_Target(CObjMgr::Get_Instance()->Get_Obj(OBJID::PLAYER));
	//CObjMgr::Get_Instance()->Add_Object(OBJID::BOSS, m_pBoss);

	m_listBoss = CObjMgr::Get_Instance()->Get_List(OBJID::BOSS);

	m_eScene = START;
	m_iBossCount = 0;
}

void CMainGame::Update()
{
	KeyCheck();
	CObjMgr::Get_Instance()->Update();
	CKeyMgr::Get_Instance()->Key_Update();

	if (m_listBoss->empty())
		Next_Scene();
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

void CMainGame::KeyCheck()
{
	if (CKeyMgr::Get_Instance()->Key_Down('1')) {
		m_pBoss->Set_Dead();
		m_pBoss = CAbstractFactory<CBoss00>::Create();
		m_pBoss->Set_Target(CObjMgr::Get_Instance()->Get_Obj(OBJID::PLAYER));
		CObjMgr::Get_Instance()->Add_Object(OBJID::BOSS, m_pBoss);
	}
	if (CKeyMgr::Get_Instance()->Key_Down('2')) {
		m_pBoss->Set_Dead();
		m_pBoss = CAbstractFactory<CBoss01>::Create();
		m_pBoss->Set_Target(CObjMgr::Get_Instance()->Get_Obj(OBJID::PLAYER));
		CObjMgr::Get_Instance()->Add_Object(OBJID::BOSS, m_pBoss);
	}
	if (CKeyMgr::Get_Instance()->Key_Down('3')) {
		m_pBoss->Set_Dead();
		m_pBoss = CAbstractFactory<CBoss02>::Create();
		m_pBoss->Set_Target(CObjMgr::Get_Instance()->Get_Obj(OBJID::PLAYER));
		CObjMgr::Get_Instance()->Add_Object(OBJID::BOSS, m_pBoss);
	}
}

void CMainGame::Next_Scene()
{
	switch (m_eScene)
	{
	case CMainGame::START:
		m_eScene = (SCENE)m_iBossCount;
		++m_iBossCount;
		break;
	case CMainGame::STAGE1:
		m_eScene = START;
		break;
	case CMainGame::STAGE2:
		m_eScene = START;
		break;
	case CMainGame::STAGE3:
		m_eScene = START;
		break;
	case CMainGame::END:
		DestroyWindow(g_hWnd);
		break;
	default:
		break;
	}

	Stage_Scene();
}

void CMainGame::Start_Scene()
{

}

void CMainGame::Stage_Scene()
{
	switch (m_eScene)
	{
	case CMainGame::STAGE1:
		m_listBoss->emplace_back(CAbstractFactory<CBoss00>::Create());
		m_listBoss->front()->Set_Target(CObjMgr::Get_Instance()->Get_Obj(OBJID::PLAYER));
		break;
	case CMainGame::STAGE2:
		m_listBoss->emplace_back(CAbstractFactory<CBoss01>::Create());
		m_listBoss->front()->Set_Target(CObjMgr::Get_Instance()->Get_Obj(OBJID::PLAYER));
		break;
	case CMainGame::STAGE3:
		m_listBoss->emplace_back(CAbstractFactory<CBoss02>::Create());
		m_listBoss->front()->Set_Target(CObjMgr::Get_Instance()->Get_Obj(OBJID::PLAYER));
		break;
	case CMainGame::END:
		DestroyWindow(g_hWnd);
		break;
	default:
		break;
	}
}
