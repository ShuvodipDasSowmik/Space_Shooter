#include "iGraphics.h"
#include <windows.h>
#include <mmsystem.h>
#pragma comment(lib, "Winmm.lib")
#include <string.h>

int flagx, flagy, mode, len;
int SS1health = 100;
char Herohealth[15];
char ScoreStr[25];
int gameWidth = 1400;
int gameHeight = 700;
unsigned char key;
int mx, my, x_1, dx, prev, curr, x = 0, y = 0, x2 = 0;
int startx = 250, starty = 240;
int setx = 250, sety = 125;
int infox = 800, infoy = 240;
int hofx = 800, hofy = 125;
int exitx = 521, exity = 40;
int r = 0, g = 0, b = 0;
int gamestate = 0, startshoot = 1;
int iconw = 350, iconh = 58;
int Score = 0;
int Settings = 0;

char *BackGround3[] = {"301.bmp", "302.bmp", "303.bmp", "304.bmp", "305.bmp", "306.bmp", "307.bmp", "308.bmp", "309.bmp", "310.bmp", "311.bmp", "312.bmp", "313.bmp", "314.bmp"};
char *SS1[] = {"SS11.bmp", "SS12.bmp", "SS13.bmp"};
char *SS2[] = {"SS21.bmp", "SS22.bmp", "SS23.bmp"};
char *Bullet2[] = {"B5.bmp", "B5.bmp", "B5.bmp", "B5.bmp", "B5.bmp", "B5.bmp", "B5.bmp", "B5.bmp", "B5.bmp", "B5.bmp", "B5.bmp", "B5.bmp", "B5.bmp", "B5.bmp", "B5.bmp", "B5.bmp", "B5.bmp", "B5.bmp", "B5.bmp", "B5.bmp", "B5.bmp", "B5.bmp"};
char *BulletE[] = {"EB.bmp", "EB.bmp", "EB.bmp", "EB.bmp", "EB.bmp", "EB.bmp", "EB.bmp", "EB.bmp", "EB.bmp", "EB.bmp", "EB.bmp", "EB.bmp"};
char *Exp[] = {"Exp1.bmp", "Exp2.bmp", "Exp3.bmp"};
char *Boss[] = {"E1.bmp", "E2.bmp", "E3.bmp"};
char *Ex[] = {"Ex1.bmp", "Ex2.bmp", "Ex3.bmp", "Ex4.bmp", "Ex5.bmp", "Ex6.bmp", "Ex7.bmp"};
char *Ast[] = {"Asteroid1.bmp", "Asteroid2.bmp"};
char *name = {"Enter Your Name"};

int SS1x = 25, SS1y = 255, SS1indx = 0, SS1width = 150, SS1Height = 73, SS1exindx = 0;
int BackGround3width = 200;
int BackGround3Speed = 1;
bool BossDeath = false;
void leftRotate();
void move();
void setEnemyVar();
void BulVar();
void Reset();
void Collision();
void setBackground();
void BossVar();
void AsteroidVar();
void File();
// void HOFshow();
// void HOFsort();
void ScoreString(int Score, char ScoreStr[]);

int EnemyDeath = 0;
bool GameOver = 0;
bool SS1show = true;
#define EneNum 6
int EnemyNum = 2;
#define B2num 22
#define EnemyBullet 6
#define BossBullet 10 // int EnemyNum = 2;int BossIncrease = 0, EnemyIncrease = 0;
int BossX, BossY;
int BossIncrease = 0, EnemyIncrease = 0;
int ExFlag = 0;
#define AsNum 10
bool Sound = true;
int Name = 1;
int namelen = 33;
char str[33], str2[33];
char HOFnames[5][35];
int HighScores[5];
char HOF[35];
int HOFflag = 0;
char cScore[15];
char num[5];

struct BackGround
{
	int x;
};
BackGround Back[14];

int Bossx;
int Bossy;
bool BossShow;
int Bossi;
int Bossindx;
int BossSpeed;
int Bosshealth;
int BossShoot;
int Bossexindx = 0;
char Bhealth[14];
int AsteroidNum = 5;

struct BossBul
{
	int BBx;
	int BBy;
	bool BBshow;
};
BossBul BB[BossBullet];

struct Asteroid
{
	int Asx;
	int Asy;
	bool Ashow;
	int Asindx;
	int AsHealth;
};
Asteroid As[AsNum];

