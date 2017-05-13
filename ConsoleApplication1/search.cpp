#include"stdafx.h"
#include"listnode.h"
#include"menu.h"
#include"mainUI.h"
#pragma warning(disable: 4996)
int p,result; char ch[40] = { 0 };
void fonts(){
	setbkmode(TRANSPARENT);
	LOGFONT fc;
	gettextstyle(&fc);
	_tcscpy_s(fc.lfFaceName, _T("微软雅黑"));
	fc.lfHeight = 19;
	fc.lfWeight = 700;
	fc.lfQuality = ANTIALIASED_QUALITY | PROOF_QUALITY;
	settextcolor(WHITE);
	settextstyle(&fc);
}
int countpage(){
	int num = 0, page = 0;
	namelist();
	char *str = NULL, strn[80] = { 0 }, *s1 = NULL, *s2 = NULL;
	sgptr nlastptr = nlist->head;
	while (nlastptr != nlist->tail){
		strcpy(strn, nlastptr->name);
		str = strcat(strn, nlastptr->singer);
		while (*str != '\0'){
			s1 = str; s2 = ch;
			while (((*s2 >= 65 && *s2 <= 90) && (*s2 == *s1 || (*s2 + 32) == *s1)) || ((*s2 >= 97 && *s2 <= 122) && (*s2 == *s1 || (*s2 - 32) == *s1)) || (*s2 == *s1) && (*s2 != '\0') && (*s1 != '\0')){
				s2++; s1++;
			}
			if (*s2 == '\0') {
				num++;
				break;
			}
			else str++;
		}
		nlastptr = nlastptr->next;
	}
	page = (num / 11);
	if (num % 11 != 0) page++;
	return page;
}
void listsearch(){
	IMAGE list;
	int h = 0;
	int renum = 0;
	loadimage(&list, "IMAGE", "list.bmp");
	setbkmode(TRANSPARENT);
	LOGFONT fs;
	gettextstyle(&fs);
	_tcscpy_s(fs.lfFaceName, _T("微软雅黑"));
	fs.lfWeight = 100;
	fs.lfHeight = 20;
	fs.lfQuality = ANTIALIASED_QUALITY | PROOF_QUALITY;
	settextcolor(RGB(33, 33, 33));
	settextstyle(&fs);
	putimage(20, 142, &list);
	namelist();
	char *str, *strn, *s1, *s2;
	sgptr nlastptr = nlist->head;
	while (nlastptr!=nlist->tail){
		strn = (char*)malloc(sizeof(song));
		strcpy(strn, nlastptr->name);
		str = strcat(strn, nlastptr->singer);
		while (*str != '\0'){
			s1 = str; s2 = ch;
			while (((*s2 >= 65 && *s2 <= 90) && (*s2 == *s1 || (*s2 + 32) == *s1)) || ((*s2 >= 97 && *s2 <= 122) && (*s2 == *s1 || (*s2 - 32) == *s1)) || (*s2 == *s1) && (*s2 != '\0') && (*s1 != '\0')){
				s2++; s1++;
			}
			if (*s2 == '\0') {
				result++; renum++;
				if (renum > 11 * (p - 1) && renum <= 11 * p){
					outtextxy(28, 169 + h, nlastptr->name);
					outtextxy(400, 169 + h, nlastptr->singer);
					h += 25;
				}
				break;
			}
			else str++;
		}
		nlastptr = nlastptr->next;
	}
	if (result == 0){
		MessageBox(wnd, "未搜索到相匹配的记录！", "警告", MB_OK | MB_ICONWARNING | MB_SYSTEMMODAL);
	}
}
void input(){
	bool flag;
	flag = InputBox(ch, 40, "请输入搜索的信息：", "搜索", NULL, 200, 0, false);
	if (flag == false) {
		return;
	}
	if (ch[0] == '\0' || ch[0] == ' '){
		MessageBox(wnd, "搜索信息不能为空！", "搜索", MB_OK | MB_ICONWARNING | MB_SYSTEMMODAL);
		return;
	}
	result = 0; p = 1;
	listsearch();
}
void search(){
	me = 6;
	main++;
	int page=0;
	char ptoc = '1';
	result = 0;
	char pc[2];
	pc[0] = '1';
	IMAGE seapage, searchback, searchhalf1, searchhalf2, shutlight, homelight, background,seatpage;
	loadimage(&seapage, "IMAGE", "seapage.bmp");
	loadimage(&searchback, "IMAGE", "search.bmp");
	loadimage(&shutlight, "IMAGE", "shutlight.bmp");
	loadimage(&homelight, "IMAGE", "homelight.bmp");
	loadimage(&background, "IMAGE", "background.bmp");
	loadimage(&searchhalf1, "IMAGE", "searchhalf1.bmp");
	loadimage(&searchhalf2, "IMAGE", "searchhalf2.bmp");
	loadimage(&seatpage, "IMAGE", "seatpage.bmp");
	setlinecolor(RGB(255, 255, 0)); setlinestyle(PS_SOLID, 3);
	for (int i = 640; i >= 0; i -= 5){
		putimage(i, 0, &searchback);
		Sleep(int(-0.156*(i / 10) + 10));
	}
	fonts();
	outtextxy(593, 112, "1");
	outtextxy(502, 112, "0");
	while (true){
		choice();
		MOUSEMSG msg;//获取鼠标信息
		while (MouseHit()){
			msg = GetMouseMsg();
			if (ch[0] != '\0'){
				if (msg.x >= 537 && msg.x <= 553 && msg.y >= 113 && msg.y <= 132){
					if (msg.uMsg == WM_LBUTTONUP){
						mciSendString("close click", 0, 0, 0);
						mciSendString(mciclick, NULL, 0, NULL);
						mciSendString("play click", 0, 0, 0);
						if (pc[0] > '1') pc[0]--;
						putimage(590, 113, &seapage);
						fonts();
						outtextxy(593, 112, pc[0]);
						if (p > 1){
							p--;
							listsearch();
						}
					}
				}
				else if (msg.x >= 604 && msg.x <= 620 && msg.y >= 113 && msg.y <= 132){
					if (msg.uMsg == WM_LBUTTONUP){
						mciSendString("close click", 0, 0, 0);
						mciSendString(mciclick, NULL, 0, NULL);
						mciSendString("play click", 0, 0, 0);
						if (pc[0] < ptoc) pc[0]++;
						putimage(590, 113, &seapage);
						fonts();
						outtextxy(593, 112, pc[0]);
						if (p < page){
							p++;
							listsearch();
						}
					}
				}
			}
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
			else if (msg.x >= 44 && msg.x <= 150 && msg.y >= 86 && msg.y <= 122){
				mciSendString(mcimouse, NULL, 0, NULL);
				mciSendString("play mouse", 0, 0, 0);
				roundrect(44, 86, 150, 122, 15, 15);
				if (msg.uMsg == WM_LBUTTONUP) {
					mciSendString("close click", 0, 0, 0);
					mciSendString(mciclick, NULL, 0, NULL);
					mciSendString("play click", 0, 0, 0);
					input();
					pc[0] = '1';
					fonts();
					putimage(590, 113, &seapage);
					outtextxy(593, 112, "1");
					page = countpage();
					sprintf(&ptoc, "%d", page);
					putimage(500, 115, &seatpage);
					outtextxy(502, 112, ptoc);
				}
			}
			else{
				mciSendString("close mouse", 0, 0, 0);
				putimage(0, 0, &searchhalf1);
				putimage(510, 0, &searchhalf2);
			}
		}
		Sleep(10);
	}
}