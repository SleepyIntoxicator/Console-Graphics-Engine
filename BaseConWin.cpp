#include "BaseConWin.h"

CBaseConWin::CBaseConWin(HANDLE pi_hWND) : m_hWND(pi_hWND){
}

CBaseConWin::~CBaseConWin()
{

}

void CBaseConWin::Update()
{

}

void CBaseConWin::Render()
{
	m_pRenderer->RenderBackground(m_Position, m_Size, CC_GRAY);
}

//void CBaseConWin::
void CBaseConWin::SetPosition(SHORT pi_x, SHORT pi_y)
{
	if (pi_x > 0 && pi_y > 0)
	m_Position = { pi_x, pi_y };
	//TODO CreateError("");
}

void CBaseConWin::SetPosition(COORD pi_position)
{
	m_Position = pi_position;
}

void CBaseConWin::SetSize(int pi_w, int pi_h)
{
	if (pi_w > 0 && pi_h > 0)
		m_Size = { pi_w, pi_h };
}

void CBaseConWin::SetSize(Size pi_size)
{
	m_Size = pi_size;
}

void CBaseConWin::SetColor(byte pi_backcolor, byte pi_textcolor)
{
	m_wColor = m_pRenderer->GetColor(pi_backcolor, pi_textcolor);
}

void CBaseConWin::SetColor(WORD pi_color)
{
	m_wColor = pi_color;
}

void CBaseConWin::GetWinHandle(HANDLE &hWND)
{
	hWND = m_hWND;
}

void CBaseConWin::GetWinPtr(CBaseConWin *pBaseWin)
{
	pBaseWin = this;
}