struct Enemy
{
	int SS2x;
	int SS2y;
	int SS2indx;
	int SS2i;
	bool SS2show;
	int SS2speed;
	int health;
	char Ehealth[14];
	bool Shootflag;
	int Exindx;
	struct EnemyBul
	{
		int EBx;
		int EBy;
		bool EBshow;
	} EB[EnemyBullet];
};
Enemy enemy[EneNum];

struct Bul2
{
	int B2x;
	int B2y;
	bool B2show;
};
Bul2 B2[B2num];

void iDraw()
{
	// place your drawing codes here
	iClear();
	int x = 0;

	if (gamestate == 0)
	{
		iShowBMP(0, 0, "HomeMenu.bmp");
		iShowBMP2(startx, starty, "Start.bmp", 0);
		iShowBMP2(setx, sety, "Settings.bmp", 0);
		iShowBMP2(infox, infoy, "Info.bmp", 0);
		iShowBMP2(hofx, hofy, "HOF.bmp", 0);
		iShowBMP2(395, 400, "Logo.bmp", 0);
		iShowBMP2(521, 40, "Exit.bmp", 0);
	}

	else if (gamestate == 1)
	{
		for (int i = 0; i < 14; i++)
		{
			iShowBMP(Back[i].x, 0, BackGround3[i]);
		}

		if (SS1show == true)
			iShowBMP2(SS1x, SS1y, SS1[SS1indx], 0);

		else if (SS1show == false && SS1exindx <= 6)
			iShowBMP2(SS1x, SS1y, Ex[SS1exindx], 0);

		for (int i = 0; i < B2num; i++)
		{
			if (B2[i].B2show && SS1show == true)
				iShowBMP2(B2[i].B2x + x2, B2[i].B2y, Bullet2[i], 0);
		}

		for (int i = 0; i < BossBullet; i++)
		{
			if (BB[i].BBshow == true && BossShoot)
				iShowBMP2(BB[i].BBx, BB[i].BBy, BulletE[i], 0);
		}

		for (int i = 0; i < EnemyNum; i++)
		{
			if (enemy[i].SS2show)
			{
				iShowBMP2(enemy[i].SS2x, enemy[i].SS2y, SS2[enemy[i].SS2indx], 0);
				iText(enemy[i].SS2x + 20, enemy[i].SS2y + 90, enemy[i].Ehealth, GLUT_BITMAP_HELVETICA_18);
			}

			else if (enemy[i].SS2show == false && enemy[i].Exindx <= 6)
				iShowBMP2(enemy[i].SS2x, enemy[i].SS2y, Ex[enemy[i].Exindx], 0);

			for (int k = 0; k < EnemyBullet; k++)
			{
				if (enemy[i].EB[k].EBshow && enemy[i].Shootflag)
					iShowBMP2(enemy[i].EB[k].EBx, enemy[i].EB[k].EBy, BulletE[k], 0);
			}
		}

		if (BossShow)
		{
			iShowBMP2(Bossx, Bossy, Boss[Bossindx], 0);
			iText(Bossx + 60, Bossy + 105, Bhealth, GLUT_BITMAP_HELVETICA_18);
		}

		else if (Bossexindx <= 6)
		{
			iShowBMP2(BossX, BossY, Ex[Bossexindx], 0);
		}

		for (int i = 0; i < AsteroidNum; i++)
		{
			if (As[i].Ashow)
			{
				if (i % 2 == 0)
				{
					iShowBMP2(As[i].Asx, As[i].Asy, Ast[0], 0);
				}

				else
				{
					iShowBMP2(As[i].Asx, As[i].Asy, Ast[1], 0);
				}
			}

			else if (As[i].Ashow == false && As[i].Asindx <= 6)
			{
				iShowBMP2(As[i].Asx, As[i].Asy, Ex[As[i].Asindx], 0);
			}
		}

		if (SS1show)
		{
			iText(15, 650, Herohealth, GLUT_BITMAP_HELVETICA_18);
			iText(15, 620, ScoreStr, GLUT_BITMAP_HELVETICA_18);
		}
		Collision();

		if (GameOver == true)
		{
			iShowBMP2(0, 0, "GameOver.bmp", 0);
			iSetColor(150, 150, 150);
			iRectangle(439, 408, 350, 40);

			if (Name == 1)
			{
				iSetColor(255, 255, 255);
				iText(445, 420, name, GLUT_BITMAP_HELVETICA_18);
			}

			if (mode == 1)
			{
				iSetColor(255, 255, 255);
				iText(445, 420, str, GLUT_BITMAP_HELVETICA_18);
			}

			char Sc[10];
			sprintf(Sc, "%d", Score);
			iText(440, 258, Sc, GLUT_BITMAP_HELVETICA_18);
		}

		ScoreString(Score, ScoreStr);

		if (Settings == 0)
		{
			iShowBMP2(400, 200, "Gamesettings.bmp", 0);
		}

		else if (Settings == 1)
		{
			iShowBMP2(400, 200, "Gamesettings2.bmp", 0);
		}

		else if (Settings == 2)
		{
			iShowBMP2(400, 200, "Gamesettings3.bmp", 0);
		}
	}

	else if (gamestate == 2)
	{
		iShowBMP(0, 0, "Homemenu.bmp");

		if (Sound == true)
		{
			iShowBMP2(430, 250, "SoundOn.bmp", 0);
		}

		else
		{
			iShowBMP2(430, 250, "SoundOff.bmp", 0);
		}

		iShowBMP2(490, 50, "Quote1.bmp", 0);
		iShowBMP2(0, 0, "BackspaceButton.bmp", 250);
	}

	else if (gamestate == 3)
	{
		iShowBMP(0, 0, "Homemenu.bmp");
		iShowBMP2(521, 500, "Credits.bmp", 0);
		iShowBMP2(521, 390, "HowToPlay.bmp", 0);
		iShowBMP2(0, 0, "Quote2.bmp", 0);
		iShowBMP2(0, 0, "BackspaceButton.bmp", 250);
	}

	else if (gamestate == 4)
	{
		File();
		iShowBMP(0, 0, "Homemenu.bmp");
		iShowBMP2(0, 0, "HOFFront.bmp", 0);
		int f = 0;

		for (int i = 0; i < 5; i++)
		{
			sprintf(num, "%d. ", i + 1);
			sprintf(cScore, "%d", HighScores[i]);
			iText(300, 450 + f, num, GLUT_BITMAP_TIMES_ROMAN_24);
			iText(340, 450 + f, HOFnames[i], GLUT_BITMAP_TIMES_ROMAN_24);
			iText(1100, 450 + f, cScore, GLUT_BITMAP_TIMES_ROMAN_24);
			f -= 50;
		}

		iShowBMP2(0, 0, "BackspaceButton.bmp", 250);
	}

	else if (gamestate == 5)
	{
		iShowBMP(0, 0, "Homemenu.bmp");
		iShowBMP2(0, 0, "Credits1.bmp", 0);
		iShowBMP2(0, 0, "BackspaceButton.bmp", 250);
	}

	else if (gamestate == 6)
	{
		iShowBMP(0, 0, "Homemenu.bmp");
		iShowBMP2(0, 0, "HTP.bmp", 0);
		iShowBMP2(0, 0, "BackspaceButton.bmp", 250);
	}
}

