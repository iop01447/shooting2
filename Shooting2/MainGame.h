#pragma once

#ifndef __MAINGAME_H__
#define __MAINGAME_H__

class CPlayer; 
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
	HDC m_hDC; 
};


#endif // !__MAINGAME_H__
