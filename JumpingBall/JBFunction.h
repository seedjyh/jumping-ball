#define	TIMER_SEC			1317
#define	TIME_REFRESH		10

#define TIMER_COUNTER		1318
#define TIME_COUNTER		10
#define	JUMP_HEIGHT			160
#define BOARD_HEIGHT		30

#define	BALL_RADIUS			6
#define X_SIDE_SAVER		6
#define Y_SIDE_SAVER		6
#define	BOARD_THICKNESS		10
#define	MAX_BOARD_SPEED		7
#define BOARD_ACCELERATION	3

#define EFFICIENCY			0.1

struct BALL {
	double	dxPosition;
	double	dyPosition;
	double	dxSpeed;
	double	dySpeed;
	bool	bAlive;
	BALL () {}
	BALL (POINT p, POINT s)
	{
		this->dxPosition	= p.x;
		this->dyPosition	= p.y;
		this->dxSpeed	= s.x;
		this->dySpeed	= s.y;
	}
	VOID	Reset(int cxClient)
	{
		this->bAlive		= true;
		this->dxPosition	= rand()%(cxClient-10)+5;
		this->dyPosition	= 10;
		this->dxSpeed		= 0;
		this->dySpeed		= 0;
		return;
	}
	VOID	Draw(HDC	hDC)
	{
		Ellipse(hDC, dxPosition-BALL_RADIUS, dyPosition-BALL_RADIUS,
			dxPosition+BALL_RADIUS, dyPosition+BALL_RADIUS);
		return;
	}
	BOOL	Move(int cxClient, int cyClient, int iBoardPosition, int iBoardWide)
	{
		dySpeed+=0.1;
		dxPosition	+=dxSpeed;
		dyPosition	+=dySpeed;
		//Lose
		if (dyPosition>cyClient)
		{
			this->bAlive	= false;
		}
		//Vertical Rebound
		if (X_SIDE_SAVER >= dxPosition || dxPosition >= cxClient-X_SIDE_SAVER)
		{
			this->dxSpeed	= -this->dxSpeed;
		}
		//Board Rebound
		if (dyPosition + Y_SIDE_SAVER >= cyClient - BOARD_HEIGHT &&
			abs(dxPosition-iBoardPosition) <= iBoardWide/2+BALL_RADIUS)
		{
			dxSpeed	+= EFFICIENCY * (dxPosition-iBoardPosition);
			this->dySpeed	= -this->dySpeed;
			return true;
		}
		return false;
	}
};

struct BOARD {
	int		ixPosition;
	int		iWide;
	double	iMoveDirection;
	BOARD	() {}
	BOARD	(int ixposition, int iwide, int iMoveDirection)
	{
		ixPosition		= ixposition;
		iWide			= iwide;
		iMoveDirection	= iMoveDirection;
	}
	VOID	Reset(int cxClient)
	{
		this->iWide		= 100;
		this->ixPosition	= cxClient/2;
		this->iMoveDirection= 0;
		return;
	}
	VOID	Move(int cxClient)
	{
		ixPosition	+= iMoveDirection;
		if (ixPosition <= 0)
		{
			ixPosition	= 0;
		}
		else if (ixPosition >= cxClient)
		{
			ixPosition	= cxClient;
		}
		return;
	}
	VOID	Draw(HDC	hDC, int cyClient)
	{
		RoundRect(hDC, ixPosition-iWide/2, cyClient-BOARD_HEIGHT,
			ixPosition+iWide/2, cyClient-BOARD_HEIGHT+BOARD_THICKNESS, 5, 3);
		return;
	}
};

VOID	DrawPause(HDC hDC, int px, int py);
VOID	DrawRestart(HDC hDC, int px, int py);

VOID	DrawTime(HDC hDC, int px, int py, int time);