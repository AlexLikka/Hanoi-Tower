/* 土法 2252050 徐子栋 */
#pragma once
#include<iostream>
#include <iomanip>
#include <windows.h>
#include <conio.h>
#include"cmd_console_tools.h"
using namespace std;


int menu();
void basic(char mode);
/* ------------------------------------------------------------------------------------------------------

     本文件功能：
	1、为了保证 hanoi_main.cpp/hanoi_menu.cpp/hanoi_multiple_solutions.cpp 能相互访问函数的函数声明
	2、一个以上的cpp中用到的宏定义（#define）或全局只读（const）变量，个数不限
	3、可以参考 cmd_console_tools.h 的写法（认真阅读并体会）
   ------------------------------------------------------------------------------------------------------ */

