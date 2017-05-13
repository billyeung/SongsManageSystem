//ÅÅÐò
#include"stdafx.h"
#include"listnode.h"
#include"menu.h"
#include"mainUI.h"
#pragma warning(disable:4996)
void font(){
	IMAGE list;
	loadimage(&list, "IMAGE", "list.bmp");
	putimage(20, 142, &list);
	setbkmode(TRANSPARENT);
	LOGFONT fs;
	gettextstyle(&fs);
	_tcscpy_s(fs.lfFaceName, _T("Î¢ÈíÑÅºÚ"));
	fs.lfWeight = 100;
	fs.lfHeight = 20;
	fs.lfQuality = ANTIALIASED_QUALITY | PROOF_QUALITY;
	settextcolor(RGB(33, 33, 33));
	settextstyle(&fs);
}
void fontp(){
	setbkmode(TRANSPARENT);
	LOGFONT fc;
	gettextstyle(&fc);
	_tcscpy_s(fc.lfFaceName, _T("Î¢ÈíÑÅºÚ"));
	fc.lfHeight = 19;
	fc.lfWeight = 700;
	fc.lfQuality = ANTIALIASED_QUALITY | PROOF_QUALITY;
	settextcolor(WHITE);
	settextstyle(&fc);
}
void nameup(int np){
	int i = 0;
	font();
	namelist();
	sgptr nlastptr = nlist->head;
	for (int p = 0; p < 11 * (np - 1); p++){
		nlastptr = nlastptr->next;
	}
	while (nlastptr != nlist->tail){
		outtextxy(28, 169 + i, nlastptr->name);
		outtextxy(400, 169 + i, nlastptr->singer);
		nlastptr = nlastptr->next;
		i += 25;
		if (i >= 275) break;
	}
}
void singerup(int sp){
	int i = 0;
	font();
	singerlist();
	sgptr slastptr = slist->head;
	for (int p = 0; p < 11 * (sp - 1); p++){
		slastptr = slastptr->next;
	}
	while (slastptr != slist->tail){
		outtextxy(28, 169 + i, slastptr->name);
		outtextxy(400, 169 + i, slastptr->singer);
		slastptr = slastptr->next;
		i += 25;
		if (i >= 275) break;
	}
}
void namedown(int np){
	int i = 0;
	font();
	namelist();
	sgptr nlastptr = nlist->tail->prior;
	for (int p = 0; p < 11 * (np - 1); p++){
		nlastptr = nlastptr->prior;
	}
	while (nlastptr != NULL){
		outtextxy(28, 169 + i, nlastptr->name);
		outtextxy(400, 169 + i, nlastptr->singer);
		nlastptr = nlastptr->prior;
		i += 25;
		if (i >= 275) break;
	}
}
void singerdown(int sp){
	int i = 0;
	font();
	singerlist();
	sgptr slastptr = slist->tail->prior;
	for (int p = 0; p < 11 * (sp - 1); p++){
		slastptr = slastptr->prior;
	}
	while (slastptr != NULL){
		outtextxy(28, 169 + i, slastptr->name);
		outtextxy(400, 169 + i, slastptr->singer);
		slastptr = slastptr->prior;
		i += 25;
		if (i >= 275) break;
	}
}
void sequences(){
	me = 7;
	main++;
	int N = 1, S = 0, func = 0, np = 1, sp = 1;
	char npc[2] = { 0 }, spc[2] = { 0 };
	int page;
	char ptoc;
	IMAGE seqpage,name,singer,cover,up,down,sequenceback, sequencehalf,shutlight, homelight, background;
	loadimage(&seqpage, "IMAGE", "seqpage.bmp");
	loadimage(&name, "IMAGE", "name.bmp");
	loadimage(&singer, "IMAGE", "singer.bmp");
	loadimage(&cover, "IMAGE", "cover.bmp");
	loadimage(&up, "IMAGE", "up.bmp");
	loadimage(&down, "IMAGE", "down.bmp");
	loadimage(&sequenceback, "IMAGE", "sequence.bmp");
	loadimage(&sequencehalf, "IMAGE", "sequencehalf.bmp");
	loadimage(&shutlight, "IMAGE", "shutlight.bmp");
	loadimage(&homelight, "IMAGE", "homelight.bmp");
	loadimage(&background, "IMAGE", "background.bmp");
	setlinecolor(RGB(255, 255, 0)); setlinestyle(PS_SOLID, 3);
	for (int i = 640; i >= 0; i -= 5){
		putimage(i, 0, &sequenceback);
		Sleep(int(-0.156*(i / 10) + 10));
	}
	nameup(np);
	page = (num / 11);
	if (num % 11 != 0) page++;
	sprintf(&ptoc, "%d", page);
	putimage(590, 113, &seqpage);
	fontp();
	npc[0] = '1'; spc[0] = '1';
	outtextxy(593, 112, "1");
	outtextxy(502, 112, ptoc);
	while (true){
		choice();
		MOUSEMSG msg;//»ñÈ¡Êó±êÐÅÏ¢
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
			else if (msg.x >= 22 && msg.x <= 142 && msg.y >= 100 && msg.y <= 122){
				line(22, 127, 142, 127);
				if (msg.uMsg == WM_LBUTTONUP) {
					mciSendString("close click", 0, 0, 0);
					mciSendString(mciclick, NULL, 0, NULL);
					mciSendString("play click", 0, 0, 0);
					putimage(590, 113, &seqpage);
					fontp();
					outtextxy(593, 112, "1");
					np = 1; func = 0; npc[0] = '1';
					if (N == 0){
						putimage(150, 101, &up);
						putimage(354, 100, &cover);
						nameup(np);
						N = 1; S = 0;
					}
					else if (N == 1){
						putimage(150, 101, &down);
						putimage(354, 100, &cover);
						namedown(np);
						N = 0; S = 0;
					}
				}
			}
			else if (msg.x >= 200 && msg.x <= 348 && msg.y >= 100 && msg.y <= 122){
				line(202, 127, 346, 127);
				if (msg.uMsg == WM_LBUTTONUP){
					mciSendString("close click", 0, 0, 0);
					mciSendString(mciclick, NULL, 0, NULL);
					mciSendString("play click", 0, 0, 0);
					putimage(590, 113, &seqpage);
					fontp();
					outtextxy(593, 112, "1");
					sp = 1; func = 1; spc[0] = '1';
					if (S == 0){
						putimage(354, 101, &up);
						putimage(148, 100, &cover);
						singerup(sp);
						S = 1; N = 0;
					}
					else if (S == 1){
						putimage(354, 101, &down);
						putimage(148, 100, &cover);
						singerdown(sp);
						S = 0; N = 0;
					}
				}
			}
			else if (msg.x >= 537 && msg.x <= 553 && msg.y >= 113 && msg.y <= 132){
				if (msg.uMsg == WM_LBUTTONUP){
					mciSendString("close click", 0, 0, 0);
					mciSendString(mciclick, NULL, 0, NULL);
					mciSendString("play click", 0, 0, 0);
					if (func == 0){
						if (npc[0] > '1') npc[0]--;
						putimage(590, 113, &seqpage);
						fontp();
						outtextxy(593, 112, npc[0]);
						if (N == 1){
							if (np > 1){
								np--;
								nameup(np);
							}
						}
						else if (N == 0){
							if (np > 1){
								np--;
								namedown(np);
							}
						}
					}
					else if (func == 1){
						if (spc[0] > '1') spc[0]--;
						putimage(590, 113, &seqpage);
						fontp();
						outtextxy(593, 112, spc);
						if (S == 1){
							if (sp > 1){
								sp--;
								singerup(sp);
							}
						}
						else if (S == 0){
							if (sp > 1){
								sp--;
								singerdown(sp);
							}
						}
					}
				}
			}
			else if (msg.x >= 604 && msg.x <= 620 && msg.y >= 113 && msg.y <= 132){
				if (msg.uMsg == WM_LBUTTONUP){
					mciSendString("close click", 0, 0, 0);
					mciSendString(mciclick, NULL, 0, NULL);
					mciSendString("play click", 0, 0, 0);
					if (func == 0){
						if (npc[0] < ptoc) npc[0]++;
						putimage(590, 113, &seqpage);
						fontp();
						outtextxy(593, 112, npc[0]);
						if (N == 1){
							if (np < page){
								np++;
								nameup(np);
							}
						}
						else if (N == 0){
							if (np < page){
								np++;
								namedown(np);
							}
						}
					}
					else if (func == 1){
						if (spc[0] < ptoc) spc[0]++;
						putimage(590, 113, &seqpage);
						fontp();
						outtextxy(593, 112, spc);
						if (S == 1){
							if (sp < page){
								sp++;
								singerup(sp);
							}
						}
						else if (S == 0){
							if (sp < page){
								sp++;
								singerdown(sp);
							}
						}
					}
				}
			}
			else if (msg.x >= 524 && msg.x <= 562 && msg.y >= 20 && msg.y <= 58){
				mciSendString(mcimouse, NULL, 0, NULL);
				mciSendString("play mouse", 0, 0, 0);
				putimage(516, 14, &homelight, SRCPAINT);
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
				putimage(20, 98, &name);
				putimage(200, 98, &singer);
				putimage(0, 0, &sequencehalf);
			}
		}
		Sleep(10);
	}
}