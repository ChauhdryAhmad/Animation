#include<iostream>
#include<iomanip>
#include<conio.h>
#include<windows.h>
#include<math.h>
#define ROWS 85
#define COLS 166
#define Pi 3.1416
#define maxDim 100
#define DBLACK 0
#define BLUE 1
#define GREEN 2
#define CYAN 3
#define RED 4
#define BROWN 5
#define LIGHTBROWN 6
#define LIGHTGREY 7
#define DARKGREY 8
#define YELLOW 9
#define DARKbROWN 10
#define GREEN 11
#define LIGHTGREEN 12
#define DARKGREEN 13
#define ORANGE 14
#define PURPLE 15

using namespace std;

void mySleep(float  a)
{
	for (int i = 1; i <= 1000000 * a; i++);
}

void mySwap(int& a, int& b)
{
	int temp = a;
	a = b;
	b = temp;
}

void SetClr(int clr)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), clr);
}

void getRowColbyLeftClick(int& rpos, int& cpos)
{
	HANDLE hInput = GetStdHandle(STD_INPUT_HANDLE);
	DWORD Events;
	INPUT_RECORD InputRecord;
	SetConsoleMode(hInput, ENABLE_PROCESSED_INPUT | ENABLE_MOUSE_INPUT | ENABLE_EXTENDED_FLAGS);
	do
	{
		ReadConsoleInput(hInput, &InputRecord, 1, &Events);
		if (InputRecord.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)
		{
			cpos = InputRecord.Event.MouseEvent.dwMousePosition.X;
			rpos = InputRecord.Event.MouseEvent.dwMousePosition.Y;
			break;
		}
	} while (true);
}

void gotoRowCol(int rpos, int cpos)
{
	COORD scrn;
	HANDLE hOuput = GetStdHandle(STD_OUTPUT_HANDLE);
	scrn.X = cpos;
	scrn.Y = rpos;
	SetConsoleCursorPosition(hOuput, scrn);
}

void fan1(int h, int w, char sym)
{
	
	for (int i = 0; i < h/2 ; i++)
	{
		for (int j = i ; j <= w - i; j++)
		{
			gotoRowCol(i, j);
			cout << sym;
		}
	}
	for (int i = h / 2; i <= h; i++)
	{
		for (int j = w - i; j <= i; j++)
		{
			gotoRowCol(i, j);
			cout << sym;
		}
	}
	
}

void fan2(int h, int w, char sym)
{
	gotoRowCol(0, 0);
	cout << sym;
	gotoRowCol(0,w);
	cout << sym;
	for (int i = 1; i < h / 2; i++)
	{
		for (int s = 0; s <= i; s++)
		{
			gotoRowCol(i, s);
			cout << sym;
		}
		for (int s = w-i; s <= w; s++)
		{
			gotoRowCol(i, s);
			cout << sym;
		}
	}
	for (int i = h / 2; i < h; i++)
	{
		gotoRowCol(i, i);
		cout << sym;
		for (int s = 0; s <= w-i; s++)
		{
			gotoRowCol(i, s);
			cout << sym;
		}
		for (int s = i; s <= w; s++)
		{
			gotoRowCol(i, s);
			cout << sym;
		}
		gotoRowCol(i, w - i);
		cout << sym;
	}
	gotoRowCol(h, 0);
	cout << sym;
	gotoRowCol(h, w);
	cout << sym;
}

void L2R(int r, int cs, int ce, char sym)
{
	for (int i = cs; i < ce; i++)
	{
		gotoRowCol(r, i);
		cout << sym;
	}
}

void T2B(int c, int rs, int re, char sym)
{
	for (int i = rs; i < re; i++)
	{
		gotoRowCol(i, c);
		cout << sym;
	}
}

void L2RD(int cs, int rs, int ce, int re, char sym)
{
	for (int r = rs, c = cs; c <= ce || r <= re; r++, c++)
	{
		gotoRowCol(r, c);
		cout << sym;
	}
}

void R2LD(int cs, int rs, int ce, int re, char sym)
{
	for (int r = rs, c = cs; c >= ce || r <= re; r++, c--)
	{
		gotoRowCol(r, c);
		cout << sym;
	}
}

void printCartoon(int cr, int cc)
{
	gotoRowCol(cr, cc);
	cout << '|';
	gotoRowCol(cr - 1, cc);
	cout << '0';
	gotoRowCol(cr - 1, cc - 1);
	cout<<'\\';
	gotoRowCol(cr - 1, cc + 1);
	cout << '/';
	gotoRowCol(cr + 1, cc - 1);
	cout << '/';
	gotoRowCol(cr + 1, cc + 1);
	cout << '\\';
}

void printA(int r, int c, int s, char sym)
{
	L2R(r, c - s, c + s, sym);
	T2B(c - s, r - s, r + s+1, sym);
	L2R(r - s, c - s, c + s, sym);
	T2B(c + s, r - s, r + s + 1, sym);
}

