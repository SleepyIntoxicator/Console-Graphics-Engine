#include "stdafx.h"
#include <time.h>
#ifndef _TIMEINFO
#define _TIMEINFO
class CEngineTimeInfo
{
public:
	UINT64 Time; // Время прошедшее со старта (мс)
	USHORT Delay;
	float Speed; //Debug speed
	short FPS;

	byte Sec;
	byte Min;
	byte H;
	int Day;
	byte Month;
	
	CEngineTimeInfo(void) : Time(NULL), Delay(NULL), Speed(1.0f), Sec(NULL), Min(NULL), H(NULL), Day(NULL), Month(NULL) {}
	CEngineTimeInfo(UINT64 pi_time, USHORT pi_delay);

	void SetTime(UINT64 pi_time, USHORT pi_delay);
	void Tick();

private:

	UINT64 LastTime;
	void Update();

	time_t m_SystemTime;
	struct tm m_sysu;

	time_t m_StartTime;
	struct tm m_stu;

	time_t m_EngineTime;
	struct tm m_eu;
public:
	void SetLastTime();
	int GetLastDiffTime();
};
#endif