/*
	function iMouseMove() is called when the user presses and drags the mouse.
	(mx, my) is the position where the mouse pointer is.
	*/
void iMouseMove(int mx, int my)
{

	// printf("x = %d, y= %d\n", mx, my);
	//  place your codes here
}

/*
	function iMouse() is called when the user presses/releases the mouse.
	(mx, my) is the position where the mouse pointer is.
	*/
void iMouse(int button, int state, int mx, int my)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		if (gamestate == 0)
		{
			if (mx >= startx && mx <= startx + iconw && my >= starty && my <= starty + iconh)
			{
				gamestate = 1;
			}

			if (mx >= setx && mx <= setx + iconw && my >= sety && my <= sety + iconh)
			{
				gamestate = 2;
			}

			if (mx >= infox && mx <= infox + iconw && my >= infoy && my <= infoy + iconh)
			{
				gamestate = 3;
			}

			if (mx >= hofx && mx <= hofx + iconw && my >= hofy && my <= hofy + iconh)
			{
				gamestate = 4;
			}

			if (mx >= exitx && mx <= exitx + iconw && my >= exity && my <= exity + iconh)
			{
				exit(0);
			}
		}

		if (gamestate == 1 && GameOver == true)
		{
			if (mx >= 439 && mx <= 439 + 350 && my >= 408 && my <= 408 + 40 && mode == 0)
			{
				mode = 1;
				Name = 0;
			}
		}

		if ((gamestate == 2 && mx >= 465 && mx <= 590 && my >= 305 && my <= 420) || (gamestate == 1 && mx >= 1247 && mx <= 1310 && my >= 650 && my <= 685))
		{
			if (Sound == true)
			{
				Sound = false;
				PlaySound(0, 0, 0);
				Settings = 2;
			}

			else if (Sound == false)
			{
				Sound = true;
				PlaySound("GameInterface.wav", NULL, SND_LOOP | SND_ASYNC);
				Settings = 1;
			}
		}

		if (gamestate == 3 && mx >= 521 && mx <= 521 + iconw && my >= 500 && my <= 500 + iconh)
		{
			gamestate = 5;
		}

		if (gamestate == 3 && mx >= 521 && mx <= 521 + iconw && my >= 390 && my <= 390 + iconh)
		{
			gamestate = 6;
		}

		if (gamestate == 1 && mx >= 1330 && mx <= 1380 && my >= 645 && my <= 690 && Settings == 0 && Sound == true)
		{
			Settings = 1;
		}

		else if (gamestate == 1 && mx >= 1330 && mx <= 1380 && my >= 645 && my <= 690 && Settings == 0 && Sound == false)
		{
			Settings = 2;
		}

		else if (gamestate == 1 && mx >= 1330 && mx <= 1380 && my >= 645 && my <= 690 && Settings != 0)
		{
			Settings = 0;
		}

		else if (gamestate == 1 && mx >= 1185 && mx <= 1233 && my >= 645 && my <= 690 && Settings != 0 && GameOver == false)
		{
			gamestate = 0;
			Reset();
		}

		if (gamestate >= 2 && gamestate <= 4 && mx >= 1266 && mx <= 1340 && my >= 650 && my <= 665)
		{
			gamestate = 0;
		}

		if (gamestate >= 5 && gamestate <= 6 && mx >= 1266 && mx <= 1340 && my >= 650 && my <= 665)
		{
			gamestate = 3;
		}

		printf("x = %d, y= %d\n", mx, my);
	}

	if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
	{
		// printf("x = %d, y= %d\n", mx, my);
	}
}

