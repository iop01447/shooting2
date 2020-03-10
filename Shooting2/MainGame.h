#pragma once

#ifndef __MAINGAME_H__
#define __MAINGAME_H__

class CObj; 
class CMainGame
{
public:
	CMainGame();
	~CMainGame();

public:
	void Initialize(); 
	void Update(); 
	void LateUpdate(); 
	void Render(); 
	void Release(); 

private:
	void KeyCheck();

private:
	HDC m_hDC; 
	CObj* m_pBoss;
};


#endif // !__MAINGAME_H__
