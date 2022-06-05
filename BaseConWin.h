#pragma once

#include "stdafx.h"
#include "ConsoleRender.h"
#ifndef _BASECONWIN
#define _BASECONWIN

class CBaseConWin
{
public:
	CBaseConWin(HANDLE pi_hWND);
	~CBaseConWin();
	void Update();
	void Render();
private:
	CCRender *m_pRenderer;
	HANDLE m_hWND;
	COORD m_Position;
	Size m_Size;
	WORD m_wColor;
public:
	void SetPosition(SHORT pi_x, SHORT pi_y);
	void SetPosition(COORD pi_position);
	void SetSize(int pi_w, int pi_h);
	void SetSize(Size pi_size);
	void SetColor(byte pi_backcolor, byte pi_textcolor);
	void SetColor(WORD pi_color);
	void GetColor(_Out_ WORD &wColor);
	void GetWinHandle(HANDLE &hWND);
	void GetWinPtr(CBaseConWin *pBaseWin);
};

#endif