#include "GameTimeInfo.h"
#include "stdafx.h"

#define _GAMETIMEINFO
#ifndef _GAMETIMEINFO

void CGameTimeInfo::Update()
{
	if (m_Sec >= SECPERMIN)
	{
		m_Min += m_Sec / SECPERMIN;
		m_Sec -= (m_Sec / 60) * 60;
	}
	if (m_Min >= 59)
	{
		m_Hour += m_Min / 60;
		m_Min -= (m_Min / 60) * 60;
	}
	if (m_Hour >= 23)
	{
		m_Day += m_Hour / 24;
		m_Hour -= (m_Hour / 24) * 24;
		GetSystemTime(&tm);

	}
	if (m_Day >= 28)
	{
		
		switch (m_Month)
		{
		case January:
		case March:
		case May:
		case July:
		case August:
		case October:
		case December:
			if (m_Day > DJanuary)
			{
				m_Month += m_Day / DJanuary;
				m_Day -= (m_Day / DJanuary) * DJanuary;
			}
			break;
		case April:
		case June:
		case September:
		case November:
			if (m_Day > DApril)
			{
				m_Month += m_Day / DApril;
				m_Day -= (m_Day / DApril) * DApril;
			}
			break;
		case Febryary:
			if (m_Day > DFebryary)
			{
				m_Month += m_Day / DFebryary;
				m_Day -= (m_Day / DFebryary) * DFebryary;
			}
			break;
		default:
			break;
		}
	}
	if (m_Month > 12)
	{
		m_Year += m_Month / 12;
		m_Month -= m_Month / 12 * 12;
	}
}

#endif