void printH(int r, int c, int s, char sym)
{
	L2R(r, c - s, c + s, sym);
	T2B(c - s, r - s, r + s + 1, sym);
	T2B(c + s, r - s, r + s + 1, sym);
}

void printM(int r, int c, int s, char sym)
{
	L2RD(c - s, r - s, c, r, sym);
	R2LD(c + s, r - s, c, r, sym);
	T2B(c - s, r - s, r + s + 1, sym);
	T2B(c + s, r - s, r + s + 1, sym);
}

void printD(int r, int c, int s, char sym)
{
	L2R(r - s, c - s, c + s, sym);
	L2R(r + s, c - s, c + s, sym);
	T2B(c - s, r - s + 1, r + s, sym);
	T2B(c + s, r - s + 1, r + s, sym);
}

void circle(int h, int k, int r, char sym)
{
	for (int theta = 0; theta < 360; theta++)
	{
		float rad = theta * Pi / 180;
		int x = r * cos(rad) + h;
		int y = r * sin(rad) + k;
		gotoRowCol(x, y);
		cout << sym;
	}
}

void arcDown(int h, int k, int r, char sym)
{
	for (int theta = 90; theta < 270; theta++)
	{
		float rad = theta * Pi / 180;
		int x = r * cos(rad) + h;
		int y = r * sin(rad) + k;
		gotoRowCol(x, y);
		cout << sym;
	}
}

void arcUp(int h, int k, int r, char sym)
{
	for (int theta = 270; theta < 450; theta++)
	{
		float rad = theta * Pi / 180;
		int x = r * cos(rad) + h;
		int y = r * sin(rad) + k;
		gotoRowCol(x, y);
		cout << sym;
	}
}

void spiral(int h, int k, int arms, char sym)
{
	float R = 1;
	float armsinterval = (ROWS / 2.0) / arms;
	float delta = armsinterval / 360;
	while (R <= ROWS / 2)
	{
		for (int theta = 0; theta < 360; theta++)
		{
			if (R > ROWS / 2.0)
				break;
			float rad = theta * Pi / 180;
			int x = R * cos(rad) + h;
			int y = R * sin(rad) + k;
			gotoRowCol(x, y);
			cout << sym;
			R += delta;
		}
	}
}

void sinewave(int w, int cr, int col, int amp, char sym)
{
	float dTheta = (w * 360.0) / col;
	float theta = 0;
	for (int c = 0; c < col; c++)
	{
		float rad = theta * Pi / 180;
		int r = amp * (-1) * sin(rad) + cr;
		gotoRowCol(r, c);
		cout << sym;
		theta += dTheta;
	}
}

void sinewave2(int w, int cr, int col, int amp, char sym)
{
	float dTheta = (w * 360.0) / col;
	float theta = 0;
	for (int c = 0; c < col; c++)
	{
		float rad = theta * Pi / 180;
		int r = amp * sin(rad) + cr;
		gotoRowCol(r, c);
		cout << sym;
		theta += dTheta;
	}
}

void sinewaveName(int w, int cr, int col, int amp, char sym[5])
{
	float dTheta = (w * 360.0) / col;
	float theta = 0;
	for (int c = 0, ri = 0; c < col; c++, ri++)
	{
		float rad = theta * Pi / 180;
		int r = amp * (-1) * sin(rad) + cr;
		gotoRowCol(r, c);
		cout << sym[ri];
		if (ri == 5)
			ri = 0;
		theta += dTheta;
	}
}

void movingSinewave(int w, int cr, int col, int amp, char sym, int sh)
{
	float dTheta = (w * 360.0) / col;
	float theta = sh;
	for (int c = 0; c < col; c++)
	{
		float rad = theta * Pi / 180;
		int r = amp * (-1) * sin(rad) + cr;
		gotoRowCol(r, c);
		cout << sym;
		theta += dTheta;
	}
}

void movingSinewaveName(int w, int cr, int col, int amp, char sym[5], int sh)
{
	float dTheta = (w * 360.0) / col;
	float theta = sh;
	for (int c = 0, ri = 0; c < col; c++, ri++)
	{
		float rad = theta * Pi / 180;
		int r = amp * (-1) * sin(rad) + cr;
		gotoRowCol(r, c);
		cout << sym[ri];
		if (ri == 5)
			ri = 0;
		theta += dTheta;
	}
}

void InitBox(int B[][maxDim], int dim)
{
	for (int i = 0; i < dim / 2; i++)
	{
		int count = 1;
		for (int c = i; c < dim - 1-i; c++, count++)
		{
			B[i][c] = count;
		}
		for (int r = i; r < dim - 1-i; r++, count++)
		{
			B[r][dim - 1-i] = count;
		}
		for (int c = dim - 1-i; c > 0+i; c--, count++)
		{
			B[dim - 1-i][c] = count;
		}
		for (int r = dim - 1-i; r > 0+i; r--, count++)
		{
			B[r][i] = count;
		}
	}
}

