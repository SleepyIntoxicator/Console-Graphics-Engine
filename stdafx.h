#pragma once

#include <string>
#include <Windows.h>

#ifndef CONSOLECOLOR
#define CONSOLECOLOR

#define CC_BLACK		0x0
#define CC_DARKBLUE		0x1
#define CC_DARKGREEN	0x2
#define CC_DARKAZURE	0x3
#define CC_DARKRED		0x4
#define CC_DARKVIOLET	0x5
#define CC_DARKYELLOW	0x6
#define CC_DARKWHITE	0x7
#define CC_GRAY			0x8
#define CC_BLUE			0x9
#define CC_GREEN		0xA
#define CC_AZURE		0xB
#define CC_RED			0xC
#define CC_VIOLET		0xD
#define CC_YELLOW		0xE
#define CC_WHITE		0xF
#endif //CONSOLECOLOR

#ifndef ORIENTATION	
#define ORIENTATION	

#define TOPLEFT		0x0		//		TL	T	TR
#define TOP			0x1		//		TL	T	TR
#define TOPRIGHT	0x2		//		TL	T	TR
#define LEFT		0x3		//		L	C	 R
#define CENTER		0x4		//		L	C	 R
#define RIGHT		0x5		//		L	C	 R
#define BOTTOMLEFT	0x6		//		BL	B	BR
#define BOTTOM		0x7		//		BL	B	BR
#define BOTTOMRIGHT	0x8		//		BL	B	BR
#endif //ORIENTATION	

#ifndef USERGRADE
#define USERGRADE

#define GRADE_PLAYER	0x0
#define GRADE_PREMIUM	0x1
#define GRADE_BOT		0x2
#define GRADE_DEV		0x3
#define GRADE_TESTER	0x4
#define GRADE_GM		0x5
#define GRADE_ADMIN		0x6
#endif //USERGRADE

#ifndef GAMESTATE
#define GAMESTATE

#define STATE_EXIT		0x0
#define STATE_NONE		0x1
#define STATE_STOP		0x2
#define STATE_DEV		0x3
#define STATE_PLAY		0x4
#endif //GAMESTATE

#define	DEBUG
#undef DEBUG

#define	WINDOWSTANDARTSIZE_X	80
#define WINDOWSTANDARTSIZE_Y	30

#define	WINDOWSTANDARTPOS_X		5
#define WINDOWSTANDARTPOS_Y		5

#define NULLTIME	0

#ifdef DEBUG
#define ENGINESPEED SECPERSEC
#define GAMESPEED SECPERSEC
#define DELAY	1//120
#else
#define ENGINESPEED	SECPERSEC
#define GAMESPEED SECPERSEC
#define DELAY	100
#endif


#ifndef TIMESCALE
#define TIMESKALE

#define SECPERSEC	1

#define SECPERMIN	60
#define SECPERHOUR	3600
#define SECPERDAY	86400

#define MINPERHOUR	60
#define MINPERDAY	1440

#define HOURPERDAY	24
//TODO	#define HOURPER

#endif

#ifndef _SIZE
#define _SIZE
typedef struct _Size
{
	int width;
	int height;
} Size;
#endif //_SIZE

#ifndef _CLIENTINFO
#define _CLIENTINFO
typedef struct _ClientInfo
{
	byte	bySystemState;
	byte	byUserGrade;
	Size	WindowSize;
	COORD	WindowPos;
	float	Speed;
} SClientInfo;
#endif

#define NEWCOUNTER int i = 0;
#define COUNTER i++			

std::string GetStr(byte pi_bySize, byte pi_ch);
std::string GetErasedStringf(float pi_val, int n);

std::string __cdecl	make_string(LPCSTR format, ...);
LPCSTR		__cdecl make_char(LPCSTR format, ...);

LPCSTR GetStateName(byte pi_systemState);