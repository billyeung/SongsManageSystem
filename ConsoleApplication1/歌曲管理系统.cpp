// ConsoleApplication1.cpp : �������̨Ӧ�ó������ڵ㡣
//
#include "stdafx.h"
#include"login.h"
#pragma warning(disable: 4996)
#pragma comment(lib,"Winmm.lib")
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
bool ExtractResource(LPCTSTR strDstFile, LPCTSTR strResType, LPCTSTR strResName)
{
	// �����ļ�
	HANDLE hFile = ::CreateFile(strDstFile, GENERIC_WRITE, NULL, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_TEMPORARY, NULL);
	if (hFile == INVALID_HANDLE_VALUE)
		return false;
	// ������Դ�ļ��С�������Դ���ڴ桢�õ���Դ��С
	HRSRC	hRes = ::FindResource(NULL, strResName, strResType);
	HGLOBAL	hMem = ::LoadResource(NULL, hRes);
	DWORD	dwSize = ::SizeofResource(NULL, hRes);
	// д���ļ�
	DWORD dwWrite = 0;  	// ����д���ֽ�
	::WriteFile(hFile, hMem, dwSize, &dwWrite, NULL);
	::CloseHandle(hFile);
	return true;
}
void main(){
	initgraph(320, 360);
	loginUI();
}