void printBox(int B[][maxDim], int dim)
{
	for (int r = 0; r < dim; r++)
	{
		for (int c = 0; c < dim; c++)
		{
			cout << setw(3) << B[r][c];
		}
		cout << endl;
	}
}

void clockRotation(int B[][maxDim], int dim)
{
	int temp;
	for (int i = 0; i < dim / 2; i++)
	{
		temp = B[i+1][i];
		for (int c = i; c < dim - 1 - i; c++)
		{
			mySwap(temp, B[i][c]);
		}
		for (int r = i; r < dim - 1 - i; r++)
		{
			mySwap(temp, B[r][dim - 1 - i]);
		}
		for (int c = dim - 1 - i; c > 0 + i; c--)
		{
			mySwap(temp, B[dim - 1 - i][c]);
		}
		for (int r = dim - 1 - i; r > 0 + i; r--)
		{
			mySwap(temp, B[r][i]);
		}
	}
}

void antiRotation(int B[][maxDim], int dim)
{
	int temp;
	for (int i = 0; i < dim / 2; i++)
	{
		temp = B[i][i];
		for (int r = i + 1; r < dim - i; r++)
		{
			mySwap(temp, B[r][i]);
		}
		for (int c = i + 1; c < dim - i; c++)
		{
			mySwap(temp, B[dim - 1 - i][c]);
		}
		for (int r = dim - 1 - i; r >= 0 + i; r--)
		{
			mySwap(temp, B[r][dim - 1 - i]);
		}
		for (int c = dim - 1 - i; c >= 0 + i; c--)
		{
			mySwap(temp, B[i][c]);
		}
	}
}

void L2Rrec(int r, int cs, int ce, char sym)
{
	for (int i = cs; i < ce; i++)
	{
		gotoRowCol(r, i);
		cout << sym;
		mySleep(10);
	}
}

void T2Brec(int c, int rs, int re, char sym)
{
	for (int i = rs; i < re; i++)
	{
		gotoRowCol(i, c);
		cout << sym;
		mySleep(10);
	}
}

void R2Lrec(int r, int cs, int ce, char sym)
{
	for (int i = ce - 1; i >= cs; i--)
	{
		gotoRowCol(r, i);
		cout << sym;
		mySleep(10);
	}
}

void B2Trec(int c, int rs, int re, char sym)
{
	for (int i = re - 1; i >= rs; i--)
	{
		gotoRowCol(i, c);
		cout << sym;
		mySleep(10);
	}
}

void spiralRectangle(int row, int col, int nor, char sym)
{
	for (int i = 1; i <= nor; i++)
	{
		SetClr(rand() % 15);
		L2Rrec(i - 1, i - 1, col - i, sym);
		T2Brec(col - i, i - 1, row - i, sym);
		R2Lrec(row - i, i - 1, col - i + 1, sym);
		B2Trec(i - 1, i, row - i, sym);
	}
	for (int i = nor; i >= 1; i--)
	{
		T2Brec(i - 1, i, row - i, ' ');
		L2Rrec(row - i, i - 1, col - i + 1, ' ');
		B2Trec(col - i, i - 1, row - i, ' '); 
		R2Lrec(i - 1, i - 1, col - i, ' ');
	}
}

void sinewave3(int w, int cr, int col, int amp, char sym, int cs)
{
	float dTheta = (w * 360.0) / col;
	float theta = 0;
	for (int c = cs; c < col; c++)
	{
		float rad = theta * Pi / 180;
		int r = amp * (-1) * sin(rad) + cr;
		gotoRowCol(r, c);
		cout << sym;
		theta += dTheta;
	}
}

void book(int row, int col, char sym)
{
	sinewave2(1, 3, col / 2, 3, sym);
	sinewave3(2, 3, col, 3, sym, col/2);
	T2B(0, 4, row - 4, sym);
	T2B(col / 2, 3, row -4, sym);
	T2B(col - 1, 3, row - 4, sym);
	sinewave2(1, row - 3, col / 2, 3, sym);
	sinewave3(2, row - 3, col, 3, sym, col / 2);

}












int mainBook()
{
	//166 85
	cout << "My screen dimension are (width : 166 & height : 85)";
	_getch();
	system("cls");
	char sym = '*';
	book(ROWS, COLS, sym);
	return _getch();
}

int mainSpiralRectangle()
{
	//166 85
	cout << "My screen dimension are (width : 166 & height : 85)";
	_getch();
	system("cls");
	int nor;
	char sym = '*';
	cout << "Enter number of rectangles : ";
	cin >> nor;
	system("cls");
	spiralRectangle(ROWS, COLS, nor, sym);
	return _getch();
}

