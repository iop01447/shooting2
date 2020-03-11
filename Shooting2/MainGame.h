#pragma once

#ifndef __MAINGAME_H__
#define __MAINGAME_H__

class CObj; 
class CMainGame
{
public:
	CMainGame();
	~CMainGame();

private:
	enum SCENE { START, STAGE1, STAGE2, STAGE3, END };

public:
	void Initialize(); 
	void Update(); 
	void LateUpdate(); 
	void Render(); 
	void Release(); 

private:
	void KeyCheck();
	void Next_Scene();
	bool Start_Scene();
	void Stage_Scene();

private:
	list<CObj*>*	m_listBoss;

	HDC				m_hDC;
	CObj*			m_pBoss;

	SCENE			m_eScene;
	int				m_iBossCount;
};


#endif // !__MAINGAME_H__
