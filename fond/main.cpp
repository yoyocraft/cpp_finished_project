#include <stdio.h>
#include <graphics.h>
#include <mmsystem.h>//“Ù¿÷ø‚
#pragma comment(lib,"winmm.lib");
#define WIN_WIDTH 800//¥∞ø⁄øÌ
#define WIN_HEIGHT 800//¥∞ø⁄∏ﬂ
#define JPG_WIDTH 250//Õº∆¨øÌ
#define JPG_HEIGHT 250//Õº∆¨∏ﬂ
#define NUM 46//µ„Œª ˝
#define JPG_NUM 10//Õº∆¨ ˝
//µ„¿‡
struct  point
{
	int x;
	int y;
};
//ƒ⁄»›
const char buff[NUM][50] = {
	"Àß∏Á¿¥¿≤1",
	"Àß∏Á¿¥¿≤2",
	"Àß∏Á¿¥¿≤3",
	"Àß∏Á¿¥¿≤4",
	"Àß∏Á",
	"Àß∏Á¿¥¿≤",
	"Àß∏Á¿¥¿≤",
	"Àß∏Á¿¥¿≤",
	"Àß∏Á¿¥¿≤",
	"Àß∏Á¿¥¿≤",
	"Àß∏Á¿¥¿≤",
	"Àß∏Á¿¥¿≤",
	"Àß∏Á¿¥¿≤",
	"Àß∏Á¿¥¿≤",
	"Àß∏Á¿¥¿≤",
	"Àß∏Á¿¥¿≤",
	"Àß∏Á¿¥¿≤",
	"Àß∏Á¿¥¿≤",
	"Àß∏Á¿¥¿≤",
	"Àß∏Á¿¥¿≤",
	"Àß∏Á¿¥¿≤",
	"Àß∏Á¿¥¿≤",
	"Àß∏Á¿¥¿≤",
	"Àß∏Á¿¥¿≤",
	"Àß∏Á¿¥¿≤",
	"Àß∏Á¿¥¿≤",
	"Àß∏Á¿¥¿≤",
	"Àß∏Á¿¥¿≤",
	"Àß∏Á¿¥¿≤",
	"Àß∏Á¿¥¿≤",
	"Àß∏Á¿¥¿≤",
	"Àß∏Á¿¥¿≤",
	"Àß∏Á¿¥¿≤",
	"Àß∏Á¿¥¿≤",
	"Àß∏Á¿¥¿≤",
	"Àß∏Á¿¥¿≤",
	"Àß∏Á¿¥¿≤",
	"Àß∏Á¿¥¿≤",
	"Àß∏Á¿¥¿≤",
	"Àß∏Á¿¥¿≤",
	"Àß∏Á¿¥¿≤",
	"Àß∏Á¿¥¿≤",
	"Àß∏Á¿¥¿≤",
	"Àß∏Á¿¥¿≤",
	"Àß∏Á¿¥¿≤",
	"Àß∏Á¿¥¿≤",
};
//µ„Œª
point arr[] = {
	{395, 258},
	{406, 222},
	{416, 193},
	{441, 162},
	{468, 133},
	{500, 117},
	{537, 105},
	{577, 107},
	{617, 120},
	{649, 146},
	{666, 173},
	{680, 211},
	{683, 247},
	{680, 293},
	{675, 338},
	{660, 385},
	{640, 440},
	{616, 484},
	{588, 529},
	{557, 573},
	{530, 610},
	{493, 645},
	{460, 675},
	{422, 696},
	{381, 676},
	{350, 654},
	{320, 626},
	{292, 606},
	{257, 570},
	{230, 540},
	{200, 500},
	{180, 470},
	{160, 430},
	{140, 390},
	{126, 342},
	{117, 293},
	{120, 250},
	{133, 203},
	{160, 170},
	{200, 140},
	{240, 130},
	{280, 135},
	{312, 146},
	{340, 170},
	{360, 195},
	{375, 230}
};


void DRAW_WIN() {
	initgraph(WIN_WIDTH, WIN_HEIGHT);//¥¥Ω®¥∞ø⁄
	setbkcolor(RGB(108, 119, 164));//…Ë÷√¥∞ø⁄±≥æ∞…´
	cleardevice();
}
void Play_Music() {
	//“Ù¿÷≤•∑≈
	mciSendString("open 1.mp3", NULL, NULL, NULL);
	mciSendString("play 1.mp3", NULL, NULL, NULL);
}
void Show_String() {
	for (int i = 0; i < NUM; i++) {
		settextcolor(RGB(rand() % 256, rand() % 256, rand() % 256));//…Ë÷√◊÷∑˚¥Æ—’…´
		outtextxy(arr[i].x, arr[i].y, buff[i]);//œ‘ æ◊÷∑˚¥Æ
		Sleep(200);
	}
}
void Show_JPG() {
	//Õº∆¨
	IMAGE bmp[JPG_NUM];//∂®“ÂÕº∆¨±‰¡ø
	char temp[56];
	for (int i = 0; i < JPG_NUM; i++) {
		memset(temp, 0, 56);//«Âø’
		sprintf_s(temp, "memory\\%d.jpg", i + 1);
		loadimage(&bmp[i], temp, JPG_WIDTH, JPG_HEIGHT, true);	//º”‘ÿÕº∆¨
		Sleep(200);
	}
	int n = 0;
	while (true) {
		for (int i = 0; i < NUM; i++) {
			settextcolor(RGB(rand() % 256, rand() % 256, rand() % 256));//…Ë÷√◊÷∑˚¥Æ—’…´
			outtextxy(arr[i].x, arr[i].y, buff[(i + n) % NUM]);//œ‘ æ◊÷∑˚¥Æ
		}
		putimage(300, 300, &bmp[n]);//Ã˘Õº
		n++;
		if (n >= JPG_NUM) { n = 0; }
		Sleep(300);
	}
}


int main() {
	DRAW_WIN();
	Play_Music();
	Show_String();
	Show_JPG();
	system("pause");
	return 0;
}