int mainAntiRotation()
{
	//166 85
	cout << "My screen dimension are (width : 166 & height : 85)";
	_getch();
	system("cls");
	int B[maxDim][maxDim] = {};
	int dim;
	cout << "Enter dimensions (odd number) : ";
	cin >> dim;
	while (dim % 2 == 0)
	{
		cout << "\nEnter Odd Number";
		cout << "\nEnter dimensions (odd number) : ";
		cin >> dim;
	}
	system("cls");
	InitBox(B, dim);
	while (true)
	{
		antiRotation(B, dim);
		mySleep(150);
		gotoRowCol(0, 0);
		printBox(B, dim);
		mySleep(100);
	}
	return _getch();
}

int mainClockRotation()
{
	//166 85
	cout << "My screen dimension are (width : 166 & height : 85)";
	_getch();
	system("cls");
	int B[maxDim][maxDim] = {};
	int dim;
	cout << "Enter dimensions (odd number) : ";
	cin >> dim;
	while (dim % 2 == 0)
	{
		cout << "\nEnter Odd Number";
		cout << "\nEnter dimensions (odd number) : ";
		cin >> dim;
	}
	system("cls");
	InitBox(B, dim);
	while (true)
	{
		clockRotation(B, dim);
		mySleep(150);
		gotoRowCol(0, 0);
		printBox(B, dim);
		mySleep(100);
	}
	return _getch();
}

int mainBox()
{
	//166 85
	cout << "My screen dimension are (width : 166 & height : 85)";
	_getch();
	system("cls");
	int B[maxDim][maxDim] = {};
	int dim;
	cout << "Enter dimensions (odd number) : ";
	cin >> dim;
	while (dim % 2 == 0)
	{
		cout << "\nEnter Odd Number";
		cout << "\nEnter dimensions (odd number) : ";
		cin >> dim;
	}
	system("cls");
	InitBox(B, dim);
	gotoRowCol(0, 0);
	printBox(B, dim);
		
	return _getch();
}

int mainAmplitute()
{
	//166 85
	cout << "My screen dimension are (width : 166 & height : 85)";
	_getch();
	system("cls");
	int cr = ROWS / 2, amp, n;
	char sym = -37;
	cout << "\nNumber of waves : ";
	cin >> n;
	_getch();
	system("cls");
	while (true)
	{
		for (amp = 1; amp < 20; amp++)
		{
			sinewave(n, cr, COLS, amp, sym);
			mySleep(5);
			sinewave(n, cr, COLS, amp, ' ');
		}
		for (amp = 20; amp > 0; amp--)
		{
			sinewave(n, cr, COLS, amp, sym);
			mySleep(5);
			sinewave(n, cr, COLS, amp, ' ');
		}
	}
	return _getch();
}

int mainMovingSinewaveName()
{
	//166 85
	cout << "My screen dimension are (width : 166 & height : 85)";
	_getch();
	system("cls");
	int cr = ROWS / 2, amp, n, sh = 0;
	char sym[5] = {'a','h','m','a','d'};
	cout << "\nAmplitute : ";
	cin >> amp;
	cout << "\nNumber of waves : ";
	cin >> n;
	_getch();
	system("cls");
	while (true)
	{
		movingSinewaveName(n, cr, COLS, amp, sym, sh);
		mySleep(5);
		movingSinewave(n, cr, COLS, amp, ' ', sh);
		sh++;
	}
	return _getch();
}

int mainMovingSinewave()
{
	//166 85
	cout << "My screen dimension are (width : 166 & height : 85)";
	_getch();
	system("cls");
	int cr = ROWS / 2, amp, n, sh = 0;
	char sym = -37;
	cout << "\nAmplitute : ";
	cin >> amp;
	cout << "\nNumber of waves : ";
	cin >> n;
	_getch();
	system("cls");
	while (true)
	{
		movingSinewave(n, cr, COLS, amp, sym, sh);
		mySleep(5);
		movingSinewave(n, cr, COLS, amp, ' ', sh);
		sh++;
	}
	return _getch();
}

int mainSinewaveName()
{
	//166 85
	cout << "My screen dimension are (width : 166 & height : 85)";
	_getch();
	system("cls");
	int cr = ROWS / 2, amp, n;
	char sym[5] = {'a','h','m','a','d'};
	cout << "\nAmplitute : ";
	cin >> amp;
	cout << "\nNumber of waves : ";
	cin >> n;
	_getch();
	system("cls");
		sinewaveName(n, cr, COLS, amp, sym);
	return _getch();
}

int mainSinewave()
{
	//166 85
	cout << "My screen dimension are (width : 166 & height : 85)";
	_getch();
	system("cls");
	int cr = ROWS / 2, amp, n;
	char sym = -37;
	cout << "\nAmplitute : ";
	cin >> amp;
	cout << "\nNumber of waves : ";
	cin >> n;
	_getch();
	system("cls");
	sinewave(n, cr, COLS, amp, sym);
	return _getch();
}

int mainSpiral()
{
	//166 85
	cout << "My screen dimension are (width : 166 & height : 85)";
	_getch();
	system("cls");
	int h = ROWS / 2;
	int k = COLS / 2;
	char sym = -37;
	spiral(h, k, 16, sym);

	return _getch();
}