void iKeyboard(unsigned char key)
{
	if (key == 'q')
	{
		// exit(0);
	}
	if (gamestate >= 2 && gamestate <= 4)
	{
		if (key == '\b')
		{
			gamestate = 0;
		}
	}

	else if (gamestate == 5 || gamestate == 6)
	{
		if (key == '\b')
		{
			gamestate = 3;
		}
	}

	int i;

	if (mode == 1)
	{
		if (key == '\r')
		{
			mode = 0;
			strcpy(str2, str);
			//printf("%s\n", str2);

			for (i = 0; i < len; i++)
				str[i] = 0;

			len = 0;
			gamestate = 0;
			GameOver = false;

			sprintf(cScore, "%d", Score);
			strcpy(HOF, str2);
			File();
			// HOFsort();
			Reset();
		}

		else
		{
			if (key != '\b' && len < namelen)
			{
				str[len] = key;
				len++;
			}
			else if (key == '\b')
			{
				str[len - 1] = 0;
				len--;
			}
		}
	}
}

void iSpecialKeyboard(unsigned char key)
{

	if (key == GLUT_KEY_END)
	{
		exit(0);
	}
	if (gamestate == 1 && key == GLUT_KEY_RIGHT && SS1x >= 0 && SS1x <= 330)
	{
		// SS1x += 20;
	}
	else if (gamestate == 1 && key == GLUT_KEY_DOWN && SS1y >= 20 && SS1y <= 600)
	{
		SS1y -= 20;
		y -= 20;
	}
	else if (gamestate == 1 && key == GLUT_KEY_UP && SS1y >= 0 && SS1y <= 580)
	{
		SS1y += 20;
		y += 20;
	}
	else if (gamestate == 1 && key == GLUT_KEY_LEFT && SS1x >= 20 && SS1x <= 350)
	{
		// SS1x -= 20;
	}

	// place your codes for other keys here
}

