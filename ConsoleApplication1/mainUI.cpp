//程序主界面
#include"stdafx.h"
#include"menu.h"
#include"convert.h"
#include"player.h"
#include"sequences.h"
#include"listnode.h"
#include"search.h"
#include"count.h"
#include"linktofile.h"
#pragma warning(disable: 4996)
HWND wnd = GetHWnd();
int main = 0;
void mainUI(){
	setlocale(LC_ALL, "Chinese-simplified");
	me = 2;
	IMAGE background, shutlight, pressplayer, pressconvert,presssequence,presscount,presssearch;
	mciSendString("close click", 0, 0, 0);
	mciSendString(mciclick, NULL, 0, NULL);
	extern void loginUI();
	setbkcolor(RGB(15, 5, 65)); cleardevice();
	menu();
	EnableMenuItem(temp, 2, MF_GRAYED);
	loadimage(&shutlight, "IMAGE", "shutlight.bmp");
	loadimage(&background, "IMAGE", "background.bmp");
	loadimage(&pressplayer, "IMAGE", "pressplayer.bmp");
	loadimage(&pressconvert, "IMAGE", "pressconvert.bmp");
	loadimage(&presssequence, "IMAGE", "presssequence.bmp");
	loadimage(&presscount, "IMAGE", "presscount.bmp");
	loadimage(&presssearch, "IMAGE", "presssearch.bmp");
	putimage(0, 0, &background);
	searchfile();
	while (true){
		choice();
		MOUSEMSG msg;//获取鼠标信息
		while (MouseHit()){
			msg = GetMouseMsg();
			if (msg.x >= 168 && msg.x <= 218 && msg.y >= 305 && msg.y <= 355){
				putimage(157, 292, &pressconvert);
				mciSendString(mcimouse, NULL, 0, NULL);
				mciSendString("play mouse", NULL, 0, NULL);
				if (msg.uMsg == WM_LBUTTONUP) {
					mciSendString("play click", 0, 0, 0);
					convert();
				}
			}
			else if (msg.x >= 245 && msg.x <= 400 && msg.y >= 185 && msg.y <= 335){
				putimage(237, 173, &pressplayer);
				mciSendString(mcimouse, NULL, 0, NULL);
				mciSendString("play mouse", NULL, 0, NULL);
				if (msg.uMsg == WM_LBUTTONUP) {
					mciSendString("play click", 0, 0, 0);
					player();
				}
			}
			else if (msg.x >= 40 && msg.x <= 140 && msg.y >= 190 && msg.y <= 290){
				putimage(31, 178, &presssequence);
				mciSendString(mcimouse, NULL, 0, NULL);
				mciSendString("play mouse", NULL, 0, NULL);
				if (msg.uMsg == WM_LBUTTONUP) {
					mciSendString("play click", 0, 0, 0);
					sequences();
				}
			}
			else if (msg.x >= 435 && msg.x <= 475 && msg.y >= 160 && msg.y <= 210){
				putimage(423, 150, &presscount);
				mciSendString(mcimouse, NULL, 0, NULL);
				mciSendString("play mouse", NULL, 0, NULL);
				if (msg.uMsg == WM_LBUTTONUP) {
					mciSendString("play click", 0, 0, 0);
					count();
				}
			}
			else if (msg.x >= 505 && msg.x <= 605 && msg.y >= 240 && msg.y <= 340){
				putimage(492, 228, &presssearch);
				mciSendString(mcimouse, NULL, 0, NULL);
				mciSendString("play mouse", NULL, 0, NULL);
				if (msg.uMsg == WM_LBUTTONUP) {
					mciSendString("play click", 0, 0, 0);
					search();
				}
			}
			else if (msg.x >= 585 && msg.x <= 620 && msg.y >= 20 && msg.y <= 60){
				putimage(578, 15, &shutlight, SRCPAINT);
				mciSendString(mcimouse, NULL, 0, NULL);
				mciSendString("play mouse", NULL, 0, NULL);
				if (msg.uMsg == WM_LBUTTONUP) {
					DeleteFile(loginBGM);
					DeleteFile(mouses);
					DeleteFile(click);
					exit(0);
				}
			}
			else {
				mciSendString("close mouse", 0, 0, 0);
				putimage(0, 0, &background);
			}
		}
		Sleep(10);
	}
}