int mainSmily()
{
	//166 85
	cout << "My screen dimension are (width : 166 & height : 85)";
	_getch();
	system("cls");
	int h = ROWS / 2;
	int k = COLS / 2;
	char sym = -37;
	int r = ROWS / 2;
	circle(h, k, r, sym);
	arcDown(22, 65, 7, sym);
	circle(25, 65, 5, sym);
	arcDown(22, 100, 7, sym);
	circle(25, 100, 5, sym);
	arcUp(55, 83, 18, sym);

	return _getch();
}

int mainBaloon()
{
	//166 85
	cout << "My screen dimension are (width : 166 & height : 85)";
	_getch();
	system("cls");
	int h = ROWS / 2;
	int k = COLS / 2;
	char sym = -37;
	int r = 1;
	char e;
	cout << "Enter F to expand the ballon and I to inflate the baloon\n";
	while (r <= ROWS / 2)
	{
		gotoRowCol(1, 0);
		cin >> e;
		if (e == 'F' || e == 'f')
		{
			circle(h, k, r + 3, sym);
			circle(h, k, r, ' ');
			r+=3;
		}
		if (e == 'I' || e == 'i')
		{
			circle(h, k, r - 3, sym);
			circle(h, k, r, ' ');
			r -= 3;
		}
	}
	system("cls");
	for (int r = 5; r < ROWS; r++)
	{
		for (int c = 5; c < COLS; c++)
		{
			gotoRowCol(r, c+1);
			cout << sym;
			gotoRowCol(r, c);
			cout << ' ';
		}
	}
	gotoRowCol(ROWS / 2, COLS / 2);
	cout << "BALOON BLASTS\n";
	return _getch();
}

int mainGrowingCircle()
{
	//166 85
	cout << "My screen dimension are (width : 166 & height : 85)";
	_getch();
	system("cls");
	int h = ROWS / 2;
	int k = COLS / 2;
	char sym = -37;
	while (true)
	{
		for (int r = 1; r <= ROWS / 2; r++)
		{
			circle(h, k, r, sym);
			mySleep(10);
			circle(h, k, r, ' ');
		}
		for (int r = ROWS / 2; r >= 1; r--)
		{
			circle(h, k, r, sym);
			mySleep(10);
			circle(h, k, r, ' ');
		}
	}
	return _getch();
}

int mainPrintCircle()
{
	//166 85
	cout << "My screen dimension are (width : 166 & height : 85)";
	_getch();
	system("cls");
	int h = ROWS / 2;
	int k = COLS / 2;
	int r = ROWS / 2;
	char sym = -37;
	circle(h, k, r, sym);

	return _getch();
}

int mainNamewww()
{
	//166 85
	cout << "My screen dimension are (width : 166 & height : 85)";
	_getch();
	system("cls");
	char sym = -37;
	char sym2 = ' ';
	for (int r1 = 5, c1 = 10, r2 = 75, c2 = 155; r1 <= 80 || c1 <= 160 || r2 >= 5 || c2 >= 10; r1 += 3, c1 += 3, r2 += 3, c2 += 3)
	{
		printA(r1, 5, 5, sym);
		mySleep(5);
		printA(r1, 5, 5, sym2);

		printH(80, c1, 5, sym);
		mySleep(5);
		printH(80, c1, 5, sym);

		printM(r2, 160, 5, sym);
		mySleep(5);
		printM(r2, 160, 5, sym);

		printD(5, c2, 5, sym);
		mySleep(5);
		printD(5, c2, 5, sym);

	}
	return 0;
}