int main()
{
	setBackground();
	setEnemyVar();
	BulVar();
	BossVar();
	AsteroidVar();

	mode = 0;
	x_1 = 0;
	dx = 1000;
	prev = curr = 0;

	// File();
	//  HOFshow();
	iSetTimer(40, move);
	PlaySound("GameInterface.wav", NULL, SND_LOOP | SND_ASYNC);
	iInitialize(gameWidth, gameHeight, "Space Shooter");

	return 0;
}

void setBackground()
{
	int sum = 0;
	for (int i = 0; i < 14; i++)
	{
		Back[i].x = sum;
		sum += BackGround3width;
	}
}

int Loopflag = 0;
int Bossflag = 0;
int VarFlag = 0;

void move()
{
	if (x_1 < gameWidth)
	{
		x_1 = x_1 + dx;
	}
	else
	{
		x_1 = 0;
		prev = curr = 0;
	}

	int curr = x_1 / 20;
	if (curr != prev)
	{ // another piece has been completely passed
		// right rotate
		leftRotate();
		prev = curr;
	}

	if (gamestate == 1)
	{
		SS1indx++;
		if (SS1indx >= 3)
			SS1indx = 0;
		int k = 1;

		for (int i = 0; i < EnemyNum; i++)
		{
			if (enemy[i].SS2x <= gameWidth && Loopflag < EnemyNum * EnemyBullet)
			{
				for (int k = 0; k < EnemyBullet; k++)
				{
					enemy[i].EB[k].EBshow = true;
					Loopflag++;
				}
			}
		}

		if (Bossx <= gameWidth && Bossflag < BossBullet)
		{
			for (int k = 0; k < BossBullet; k++)
			{
				BB[k].BBshow = true;
				Bossflag++;
			}
		}

		for (int i = 0; i < EnemyNum; i++)
		{
			if (enemy[i].SS2x >= 1250)
			{
				enemy[i].SS2x -= 10;
				for (int k = 0; k < EnemyBullet; k++)
				{
					enemy[i].EB[k].EBx -= 5;
				}
			}

			if (enemy[i].SS2x <= 1250)
			{
				if (enemy[i].SS2show)
					enemy[i].Shootflag = true;

				enemy[i].SS2y += enemy[i].SS2speed * enemy[i].SS2i;

				if (enemy[i].SS2y >= gameHeight - 70)
					enemy[i].SS2i = -1;

				else if (enemy[i].SS2y <= 20)
					enemy[i].SS2i = 1;
			}

			enemy[i].SS2indx++;

			if (enemy[i].SS2indx >= 3)
				enemy[i].SS2indx = 0;
		}
		for (int i = 0; i < B2num; i++)
		{
			B2[i].B2x += 30;
			if (B2[i].B2x >= gameWidth)
			{
				if (B2[i].B2show == false)
					B2[i].B2show = true;

				B2[i].B2x = SS1x + 100;
				B2[i].B2y = SS1y;
			}
		}
		for (int i = 0; i < AsteroidNum; i++)
		{
			As[i].Asx -= 10;
			if (As[i].Asx < 0)
			{
				As[i].Asx = gameWidth + 1800;
				As[i].Asy = rand() % 600;

				if (As[i].Ashow == false)
				{
					As[i].Ashow = true;
				}
			}
		}

		for (int k = 0; k < EnemyNum; k++)
		{
			if (enemy[k].SS2x <= gameWidth)
			{
				for (int i = 0; i < EnemyBullet; i++)
				{
					enemy[k].EB[i].EBx -= 30;
					// enemy[k].EB[i].EBshow = true;
					if (enemy[k].EB[i].EBshow == false && enemy[k].EB[i].EBx < 0)
						enemy[k].EB[i].EBshow = true;

					if (enemy[k].EB[i].EBx <= 0 && enemy[k].SS2show == true)
					{
						enemy[k].EB[i].EBx = enemy[k].SS2x + 64;
						enemy[k].EB[i].EBy = enemy[k].SS2y + 58;
					}
				}
			}
			if (enemy[k].SS2show == false && enemy[k].Exindx <= 6)
			{
				enemy[k].Exindx++;
			}
		}
		if (EnemyDeath == EnemyNum)
		{
			Bossindx++;
			if (Bossindx >= 3)
				Bossindx = 0;

			if (Bossx >= 1180)
			{
				Bossx -= 10;
				for (int k = 0; k < BossBullet; k++)
				{
					BB[k].BBx -= 10;
				}
			}

			else
			{
				if (BossShow)
					BossShoot = true;

				Bossy += Bossi * BossSpeed;

				if (Bossy >= gameHeight - 110)
					Bossi = -1;

				else if (Bossy <= 40)
					Bossi = 1;

				for (int k = 0; k < BossBullet; k++)
				{
					BB[k].BBx -= 30;
					if (BB[k].BBx <= 0)
					{
						if (BB[k].BBshow == false && BB[k].BBx < 0)
							BB[k].BBshow = true;
						BB[k].BBx = Bossx + 50;
						BB[k].BBy = Bossy + 30;
					}
				}
			}
		}
		if (SS1show == false && SS1exindx <= 6)
		{
			SS1exindx++;
		}
		if (BossShow == false && Bossexindx <= 6)
		{
			Bossexindx++;
			for (int i = 0; i < BossBullet; i++)
			{
				BB[i].BBx -= 30;

				if (BB[i].BBx < 0)
					BB[i].BBshow = false;
			}
		}

		int ConFlag = 0;
		if (BossShow == false)
		{
			for (int i = 0; i < BossBullet; i++)
			{
				if (BB[i].BBx > 0)
					BB[i].BBx -= 30;
			}
		}
		if (BossDeath == true)
		{
			if (EnemyNum <= 3)
				EnemyNum++;

			BossIncrease += 60;
			EnemyIncrease += 40;

			setEnemyVar();

			BossDeath = false;
			EnemyDeath = 0;
			VarFlag = 1;
		}
		if (VarFlag == 1 && EnemyDeath == EnemyNum)
		{
			BossVar();
			VarFlag = 0;
		}
		for (int i = 0; i < AsteroidNum; i++)
		{
			if (As[i].Ashow == false && As[i].Asindx <= 6)
			{
				As[i].Asindx++;
			}
			if (As[i].Asindx >= 6 && As[i].Ashow == true)
			{
				As[i].Asindx = 0;
			}
		}
	}
}

