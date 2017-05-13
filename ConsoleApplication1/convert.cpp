//格式转换
#include "stdafx.h"
#include "mainUI.h"
#include "menu.h"
#include"mainUI.h"
#include"linktofile.h"
#pragma warning(disable: 4996)
#pragma comment(lib,"Winmm.lib")
struct song{
	char name[45];
	char singer[35];
}song;
void convert(){
	register int n = 0, s = 0;
	me = 9;
	main++;
	IMAGE convertback,shutlight,homelight,background;
	loadimage(&convertback,"IMAGE", "convert.bmp");
	loadimage(&shutlight, "IMAGE", "shutlight.bmp");
	loadimage(&homelight, "IMAGE", "homelight.bmp");
	loadimage(&background, "IMAGE", "background.bmp");
	setlinecolor(RGB(255, 255, 0)); setlinestyle(PS_SOLID, 3);
	FILE *fp, *fpr;
	fp = fopen(songpath, "r");
	fpr = fopen(newpath, "w");
	do{
		fgets(song.name, 45, fp);
		fgets(song.singer, 35, fp);
		song.name[strlen(song.name) - 1] = '\0';
		song.singer[strlen(song.singer) - 1] = '\0';
		n = strlen(song.name)-2;
		while (song.name[n] == ' ') {
			song.name[n] = '\0';
			n--;
		}
		s = strlen(song.singer)-2;
		while (song.singer[s] == ' ') {
			song.singer[s] = '\0';
			s--;
		}
		fprintf(fpr, "%d%d%s%s", strlen(song.name), strlen(song.singer), song.name, song.singer);
	} while (!feof(fp));
	fclose(fp);	fclose(fpr);
	for (int i = 640; i >= 0; i -= 5){
		putimage(i, 0, &convertback);
		Sleep(int(-0.156*(i / 10) + 10));
	}
	while (true){
		choice();
		MOUSEMSG msg;//获取鼠标信息
		while (MouseHit()){
			msg = GetMouseMsg();
			if (msg.x >= 585 && msg.x <= 620 && msg.y >= 20 && msg.y <= 58){
				mciSendString(mcimouse, NULL, 0, NULL);
				mciSendString("play mouse", 0, 0, 0);
				putimage(578, 15, &shutlight, SRCPAINT);
				if (msg.uMsg == WM_LBUTTONUP) {
					DeleteFile(loginBGM);
					DeleteFile(mouses);
					DeleteFile(click);
					exit(0);
				}
			}
			else if (msg.x >= 524 && msg.x <= 562 && msg.y >= 20 && msg.y <= 58){
				putimage(516, 14, &homelight, SRCPAINT);
				mciSendString(mcimouse, NULL, 0, NULL);
				mciSendString("play mouse", 0, 0, 0);
				if (msg.uMsg == WM_LBUTTONUP) {
					mciSendString("close click", 0, 0, 0);
					mciSendString(mciclick, NULL, 0, NULL);
					mciSendString("play click", 0, 0, 0);
					for (int i = -640; i <= 0; i += 5){
						putimage(i, 0, &background);
						Sleep(int(0.156*(i / 10) + 10));
					}
					mainUI();
				}
			}
			else if (msg.x >= 268 && msg.x <= 372 && msg.y >= 320 && msg.y <= 356){
				mciSendString(mcimouse, NULL, 0, NULL);
				mciSendString("play mouse", 0, 0, 0);
				roundrect(268, 320, 372, 356, 15, 15);
				if (msg.uMsg == WM_LBUTTONUP) {
					mciSendString("close click", 0, 0, 0);
					mciSendString(mciclick, NULL, 0, NULL);
					mciSendString("play click", 0, 0, 0);
					char cmd[128] = { 0 };
					cmd[0] = '\"';
					strcat(cmd, newpath);
					strcat(cmd, "\"");
					system(cmd);
				}
			}
			else {
				mciSendString("close mouse", 0, 0, 0);
				putimage(0, 0, &convertback);
			}
		}
		Sleep(10);
	}
}