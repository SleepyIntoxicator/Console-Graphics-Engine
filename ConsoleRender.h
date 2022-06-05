#pragma once

#include <string>
#include <Windows.h>
#include <conio.h>
#include <mutex>

#include "stdafx.h"
#include "EngineTimeInfo.h"
//using namespace std;

#ifndef _CONSOLERENDER
#define _CONDOLERENDER

class CCRender
{
public:
	CCRender(SClientInfo *pi_pClientInfo, CEngineTimeInfo *pi_pTimeInfo);
	void Prepare(int pi_width, int pi_height);
	void Render(void);
	void Complete();
private:
	HANDLE m_hWinFirst, m_hWinSecond, m_hWinNotActive;
	COORD	m_cNullPoint;
	Size	m_WindowSize;
	COORD	m_WindowPos;
	CEngineTimeInfo *m_pEngineTimeInfo;
	WORD m_WinColor;

	bool m_isDebug;
	SClientInfo *m_pClientInfo;
	LPDWORD			m_dwL;			//dwLenght for lenght of written data

	std::mutex m_mutex;
	int DELETEMESSAGE;
public:
	void ConsolePrint(std::string pi_str, int pi_x, int pi_y);
	void ConsolePrint(int pi_x, int pi_y, LPCSTR format,  ...);
	void RenderPercentBar(int pi_val, int pi_valMax, int pi_size, int pi_x, int pi_y, bool pi_bPrintPer);  //Not working
	void RenderXPBar(int pi_xp, int pi_size);
	void RenderWindow(std::string pi_name, byte pi_orientation, int pi_x, int pi_y, int pi_w, int pi_h, byte pi_backColor);
	void RenderError(std::string pi_errorText);
	void RenderProgressBar(int pi_value, int pi_maxValue, int pi_size, int pi_x, int pi_y, byte pi_activeColor, byte pi_passiveColor, bool pi_bRenderValue);
	void RenderProgressBarEx(int pi_value, int pi_maxValue, int pi_size, int pi_x, int pi_y, byte pi_activeColor, byte pi_passiveColor, byte pi_backcolor, bool pi_bRenderValue);
	void RenderProgressBarExV(int pi_value, int pi_maxValue, int pi_size_w, int pi_size_h, int pi_x, int pi_y, byte pi_activeColor, byte pi_passiveColor, byte pi_backColor, bool pi_bUp, bool pi_bRenderValue);
	
	void RenderTimeInformer(int pi_x, int pi_y);
	void RenderClientInformer(int pi_x, int pi_y);
	//	 RENDERBACKGROUND	RENDERBACKGROUNDEX
	void RenderBackground(int pi_x, int pi_y, int pi_w, int pi_h, byte pi_color);
	void RenderBackground(COORD pi_pos, Size pi_size, byte pi_color);
	void RenderBackgroundEx(int pi_x, int pi_y, int pi_w, int pi_h, byte pi_color, char pi_ch);
	void RenderBackgroundEx(COORD pi_pos, Size pi_size, byte pi_color, char pi_ch);
	
	void RenderRUSSIANFLAG(int pi_x, int pi_y);
	void RenderITALIANFLAG(int pi_x, int pi_y);

	void SetWindowSize(int pi_newW, int pi_newH);
	std::string PrepareText(std::string pi_str, byte pi_orientation, int pi_size);
	void SetCurPos(int pi_x, int pi_y);
	void SetCursorVisible(bool pi_isVisible);

	inline WORD GetColor(byte pi_byBackgroundColor, byte pi_byTextColor)		{ return (pi_byBackgroundColor << 4) + pi_byTextColor; }
	inline void ConsolePrint(std::string pi_str)										{ WriteFile(m_hWinNotActive, pi_str.data(), pi_str.size(), m_dwL, NULL); }

	void SwapBuffer();
	HANDLE GetSecondHANDLE();
	
	void RenderPeccentBar(int pi_val, int pi_valMax, int pi_size, int pi_x, int pi_y, bool pi_bPrintPer);

private:
	inline void SetConsoleColor(byte pi_byBackgroundColor, byte pi_byTextColor)	{ SetConsoleTextAttribute(m_hWinNotActive, GetColor(pi_byBackgroundColor, pi_byTextColor)); }
	inline void SetConsoleColor(WORD pi_newWinColor)	{ SetConsoleTextAttribute(m_hWinNotActive, pi_newWinColor); }
};
#endif