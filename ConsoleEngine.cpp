#include "ConsoleEngine.h"
#include "EngineTimeInfo.h"
#include "WinError.h"

CCEngine::CCEngine(bool pi_isDev = false)
{
	m_CCR = nullptr;

	m_WindowSize = { WINDOWSTANDARTSIZE_X, WINDOWSTANDARTSIZE_Y };
	m_WindowPos =  { WINDOWSTANDARTPOS_X,  WINDOWSTANDARTPOS_Y };
	m_hWindowFirst = NULL;
	m_hWindowSecond = NULL;

	m_bySystemState = STATE_NONE;
	m_byUserGrade = NULL;

	m_isDebug = false;
	m_EngineTimeInfo.SetTime(NULL, NULL);
	m_EngineTimeInfo.Speed = NULL;
	m_ClientInfo = { NULL, NULL, { NULL, NULL }, { NULL, NULL }, NULL };
}

void CCEngine::Prepare(int pi_width, int pi_height)
{
	m_CCR = new CCRender(&m_ClientInfo, &m_EngineTimeInfo);
	m_CCR->Prepare(pi_width, pi_height);
	m_WindowSize = { pi_width, pi_height };
	m_hWindowFirst = GetStdHandle(STD_OUTPUT_HANDLE);
	m_hWindowSecond = m_CCR->GetSecondHANDLE();
	m_byUserGrade = GRADE_PLAYER;
	m_EngineTimeInfo.SetTime(NULLTIME, DELAY);
	m_EngineTimeInfo.Speed = ENGINESPEED;

#ifdef DEBUG
	m_isDebug = true;
#endif
}

void CCEngine::Start()
{
	m_bySystemState = STATE_PLAY;
	while (m_bySystemState != STATE_EXIT)
	{
		Update();
	}
}

void CCEngine::Update()
{
	while (_kbhit())
	{
		char ch = _getch();
		if (ch == '*')
			if (m_EngineTimeInfo.Speed < 1000000)
			m_EngineTimeInfo.Speed *= 10;
		if (ch == '/')
			if (m_EngineTimeInfo.Speed > 0.1)
				m_EngineTimeInfo.Speed /= 10;
		if (GetAsyncKeyState(VK_F1) == -32768)
			m_bySystemState = STATE_EXIT;
		if (GetAsyncKeyState(VK_F2) == -32768)
			NextSystemState();
		if (GetAsyncKeyState(VK_LCONTROL) == -32768/* && GetAsyncKeyState(112) == -32768*/)
		{
			SetSystemState(STATE_STOP);
			m_CCR->Render();
			m_EngineTimeInfo.SetLastTime();
		}
	}
	m_ClientInfo = { m_bySystemState, m_byUserGrade, m_WindowSize, m_WindowPos, m_EngineTimeInfo.Speed };
	//**********************************************************************************************
	//DELETE**********************************************************************************************
	//**********************************************************************************************
	if (GetSystemState() != STATE_STOP)
	{
		m_CCR->Render();
		m_EngineTimeInfo.SetLastTime();
	}
	Tick();
}

void CCEngine::Tick()
{
	m_EngineTimeInfo.Tick();
}

void CCEngine::Complete()
{
	m_CCR->Complete();
}

//With no STATE_EXIT
void CCEngine::NextSystemState()
{
	m_bySystemState++;
	if (m_bySystemState > STATE_PLAY)
		m_bySystemState -= STATE_PLAY;
}
void CCEngine::SetSystemState(byte pi_state)
{
	if (pi_state > -1 && pi_state < 5)
	{
		m_bySystemState = pi_state;
	}
}
byte CCEngine::GetSystemState()
{
	return m_bySystemState;
}
void CCEngine::SetWindowSize(int pi_width, int pi_height)
{ 
	m_WindowSize = { pi_width, pi_height }; 
}
void CCEngine::SetUserGrade(byte pi_byUserGrade)
{
	m_bySystemState = pi_byUserGrade;
}