#include"stdafx.h"
#include"mainUI.h"
#include"player.h"
#include"listnode.h"
#include"linktofile.h"
#pragma warning(disable: 4996)
char songpath[100] = "song.txt", newpath[100] = "Newsong.txt", musicpath[100] = { 0 }, mpath[100] = { 0 };
void searchfile(){
	char ch[100];
	char path[100] = { 0 };
	bool flag;
	FILE *fp, *fpn;
	fp = fopen(songpath, "r");
	if (fp == NULL){
	start:
		flag = InputBox(ch, 100, "�ڳ����Ŀ¼����song.txt�ļ���\n������song.txt�����ļ���·����", "�޷��ҵ��ļ�", NULL, 400, 0, false);
		if (flag == false) {
			DeleteFile(loginBGM);
			DeleteFile(mouses);
			DeleteFile(click);
			exit(0);
		}
		if (ch[0] == '\0' || ch[0] == ' '){
			MessageBox(wnd, "�ļ�·������Ϊ�գ�", "�޷��ҵ��ļ�", MB_OK | MB_ICONWARNING | MB_SYSTEMMODAL);
			goto start;
		}
	re:
		strcpy(path, ch);
		fpn = fopen(strcat(ch, "\\song.txt"), "r");
		if (fpn == NULL){
			flag = InputBox(ch, 100, "��ָ��·������song.txt�ļ���\n������song.txt�ļ�·����", "�޷��ҵ��ļ�", NULL, 300, 0, false);
			if (flag == false) {
				DeleteFile(loginBGM);
				DeleteFile(mouses);
				DeleteFile(click);
				exit(0);
			}
			if (ch[0] == '\0' || ch[0] == ' '){
				MessageBox(wnd, "�ļ�·������Ϊ�գ�", "�޷��ҵ��ļ�", MB_OK | MB_ICONWARNING | MB_SYSTEMMODAL);
			}
			goto re;
		}
		else {
			fclose(fpn);
			strcpy(songpath, ch);
			strcpy(newpath, strcat(path, "\\Newsong.txt"));
			MessageBox(wnd, "song.txt�ɹ����ӣ�", "�ҵ��ļ�", MB_OK | MB_ICONWARNING | MB_SYSTEMMODAL);
		}
	}
	else fclose(fp);
}
void linkfile(){
	char ch[100];
	char path[100] = { 0 };
	bool flag;
	FILE *fpn;
start:
	flag = InputBox(ch, 100, "��������song.txt�����ļ���·����", "���������ļ�", NULL, 400, 0, false);
	if (flag == false) {
		return;
	}
	if (ch[0] == '\0' || ch[0] == ' '){
		MessageBox(wnd, "�ļ�·������Ϊ�գ�", "�޷��ҵ��ļ�", MB_OK | MB_ICONWARNING | MB_SYSTEMMODAL);
		goto start;
	}
re:
	strcpy(path, ch);
	fpn = fopen(strcat(ch, "\\song.txt"), "r");
	if (fpn == NULL){
		flag = InputBox(ch, 100, "��ָ��·������song.txt�ļ���\n������song.txt�ļ�·����", "�޷��ҵ��ļ�", NULL, 300, 0, false);
		if (flag == false) {
			return;
		}
		if (ch[0] == '\0' || ch[0] == ' '){
			MessageBox(wnd, "�ļ�·������Ϊ�գ�", "�޷��ҵ��ļ�", MB_OK | MB_ICONWARNING | MB_SYSTEMMODAL);
		}
		goto re;
	}
	else {
		fclose(fpn);
		strcpy(songpath, ch);
		strcpy(newpath, strcat(path, "\\Newsong.txt"));
		MessageBox(wnd, "song.txt�ɹ����ӣ�", "�ҵ��ļ�", MB_OK | MB_ICONWARNING | MB_SYSTEMMODAL);
		on = 0; os = 0;
	}
}
char chl[100] = { 0 }, chf[100] = { 0 };
FILE *fp, *fpw;
void pinput(){
	bool flag;
	flag = InputBox(chf, 100, "���������������ļ���·����", "��������", NULL, 400, 0, false);
	if (flag == false) {
		if (pin == 0 || pli == 0) {
			pin = 0;
			mainUI();
		}
		else {
			fclose(fp);
			pli = 1;
			return;
		}
	}
	if (chf[0] == '\0' || chf[0] == ' '){
		MessageBox(wnd, "�ļ�·������Ϊ�գ�", "�޷�������", MB_OK | MB_ICONWARNING | MB_SYSTEMMODAL);
		if (pin == 0) mainUI();
		return;
	}
	if (strchr(chf, '\\') == NULL || strchr(chf, '\\') == NULL){
		MessageBox(wnd, "�ļ�·����ʽ����", "�޷�������", MB_OK | MB_ICONWARNING | MB_SYSTEMMODAL);
		if (pin == 0) mainUI();
		return;
	}
	fpw = fopen("songpath.data", "w");
	fprintf(fpw, "%s", &chf);
	fclose(fpw);
	pin = 0; pli = 0;
	linksong();
}
void linksong(){
	char cmd[100] = { 0 }, ch3[20] = "��ǰ�ļ���·��Ϊ��";
	fp = fopen("songpath.data", "r");
	if (fp == NULL){
		fpw = fopen("songpath.data", "w");
		fclose(fpw);
		fp = fopen("songpath.data", "r");
	}
	if (pin == 0) fgets(chf, 100, fp);
	else if (pin == 1 || chf[1] == '\0') pinput();
	if (fp != NULL) fclose(fp);
	if (pli == 0){
		strcpy(mpath, ch3);
		strcat(mpath, chf);
		sprintf_s(cmd, "dir %s/b>playsong.data", chf);
		system(cmd);
		strcpy(musicpath, chf);
		strcat(musicpath, "\\");
		stop();
		musiclist();
	}
	pin = 1;
}