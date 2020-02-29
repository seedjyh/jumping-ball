#include <string.h>
#include <stdio.h>
#include <windows.h>

VOID	DrawPause(HDC hDC, int px, int py)
{
	SYSTEMTIME	st;
	GetSystemTime(&st);
	SetTextColor(hDC, RGB(255, 255, 200));
	SetBkMode(hDC, TRANSPARENT);
	TextOut(hDC, px, py, TEXT("Paused"), 6);
	return;
}

VOID	DrawRestart(HDC hDC, int px, int py)
{
	SYSTEMTIME	st;
	GetSystemTime(&st);
	if (0 == st.wSecond%2)
	{
		SetTextColor(hDC, RGB(255, 255, 200));
		SetBkMode(hDC, TRANSPARENT);
		TextOut(hDC, px, py, TEXT("Enter To Restart"), 16);
	}
	return;
}

VOID	DrawTime(HDC hDC, int px, int py, int time)
{
	static	int i, j, hour, minute, second, mcsecond;
	static	TCHAR	Time[16];
	mcsecond= time % 100;
	time	/= 100;
	second	= time % 60;
	time	/=60;
	minute	= time % 60;
	time	/=60;
	hour	= time;

	Time[0]	= '0' + hour/10;
	Time[1]	= '0' + hour%10;
	Time[2]	= 'h';
	Time[3]	= '0' + minute/10;
	Time[4]	= '0' + minute%10;
	Time[5]	= '\'';
	Time[6]	= '0' + second/10;
	Time[7]	= '0' + second%10;
	Time[8]	= '\"';
	Time[9]	= '0' + mcsecond/10;
	Time[10]	= '0' + mcsecond%10;
	Time[11]	= '\0';
	SetTextColor(hDC, RGB(255, 200, 200));
	SetBkMode(hDC, TRANSPARENT);
	TextOut(hDC, px, py, Time, 11);
	return;
}