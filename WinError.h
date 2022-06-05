#ifndef _WINERROR
#define _WINERROR
#include "BaseConWin.h"

class CWinError : public CBaseConWin
{
public:
	CWinError(HANDLE pi_hWND);
	void Update();
	void Render();
private:

public:

};
/*
Expression	:
Function	:
File		:
Line		:
Description	:
*/
/*
Function	: CPatrolPathManager::select_point


FATAL ERROR [error]Expression    : !m_error_code
[error]Function      : raii_guard::~raii_guard
[error]File          : D:\prog_repository\sources\trunk\xrServerEntities\script_storage.cpp
[error]Line          : 748
[error]Description   : ...r. - Зов Припяти\gamedata\scripts\sound_theme.script:256: bad argument #2 to 'random' (interval is empty)
*/

#endif