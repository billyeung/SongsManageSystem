//注册登录模块
#include"stdafx.h"
#include"mainUI.h"
#pragma warning(disable:4996)
#pragma comment(lib, "MSIMG32.LIB")
bool flag;
int x1c, x2c, y1c, y2c; double t = 0, tc = 0, ac = 2 * PI;
TCHAR mcilogin[100], loginBGM[_MAX_PATH], mcimouse[100], mouses[_MAX_PATH], mciclick[100], click[_MAX_PATH];;
void clear(){
	setcolor(RGB(0, 30, 40));
	setlinestyle(PS_SOLID | PS_ENDCAP_ROUND, 10);
	x1c = (int)(-70 * sin(ac));
	y1c = (int)(-70 * cos(ac));
	x2c = (int)(-70 * sin(ac));
	y2c = (int)(-70 * cos(ac));
	line(x1c, y1c, x2c, y2c);
	ac -= PI / 90;
	if (tc <= 2 * PI){
		Sleep((int)(4 * cos(tc) + 5));
		tc += PI / 90;
	}
}
void circle(){
	int x1, x2, y1, y2, i = 100;
	setorigin(160, 180);
	setlinestyle(PS_SOLID | PS_ENDCAP_ROUND, 10);
	for (double a = 2 * PI; a >= 0; a -= PI / 90){
		setlinecolor(RGB(i, i, i));
		x1 = (int)(-70 * sin(a));
		y1 = (int)(-70 * cos(a));
		x2 = (int)(-70 * sin(a));
		y2 = (int)(-70 * cos(a));
		line(x1, y1, x2, y2);
		if (t <= 2 * PI){
			Sleep((int)(4 * cos(t) + 5));
			t += PI / 90;
		}
		i += 2;
		if (i > 255) i = 255;
		if (a < 2 * PI / 3){
			clear();
			setlinecolor(RGB(i, i, i));
		}
	}
	setcolor(RGB(0, 30, 40));
	while (ac >= 0){
		x1c = (int)(-70 * sin(ac));
		y1c = (int)(-70 * cos(ac));
		x2c = (int)(-70 * sin(ac));
		y2c = (int)(-70 * cos(ac));
		line(x1c, y1c, x2c, y2c);
		ac -= PI / 90;
		if (tc <= 2 * PI){
			Sleep((int)(4 * cos(tc) + 5));
			tc += PI / 90;
		}
	}
	Sleep(200);
	tc = 0, ac = 2 * PI, t = 0;
}
void signup() {
	extern void loginUI();
	char getnewname[10], getnewpass[10];
	FILE *fpn;
	fpn=fopen("newusers.data", "a");
	flag=InputBox(getnewname, 10, "请输入新用户名：", "用户注册", NULL, 200, 0, false);
	if (flag == false) {
		fclose(fpn); loginUI();
	}
	if (getnewname[0] == '\0' || getnewname[0] == ' '){
		MessageBox(wnd, "用户名不能为空！", "用户注册", MB_OK | MB_ICONWARNING | MB_SYSTEMMODAL);
		loginUI();
	}
	flag=InputBox(getnewpass, 10, "请输入新用户密码：", "用户注册", NULL, 200, 0, false);
	if (flag == false) {
		fclose(fpn); loginUI();
	}
	if (getnewpass[0] == '\0'|| getnewname[0] == ' '){
		MessageBox(wnd, "密码不能为空！", "用户注册", MB_OK | MB_ICONWARNING | MB_SYSTEMMODAL);
		loginUI();
	}
	fprintf(fpn, "%s %s ", getnewname, getnewpass);
	fclose(fpn);
	MessageBox(wnd, "注册成功！", "用户注册", MB_OK | MB_ICONWARNING | MB_SYSTEMMODAL);
	loginUI();
}
void login(){
	extern void loginUI(); IMAGE loginblank; char ch;
	loadimage(&loginblank, "image", "login.jpg", 320, 569);
	FILE *fpc, *fpg;
	fpc = fopen("newusers.data", "r");
	if (fpc == NULL) fpc = fopen("newusers.data", "w");
	ch = fgetc(fpc);
	if (ch == EOF){
		MessageBox(wnd, "请注册新用户！", "警告", MB_OK | MB_ICONWARNING | MB_SYSTEMMODAL);
		fclose(fpc);
		signup();
	}
	else{
		// 定义字符串缓冲区，并接收用户输入
		fclose(fpc);
		fpg = fopen("newusers.data", "r");
		char logname[10], password[10], getlogname[10], getpassword[10];
		flag = InputBox(getlogname, 10, "请输入账号：", "用户登录", NULL, 200, 0, false);
		if (flag == false) loginUI();
		if (getlogname[0] == '\0'){
			MessageBox(wnd, "用户名不能为空！", "用户登录", MB_OK | MB_ICONWARNING | MB_SYSTEMMODAL);
			loginUI();
		}
		flag = InputBox(getpassword, 10, "请输入密码：", "用户登录", NULL, 200, 0, false);
		if (flag == false) loginUI();
		if (getpassword[0] == '\0'){
			MessageBox(wnd, "密码不能为空！", "用户登录", MB_OK | MB_ICONWARNING | MB_SYSTEMMODAL);
			loginUI();
		}
		fscanf(fpg, "%s %s ", logname, password);
		while ((strcmp(logname, getlogname) != 0) || (strcmp(password, getpassword) != 0)){
			if (feof(fpg)){
				MessageBox(wnd, "账号或密码错误，请重新输入。", "警告", MB_OK | MB_ICONWARNING | MB_SYSTEMMODAL);
				fclose(fpg);
				loginUI();
			}
			else fscanf(fpg, "%s %s ", logname, password);
		}
	}
	//过场动画
	putimage(0, -180, &loginblank);
	Sleep(100);
	for (double i = 0; i <= 180; i++){
		putimage(0, -180+i, &loginblank);
		Sleep(int(sqrt(i/10)));
	}
	circle(); circle();
	mciSendString("stop loginmusic", NULL, 0, NULL);//停止音乐
	DeleteFile(loginBGM);
	// 产生临时文件的文件名
	::GetTempPath(_MAX_PATH, mouses);
	_tcscat_s(mouses, _T("mouse.wav"));
	// 将 MP3 资源提取为临时文件
	ExtractResource(mouses, _T("WAVE"), _T("mouse.wav"));
	_stprintf_s(mcimouse, _T("open \"%s\" alias mouse"), mouses);
	// 产生临时文件的文件名
	::GetTempPath(_MAX_PATH, click);
	_tcscat_s(click, _T("click.wav"));
	// 将 MP3 资源提取为临时文件
	ExtractResource(click, _T("WAVE"), _T("click.wav"));
	_stprintf_s(mciclick, _T("open \"%s\" alias click"), click);
	initgraph(640, 480);
	mainUI();
}
IMAGE loginimg,shutlight;
void loginUI(){
	// 产生临时文件的文件名
	::GetTempPath(_MAX_PATH, loginBGM);
	_tcscat_s(loginBGM, _T("loginBGM.mp3"));
	// 将 MP3 资源提取为临时文件
	ExtractResource(loginBGM, _T("MP3"), _T("loginBGM.mp3"));
	_stprintf_s(mcilogin, _T("open \"%s\" alias loginmusic"), loginBGM);
	mciSendString(mcilogin, NULL, 0, NULL);
	mciSendString("play loginmusic", NULL, 0, NULL);
	setorigin(0, 0);
	loadimage(&loginimg, "IMAGE", "login.bmp", 320, 569);
	putimage(0, -180, &loginimg);
	setlinecolor(RGB(255, 255, 0)); setlinestyle(PS_SOLID, 3);
	// 获取鼠标消息
	while (true){
		MOUSEMSG msg;
		while (MouseHit()){
			msg = GetMouseMsg();
			if (msg.x >= 267 && msg.x <= 310 && msg.y >= 10 && msg.y <= 53){
				loadimage(&shutlight, "IMAGE", "shutlight.bmp");
				putimage(264, 7, &shutlight, SRCPAINT);
				if (msg.uMsg == WM_LBUTTONUP) {
					DeleteFile(loginBGM);
					DeleteFile(mouses);
					DeleteFile(click);
					exit(0);
				}
			}
			else if (msg.x >= 108 && msg.x <= 212 && msg.y >= 213 && msg.y <= 247){
				roundrect(108, 213, 212, 247, 15, 15);
				if (msg.uMsg == WM_LBUTTONUP) {
					signup(); break;
				}
			}
			else if (msg.x >= 108 && msg.x <= 212 && msg.y >= 258 && msg.y <= 292){
				roundrect(108, 258, 212, 292, 15, 15);
				if (msg.uMsg == WM_LBUTTONUP) {
					login(); break;
				}
			}
			else putimage(0, -180, &loginimg);
		}
		Sleep(10);
	}
}