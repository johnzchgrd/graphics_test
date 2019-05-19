#pragma once
#include "graphics.h"
#include "extgraph.h"
#include "genlib.h"
#include "simpio.h"
#include "random.h"
#include "strlib.h"
#include "conio.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stddef.h>

#include <windows.h>
#include <olectl.h>
#include <mmsystem.h>
#include <wingdi.h>
#include <ole2.h>
#include <ocidl.h>
#include <winuser.h>

#include "linkedlist.h"

#define NLIST     4
#define LINE      0
#define RECT      1
#define ELLIPSE   2
#define STRING    3

#define SYSCOLOR "Red"  /*Ĭ�ϻ�ͼ��ɫ*/

#define CURSOR "|"          /*������*/
#define CURSOR_BLINK  1     /*�����˸��ʱ���¼���־��*/
const int timerseconds = 500; /*�����˸����ms*/
bool isCursorBlink = FALSE;  /*����Ƿ���˸*/

void KeyboardEventProcess(int key, int event);               /*������Ϣ�ص�����*/
void CharEventProcess(char c);                               /*�ַ���Ϣ�ص�����*/
void MouseEventProcess(int x, int y, int button, int event);/*�����Ϣ�ص�����*/
void TimerEventProcess(int timerID);                         /*��ʱ����Ϣ�ص�����*/
/////////////////////////�ṹ�嶨��/////////////////////////////////
typedef struct {/*ֱ������*/
	double x1, y1;/*��һ��������*/
	double x2, y2;/*�ڶ���������*/
	int PenSize; /*��ϸ*/
	string color; /*��ɫ*/
	bool isSelected; /*ѡ��*/
} *LineT;

typedef struct {/*��������*/
	double x1, y1;/*���½�����*/
	double x2, y2;/*���Ͻ�����*/
	int PenSize; /*��ϸ*/
	string color; /*��ɫ*/
	bool isSelected; /*ѡ��*/
} *RectT;

typedef struct {/*��Բ����*/
	double cx, cy;/*Բ��*/
	double rx, ry;/*������*/
	int PenSize; /*��ϸ*/
	string color; /*��ɫ*/
	bool isSelected; /*ѡ��*/
} *EllipseT;

typedef struct {/*�ı�����*/
	string text;/*�ı�ָ��*/
	double x, y;/*�ı���ʾ��ʼλ������*/
	int PointSize; /*���ִ�С*/
	string color; /*��ɫ*/
	bool isSelected; /*ѡ��*/
	int curPos; /*���λ��*/
	bool isDisplayed; /*����Ƿ�����ʾ״̬*/
} *TextT;


/////////////////////////////////////////ȫ�ֱ���///////////////////////////////////////
linkedlistADT list[NLIST] = { NULL, NULL, NULL, NULL };/*����ͼ��Ԫ������ָ��*/
double minDistance[NLIST] = { 100000000.0, 1000000000.0, 1000000000.0, 1000000000.0 };
int curList = LINE; /*��ǰ�������*/
LineT curLine = NULL;/*ֱ������ĵ�ǰ����ָ��*/
RectT curRect = NULL;/*��������ĵ�ǰ����ָ��*/
EllipseT curEllipse = NULL;/*��Բ����ĵ�ǰ����ָ��*/
TextT curText = NULL;/*�ı�����ĵ�ǰ����ָ��*/

bool isSelected = FALSE; /*ͼ��Ԫ��ѡ��״̬*/

#define TEXTLEN  100
static TextT tptr; /*��ǰ�༭�ı�����ָ��*/
static bool inText = FALSE; /*�Ƿ��ڵ�ǰ�ı��༭״̬*/
static char textbuf[TEXTLEN + 1];/*��ǰ�ı�������*/

////////////////////////��������////////////////////////////////////

/*��Բ������*/
void DrawCenteredEllipse(void *ellipse);/*����Բ*/
bool EllipseEqual(void *ellipse1, void *ellipse2);/*�Ƚ�������Բ���*/
EllipseT SelectNearestNodeE(linkedlistADT list, double mx, double my);/*ѡ��(mx,my)����Ľ��*/

/*ֱ�ߴ�����*/
void DrawLineD(void *line);
bool LineEqual(void *line1, void *line2);
LineT SelectNearestNodeL(linkedlistADT list, double mx, double my);

/*���δ�����*/
void DrawRect(void *rect);
bool RectEqual(void *rect1, void *rect2);
RectT SelectNearestNodeR(linkedlistADT list, double mx, double my);

/*�ı�������*/
void DrawTextT(void *text); /*��ʾ�ı�*/
bool TextEqual(void *text1, void *text2);/*�Ƚ������ı��Ƿ���ͬ*/
TextT SelectNearestNodeT(linkedlistADT list, double mx, double my);
void InsertCharToString(string str, int pos, char c);/*���ַ�c���뵽�ַ���str��posλ��*/
void DeleteCharFromString(string str, int pos);/*ɾ���ַ���str��posλ���ַ�*/
void DrawCursor(string str, int curPos, double startx, double starty);/*��ʾ�ı����*/

void PickNearestNode(linkedlistADT list[], double mx, double my);/*ѡ��(mx,my)������*/
void TraverseAllList();/*ˢ������ͼ�ζ���*/