void leftRotate()
{
	char *p = BackGround3[0];
	for (int i = 0; i <= 12; i++)
	{
		BackGround3[i] = BackGround3[i + 1];
	}
	BackGround3[13] = p;
}

void Reset()
{
	EnemyNum = 2;
	BossIncrease = 0;
	EnemyIncrease = 0;
	EnemyDeath = 0;
	Score = 0;
	SS1health = 100;
	Name = 1;
	name = "Enter Your Name";
	SS1show = true;
	SS1x = 25, SS1y = 235, SS1indx = 0, SS1exindx = 0;

	for (int i = 0; i < EnemyNum; i++)
	{
		int f = 0;
		enemy[i].SS2x = gameWidth + 800 + f;
		enemy[i].SS2y = rand() % 600;
		enemy[i].SS2indx = rand() % 3;
		f += 100;
	}

	BulVar();
	setEnemyVar();
	BossVar();
}

void setEnemyVar()
{
	int f = 0;
	int x = 0;

	for (int i = 0; i < EnemyNum; i++)
	{
		enemy[i].SS2x = gameWidth + 800 + f;
		enemy[i].SS2y = 20 + x;
		enemy[i].SS2indx = rand() % 3;
		enemy[i].SS2show = true;
		enemy[i].SS2i = 1;
		enemy[i].SS2speed = 7;
		enemy[i].health = 60 + EnemyIncrease;
		enemy[i].Shootflag = false;
		enemy[i].Exindx = 0;
		f += 80;
		x += gameHeight / EnemyNum + 25;

		int flag = 0;
		for (int k = 0; k < EnemyBullet; k++)
		{
			enemy[i].EB[k].EBx = enemy[i].SS2x + 64 + flag;
			enemy[i].EB[k].EBy = enemy[i].SS2y + 58;
			flag -= 60;
			enemy[i].EB[k].EBshow = false;
		}
	}
}

void BulVar()
{
	int flag = SS1x + 100;
	for (int i = 0; i < B2num; i++)
	{
		B2[i].B2x = flag;
		B2[i].B2y = SS1y;
		flag += 60;
		B2[i].B2show = false;
	}
}

