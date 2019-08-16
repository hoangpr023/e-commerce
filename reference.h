#pragma once
#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <iostream>

using namespace std;

#define BLACK_COLOR			0
#define DARK_BLUE_COLOR		1
#define DARK_GREEN_COLOR	2
#define DARK_CYAN_COLOR		3
#define DARK_RED_COLOR		4
#define DARK_PINK_COLOR		5
#define DARK_YELLOW_COLOR	6
#define DARK_WHITE_COLOR	7
#define GREY_COLOR			8
#define BLUE_COLOR			9
#define GREEN_COLOR			10
#define CYAN_COLOR			11
#define RED_COLOR			12
#define PINK_COLOR			13
#define YELLOW_COLOR		14
#define WHITE_COLOR			15

#define KEY_UP		1072
#define KEY_DOWN	1080
#define KEY_LEFT	1075
#define KEY_RIGHT	1077
#define KEY_NONE	-1

class Reference {
public:
    static int inputKey();
    static void clrscr();
    static void gotoXY (int x, int y);
    static int whereX();
    static int whereY();
    static void noCursorType();
    static void setTextColor (int color);
    static void draw (int left, int right, int top, int down);
    static string lowerCase (string x);
};