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

#define SYSCOLOR "Red"  /*默认绘图颜色*/

#define CURSOR "|"          /*光标符号*/
#define CURSOR_BLINK  1     /*光标闪烁定时器事件标志号*/
const int timerseconds = 500; /*光标闪烁周期ms*/
bool isCursorBlink = FALSE;  /*光标是否闪烁*/

void KeyboardEventProcess(int key, int event);               /*键盘消息回调函数*/
void CharEventProcess(char c);                               /*字符消息回调函数*/
void MouseEventProcess(int x, int y, int button, int event);/*鼠标消息回调函数*/
void TimerEventProcess(int timerID);                         /*定时器消息回调函数*/
/////////////////////////结构体定义/////////////////////////////////
typedef struct {/*直线类型*/
	double x1, y1;/*第一个点坐标*/
	double x2, y2;/*第二个点坐标*/
	int PenSize; /*粗细*/
	string color; /*颜色*/
	bool isSelected; /*选中*/
} *LineT;

typedef struct {/*矩形类型*/
	double x1, y1;/*左下角坐标*/
	double x2, y2;/*右上角坐标*/
	int PenSize; /*粗细*/
	string color; /*颜色*/
	bool isSelected; /*选中*/
} *RectT;

typedef struct {/*椭圆类型*/
	double cx, cy;/*圆心*/
	double rx, ry;/*长短轴*/
	int PenSize; /*粗细*/
	string color; /*颜色*/
	bool isSelected; /*选中*/
} *EllipseT;

typedef struct {/*文本类型*/
	string text;/*文本指针*/
	double x, y;/*文本显示起始位置坐标*/
	int PointSize; /*文字大小*/
	string color; /*颜色*/
	bool isSelected; /*选中*/
	int curPos; /*光标位置*/
	bool isDisplayed; /*光标是否处于显示状态*/
} *TextT;


/////////////////////////////////////////全局变量///////////////////////////////////////
linkedlistADT list[NLIST] = { NULL, NULL, NULL, NULL };/*四类图形元素链表指针*/
double minDistance[NLIST] = { 100000000.0, 1000000000.0, 1000000000.0, 1000000000.0 };
int curList = LINE; /*当前链表序号*/
LineT curLine = NULL;/*直线链表的当前对象指针*/
RectT curRect = NULL;/*矩形链表的当前对象指针*/
EllipseT curEllipse = NULL;/*椭圆链表的当前对象指针*/
TextT curText = NULL;/*文本链表的当前对象指针*/

bool isSelected = FALSE; /*图形元素选中状态*/

#define TEXTLEN  100
static TextT tptr; /*当前编辑文本对象指针*/
static bool inText = FALSE; /*是否处于当前文本编辑状态*/
static char textbuf[TEXTLEN + 1];/*当前文本缓冲区*/

////////////////////////函数声明////////////////////////////////////

/*椭圆处理函数*/
void DrawCenteredEllipse(void *ellipse);/*画椭圆*/
bool EllipseEqual(void *ellipse1, void *ellipse2);/*比较两个椭圆相等*/
EllipseT SelectNearestNodeE(linkedlistADT list, double mx, double my);/*选择靠(mx,my)最近的结点*/

/*直线处理函数*/
void DrawLineD(void *line);
bool LineEqual(void *line1, void *line2);
LineT SelectNearestNodeL(linkedlistADT list, double mx, double my);

/*矩形处理函数*/
void DrawRect(void *rect);
bool RectEqual(void *rect1, void *rect2);
RectT SelectNearestNodeR(linkedlistADT list, double mx, double my);

/*文本处理函数*/
void DrawTextT(void *text); /*显示文本*/
bool TextEqual(void *text1, void *text2);/*比较两个文本是否相同*/
TextT SelectNearestNodeT(linkedlistADT list, double mx, double my);
void InsertCharToString(string str, int pos, char c);/*将字符c插入到字符串str的pos位置*/
void DeleteCharFromString(string str, int pos);/*删除字符串str的pos位置字符*/
void DrawCursor(string str, int curPos, double startx, double starty);/*显示文本光标*/

void PickNearestNode(linkedlistADT list[], double mx, double my);/*选择靠(mx,my)最近结点*/
void TraverseAllList();/*刷新所有图形对象*/