void BossVar()
{
	Bossx = gameWidth + 800;
	Bossy = rand() % 500;
	BossShow = true;
	BossSpeed = 4;
	BossShoot = false;
	Bosshealth = 120 + BossIncrease;
	Bossi = 1;
	int flag = 0;

	for (int i = 0; i < BossBullet; i++)
	{
		BB[i].BBx = Bossx + 50 + flag;
		BB[i].BBy = Bossy + 30;
		flag -= 60;
		BB[i].BBshow = true;
	}
}

void healthstring(char ara[], int h)
{
	int indx = 0, k = 10;
	char arr[9] = {'H', 'e', 'a', 'l', 't', 'h', ' ', '=', ' '};
	for (int i = 0; i < 9; i++)
	{
		ara[i] = arr[i];
	}
	for (int i = 9; i < 13; i++)
	{
		ara[i] = (h % k) + '0';
		h /= 10;
	}
	// printf("%s\n", ara);
	for (int i = 9, j = 12; i < 11, j >= 11; i++, j--)
	{
		int temp = ara[i];
		ara[i] = ara[j];
		ara[j] = temp;
	}
	// printf("%s\n", ara);
}

void AsteroidVar()
{
	int f = 0;
	for (int i = 0; i < AsteroidNum; i++)
	{
		As[i].Asx = gameWidth + 1500 + f;
		As[i].Asy = rand() % 600;
		As[i].Ashow = true;
		As[i].Asindx = 0;

		if (i % 2 == 0)
		{
			As[i].AsHealth = 100;
		}
		else
		{
			As[i].AsHealth = 50;
		}
		f += 500;
	}
}

void Collision()
{
	for (int i = 0; i < B2num; i++)
	{
		for (int k = 0; k < EnemyNum; k++)
		{
			if (SS1show == 1 && B2[i].B2show == true && enemy[k].SS2show == true && B2[i].B2x >= enemy[k].SS2x && (B2[i].B2y >= enemy[k].SS2y && B2[i].B2y <= enemy[k].SS2y + 85))
			{
				B2[i].B2show = false;
				enemy[k].health -= 5;

				if (enemy[k].health <= 0)
				{
					Score += 50;
					enemy[k].SS2show = false;
					EnemyDeath++;
				}
			}
			healthstring(enemy[k].Ehealth, enemy[k].health);
		}

		if (SS1show == 1 && B2[i].B2show == true && BossShow == true && B2[i].B2x >= Bossx + 20 && B2[i].B2y >= Bossy + 25 && B2[i].B2y <= Bossy + 65)
		{
			B2[i].B2show = false;
			Bosshealth -= 5;

			if (Bosshealth <= 0)
			{
				Score += 100;
				BossX = Bossx;
				BossY = Bossy;
				BossShow = false;
				BossDeath = true;
				Bossexindx = 0;
			}
		}

		for (int k = 0; k < AsteroidNum; k++)
		{
			if (k % 2 == 0 && SS1show == 1 && B2[i].B2show == true && As[k].Ashow == true && B2[i].B2x >= As[k].Asx && B2[i].B2y >= As[k].Asy && B2[i].B2y <= As[k].Asy + 63)
			{
				As[k].AsHealth -= 5;
				B2[i].B2show = false;
			}

			else if (k % 2 != 0 && SS1show == 1 && B2[i].B2show == true && As[k].Ashow == true && B2[i].B2x >= As[k].Asx - 10 && B2[i].B2y >= As[k].Asy && B2[i].B2y <= As[k].Asy + 40)
			{
				As[k].AsHealth -= 5;
				B2[i].B2show = false;
			}

			if (As[k].AsHealth <= 0)
			{
				Score += 25;
				As[k].Ashow = false;
				if (k % 2 == 0)
				{
					As[k].AsHealth = 100;
				}
				else
				{
					As[k].AsHealth = 50;
				}
			}
		}
	}

	for (int i = 0; i < EnemyNum; i++)
	{
		for (int j = 0; j < EnemyBullet; j++)
		{
			if (enemy[i].EB[j].EBshow == true && enemy[i].EB[j].EBx >= SS1x && enemy[i].EB[j].EBx <= SS1x + SS1width && enemy[i].EB[j].EBy >= SS1y && enemy[i].EB[j].EBy <= SS1y + SS1Height)
			{
				enemy[i].EB[j].EBshow = false;
				SS1health -= 5;
			}
		}
	}

	for (int i = 0; i < BossBullet; i++)
	{
		if (BB[i].BBshow == true && BB[i].BBx >= SS1x && BB[i].BBx <= SS1x + SS1width && BB[i].BBy >= SS1y && BB[i].BBy <= SS1y + SS1Height)
		{
			BB[i].BBshow = false;
			SS1health -= 5;
		}
	}

	healthstring(Bhealth, Bosshealth);

	if (SS1health <= 0)
	{
		SS1show = false;
		GameOver = 1;
	}

	for (int i = 0; i < AsteroidNum; i++)
	{
		if (As[i].Asx >= SS1x && As[i].Asx <= SS1width && As[i].Asy >= SS1y && As[i].Asy <= SS1y + SS1Height && As[i].Ashow == true)
		{
			if (i % 2 == 0)
			{
				SS1health -= 50;
				As[i].Ashow = false;
			}
			else
			{
				SS1health -= 100;
				As[i].Ashow = false;
			}
		}
	}

	healthstring(Herohealth, SS1health);
}

