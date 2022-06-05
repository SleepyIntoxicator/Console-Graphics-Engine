#pragma once
#ifndef _CONSOLEENGINE
#define _CONSOLEENGINE

#include "ConsoleRender.h"
#include "stdafx.h"

class CCEngine
{
public:
	CCEngine(bool isDev);

	void Prepare(int pi_width, int pi_height);
	void Start();
	void Complete();

	
private:
	CCRender	*m_CCR;


	Size	m_WindowSize;
	COORD	m_WindowPos;
	HANDLE	m_hWindowFirst, m_hWindowSecond;

	byte	m_bySystemState;
	byte	m_byUserGrade;

	SClientInfo m_ClientInfo;
	bool	m_isDebug;

	CEngineTimeInfo m_EngineTimeInfo;
private:
	void Update();
	void Tick();
inline void SetWindowPos(SHORT pi_x, SHORT pi_y)			{ m_WindowPos = { pi_x, pi_y }; }

	void NextSystemState();
	void SetSystemState(byte pi_state);
	byte GetSystemState();
	void SetWindowSize(int pi_width, int pi_height);
	void SetUserGrade(byte pi_byUserGrade);
	 
};

#endif