int mainNameMovingAllDir()
{
	//166 85
	cout << "My screen dimension are (width : 166 & height : 85)";
	_getch();
	system("cls");
	char sym = -37;
	char sym2 = ' ';
	for (int rv = 5; rv <= 80; rv += 3)
	{
		SetClr(rand() % 15);
		printA(rv, 5, 5, sym);
		mySleep(5);
		printA(rv, 5, 5, sym2);
		mySleep(5);
	}
	for (int ch = 5; ch <= 160; ch += 3)
	{
		SetClr(rand() % 15);
		printA(80, ch, 5, sym);
		mySleep(5);
		printA(80, ch, 5, sym2);
		mySleep(5);
	}
	for (int rv = 80; rv >= 5; rv -= 3)
	{
		SetClr(rand() % 15);
		printA(rv, 160, 5, sym);
		mySleep(5);
		printA(rv, 160, 5, sym2);
		mySleep(5);
	}
	for (int ch = 160; ch >= 5; ch -= 3)
	{
		SetClr(rand() % 15);
		printA(5, ch, 5, sym);
		mySleep(5);
		printA(5, ch, 5, sym2);
		mySleep(5);
	}
	for (int r = 5, c = 5; r <= 80 && c <= 160; r += 3, c += 3)
	{
		SetClr(rand() % 15);
		printA(r, c, 5, sym);
		mySleep(5);
		printA(r, c, 5, sym2);
		mySleep(5);
	}
	for (int r = 5, c = 160; r <= 80 && c >= 5; r += 3, c -= 3)
	{
		SetClr(rand() % 15);
		printA(r, c, 5, sym);
		mySleep(5);
		printA(r, c, 5, sym2);
		mySleep(5);
	}
	for (int rv = 5; rv <= 80; rv += 3)
	{
		SetClr(rand() % 15);
		printH(rv, 5, 5, sym);
		mySleep(5);
		printH(rv, 5, 5, sym2);
		mySleep(5);
	}
	for (int ch = 5; ch <= 160; ch += 3)
	{
		SetClr(rand() % 15);
		printH(80, ch, 5, sym);
		mySleep(5);
		printH(80, ch, 5, sym2);
		mySleep(5);
	}
	for (int rv = 80; rv >= 5; rv -= 3)
	{
		SetClr(rand() % 15);
		printH(rv, 160, 5, sym);
		mySleep(5);
		printH(rv, 160, 5, sym2);
		mySleep(5);
	}
	for (int ch = 160; ch >= 5; ch -= 3)
	{
		SetClr(rand() % 15);
		printH(5, ch, 5, sym);
		mySleep(5);
		printH(5, ch, 5, sym2);
		mySleep(5);
	}
	for (int r = 5, c = 5; r <= 80 && c <= 160; r += 3, c += 3)
	{
		SetClr(rand() % 15);
		printH(r, c, 5, sym);
		mySleep(5);
		printH(r, c, 5, sym2);
		mySleep(5);
	}
	for (int r = 5, c = 160; r <= 80 && c >= 5; r += 3, c -= 3)
	{
		SetClr(rand() % 15);
		printH(r, c, 5, sym);
		mySleep(5);
		printH(r, c, 5, sym2);
		mySleep(5);
	}
	for (int rv = 5; rv <= 80; rv += 3)
	{
		SetClr(rand() % 15);
		printM(rv, 5, 5, sym);
		mySleep(5);
		printM(rv, 5, 5, sym2);
		mySleep(5);
	}
	for (int ch = 5; ch <= 160; ch += 3)
	{
		SetClr(rand() % 15);
		printM(80, ch, 5, sym);
		mySleep(5);
		printM(80, ch, 5, sym2);
		mySleep(5);
	}
	for (int rv = 80; rv >= 5; rv -= 3)
	{
		SetClr(rand() % 15);
		printM(rv, 160, 5, sym);
		mySleep(5);
		printM(rv, 160, 5, sym2);
		mySleep(5);
	}
	for (int ch = 160; ch >= 5; ch -= 3)
	{
		SetClr(rand() % 15);
		printM(5, ch, 5, sym);
		mySleep(5);
		printM(5, ch, 5, sym2);
		mySleep(5);
	}
	for (int r = 5, c = 5; r <= 80 && c <= 160; r += 3, c += 3)
	{
		SetClr(rand() % 15);
		printM(r, c, 5, sym);
		mySleep(5);
		printM(r, c, 5, sym2);
		mySleep(5);
	}
	for (int r = 5, c = 160; r <= 80 && c >= 5; r += 3, c -= 3)
	{
		SetClr(rand() % 15);
		printM(r, c, 5, sym);
		mySleep(5);
		printM(r, c, 5, sym2);
		mySleep(5);
	}
	for (int rv = 5; rv <= 80; rv += 3)
	{
		SetClr(rand() % 15);
		printA(rv, 5, 5, sym);
		mySleep(5);
		printA(rv, 5, 5, sym2);
		mySleep(5);
	}
	for (int ch = 5; ch <= 160; ch += 3)
	{
		SetClr(rand() % 15);
		printA(80, ch, 5, sym);
		mySleep(5);
		printA(80, ch, 5, sym2);
		mySleep(5);
	}
	for (int rv = 80; rv >= 5; rv -= 3)
	{
		SetClr(rand() % 15);
		printA(rv, 160, 5, sym);
		mySleep(5);
		printA(rv, 160, 5, sym2);
		mySleep(5);
	}
	for (int ch = 160; ch >= 5; ch -= 3)
	{
		SetClr(rand() % 15);
		printA(5, ch, 5, sym);
		mySleep(5);
		printA(5, ch, 5, sym2);
		mySleep(5);
	}
	for (int r = 5, c = 5; r <= 80 && c <= 160; r += 3, c += 3)
	{
		SetClr(rand() % 15);
		printA(r, c, 5, sym);
		mySleep(5);
		printA(r, c, 5, sym2);
		mySleep(5);
	}
	for (int r = 5, c = 160; r <= 80 && c >= 5; r += 3, c -= 3)
	{
		SetClr(rand() % 15);
		printA(r, c, 5, sym);
		mySleep(5);
		printA(r, c, 5, sym2);
		mySleep(5);
	}
	for (int rv = 5; rv <= 80; rv += 3)
	{
		SetClr(rand() % 15);
		printD(rv, 5, 5, sym);
		mySleep(5);
		printD(rv, 5, 5, sym2);
		mySleep(5);
	}
	for (int ch = 5; ch <= 160; ch += 3)
	{
		SetClr(rand() % 15);
		printD(80, ch, 5, sym);
		mySleep(5);
		printD(80, ch, 5, sym2);
		mySleep(5);
	}
	for (int rv = 80; rv >= 5; rv -= 3)
	{
		SetClr(rand() % 15);
		printD(rv, 160, 5, sym);
		mySleep(5);
		printD(rv, 160, 5, sym2);
		mySleep(5);
	}
	for (int ch = 160; ch >= 5; ch -= 3)
	{
		SetClr(rand() % 15);
		printD(5, ch, 5, sym);
		mySleep(5);
		printD(5, ch, 5, sym2);
		mySleep(5);
	}
	for (int r = 5, c = 5; r <= 80 && c <= 160; r += 3, c += 3)
	{
		SetClr(rand() % 15);
		printD(r, c, 5, sym);
		mySleep(5);
		printD(r, c, 5, sym2);
		mySleep(5);
	}
	for (int r = 5, c = 160; r <= 80 && c >= 5; r += 3, c -= 3)
	{
		SetClr(rand() % 15);
		printD(r, c, 5, sym);
		mySleep(5);
		printD(r, c, 5, sym2);
		mySleep(5);
	}
	_getch();

	return 0;
}