void ScoreString(int Score, char ScoreStr[])
{
	int i = 0;
	char t[8] = {'S', 'c', 'o', 'r', 'e', ' ', '=', ' '};

	while (i < 8)
	{
		ScoreStr[i] = t[i];
		i++;
	}

	while (Score)
	{
		int x = Score % 10;
		ScoreStr[i] = x + '0';
		// printf("%c ", ScoreStr[i]);
		i++;
		Score /= 10;
	}

	ScoreStr[i] = 0;

	for (int k = 8, m = i - 1; k < 8 + (i - 8) / 2, m >= 8 + (i - 8) / 2; k++, m--)
	{
		char temp = ScoreStr[k];
		ScoreStr[k] = ScoreStr[m];
		ScoreStr[m] = temp;
	}
	// printf("%s\n", ScoreStr);
}

void File()
{
	FILE *tempname;
	FILE *HOF;
	FILE *Scores;
	FILE *tempscore;
	int score;
	char name[35];
	strcpy(name, str2);
	score = Score;
	char s[8];
	char n[35];

	tempname = fopen("tempname.txt", "a");
	HOF = fopen("HOF.txt", "r");
	Scores = fopen("Scores.txt", "r");
	tempscore = fopen("tempscore.txt", "a");

	int flag = 0;
	char tempn[35];
	int temps;

	for (int i = 0; i < 5; i++)
	{
		fgets(s, 10, Scores);
		fgets(n, 35, HOF);

		int a = atoi(s);

		if (score < a)
		{
			char b[8];
			itoa(a, b, 10);
			fprintf(tempname, n);
			// fprintf(tempname, "\n");

			fprintf(tempscore, b);
			fprintf(tempscore, "\n");

			HighScores[i] = a;
			strcpy(HOFnames[i], n);
		}

		else if (flag != 1)
		{
			char b[8];
			itoa(score, b, 10);
			fprintf(tempname, name);
			fprintf(tempname, "\n");

			fprintf(tempscore, b);
			fprintf(tempscore, "\n");
			flag = 1;

			strcpy(tempn, n);
			temps = a;
			HighScores[i] = Score;
			strcpy(HOFnames[i], str2);
		}

		else if (flag == 1 || flag == 2)
		{
			char b[8];
			itoa(temps, b, 10);
			fprintf(tempname, tempn);
			// fprintf(tempname, "\n");

			fprintf(tempscore, b);
			fprintf(tempscore, "\n");

			strcpy(tempn, n);
			temps = a;
			flag == 2;

			HighScores[i] = temps;
			strcpy(HOFnames[i], tempn);
		}
	}

	if (flag == 2)
	{
		char b[8];
		itoa(temps, b, 10);

		fprintf(tempname, tempn);
		fprintf(tempname, "\n");

		fprintf(tempscore, b);
		fprintf(tempscore, "\n");

		HighScores[5] = temps;
		strcpy(HOFnames[5], tempn);
	}

	fclose(HOF);
	fclose(Scores);
	fclose(tempname);
	fclose(tempscore);

	remove("HOF.txt");
	remove("Scores.txt");
	rename("tempscore.txt", "Scores.txt");
	rename("tempname.txt", "HOF.txt");
}

/*Finished*/