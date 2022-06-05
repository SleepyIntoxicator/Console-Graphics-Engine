#include "stdafx.h"
std::string GetErasedStringf(float pi_val, int n)
{
	std::string strVal = std::to_string(pi_val);
	return strVal.erase(strVal.find(".") + n, 10);
}

std::string GetStr(byte pi_bySize, byte pi_ch)
{
	std::string str;
	str.resize(pi_bySize, pi_ch);
	return str;
	
}


std::string __cdecl	make_string(LPCSTR format, ...)
{
	va_list		args;
	va_start(args, format);

	char		temp[4096];
	vsprintf_s(temp, format, args);
	
	return		std::string(temp);
}

LPCSTR __cdecl make_char(LPCSTR format, ...)
{
	va_list		args;
	va_start(args, format);

	char		temp[4096];
	vsprintf_s(temp, format, args);

	return		temp;
}

LPCSTR GetStateName(byte pi_systemState)
{
	switch (pi_systemState)
	{
	case STATE_EXIT:
		return "EXIT";
		break;
	case STATE_NONE:
		return "NONE";
		break;
	case STATE_STOP:
		return "STOP";
		break;
	case STATE_DEV:
		return "DEV";
		break;
	case STATE_PLAY:
		return "PLAY";
		break;
	default:
		return "NOSTATE";
		break;
	}
	return "NOSTATE";
}
