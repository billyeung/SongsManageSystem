// stdafx.h : ��׼ϵͳ�����ļ��İ����ļ���
// ���Ǿ���ʹ�õ��������ĵ�
// �ض�����Ŀ�İ����ļ�
//

#pragma once
#pragma comment(linker, "/entry:mainCRTStartup /subsystem:windows")

#include "targetver.h"
#include <stdio.h>
#include <tchar.h>

// TODO:  �ڴ˴����ó�����Ҫ������ͷ�ļ�
#include<string.h>
#include<conio.h>
#include<windows.h>
#include<time.h>
#include <graphics.h>
#include<math.h>
#include<stdlib.h>
#include <locale.h>
#include "resource.h"
#define PI 3.1415926535
extern HWND wnd;
extern HMENU hMenu, temp, temp1;
extern bool ExtractResource(LPCTSTR strDstFile, LPCTSTR strResType, LPCTSTR strResName);
extern TCHAR mcilogin[100], loginBGM[_MAX_PATH], mcimouse[100], mouses[_MAX_PATH], mciclick[100], click[_MAX_PATH];
