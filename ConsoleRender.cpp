#include "ConsoleRender.h"

//***********************************************************************
//***********************************************************************
//	STANDART RENDER FUNC	//*******************************************
CCRender::CCRender(SClientInfo *pi_pClientInfo, CEngineTimeInfo *pi_pTimeInfo) //DANGER BUGS!!!
{
	m_hWinFirst = GetStdHandle(STD_OUTPUT_HANDLE);
	m_hWinSecond = CreateConsoleScreenBuffer(GENERIC_WRITE, FILE_SHARE_WRITE, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
	m_hWinNotActive = NULL;

	m_cNullPoint = { NULL, NULL };
	m_WindowSize = { WINDOWSTANDARTSIZE_X, WINDOWSTANDARTSIZE_Y };

	//SetWindowSize(ws_width, ws_height);
	COORD crd = { WINDOWSTANDARTSIZE_X, WINDOWSTANDARTSIZE_Y };
	m_WindowSize = { WINDOWSTANDARTSIZE_X, WINDOWSTANDARTSIZE_Y };
	SMALL_RECT src = { 0, 0, crd.X - 1, crd.Y - 1 };
	SetConsoleWindowInfo(m_hWinFirst, true, &src);
	SetConsoleScreenBufferSize(m_hWinFirst, crd);

	SetConsoleWindowInfo(m_hWinSecond, true, &src);
	SetConsoleScreenBufferSize(m_hWinSecond, crd);

	m_WinColor = GetColor(CC_BLACK, CC_WHITE);

	m_isDebug = FALSE;
	m_pClientInfo = pi_pClientInfo;
	m_pEngineTimeInfo = pi_pTimeInfo;
	SetCursorVisible( false );

}

void CCRender::Prepare(int pi_width, int pi_height)
{


	m_hWinNotActive = m_hWinSecond;

	m_WindowSize = { pi_width, pi_height };

	//SetWindowSize(ws_width, ws_height);
	COORD crd = { pi_width, pi_height };
	SMALL_RECT src = { 0, 0, crd.X - 1, crd.Y - 1 };


	SetConsoleWindowInfo(m_hWinFirst, true, &src);
	SetConsoleScreenBufferSize(m_hWinFirst, crd);

	SetConsoleWindowInfo(m_hWinSecond, true, &src);
	SetConsoleScreenBufferSize(m_hWinSecond, crd);

	SetConsoleWindowInfo(m_hWinFirst, true, &src);
	SetConsoleWindowInfo(m_hWinSecond, true, &src);
	
	SetConsoleTitle("Console Engine");
#ifndef DEBUG 
	SetConsoleTitle("Console Engine v0.1.272 _debug 2.IV.2017");
	m_isDebug = true;
#endif
	DELETEMESSAGE = NULL;

}

void CCRender::Render()
{
		RenderBackground(0, 0, m_WindowSize.width, m_WindowSize.height, CC_BLACK);

		RenderRUSSIANFLAG(0, 0);
		RenderITALIANFLAG(10, 10);

		RenderWindow("Window 10 10 100 10 LEFT DARKGREEN", LEFT, 10, 10, 100, 10, CC_DARKGREEN);
		RenderError(make_string("Critical error in Line : %d", __LINE__));
		RenderTimeInformer(20, 0);
		if (m_isDebug)
		{
			RenderClientInformer(40, 0);
		}
		byte	KBState[256];
		memset(KBState, 0, sizeof(256));
		GetKeyState(0);
		GetKeyboardState(KBState);
		SetConsoleColor(CC_BLACK, CC_RED);
		for (int i = 0; i < 256; i++)
		{
			KBState[i] = KBState[i] >> 7;
			ConsolePrint(std::to_string(KBState[i]), i, 35);
		}
		if (KBState[VK_F6] == 1 && DELETEMESSAGE < 100)
			DELETEMESSAGE += 1;
		if (KBState[VK_F7] == 1 && DELETEMESSAGE > 0)
			DELETEMESSAGE -= 1;
		RenderProgressBarExV(DELETEMESSAGE, 100, 5, 40, 138, 0, CC_GREEN, CC_DARKGREEN, CC_BLACK, true, true);
		int Predict = 100;
		if (m_pEngineTimeInfo->Delay <= 50)
			Predict = 50;
		else if (m_pEngineTimeInfo->Delay > 50 && m_pEngineTimeInfo->Delay <= 100)
			Predict = 100;
		else if (m_pEngineTimeInfo->Delay > 100 && m_pEngineTimeInfo->Delay <= 1000)
			Predict = 1000;
		else if (m_pEngineTimeInfo->Delay > 1000 && m_pEngineTimeInfo->Delay <= 5000)
			Predict = 5000;
		else if (m_pEngineTimeInfo->Delay > 5000 && m_pEngineTimeInfo->Delay <= 10000)
			Predict = 10000;
		else
			Predict = 100000;
		//RenderDelayInfo
		RenderProgressBarEx(m_pEngineTimeInfo->Delay, Predict, 50, 0, 25, CC_GREEN, CC_DARKGREEN, CC_BLACK, true);
		RenderProgressBarEx(Predict, 100, 2, 60, 25, CC_GREEN, CC_DARKGREEN, CC_BLACK, true);
		RenderProgressBarEx(m_pEngineTimeInfo->FPS, Predict, 50, 0, 26, CC_BLUE, CC_DARKBLUE, CC_BLACK, true);
		RenderProgressBarEx(m_pClientInfo->bySystemState, 4, 4, 60, 26, CC_RED, CC_DARKRED, CC_BLACK, true);
		//RenderTimeBar
		RenderProgressBarEx(m_pEngineTimeInfo->Sec, 60, 60, 70, 0, CC_YELLOW, CC_DARKYELLOW, CC_BLACK, true);
		RenderProgressBarEx(m_pEngineTimeInfo->Min, 60, 60, 70, 1, CC_AZURE, CC_DARKAZURE, CC_BLACK, true);
		RenderProgressBarEx(m_pEngineTimeInfo->H, 24, 24, 70, 2, CC_RED, CC_DARKRED, CC_BLACK, true);

		RenderProgressBarEx(0, 1, 12 * 2, 70, 3, CC_GREEN, CC_DARKGREEN, CC_BLACK, false);
		RenderProgressBarEx(1, 1, 1 * 2, 70 + m_pEngineTimeInfo->Month * 2, 3, CC_GREEN, CC_DARKGREEN, CC_BLACK, false);


		RenderProgressBarEx(m_pEngineTimeInfo->Day, 365, 100, 0, 6, CC_BLUE, CC_DARKBLUE, CC_BLACK, true);
		SetCurPos(50, 50);
		RenderProgressBarExV(5, 10, 1, 10, 4, 0, CC_WHITE, CC_DARKWHITE, CC_BLACK, true, true);
		SwapBuffer();
}

void CCRender::Complete( void )
{

}
//***************************************************************
//***************************************************************
//	RENDER FUNC		//*******************************************

void CCRender::RenderPercentBar(int pi_val, int pi_valMax, int pi_size, int pi_x, int pi_y, bool pi_bPrintPer)  //Not working
{
	//DANGER There is a magic numbers 3 & 5
	RenderProgressBar(pi_val, pi_valMax, pi_size, pi_x + 3, pi_y + 5, CC_GREEN, CC_DARKGREEN, pi_bPrintPer);
	float Percent = ((float)pi_val / (float)pi_valMax) * 100;
	ConsolePrint(" " + std::to_string(Percent) + "%", pi_x + 3, pi_y + 5);
}

void CCRender::RenderXPBar(int pi_xp, int pi_size) //DANGER This is "labirint"
{
	int nSize = pi_size / 10;
	int nFull = pi_xp / nSize;
	int nEmpty = nSize - nFull;
	int nPart = pi_xp - nFull * nSize;
	for (int i = 0; i < nFull; i++)
	{
		SetConsoleColor(CC_AZURE, NULL);
		ConsolePrint(GetStr(nSize, ' '), nSize * i + i, m_WindowSize.height - 1);
		SetConsoleColor(CC_GRAY, NULL);
		ConsolePrint(" ");
	}
	RenderProgressBar(nPart, 10, 10, nSize * nFull + nFull, m_WindowSize.height, CC_AZURE, CC_DARKAZURE, false);
	int BeginPos = (nFull + 1) * nSize;
	for (int i = 0; i < nEmpty; i++)
	{
		SetConsoleColor(CC_GRAY, NULL);
		ConsolePrint(" ");
		SetConsoleColor(CC_DARKAZURE, NULL);
		ConsolePrint(GetStr(nSize, ' '), nFull * nSize + nFull + nSize + nSize * i + 1, m_WindowSize.height - 1);
	}
}

void CCRender::ConsolePrint(std::string pi_str, int pi_x, int pi_y)
{
	SetCurPos(pi_x, pi_y);
	ConsolePrint(pi_str);
}

void CCRender::ConsolePrint(int pi_x, int pi_y, LPCSTR format,  ...)
{
	va_list		args;
	va_start(args, format);
	char		temp[4096];
	vsprintf_s(temp, format, args);

	SetCurPos(pi_x, pi_y);
	ConsolePrint(temp);
}

void CCRender::RenderWindow(std::string pi_name, byte pi_orientation, int pi_x, int pi_y, int pi_w, int pi_h, byte pi_backColor)
{
	RenderBackground(pi_x, pi_y, pi_w, pi_h, pi_backColor);

	SetConsoleColor(CC_BLUE, CC_WHITE);
	ConsolePrint(PrepareText(pi_name, pi_orientation, pi_w), pi_x, pi_y);
	SetConsoleColor(CC_BLUE, CC_DARKAZURE);
	for (int i = 1; i < pi_h; i++)
	{
		ConsolePrint("\xB0", pi_x, pi_y + i);
		ConsolePrint("\xB0", pi_x + pi_w - 1, pi_y + i);
	}

	ConsolePrint(GetStr(pi_w, '\xB0'), pi_x, pi_y + pi_h);
	SetConsoleColor(CC_RED, CC_WHITE);
	ConsolePrint(" X ", pi_x + pi_w - 3, pi_y);
}

void CCRender::RenderError(std::string pi_errorText)
{
	int pi_x = 15;
	int pi_y = 15;
	int pi_w = 40;
	int pi_h = 7;


	RenderBackground(pi_x, pi_y, pi_w, pi_h, CC_GRAY);

	SetConsoleColor(CC_DARKRED, CC_WHITE);
	ConsolePrint(PrepareText("Error", LEFT, pi_w), pi_x, pi_y);

	SetConsoleColor(CC_BLACK, CC_RED);
	for (int i = 1; i < 7; i++)
	{
		ConsolePrint("\xB0", pi_x, pi_y + i);
		ConsolePrint("\xB0", pi_x + pi_w - 1, pi_y + i);
	}
	ConsolePrint(GetStr(pi_w, '\xB0'), pi_x, pi_y + pi_h);

	SetConsoleColor(CC_GRAY, CC_RED);
	ConsolePrint(pi_errorText, pi_x + 3, pi_y + pi_h / 2);
}

void CCRender::RenderProgressBar(int pi_value, int pi_maxValue, int pi_size, int pi_x, int pi_y, byte pi_activeColor, byte pi_passiveColor, bool pi_bRenderValue = false)
{
	float Percent;
	if (pi_value == 0) Percent = 0;
	else Percent = float(pi_value) / float(pi_maxValue);
	if (Percent > 1.0f) Percent = 1.0f;
	int n = (int)(Percent * pi_size);
	SetConsoleColor(pi_activeColor, pi_passiveColor);
	ConsolePrint(GetStr(n, '\xB0'), pi_x, pi_y);
	int m = pi_size - n;
	SetConsoleColor(pi_passiveColor, pi_activeColor);
	ConsolePrint(GetStr(m, '\xB0'), pi_x + n, pi_y);
	if (pi_bRenderValue)
	{
		SetConsoleColor(CC_BLACK, pi_activeColor);
		ConsolePrint(" " + std::to_string(pi_value) + "/" + std::to_string(pi_maxValue));
	}
}

void CCRender::RenderProgressBarEx(int pi_value, int pi_maxValue, int pi_size, int pi_x, int pi_y, byte pi_activeColor, byte pi_passiveColor, byte pi_backColor, bool pi_bRenderValue = false)
{
	float Percent;
	if (pi_value == 0) Percent = 0;
	else Percent = float(pi_value) / float(pi_maxValue);
	if (Percent > 1.0f) Percent = 1.0f;
	int n = (int)(Percent * pi_size);
	SetConsoleColor(pi_backColor, pi_activeColor);
	ConsolePrint(GetStr(n, '\xB0'), pi_x, pi_y);
	int m = pi_size - n;
	SetConsoleColor(pi_backColor, pi_passiveColor);
	ConsolePrint(GetStr(m, '\xB0'), pi_x + n, pi_y);
	if (pi_bRenderValue)
	{
		SetConsoleColor(CC_BLACK, pi_activeColor);
		ConsolePrint(" " + std::to_string(pi_value) + "/" + std::to_string(pi_maxValue));
	}
}

void CCRender::RenderProgressBarExV(int pi_value, int pi_maxValue, int pi_size_w, int pi_size_h, int pi_x, int pi_y, byte pi_activeColor, byte pi_passiveColor, byte pi_backColor, bool pi_bUp, bool pi_bRenderValue)
{
	float Percent;
	if (pi_value == 0) Percent = 0;
	else Percent = float(pi_value) / float(pi_maxValue);
	if (Percent > 1.0f) Percent = 1.0f;
	int n = (int)(Percent * pi_size_h);
	SetConsoleColor(pi_backColor, pi_activeColor);
	if (!pi_bUp)
	{
		for (int i = 0; i < n; i++)
		{
			ConsolePrint(GetStr(pi_size_w, '\xB0'), pi_x, pi_y + i);
		}
		int m = pi_size_h - n;
		SetConsoleColor(pi_backColor, pi_passiveColor);
		for (int i = 0; i < m; i++)
		{
			ConsolePrint(GetStr(pi_size_w, '\xB0'), pi_x, pi_y + n + i);
		}
	}
	else
	{
		int m = pi_size_h - n;
		for (int i = 0; i < n; i++)
		{
			ConsolePrint(GetStr(pi_size_w, '\xB0'), pi_x, pi_y + m + i);
		}
		
		SetConsoleColor(pi_backColor, pi_passiveColor);
		for (int i = 0; i < m; i++)
		{
			ConsolePrint(GetStr(pi_size_w, '\xB0'), pi_x, pi_y + i);
		}
	}
	if (pi_bRenderValue)
	{
		SetConsoleColor(CC_BLACK, pi_activeColor);
		ConsolePrint(pi_x, pi_y + pi_size_h, "%d", pi_value);
		ConsolePrint(pi_x, pi_y + pi_size_h +1, "/");
		ConsolePrint(pi_x, pi_y + pi_size_h +2, "%d", pi_maxValue);
	}
}

void CCRender::RenderTimeInformer(int pi_x, int pi_y)
{
	RenderBackground(pi_x, pi_y, 20, 4, CC_BLACK);
	SetConsoleColor(CC_BLACK, CC_DARKYELLOW);

	NEWCOUNTER
		if (m_pEngineTimeInfo->Time < SECPERHOUR * 1000)
	{
		ConsolePrint(pi_x, pi_y + COUNTER, "Time: %2d:%2d m/s", m_pEngineTimeInfo->Min, m_pEngineTimeInfo->Sec);
	}
		else if (m_pEngineTimeInfo->Time >= SECPERHOUR * 1000 && m_pEngineTimeInfo->Time < SECPERDAY * 1000)
	{
		ConsolePrint(pi_x, pi_y + COUNTER, "Time: %2d:%2d\th/m", m_pEngineTimeInfo->H, m_pEngineTimeInfo->Min);
	}
		else if (m_pEngineTimeInfo->Time >= SECPERDAY * 1000)
	{
		ConsolePrint(pi_x, pi_y + COUNTER, "Time: %2d:%2d\tD/h", m_pEngineTimeInfo->Day, m_pEngineTimeInfo->H);
	}
	else
	{
		ConsolePrint(pi_x, pi_y + COUNTER, "ERR CRender.cpp in line %d", __LINE__);
	}
	ConsolePrint(pi_x, pi_y + COUNTER, "FPS: %d", m_pEngineTimeInfo->FPS);
		ConsolePrint(pi_x, pi_y + COUNTER, "Delay: %d\tms", m_pEngineTimeInfo->Delay);
		ConsolePrint(pi_x, pi_y + COUNTER, "EngineSpeed:%.2f", m_pClientInfo->Speed);
}

void CCRender::RenderClientInformer(int pi_x, int pi_y)
{
	RenderBackground(pi_x, pi_y, 20, 6, CC_BLACK);
	SetConsoleColor(CC_BLACK, CC_DARKYELLOW);
	NEWCOUNTER
		ConsolePrint(pi_x, pi_y + COUNTER, "SystemState: %s", GetStateName(m_pClientInfo->bySystemState));
		ConsolePrint(pi_x, pi_y + COUNTER, "UserGrade: %d", m_pClientInfo->byUserGrade);
		ConsolePrint(pi_x, pi_y + COUNTER, "WindowPos.X: %d", m_pClientInfo->WindowPos.X);
		ConsolePrint(pi_x, pi_y + COUNTER, "WindowPos.Y: %d", m_pClientInfo->WindowPos.Y);
		ConsolePrint(pi_x, pi_y + COUNTER, "WindowSize: %dx%d", m_pClientInfo->WindowSize.width, m_pClientInfo->WindowSize.height);
		ConsolePrint(pi_x, pi_y + COUNTER, "isDebug: %d", m_isDebug);
}

void CCRender::RenderBackground(int pi_x, int pi_y, int pi_w, int pi_h, byte pi_color)
{
	for (int i = 0; i < pi_h; i++)
	{
		SetConsoleColor(pi_color, CC_BLACK);
		ConsolePrint(GetStr(pi_w, ' '), pi_x, pi_y + i);
	}
}

void CCRender::RenderBackground(COORD pi_pos, Size pi_size, byte pi_color)
{
	for (int i = 0; i < pi_size.height; i++)
	{
		SetConsoleColor(pi_color, CC_BLACK);
		ConsolePrint(GetStr(pi_size.width, ' '), pi_pos.X, pi_pos.Y + i);
	}
}

void CCRender::RenderBackgroundEx(int pi_x, int pi_y, int pi_w, int pi_h, byte pi_color, char ch)
{
	for (int i = 0; i < pi_h; i++)
	{
		SetConsoleColor(pi_color, CC_BLACK);
		ConsolePrint(GetStr(pi_w, ch), pi_x, pi_y + i);
	}
}

void CCRender::RenderBackgroundEx(COORD pi_pos, Size pi_size, byte pi_color, char ch)
{
	for (int i = 0; i < pi_size.height; i++)
	{
		SetConsoleColor(pi_color, CC_BLACK);
		ConsolePrint(GetStr(pi_size.width, ch), pi_pos.X, pi_pos.Y + i);
	}
}

void CCRender::RenderRUSSIANFLAG(int pi_x, int pi_y)
{
	SetCurPos(pi_x, pi_y);
	for (int i = 0; i < 2; i++)
	{
		RenderProgressBar(1, 1, 3, pi_x + 0, i, CC_WHITE, CC_DARKWHITE, false);
		RenderProgressBar(1, 1, 3, pi_x + 3, i, CC_BLUE, CC_DARKBLUE, false);
		RenderProgressBar(1, 1, 3, pi_x + 6, i, CC_RED, CC_DARKRED, false);
	}
}

void CCRender::RenderITALIANFLAG(int pi_x, int pi_y)
{
	SetCurPos(pi_x, pi_y);
	for (int i = 0; i < 2; i++)
	{
		RenderProgressBar(1, 1, 3, pi_x + 0, i, CC_GREEN, CC_DARKGREEN, false);
		RenderProgressBar(1, 1, 3, pi_x + 3, i, CC_WHITE, CC_DARKWHITE, false);
		RenderProgressBar(1, 1, 3, pi_x + 6, i, CC_RED, CC_DARKRED, false);
	}
}


//***************************************************************
//***************************************************************
//	LOW LEVEL FUNC	//*******************************************

void CCRender::SetWindowSize(int pi_newW, int pi_newH)
{
	//Set window box & buffer size
	m_WindowSize = { pi_newW, pi_newH };
	COORD WinSize = { pi_newW, pi_newH };
	SMALL_RECT src = { 0, 0, m_WindowSize.width - 1, m_WindowSize.height - 1 };
	SetConsoleWindowInfo(m_hWinFirst, true, &src);
	SetConsoleScreenBufferSize(m_hWinFirst, WinSize);

	SetConsoleWindowInfo(m_hWinSecond, true, &src);
	SetConsoleScreenBufferSize(m_hWinSecond, WinSize);
}

std::string CCRender::PrepareText(std::string pi_str, byte pi_orientation, int pi_size)
{
	int halfX = 0;
	switch (pi_orientation)
	{
	case LEFT:
		return " " + pi_str + GetStr(pi_size - pi_str.length() - 1, ' ');
	case CENTER:
		halfX = (pi_size - pi_str.length()) / 2;
		return GetStr(halfX, ' ') + pi_str + GetStr(halfX + 1, ' ') + "";
	case RIGHT:
		return GetStr(pi_size - pi_str.length() - 1, ' ') + pi_str + " ";
	default:
		SetConsoleColor(CC_BLUE, CC_YELLOW);
		return "Error:~231 CM.cpp f:PrepareText(str, byte, int)";
	}

}

void CCRender::SetCurPos(int pi_x, int pi_y)
{
	COORD NewPos;
	NewPos.X = pi_x;	NewPos.Y = pi_y;
	SetConsoleCursorPosition(m_hWinNotActive, NewPos);
}

void CCRender::SetCursorVisible(bool pi_isVisible)
{
	CONSOLE_CURSOR_INFO CursorInfo;
	GetConsoleCursorInfo(m_hWinFirst, &CursorInfo);
	CursorInfo.bVisible = pi_isVisible;
	SetConsoleCursorInfo(m_hWinFirst, &CursorInfo);
	SetConsoleCursorInfo(m_hWinSecond, &CursorInfo);
}

HANDLE CCRender::GetSecondHANDLE()
{
	return this->m_hWinSecond;
}

void CCRender::SwapBuffer()
{
	SetConsoleActiveScreenBuffer(m_hWinNotActive);
	if (m_hWinNotActive == m_hWinFirst) m_hWinNotActive = m_hWinSecond;
	else m_hWinNotActive = m_hWinFirst;
	SetConsoleCursorPosition(m_hWinNotActive, m_cNullPoint);
}