int mainGrowing()
{
	//166 85
	cout << "My screen dimension are (width : 166 & height : 85)";
	_getch();
	system("cls");
	char sym = -37;
	char sym2 = ' ';
	while (true)
	{
		for (int i = 5; i <= 40; i += 2)
		{
			SetClr(rand() % 15);
			printA(40, 75, i, sym);
			mySleep(10);
			printA(40, 75, i, sym2);
			mySleep(5);
		}
		for (int i = 5; i <= 40; i += 2)
		{
			SetClr(rand() % 15);
			printH(40, 75, i, sym);
			mySleep(10);
			printH(40, 75, i, sym2);
			mySleep(5);
		}
		for (int i = 5; i <= 40; i += 2)
		{
			SetClr(rand() % 15);
			printM(40, 75, i, sym);
			mySleep(10);
			printM(40, 75, i, sym2);
			mySleep(5);
		}
		for (int i = 5; i <= 40; i += 2)
		{
			SetClr(rand() % 15);
			printA(40, 75, i, sym);
			mySleep(10);
			printA(40, 75, i, sym2);
			mySleep(5);
		}
		for (int i = 5; i <= 40; i += 2)
		{
			SetClr(rand() % 15);
			printD(40, 75, i, sym);
			mySleep(10);
			printD(40, 75, i, sym2);
			mySleep(5);
		}
	}
	_getch();

	return 0;
}

int mainPrintName()
{
	//166 85
	cout << "My screen dimension are (width : 166 & height : 85)";
	_getch();
	system("cls");
	char sym = -37;
	printA(20, 20, 5, sym);
	printH(20, 35, 5, sym);
	printM(20, 50, 5, sym);
	printA(20, 65, 5, sym);
	printD(20, 80, 5, sym);

	_getch();

	return 0;
}

int mainManyStone()
{
	//166 85
	cout << "My screen dimension are (width : 166 & height : 85)";
	_getch();
	system("cls");
	char sym = -37;
	L2R(15, 0, 30, sym);
	T2B(30, 15, 84, sym);
	L2R(77, 30, 165, sym);
	printCartoon(13, 29);
	int Ir = 13, Ic = 30;
	int ppr = Ir, ppc = Ic;

	int v[] = { 10,15,20,5,25 };
	int size = sizeof(v) / sizeof(int);
	for (float t = 0; true; t += 0.0001)
	{
		for (int i = 0; i < size; i++)
		{

			int pr = Ir + 4.9 * t * t;
			int pc = Ic + v[i] * t;
			if (pr < 77)
			{
				gotoRowCol(ppr, ppc);
				cout << ' ';
				gotoRowCol(pr, pc);
				cout << sym;
				ppr = pr; ppc = pc;
			}
			else
			{
				gotoRowCol(76, pc);
				cout << sym;
				break;
			}
		}
	}
	_getch();
	return 0;
}

