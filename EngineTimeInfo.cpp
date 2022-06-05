#include "EngineTimeInfo.h"

CEngineTimeInfo::CEngineTimeInfo(UINT64 pi_time, USHORT pi_delay)
{
	Time = pi_time;
	Delay = pi_delay;
	FPS = -1;

	m_StartTime = time(NULL);
	localtime_s(&m_stu, &m_StartTime);

	Update();
}


void CEngineTimeInfo::SetTime(UINT64 pi_time, USHORT pi_delay)
{
	Time = pi_time;
	Delay = pi_delay;

	m_StartTime = time(NULL);
	m_EngineTime = time(NULL);
	localtime_s(&m_stu, &m_StartTime);

	Update();
}

void CEngineTimeInfo::Tick()
{
	Delay += clock() - Time;
	Delay /= 2;
	Time = clock() * Speed;


	Update();
}

void CEngineTimeInfo::Update()
{
	if (Delay == 0)
		FPS = -1;
	else
		FPS = 1000 / Delay;

	/*Sec = (Time + 3600 ) / 1000;
	Min = Sec / 60;
	H = Min / 60;
	Day = H / 24;

	Sec -= Min * 60;
	Min -= H * 60;
	H -= H / 24 * 24;*/
	
	m_SystemTime = time(NULL);
	m_EngineTime = time(NULL);
	localtime_s(&m_sysu, &m_SystemTime);
	localtime_s(&m_eu, &m_EngineTime);
	/*Sec =	m_sysu.tm_sec;
	Min =	m_sysu.tm_min;
	H =		m_sysu.tm_hour;
	Day =	m_sysu.tm_yday;
	Month = m_sysu.tm_mon;*/

	m_eu.tm_sec		-= m_stu.tm_sec	;
	m_eu.tm_min		-= m_stu.tm_min	;
	m_eu.tm_hour	-= m_stu.tm_hour;
	m_eu.tm_yday	-= m_stu.tm_yday;
	m_eu.tm_mon		-= m_stu.tm_mon	;
	m_eu.tm_year	-= m_stu.tm_year;
	if (m_eu.tm_sec < 0)
	{
		m_eu.tm_min--;
		m_eu.tm_sec += 60;
	}
	if (m_eu.tm_min < 0)
	{
		m_eu.tm_hour--;
		m_eu.tm_min += 60;
	}
	if (m_eu.tm_hour < 0)
	{
		m_eu.tm_mon--;
		m_eu.tm_hour += 24;
	}
	if (m_eu.tm_mon < 0)
	{
		m_eu.tm_mon = 0; //if new year - error
	}
	Sec =	m_sysu.tm_sec;
	Min =	m_sysu.tm_min;
	H =		m_sysu.tm_hour;
	Day =	m_sysu.tm_yday;
	Month = m_sysu.tm_mon;
}

void CEngineTimeInfo::SetLastTime()
{
	LastTime = clock();
}

int CEngineTimeInfo::GetLastDiffTime()
{
	return clock() - LastTime;
}