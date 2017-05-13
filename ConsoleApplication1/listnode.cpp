//建立链表
#include"stdafx.h"
#include"mainUI.h"
#include"listnode.h"
#include"linktofile.h"
#pragma warning(disable: 4996)
int on = 0, os = 0, num = 0;
//歌曲名称排列链表
sglist * initlist(){
	sglist *plist = (sglist *)malloc(sizeof(sglist));
	if (plist == NULL){
		MessageBox(wnd, "内存错误！", "警告", MB_OK | MB_ICONWARNING | MB_SYSTEMMODAL);
		return NULL;
	}
	plist->head = NULL;
	plist->tail = (sgptr)malloc(sizeof(song));
	if (plist->tail == NULL){
		MessageBox(wnd, "内存错误！", "警告", MB_OK | MB_ICONWARNING | MB_SYSTEMMODAL);
		return NULL;
	}
	plist->tail->prior = NULL;
	plist->tail->next = NULL;
	return plist;
}
mslist * minitlist(){
	mslist *plist = (mslist *)malloc(sizeof(mslist));
	if (plist == NULL){
		MessageBox(wnd, "内存错误！", "警告", MB_OK | MB_ICONWARNING | MB_SYSTEMMODAL);
		return NULL;
	}
	plist->head = NULL;
	plist->tail = (msptr)malloc(sizeof(music));
	if (plist->tail == NULL){
		MessageBox(wnd, "内存错误！", "警告", MB_OK | MB_ICONWARNING | MB_SYSTEMMODAL);
		return NULL;
	}
	plist->tail->prior = NULL;
	plist->tail->next = NULL;
	return plist;
}
sglist *nlist,*slist;
mslist *mlist;
void namelist(){
	if (on >= 1) return;
	register int n = 0, s = 0;
	num = 0;
	FILE *fp;
	fp = fopen(songpath, "r");
	nlist = NULL;
	nlist = initlist();
	char getname[45] = { 0 }, getsinger[35] = { 0 };
	fgets(getname, 45, fp);
	fgets(getsinger, 35, fp);
	getname[strlen(getname) - 1] = '\0';
	getsinger[strlen(getsinger) - 1] = '\0';
	n = strlen(getname) - 2;
	while (getname[n] == ' ') {
		getname[n] = '\0';
		n--;
	}
	s = strlen(getsinger) - 2;
	while (getsinger[s] == ' ') {
		getsinger[s] = '\0';
		s--;
	}
	while (!feof(fp)){	
		sgptr npreptr = NULL, nlastptr, newptr = NULL;
		fflush(stdin);
		newptr = (sgptr)malloc(sizeof(song));
		if (newptr == NULL){
			MessageBox(wnd, "内存错误！", "警告", MB_OK | MB_ICONWARNING | MB_SYSTEMMODAL);
			return;
		}
		strcpy(newptr->name, getname);
		strcpy(newptr->singer, getsinger);
		newptr->prior = NULL;
		newptr->next = NULL;
		nlastptr = nlist->head;
		num++;
		while ((nlastptr != NULL) && (strcmp(getname, nlastptr->name) == 1 || (strcmp(getname, nlastptr->name) == 0 && strcmp(getsinger, nlastptr->singer) == 1))){
			npreptr = nlastptr;
			nlastptr = nlastptr->next;
		}
		if (npreptr == NULL){
			newptr->next = nlist->head;
			if (nlist->head != NULL)
				nlist->head->prior = newptr;
			else {
				newptr->next = nlist->tail;
				nlist->tail->prior = newptr;
			}
			nlist->head = newptr;
		}
		else{
			if (npreptr->next == NULL){
				newptr->prior = nlist->tail;
				nlist->tail->next = newptr;
				nlist->tail = newptr;
			}
			else{
				newptr->prior = nlastptr->prior;
				newptr->next = nlastptr;
				npreptr->next = newptr;
				nlastptr->prior = newptr;
			}
		}
		fgets(getname, 45, fp);
		fgets(getsinger, 35, fp);
		getname[strlen(getname) - 1] = '\0';
		getsinger[strlen(getsinger) - 1] = '\0';
		n = strlen(getname) - 2;
		while (getname[n] == ' ') {
			getname[n] = '\0';
			n--;
		}
		s = strlen(getsinger) - 2;
		while (getsinger[s] == ' ') {
			getsinger[s] = '\0';
			s--;
		}
	}
	fclose(fp);
	on++;
}
//演唱者名字排列链表
void singerlist(){
	if (os >= 1) return;
	register int n = 0, s = 0, num = 0;
	FILE *fp;
	fp = fopen(songpath, "r");
	slist = NULL;
	slist = initlist();
	char getname[45] = { 0 }, getsinger[35] = { 0 };
	fgets(getname, 45, fp);
	fgets(getsinger, 35, fp);
	getname[strlen(getname) - 1] = '\0';
	getsinger[strlen(getsinger) - 1] = '\0';
	n = strlen(getname) - 2;
	while (getname[n] == ' ') {
		getname[n] = '\0';
		n--;
	}
	s = strlen(getsinger) - 2;
	while (getsinger[s] == ' ') {
		getsinger[s] = '\0';
		s--;
	}
	while (!feof(fp)){
		sgptr spreptr = NULL, slastptr, newptr = NULL;
		fflush(stdin);
		newptr = (sgptr)malloc(sizeof(song));
		if (newptr == NULL){
			MessageBox(wnd, "内存错误！", "警告", MB_OK | MB_ICONWARNING | MB_SYSTEMMODAL);
			return;
		}
		strcpy(newptr->name, getname);
		strcpy(newptr->singer, getsinger);
		newptr->prior = NULL;
		newptr->next = NULL;
		slastptr = slist->head;
		while ((slastptr != NULL) && (strcmp(getsinger, slastptr->singer) == 1 || (strcmp(getsinger, slastptr->singer) == 0 && strcmp(getname, slastptr->name) == 1))){
			spreptr = slastptr;
			slastptr = slastptr->next;
		}
		if (spreptr == NULL){
			newptr->next = slist->head;
			if (slist->head != NULL)
				slist->head->prior = newptr;
			else {
				newptr->next = slist->tail;
				slist->tail->prior = newptr;
			}
			slist->head = newptr;
		}
		else{
			if (spreptr->next == NULL){
				newptr->prior = slist->tail;
				slist->tail->next = newptr;
				slist->tail = newptr;
			}
			else{
				newptr->prior = slastptr->prior;
				newptr->next = slastptr;
				spreptr->next = newptr;
				slastptr->prior = newptr;
			}
		}
		fgets(getname, 45, fp);
		fgets(getsinger, 35, fp);
		getname[strlen(getname) - 1] = '\0';
		getsinger[strlen(getsinger) - 1] = '\0';
		n = strlen(getname) - 2;
		while (getname[n] == ' ') {
			getname[n] = '\0';
			n--;
		}
		s = strlen(getsinger) - 2;
		while (getsinger[s] == ' ') {
			getsinger[s] = '\0';
			s--;
		}
	}
	fclose(fp);
	os++;
}
int pli;
void musiclist(){
	extern int pin;
	extern long here, herec, start, paustart, forward;
	extern msptr lastptr;
	FILE *fp,*fpw;
	fp = fopen("playsong.data", "r");
	fprintf(fp, "\n");
	mlist = NULL;
	mlist = minitlist();
	char getname[100] = { 0 };
r:
	fgets(getname, 100, fp);
	if (getname[1] == '\0') {
		MessageBox(wnd, "该路径下无mp3或wma文件！", "无法找音乐", MB_OK | MB_ICONWARNING | MB_SYSTEMMODAL);
		fpw = fopen("songpath.data", "w");
		fprintf(fpw, "%s", &chl);
		fclose(fpw);
		pin = 0;
		pinput();
	}
	getname[strlen(getname) - 1] = '\0';
	while (!feof(fp)){
		char *ptr = strchr(getname, '.');
		if (getname[strlen(getname) - 1] == '.') goto r;
		if (ptr == NULL) goto r;
		else if (strcmp(ptr, ".mp3") != 0 && strcmp(ptr, ".wma") != 0) goto r;
		msptr newptr = NULL;
		fflush(stdin);
		newptr = (msptr)malloc(sizeof(music));
		if (newptr == NULL){
			MessageBox(wnd, "内存错误！", "警告", MB_OK | MB_ICONWARNING | MB_SYSTEMMODAL);
		}
		strcpy(newptr->name, getname);
		newptr->prior = NULL;
		newptr->next = NULL;
		if (mlist->head == NULL) mlist->head = newptr;
		else{
			mlist->tail->next = newptr;
			newptr->prior = mlist->tail;
			mlist->tail = newptr;
			if (mlist->head->next == NULL){
				mlist->head->next = mlist->tail;
				mlist->tail->prior = mlist->head;
			}
		}
		fgets(getname, 100, fp);
		getname[strlen(getname) - 1] = '\0';
	}
	if (mlist->head->name == NULL) {
		MessageBox(wnd, "该路径下无mp3或wma文件！", "无法找音乐", MB_OK | MB_ICONWARNING | MB_SYSTEMMODAL);
		fpw = fopen("songpath.data", "w");
		fprintf(fpw, "%s", &chl);
		fclose(fpw);
		pin = 0;
		pinput();
	}
	mlist->tail->next = mlist->head;
	mlist->head->prior = mlist->tail;
	fclose(fp);
	pli = 1;
	lastptr = mlist->head;
	MessageBox(wnd, "音乐成功链接！", "找到音乐", MB_OK | MB_ICONWARNING | MB_SYSTEMMODAL);
	here = 0, herec = 0, start = 0, paustart = 0, forward = 0;
	strcpy(chl, chf);
}