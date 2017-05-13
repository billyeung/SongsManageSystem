//播放器
#include"stdafx.h"
#include"menu.h"
#include"mainUI.h"
#include"linktofile.h"
#include"listnode.h"
#pragma warning(disable: 4996)
int min, sec, pmin, psec, pflag = 0, pmode = 0, pin = 0;
char slen[256] = { 0 }, plen[255] = { 0 }, sch[100] = { 0 };
long here, herec, llen = 1, cplen, p, vol = 500, start, paustart, pautime, pautimec, forward;
char v[3] = "50";
msptr lastptr = NULL;
IMAGE playerplay;
void getlength(){
	mciSendString("status mymusic length", slen, 255, 0);
	llen = strtol(slen, 0, 0) / 1000;//测量出媒体长度，单位为秒，需要转化
	min = llen / 60;//分
	sec = llen % 60;//秒
}
void printtime(){
	extern void nexts();
	IMAGE cleartime;
	loadimage(&cleartime, "IMAGE", "cleartime.bmp");
	LOGFONT fct;
	char ptime[20] = { 0 };
	char length[7] = { 0 };
	if (pmode == 1&&pflag==1) {
		here = herec = clock() - start - pautimec + forward;
		pautime = 0;
	}
	else here = herec;
	pmin = (here / 1000) / 60;
	psec = (here / 1000) % 60;
	if (pmin >= 10 && psec >= 10)
		sprintf(ptime, "%d:%d / ", pmin, psec);
	else if (pmin<10 && psec >= 10)
		sprintf(ptime, "0%d:%d / ", pmin, psec);
	else if (pmin >= 10 && psec<10)
		sprintf(ptime, "%d:0%d / ", pmin, psec);
	else
		sprintf(ptime, "0%d:0%d / ", pmin, psec);
	if (min >= 10 && sec >= 10)
		sprintf(length, "%d:%d", min, sec);
	else if (min<10 && sec >= 10)
		sprintf(length, "0%d:%d", min, sec);
	else if (min >= 10 && sec<10)
		sprintf(length, "%d:0%d", min, sec);
	else
		sprintf(length, "0%d:0%d", min, sec);
	strcat(ptime, length);
	gettextstyle(&fct);
	_tcscpy_s(fct.lfFaceName, _T("微软雅黑"));
	fct.lfHeight = 27;
	fct.lfWeight = 200;
	fct.lfQuality = ANTIALIASED_QUALITY | PROOF_QUALITY;
	settextcolor(WHITE);
	settextstyle(&fct);
	putimage(125, 220, &cleartime);
	outtextxy(129, 223, ptime);
	if (here >= llen * 1000) nexts();
}
void printvol(){
	LOGFONT fc;
	gettextstyle(&fc);
	_tcscpy_s(fc.lfFaceName, _T("微软雅黑"));
	fc.lfHeight = 17;
	fc.lfWeight = 500;
	fc.lfQuality = ANTIALIASED_QUALITY | PROOF_QUALITY;
	settextcolor(WHITE);
	settextstyle(&fc);
	if (vol == 0) outtextxy(468, 244, v);
	else if (vol == 1000) outtextxy(460, 244, v);
	else outtextxy(464, 244, v);
}
void stop(){
	mciSendString("stop mymusic", NULL, 0, NULL);//停止音乐
	mciSendString("close mymusic", NULL, 0, NULL);
	pflag = 0;
	pmode = 0;
	here = herec = 0;
	putimage(130, 263, &playerplay);
}
void getsong(){
	IMAGE clearname;
	loadimage(&clearname, "IMAGE", "clearname.bmp");
	char path[100] = { 0 }, songname[100] = { 0 };
	strcpy_s(songname, lastptr->name);
	strcpy_s(path, musicpath);
	strcat_s(path, songname);
	sprintf_s(sch, "open \"%s\" alias mymusic", path);
	putimage(0, 327, &clearname);
	settextstyle(20,0,0);
	outtextxy(128, 330, songname);
}
void plays(){
	char ch[100];
	getsong();
	mciSendString(TEXT(sch), NULL, 0, NULL);//开始音乐
	sprintf(ch, "setaudio mymusic volume to %ld", vol);
	pmode = 1;
	mciSendString("play mymusic", NULL, 0, NULL);
	mciSendString(ch, 0, 0, 0);
	pautime = pautimec = 0;
	forward = 0;
	start = clock();
	getlength();
}
void previouss(){
	stop();
	lastptr = lastptr->prior;
	getsong();
	mciSendString(TEXT(sch), NULL, 0, NULL);//开始音乐
	mciSendString("play mymusic", NULL, 0, NULL);
	pmode = 1; pflag = 1;
	pautime = pautimec = 0;
	forward = 0;
	start = clock();
	getlength();
}
void nexts(){
	stop();
	lastptr = lastptr->next;
	getsong();
	mciSendString(TEXT(sch), NULL, 0, NULL);//开始音乐
	mciSendString("play mymusic", NULL, 0, NULL);
	pmode = 1; pflag = 1;
	pautime = pautimec = 0;
	forward = 0;
	start = clock();
	getlength();
}
void resume(){
	mciSendString("resume mymusic", NULL, 0, NULL);
	pautime = clock() - paustart;
	pautimec += pautime;
}
void pauses(){
	mciSendString("pause mymusic", NULL, 0, NULL);//暂停音乐
	paustart = clock();
}
void rewinds(){
	if (pflag == 0) return;
	char ch[30];
	here = here - 10000;
	forward -= 10000;
	if (here < 10000){//快退到开始状态
		here = herec = 0;
		forward = 0;
	}
	sprintf(ch, "seek mymusic to %ld", here);
	mciSendString(ch, 0, 0, 0);
	if (pflag == 1){
		if (here < 10000) plays();
		else mciSendString("play mymusic", 0, 0, 0);
	}
}
void ffs(){
	if (pflag == 0) return;
	char ch[30];
	here = here + 10000;
	forward += 10000;
	if (here>llen*1000){//快进到结束状态
		here = llen * 1000;
	}
	sprintf(ch, "seek mymusic to %ld", here);
	mciSendString(ch, 0, 0, 0);
	if (pflag == 1) mciSendString("play mymusic", 0, 0, 0);
}
void volup(){
	IMAGE clearvol;
	loadimage(&clearvol, "IMAGE", "clearvol.bmp");
	putimage(430, 245, &clearvol);
	char ch[50] = { 0 };
	vol += 100;
	if (vol >= 1000) vol = 1000;
	sprintf(v, "%ld", vol / 10);
	sprintf(ch, "setaudio mymusic volume to %ld", vol);
	mciSendString(ch, 0, 0, 0);
	printvol();
}
void voldown(){
	IMAGE clearvol;
	loadimage(&clearvol, "IMAGE", "clearvol.bmp");
	putimage(430, 245, &clearvol);
	char ch[50] = { 0 };
	vol -= 100;
	if (vol < 0) vol = 0;
	sprintf(v, "%ld", vol / 10);
	sprintf(ch, "setaudio mymusic volume to %ld", vol);
	mciSendString(ch, 0, 0, 0);
	printvol();
}
void player(){
	me = 5;
	main++;
	setbkmode(TRANSPARENT);
	IMAGE changepath, playerback, playerhalf, playeremp, playerpause, buttonleft, buttonright, shutlight, homelight, background, play, pause, pauselight, previous, next, rewind, ff, playback;
	loadimage(&changepath, "IMAGE", "changepath.bmp");
	loadimage(&playerback, "IMAGE", "playerback.bmp");
	loadimage(&playerplay, "IMAGE", "playerplay.bmp");
	loadimage(&playerhalf, "IMAGE", "playerhalf.bmp");
	loadimage(&buttonleft, "IMAGE", "buttonleft.bmp");
	loadimage(&playeremp, "IMAGE", "playeremp.bmp");
	loadimage(&playerpause, "IMAGE", "playerpause.bmp");
	loadimage(&shutlight, "IMAGE", "shutlight.bmp");
	loadimage(&homelight, "IMAGE", "homelight.bmp");
	loadimage(&background, "IMAGE", "background.bmp");
	loadimage(&play, "IMAGE", "play.bmp");
	loadimage(&pause, "IMAGE", "pause.bmp");
	loadimage(&pauselight, "IMAGE", "pauselight.bmp");
	loadimage(&previous, "IMAGE", "previous.bmp");
	loadimage(&next, "IMAGE", "next.bmp");
	loadimage(&rewind, "IMAGE", "rewind.bmp");
	loadimage(&ff, "IMAGE", "ff.bmp");
	loadimage(&playback, "IMAGE", "playback.bmp");
	for (int i = 640; i >= 0; i -= 5){
		putimage(i, 0, &playerback);
		Sleep(int(-0.156*(i / 10) + 10));
	}
	here = 0, herec = 0, start = 0, paustart = 0, forward = 0;
start:
	printvol();
	if (pin == 0) linksong();
	putimage(0, 400, &changepath);
	settextstyle(20, 0, 0);
	outtextxy(0, 440, mpath);
	MOUSEMSG msg;//获取鼠标信息
	while (true){
		choice();
		printtime();
		while (MouseHit()){
			msg = GetMouseMsg();
			if (msg.x >= 585 && msg.x <= 620 && msg.y >= 20 && msg.y <= 58){
				putimage(578, 15, &shutlight, SRCPAINT);
				if (msg.uMsg == WM_LBUTTONUP) {
					DeleteFile(loginBGM);
					DeleteFile(mouses);
					DeleteFile(click);
					exit(0);
				}
			}
			else if (msg.x >= 130 && msg.x <= 190 && msg.y >= 263 && msg.y <= 323){
				putimage(130, 263, &previous);
				if (msg.uMsg == WM_LBUTTONUP) previouss();
			}
			else if (msg.x >= 210 && msg.x <= 270 && msg.y >= 263 && msg.y <= 323){
				putimage(210, 263, &rewind);
				if (msg.uMsg == WM_LBUTTONUP) rewinds();
			}
			else if (msg.x >= 498 && msg.x <= 509 && msg.y >= 227 && msg.y <= 240){
				if (msg.uMsg == WM_LBUTTONUP) volup();
			}
			else if (msg.x >= 430 && msg.x <= 442 && msg.y >= 232 && msg.y <= 235){
				if (msg.uMsg == WM_LBUTTONUP) voldown();
			}
			else if (msg.x >= 290 && msg.x <= 350 && msg.y >= 263 && msg.y <= 323){
				if (pflag == 0){
					putimage(290, 263, &play);
					if (msg.uMsg == WM_LBUTTONUP) {
						pflag = 1;
						putimage(130, 263, &playerpause);
						putimage(290, 263, &pauselight);
						if(pmode==0) plays();
						else resume();
					}
				}
				else if (pflag == 1){
					putimage(290, 263, &pauselight);
					if (msg.uMsg == WM_LBUTTONUP) {
						pflag = 0;
						putimage(130, 263, &playerplay);
						pauses();
					}
				}
			}
			else if (msg.x >= 370 && msg.x <= 430 && msg.y >= 263 && msg.y <= 323){
				putimage(370, 263, &ff);
				if (msg.uMsg == WM_LBUTTONUP) ffs();
			}
			else if (msg.x >= 450 && msg.x <= 510 && msg.y >= 263 && msg.y <= 323){
				putimage(450, 263, &next);
				if (msg.uMsg == WM_LBUTTONUP) nexts();
			}
			else if (msg.x >= 0 && msg.x <= 100 && msg.y >= 400 && msg.y <= 440){
				if (msg.uMsg == WM_LBUTTONUP) {
					linksong();
					goto start;
				}
			}
			else if (msg.x >= 524 && msg.x <= 562 && msg.y >= 20 && msg.y <= 58){
				putimage(516, 14, &homelight, SRCPAINT);
				if (msg.uMsg == WM_LBUTTONUP) {
					stop();
					pflag = 0;
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
				if (pflag == 0) putimage(130, 263, &playerplay);
				else if (pflag == 1) putimage(130, 263, &playerpause);
				putimage(0, 0, &playerhalf);
			}
		}
		Sleep(10);
	}
}