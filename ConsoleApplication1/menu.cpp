//主界面的菜单
#include"stdafx.h"
#include"player.h"
#include"convert.h"
#include"listnode.h"
#include"search.h"
#include"sequences.h"
#include"count.h"
#include"mainUI.h"
#include"menu.h"
#include"linktofile.h"
#include"login.h"
WNDPROC OldProc;
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
int menumess,me,i=0;
HMENU hMenu, temp,temp1,temp2;
void enable(){
	EnableMenuItem(temp, me, MF_GRAYED);
	EnableMenuItem(temp1, me, MF_GRAYED);
	for (int m = 2; m <= 10; m++){
		if ((m == me)||(m==2&&main==0)) continue;
		EnableMenuItem(temp, m, MF_ENABLED);
		EnableMenuItem(temp1, m, MF_ENABLED);
	}
}
void menu(){
	if (i >= 1) return;
	extern void login();
	HWND wnd = GetHWnd();
	hMenu = CreateMenu();// 创建菜单
	temp = CreateMenu();
	temp1 = CreateMenu();
	temp2 = CreateMenu();
	AppendMenu(temp, MF_STRING, IDM_ELE, TEXT("&重链接song.txt"));
	AppendMenu(temp, MF_STRING, IDM_TWO, TEXT("&主页"));
	AppendMenu(temp, MF_STRING, IDM_ONE, TEXT("&注销"));
	AppendMenu(temp, MF_STRING, IDM_TEN, TEXT("&退出"));
	//......AppendMenu(....) 添加更多的菜单
	AppendMenu(temp1, MF_POPUP, IDM_FIV, TEXT("&播放"));
	AppendMenu(temp1, MF_POPUP, IDM_SIX, TEXT("&搜索"));
	AppendMenu(temp1, MF_POPUP, IDM_SEV, TEXT("&排序"));
	AppendMenu(temp1, MF_POPUP, IDM_EIG, TEXT("&统计"));
	AppendMenu(temp1, MF_POPUP, IDM_NIN, TEXT("&格式转换"));
	AppendMenu(temp2, MF_STRING, IDM_THR, TEXT("&查看帮助"));
	AppendMenu(temp2, MF_STRING, IDM_FOU, TEXT("&关于 歌曲管理系统"));
	AppendMenu(hMenu, MF_POPUP, (UINT)temp, TEXT("&文件"));// 将菜单 temp 装进菜单 hMenu 中
	AppendMenu(hMenu, MF_POPUP, (UINT)temp1, TEXT("&功能"));// 将菜单 temp1 装进菜单 hMenu 中
	AppendMenu(hMenu, MF_POPUP, (UINT)temp2, TEXT("&帮助"));
	SetMenu(wnd, hMenu); // 将菜单设置进窗口
	OldProc = (WNDPROC)SetWindowLong(wnd, GWL_WNDPROC, (LONG)WndProc); // 设置新的菜单处理函数
	i++;
}
void choice(){
	int flag; extern void loginUI(); 
	extern int pflag, pmode;
	extern long here, herec;
	IMAGE background;
	loadimage(&background, "IMAGE", "background.bmp");
	enable();
	//菜单选择进入函数
	if (menumess == 1){
		flag = MessageBox(wnd, "确认注销？", "注销", MB_YESNO | MB_ICONQUESTION | MB_SYSTEMMODAL);
		menumess = 0;
		if (flag == 6){
			mciSendString("stop mymusic", NULL, 0, NULL);//停止音乐
			mciSendString("close mymusic", NULL, 0, NULL);
			i = 0;
			DeleteFile(loginBGM);
			DeleteFile(mouses);
			DeleteFile(click);
			initgraph(320, 360);
			mciSendString("close loginmusic", NULL, 0, NULL);
			pflag = 0;
			pmode = 0;
			here = herec = 0;
			loginUI();
		}
	}
	if (menumess == 2){
		menumess = 0;
		mciSendString("stop mymusic", NULL, 0, NULL);//停止音乐
		mciSendString("close mymusic", NULL, 0, NULL);
		for (int i = -640; i <= 0; i += 5){
			putimage(i, 0, &background);
			Sleep(int(0.156*(i / 10) + 10));
		}
		mainUI();
	}
	if (menumess == 5){
		menumess = 0;
		mciSendString("stop mymusic", NULL, 0, NULL);//停止音乐
		mciSendString("close mymusic", NULL, 0, NULL);
		pflag = 0;
		pmode = 0;
		here = herec = 0;
		player();
	}
	if (menumess == 6){
		menumess = 0;
		mciSendString("stop mymusic", NULL, 0, NULL);//停止音乐
		mciSendString("close mymusic", NULL, 0, NULL);
		search();
	}
	if (menumess == 7){
		menumess = 0;
		mciSendString("stop mymusic", NULL, 0, NULL);//停止音乐
		mciSendString("close mymusic", NULL, 0, NULL);
		sequences();
	}
	if (menumess == 8){
		menumess = 0;
		mciSendString("stop mymusic", NULL, 0, NULL);//停止音乐
		mciSendString("close mymusic", NULL, 0, NULL);
		count();
	}
	if (menumess == 9){
		menumess = 0;
		mciSendString("stop mymusic", NULL, 0, NULL);//停止音乐
		mciSendString("close mymusic", NULL, 0, NULL);
		convert();
	}
	if (menumess == 11){
		menumess = 0;
		linkfile();
	}
}
LRESULT CALLBACK WndProc(HWND wnd, UINT message, WPARAM wParam, LPARAM lParam){
	extern void login(), loginUI(), player(); extern int menumess;
	switch (message)
	{
	case WM_COMMAND: // 启动某个菜单项时收到该消息
		switch (LOWORD(wParam)) // LOWORD(wParam) 储存了菜单的 ID，根据 ID 判断当前点击的是哪个菜单
		{
		case IDM_ONE:
			menumess = 1;
			break;
		case IDM_TWO:
			me = menumess = 2;
			break;
		case IDM_THR:
			MessageBox(wnd, "欢迎来到歌曲管理系统！\n本系统旨在为您打造一个界面清新、操作方便的日常管理工具，分为以下五大功能：\n排序：将song.txt文件中信息按不同方式排序，使歌曲信息一目了然，便于管理；\n格式转换：无损压缩song.txt中歌曲信息至Newsong.txt，节省存储空间。新文件置于song.txt相同目录下；\n播放：播放指定目录下的mp3或wma音频文件，若需更改目录请单击左下角“更改路径”按钮；\n统计：统计song.txt中歌曲数目和演唱者数目，重复歌曲不计；\n搜索：搜索song.txt中相关信息。\n本系统中如需输入路径，一律使用单斜杠(\\)。若在使用过程中遇到任何问题，欢迎咨询QQ：1023523897，本团队将竭力为您解答！\n\t\t\t\t————DUANG 团队", "帮助", MB_OK | MB_ICONQUESTION | MB_SYSTEMMODAL);
			break;
		case IDM_FOU:
			MessageBox(wnd, "歌曲管理系统 Ver1.3\nBy 杨尹豪&杜明坤\nCopyright (C) 2015 Duang's Corporation.\nAll Rights Reserved.", "关于 歌曲管理系统", MB_OK | MB_SYSTEMMODAL);
			break;
		case IDM_FIV:
			me = menumess = 5;
			break;
		case IDM_SIX:
			me = menumess = 6;
			break;
		case IDM_SEV:
			me = menumess = 7;
			break;
		case IDM_EIG:
			me = menumess = 8;
			break;
		case IDM_NIN:
			me = menumess = 9;
			break;
		case IDM_TEN:
			DeleteFile(loginBGM);
			DeleteFile(mouses);
			DeleteFile(click);
			exit(0);
			break;
		case IDM_ELE:
			menumess = 11;
			break;
		}
		break;
	}
	return CallWindowProc(OldProc, wnd, message, wParam, lParam);
}