int mainStoneThrow1by1()
{

	//166 85
	cout << "My screen dimension are (width : 166 & height : 85)";
	_getch();
	system("cls");
	char sym = -37;
	L2R(15, 0, 30, sym);
	T2B(30, 15, 84, sym);
	L2R(77, 30, 165, sym);
	printCartoon(13, 29);
	int Ir = 13, Ic = 30;
	int v[] = { 10,15,20,5,25 };
	int s[] = { 5,9,12,14,16 };
	int size = sizeof(v) / sizeof(int);
	for (int i = 0; i < size; i++)
	{
		for (int j = i; j < size; j++)
		{
			gotoRowCol(14, s[j]);
			cout << sym;
		}
		gotoRowCol(14, s[i]);
		cout << ' ';
		int ppr = Ir, ppc = Ic;

		for (float t = 0; true; t += 0.0001)
		{
			int pr = Ir + 4.9 * t * t;
			int pc = Ic + v[i] * t;
			if (pr < 77)
			{
				gotoRowCol(ppr, ppc);
				cout << ' ';
				gotoRowCol(pr, pc);
				cout << sym;
				ppr = pr; ppc = pc;
			}
			else
			{
				gotoRowCol(76, pc);
				cout << sym;
				break;
			}
		}
	}
	_getch();
	return 0;
}

int mainOneStone()
{
	//166 85
	cout << "My screen dimension are (width : 166 & height : 85)";
	_getch();
	system("cls");
	char sym = -37;
	L2R(15, 0, 30, sym);
	T2B(30, 15, 84, sym);
	L2R(77, 30, 165, sym);
	printCartoon(13, 29);
	int Ir = 13, Ic = 30;
	int ppr = Ir, ppc = Ic;
	int v = 10;
	for (float t = 0; true; t += 0.0001)
	{
		int pr = Ir + 4.9 * t * t;
		int pc = Ic + v * t;
		if (pr < 77)
		{
			gotoRowCol(ppr, ppc);
			cout << ' ';
			gotoRowCol(pr, pc);
			cout << sym;
			ppr = pr; ppc = pc;
		}
		else
		{
			gotoRowCol(76, pc);
			cout << sym;
			break;
		}
	}
	_getch();
	return 0;
}

int mainFan()
{
	//72 71
	cout << "My screen dimension are (width : 72 & height : 72)";
	_getch();
	system("cls");
	int h = 70;
	int w = 70;
	char sym = -37;
	float t = 100;
	while (true)
	{
		system("cls");
		//SetClr(rand() % 15);
		fan1(h, w, sym);
		//SetClr(rand() % 15);
		mySleep(t);
		system("cls");
		//SetClr(rand() % 15);
		fan2(h, w, sym);
		//SetClr(rand() % 15);
		mySleep(t);
		t *= 0.9;
	}
	_getch();
	return 0;

}

int main()
{
	int ch;
	cout << "Which animation you want to run : ";
	cout << "\n1-Fan\n2-Throwing stone\n3-Throwing 5 stone\n4-Printing name\n5-Name Growing\n6-Name moving multiple direction\n7-Circle\n8-Growing Circle\n9-Ballon\n10-Smilly face\n11-Spiral\n12-Sinewave\n13-Name Sinewave\n14-Moving Sinewave\n15-Name Moving Sinewave\n16-Sinewave Changing Amplitute\n17-Print Box\n18-Box Clockwise direction\n19-Box Anti-Clockwise direction\n20-Spiral Rectangle\n21-Book\n";
	cin >> ch;
	while (ch > 21)
	{
		cout << "\nWrong Input\nEnter again\n";
		cout << "Which animation you want to run : ";
		cout << "\n1-Fan\n2-Throwing stone\n3-Throwing 5 stone\n4-Printing name\n5-Name Growing\n6-Name moving multiple direction\n7-Circle\n8-Growing Circle\n9-Ballon\n10-Smilly face\n11-Spiral\n12-Sinewave\n13-Name Sinewave\n14-Moving Sinewave\n15-Name Moving Sinewave\n16-Sinewave Changing Amplitute\n17-Print Box\n18-Box Clockwise direction\n19-Box Anti-Clockwise direction\n20-Spiral Rectangle\n21-Book\n";
		cin >> ch;
	}
	switch (ch)
	{
	case 1:
		mainFan();
		break;
	case 2:
		mainOneStone();
		break;
	case 3:
		mainStoneThrow1by1();
		break;
	case 4:
		mainPrintName();
		break;
	case 5:
		mainGrowing();
		break;
	case 6:
		mainNameMovingAllDir();
		break;
	case 7:
		mainPrintCircle();
		break;
	case 8:
		mainGrowingCircle();
		break;
	case 9:
		mainBaloon();
		break;
	case 10:
		mainSmily();
		break;
	case 11:
		mainSpiral();
		break;
	case 12:
		mainSinewave();
		break;
	case 13:
		mainSinewaveName();
		break;
	case 14:
		mainMovingSinewave();
		break;
	case 15:
		mainMovingSinewaveName();
		break;
	case 16:
		mainAmplitute();
		break;
	case 17:
		mainBox();
		break;
	case 18:
		mainClockRotation();
		break;
	case 19:
		mainAntiRotation();
		break;
	case 20:
		mainSpiralRectangle();
		break;
	case 21:
		mainBook();
		break;
	}
	return _getch();
}




