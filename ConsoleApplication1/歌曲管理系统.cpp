// ConsoleApplication1.cpp : 定义控制台应用程序的入口点。
//
#include "stdafx.h"
#include"login.h"
#pragma warning(disable: 4996)
#pragma comment(lib,"Winmm.lib")
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
bool ExtractResource(LPCTSTR strDstFile, LPCTSTR strResType, LPCTSTR strResName)
{
	// 创建文件
	HANDLE hFile = ::CreateFile(strDstFile, GENERIC_WRITE, NULL, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_TEMPORARY, NULL);
	if (hFile == INVALID_HANDLE_VALUE)
		return false;
	// 查找资源文件中、加载资源到内存、得到资源大小
	HRSRC	hRes = ::FindResource(NULL, strResName, strResType);
	HGLOBAL	hMem = ::LoadResource(NULL, hRes);
	DWORD	dwSize = ::SizeofResource(NULL, hRes);
	// 写入文件
	DWORD dwWrite = 0;  	// 返回写入字节
	::WriteFile(hFile, hMem, dwSize, &dwWrite, NULL);
	::CloseHandle(hFile);
	return true;
}
void main(){
	initgraph(320, 360);
	loginUI();
}