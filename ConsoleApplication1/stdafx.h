// stdafx.h : 标准系统包含文件的包含文件，
// 或是经常使用但不常更改的
// 特定于项目的包含文件
//

#pragma once
#pragma comment(linker, "/entry:mainCRTStartup /subsystem:windows")

#include "targetver.h"
#include <stdio.h>
#include <tchar.h>

// TODO:  在此处引用程序需要的其他头文件
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
