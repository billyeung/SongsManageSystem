#include"stdafx.h"
#include"listnode.h"
#include"menu.h"
#include"mainUI.h"
#pragma warning(disable: 4996)
char namec[3], singerc[3];
void listcount(int *name, int *singer) {
	namelist();
	sgptr nlastptr = nlist->head;
	sgptr nextptr = NULL;
	do{
		nextptr = nlastptr->next;
		if (strcmp(nlastptr->name, nextptr->name) == 0){
			if (strcmp(nlastptr->singer, nextptr->singer) == 0) (*name)--;
		}
		nlastptr = nextptr;
		(*name)++;
	} while (nextptr->next != nlist->tail);
	singerlist();
	sgptr slastptr = slist->head;
	nextptr = NULL;
	do{
		nextptr = slastptr->next;
		if (strcmp(slastptr->singer, nextptr->singer) != 0) (*singer)++;
		slastptr = nextptr;
	} while (nextptr->next!=slist->tail);
	sprintf(namec, "%d", *name);
	sprintf(singerc, "%d", *singer);
}
void count(){
	me = 8;
	main++;
	int name = 1, singer = 1;
	IMAGE countback, counthalf,shutlight, homelight, background;
	loadimage(&countback, "IMAGE", "count.bmp");
	loadimage(&shutlight, "IMAGE", "shutlight.bmp");
	loadimage(&homelight, "IMAGE", "homelight.bmp");
	loadimage(&background, "IMAGE", "background.bmp");
	loadimage(&counthalf, "IMAGE", "counthalf.bmp");
	setlinecolor(RGB(255, 255, 0)); setlinestyle(PS_SOLID, 3);
	for (int i = 640; i >= 0; i -= 5){
		putimage(i, 0, &countback);
		Sleep(int(-0.156*(i / 10) + 10));
	}
	listcount(&name, &singer);
	setbkmode(TRANSPARENT);
	LOGFONT fc;
	gettextstyle(&fc);
	_tcscpy_s(fc.lfFaceName, _T("微软雅黑"));
	fc.lfHeight = 50;
	fc.lfQuality = ANTIALIASED_QUALITY | PROOF_QUALITY;
	settextcolor(RGB(15,5,65));
	settextstyle(&fc);
	while (true){
		if (name >= 10 && singer >= 10){
			outtextxy(177, 206, namec);
			outtextxy(343, 206, singerc);
		}
		else if (name >= 10 && singer < 10){
			outtextxy(177, 206, namec);
			outtextxy(359, 206, singerc);
		}
		else if (name < 10 && singer >= 10){
			outtextxy(189, 206, namec);
			outtextxy(343, 206, singerc);
		}
		else{
			outtextxy(189, 206, namec);
			outtextxy(359, 206, singerc);
		}
		choice();
		MOUSEMSG msg;//获取鼠标信息
		msg = GetMouseMsg();
		if (msg.x >= 585 && msg.x <= 620 && msg.y >= 20 && msg.y <= 58){
			putimage(578, 15, &shutlight, SRCPAINT);
			mciSendString(mcimouse, NULL, 0, NULL);
			mciSendString("play mouse", 0, 0, 0);
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
		else {
			mciSendString("close mouse", 0, 0, 0);
			putimage(520, 0, &counthalf);
		}
	}
}