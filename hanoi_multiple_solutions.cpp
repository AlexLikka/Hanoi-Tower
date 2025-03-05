/* 土法 2252050 徐子栋 */
#include"hanoi.h"

static int ct = 0;
static int a[10];
static int b[10];
static int c[10];
static int topa;
static int topb;
static int topc;
static int dt = 0;

/* ----------------------------------------------------------------------------------

     本文件功能：
	1、存放被 hanoi_main.cpp 中根据菜单返回值调用的各菜单项对应的执行函数

     本文件要求：
	1、不允许定义外部全局变量（const及#define不在限制范围内）
	2、允许定义静态全局变量（具体需要的数量不要超过文档显示，全局变量的使用准则是：少用、慎用、能不用尽量不用）
	3、静态局部变量的数量不限制，但使用准则也是：少用、慎用、能不用尽量不用
	4、按需加入系统头文件、自定义头文件、命名空间等

   ----------------------------------------------------------------------------------- */


/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/


//参数初始化
void initial()
{
	int i;
	ct = 0;
	for (i = 0; i < 10; i++) {
		a[i] = 0;
	}
	for (i = 0; i < 10; i++) {
		b[i] = 0;
	}
	for (i = 0; i < 10; i++) {
		c[i] = 0;
	}
	topa = 0;
	topb = 0;
	topc = 0;
	dt = 0;
}

//输入阶段
void input(int* n, char* src, char* tmp, char* dst, int* ifshow, char mode)
{
    while (1) {
        cout << "请输入汉诺塔的层数(1-10)" << endl;
        cin >> *n;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(2000, '\n');
        }
        else if (*n >= 1 && *n <= 10)
            break;
    }
    while (1) {
        cout << "请输入起始柱(A-C)" << endl;
        cin >> *src;
        if (*src >= 'a' && *src <= 'c')
            *src = char(*src - 'a' + 'A');
        if (cin.fail()) {
            cin.clear();
            cin.ignore(2000, '\n');
        }
        else if (*src >= 'A' && *src <= 'C')
            break;
    }
    while (1) {
        cout << "请输入目标柱(A-C)" << endl;
        cin >> *dst;
        if (*dst >= 'a' && *dst <= 'c')
            *dst = char(*dst - 'a' + 'A');
        if (cin.fail()) {
            cin.clear();
            cin.ignore(2000, '\n');
        }
        else if (*dst >= 'A' && *dst <= 'C' && *src != *dst)
            break;
        else if (*src == *dst)
            cout << "目标柱(" << *dst << ")不能与起始柱(" << *src << ")相同" << endl;
    }
	if (mode == '4') {
		while (1) {
			cout << "请输入移动速度(0-5: 0-按回车单步演示 1-延时最长 5-延时最短)" << endl;
			cin >> dt;
			if (cin.fail()) {
				cin.clear();
				cin.ignore(2000, '\n');
			}
			else if (dt < 0 || dt > 5) {
				cin.clear();
				cin.ignore(2000, '\n');
			}
			else {
				cin.clear();
				cin.ignore(2000, '\n');
				break;
			}
		}
		while (1) {
			cout << "请输入是否显示内部数组值(0-不显示 1-显示)" << endl;
			cin >> *ifshow;
			if (cin.fail()) {
				cin.clear();
				cin.ignore(2000, '\n');
			}
			else if (*ifshow != 0 && *ifshow != 1) {
				cin.clear();
				cin.ignore(2000, '\n');
			}
			else {
				cin.clear();
				cin.ignore(2000, '\n');
				break;
			}
		}
	}
	*tmp = 'A' + 'B' + 'C' - *src - *dst;
}

//数组初始化
void initial_stacks(int n, char src, char tmp, char dst)
{
	int i;
	if (src == 'A') {
		topa = n;
		for (i = 0; i < n; i++) {
			a[i] = n - i;
		}
	}
	if (src == 'B') {
		topb = n;
		for (i = 0; i < n; i++) {
			b[i] = n - i;
		}
	}
	if (src == 'C') {
		topc = n;
		for (int i = 0; i < n; i++) {
			c[i] = n - i;
		}
	}
}

//延迟时间
void delay()
{
	if (dt == 0) {
		system("pause");
	}
	else if (dt == 1) {
		Sleep(2000);
	}
	else if (dt == 2) {
		Sleep(1500);
	}
	else if (dt == 3) {
		Sleep(1000);
	}
	else if (dt == 4) {
		Sleep(500);
	}
}

//数组栈操作，盘从i移动到j
void do_stack(char i, char j)
{
	if (i == 'A') {
		if (j == 'B') {
			b[topb++] = a[--topa];
			a[topa] = 0;
		}
		else if (j == 'C') {
			c[topc++] = a[--topa];
			a[topa] = 0;
		}
	}
	else if (i == 'B') {
		if (j == 'A') {
			a[topa++] = b[--topb];
			b[topb] = 0;
		}
		else if (j == 'C') {
			c[topc++] = b[--topb];
			b[topb] = 0;
		}
	}
	else if (i == 'C') {
		if (j == 'A') {
			a[topa++] = c[--topc];
			c[topc] = 0;
		}
		else if (j == 'B') {
			b[topb++] = c[--topc];
			c[topc] = 0;
		}
	}
}

//横向输出1：步，并移动栈
void out_step(int n, char src, char dst, char mode)
{
	cct_setcolor();
	if (mode == '4') {
		cct_gotoxy(0, 26);
	}
    else if (mode == '7' || mode == '8' || mode == '9') {
		cct_gotoxy(0, 33);
	}
	cout << "第" << setw(4) << ++ct << " 步" << "(" << setw(2) << n << "): " << src << "-->" << dst << " ";
	do_stack(src, dst);
}

//横向输出2：数组
void out_stack_h(char mode)
{
	cct_setcolor();
	if (mode == '4') {
		cct_gotoxy(22, 26);
	}
	else if (mode == '7' || mode == '8' || mode == '9') {
		cct_gotoxy(22, 33);
	}

	int count = 0;
	cout << " A:";
	for (int i = 0; i < 10; i++) {
		if (a[i] == 0)
			break;
		else {
			cout << setw(2) << a[i];
			count++;
		}
	}
	cout << setw(21 - 2 * count) << setfill(' ') << " ";

	cout << "B:";
	count = 0;
	for (int i = 0; i < 10; i++) {
		if (b[i] == 0)
			break;
		else {
			cout << setw(2) << b[i];
			count++;
		}
	}
	cout << setw(21 - 2 * count) << setfill(' ') << " ";

	cout << "C:";
	count = 0;
	for (int i = 0; i < 10; i++) {
		if (c[i] == 0)
			break;
		else {
			cout << setw(2) << c[i];
			count++;
		}
	}
	cout << setw(21 - 2 * count) << setfill(' ') << " ";

	cout << endl;

	if (mode == '4') {
		delay();
	}
}

//纵向输出数组
void out_stack_v(char mode)
{
	cct_setcolor();
	int x, y;
	if (mode == '7' || mode == '8' || mode == '9') {
		x = 11;
		y = 27;
	}
	else {
		x = 11;
		y = 16;
	}
	//a
	int i;
	cct_gotoxy(x, y);
	for (i = 0; i < 10; i++) {
		if (a[i] != 0) {
			cout << a[i];
		}
		else
			cout << " ";
		y--;
		cct_gotoxy(x, y);
	}
	//b
	y += 10;
	x += 10;
	cct_gotoxy(x, y);
	for (i = 0; i < 10; i++) {
		if (b[i] != 0) {
			cout << b[i];
		}
		else
			cout << " ";
		y--;
		cct_gotoxy(x, y);
	}
	//c
	y += 10;
	x += 10;
	cct_gotoxy(x, y);
	for (i = 0; i < 10; i++) {
		if (c[i] != 0) {
			cout << c[i];
		}
		else
			cout << " ";
		y--;
		cct_gotoxy(x, y);
	}
	delay();
}

//图形化部分
//画基本柱
void draw_column()
{
	int i, j;
	//托，间隔40，宽23，中间为11
	cct_showch(0, 15, ' ', COLOR_HYELLOW, COLOR_HYELLOW, 23);
	cct_showch(40, 15, ' ', COLOR_HYELLOW, COLOR_HYELLOW, 23);
	cct_showch(80, 15, ' ', COLOR_HYELLOW, COLOR_HYELLOW, 23);
	//柱，高10
	for (i = 0; i < 3; i++) {
		for (j = 14; j >= 5; j--) {
			cct_showch(i * 40 + 11, j, ' ', COLOR_HYELLOW, COLOR_HYELLOW, 1);
			Sleep(10);
		}
	}
}

//画初始盘
void draw_plate(int n, char src)
{
	dt = 4;
	int i;
	for (i = n; i >= 1; i--) {
		cct_showch((src - 'A') * 40 + 11 - i, 14 - n + i, ' ', COLOR_HYELLOW - i, COLOR_HYELLOW - i, 2 * i + 1);
		Sleep(10);
	}
}

//盘上升/下降纵向移动
void move_v(int n, char src, char tmp, char dst, int head)
{
	int move_column[3] = { topa ,topb, topc };
	int x, y, ye;
	int i;
	Sleep(10);
	if (head == 1) {
		x = (src - 'A') * 40 + 11;
		y = 14 - move_column[src - 'A'];
		ye = 4;
		for (i = y; i >= ye; i--) {
			cct_showch(x - n, i, ' ', COLOR_HYELLOW - n, COLOR_HYELLOW - n, 2 * n + 1);
			if (i != y) {
				cct_showch(x - n, i + 1, ' ', COLOR_BLACK, COLOR_WHITE, 2 * n + 1);
				cct_showch(x, i + 1, ' ', COLOR_HYELLOW, COLOR_WHITE, 1);
			}
			Sleep(30);
		}
	}
	else if (head == 0) {
		x = (dst - 'A') * 40 + 11;
		ye = 15 - move_column[dst - 'A'];
		y = 4;
		for (i = y; i <= ye; i++) {
			cct_showch(x - n, i, ' ', COLOR_HYELLOW - n, COLOR_HYELLOW - n, 2 * n + 1);
			if (i != y) {
				cct_showch(x - n, i - 1, ' ', COLOR_BLACK, COLOR_WHITE, 2 * n + 1);
				if (i != y + 1) {
					cct_showch(x, i - 1, ' ', COLOR_HYELLOW, COLOR_WHITE, 1);
				}
			}
			Sleep(30);
		}
	}
}

//盘横向移动
void move_h(int n, char src, char tmp, char dst)
{
	int head;
	int	y = 4;
	int x = (src - 'A') * 40 + 11;
	int xe = (dst - 'A') * 40 + 11;
	if (dst - src > 0) {
		head = 1;
	}
	else {
		head = -1;
	}
	Sleep(10);
	while (1) {
		if (head == 1) {
			cct_showch(x - n, y, ' ', COLOR_HYELLOW - n, COLOR_HYELLOW - n, 2 * n + 1);
			if (x != xe) {
				cct_showch(x - n - 1, y, ' ', COLOR_BLACK, COLOR_WHITE, 1);
				cct_showch(x - n, y, ' ', COLOR_HYELLOW - n, COLOR_WHITE, 2 * n + 1);
			}
			if (x == xe) {
				cct_showch(x - n - 1, y, ' ', COLOR_BLACK, COLOR_WHITE, 1);
				break;
			}
			x += head;
			Sleep(10);
		}
		else {
			cct_showch(x - n, y, ' ', COLOR_HYELLOW - n, COLOR_HYELLOW - n, 2 * n + 1);
			if (x != xe) {
				cct_showch(x + n + 1, y, ' ', COLOR_BLACK, COLOR_WHITE, 1);
				cct_showch(x - n, y, ' ', COLOR_HYELLOW - n, COLOR_WHITE, 2 * n + 1);
			}
			if (x == xe) {
				cct_showch(x + n + 1, y, ' ', COLOR_BLACK, COLOR_WHITE, 1);
				break;
			}
			x += head;
			Sleep(10);
		}
	}
}

//运动总控
void do_m(int n, char src, char tmp, char dst, int ifshow, char mode)
{
	if (mode == '1') {
		cout << n << "# " << src << "---->" << dst << endl;
	}
	else if (mode == '2') {
		cout << "第" << setfill(' ') << setw(4) << ++ct << " 步(" << setw(2) << n << "#: " << src << "-->" << dst << ")" << endl;
	}
	else if (mode == '3') {
		out_step(n, src, dst, mode);
		out_stack_h(mode);
	}
	else if (mode == '4') {
		out_step(n, src, dst, mode);
		if (ifshow == 1) {
			out_stack_h(mode);
		}
		out_stack_v(mode);
	}
	else if (mode == '7' || mode == '8' || mode == '9') {
		out_step(n, src, dst, mode);
		if (ifshow == 1) {
			out_stack_h(mode);
		}
		out_stack_v(mode);
		move_v(n, src, tmp, dst, 1);
		move_h(n, src, tmp, dst);
		move_v(n, src, tmp, dst, 0);
	}
}

//基础算法
void hanoi(int n, char src, char tmp, char dst, int ifshow, char mode)
{
	if (mode == '7') {
		if (n == 1) {
			do_m(n, src, tmp, dst, ifshow, mode);
		}
		else {
			hanoi(n - 1, src, dst, tmp, ifshow, mode);
		}
	}
	else {
		if (n == 1) {
			do_m(n, src, tmp, dst, ifshow, mode);
		}
		else {
			hanoi(n - 1, src, dst, tmp, ifshow, mode);
			do_m(n, src, tmp, dst, ifshow, mode);
			hanoi(n - 1, tmp, src, dst, ifshow, mode);
		}
	}
}

//游戏逻辑
void game(int n, char src, char tmp, char dst, int ifshow, char mode)
{
	while (1) {
		cct_setcolor();
		cct_gotoxy(0, 34);
		cout << "                                                                                              ";
		cct_gotoxy(0, 34);
		cout << "请输入移动的柱号(命令形式：AC=A顶端的盘子移动到C，Q=退出) ：";
		char game_src, game_dst;
		int ns = 11, nd = 11;
		cin >> game_src;
		if (game_src == 'q' || game_src == 'Q') {
			cout << "游戏中止！！！！！！！！！！！！！！" << endl;
			cin.clear();
			cin.ignore(2000, '\n');
			break;
		}
		else if (game_src >= 'a' && game_src <= 'c') {
			game_src = char(game_src - 'a' + 'A');
		}
		else if (game_src >= 'A' && game_src <= 'C') {

		}
		else {
			cin.clear();
			cin.ignore(2000, '\n');
			continue;
		}
		if (game_src >= 'A' && game_src <= 'C') {
			cin >> game_dst;
			if (game_dst >= 'a' && game_dst <= 'c') {
				game_dst = char(game_dst - 'a' + 'A');
			}
			if (game_src >= 'A' && game_src <= 'C' && game_dst >= 'A' && game_dst <= 'C') {
				char game_tmp = 'A' + 'B' + 'C' - game_src - game_dst;
				if (game_src == 'A' && topa > 0) {
					ns = a[topa - 1];
				}
				else if (game_src == 'B' && topb > 0) {
					ns = b[topb - 1];
				}
				else if (game_src == 'C' && topc > 0) {
					ns = c[topc - 1];
				}
				else {
					cct_setcolor();
					cct_gotoxy(0, 35);
					cout << "非法移动！起始柱为空！";
					continue;
				}

				if (game_dst == 'A' && topa > 0) {
					nd = a[topa - 1];
				}
				else if (game_dst == 'B' && topb > 0) {
					nd = b[topb - 1];
				}
				else if (game_dst == 'C' && topc > 0) {
					nd = c[topc - 1];
				}

				if (nd >= ns) {
					cct_setcolor();
					cct_gotoxy(0, 35);
					do_m(ns, game_src, game_tmp, game_dst, ifshow, mode);
				}
				else {
					cct_gotoxy(0, 35);
					cct_setcolor();
					cout << "非法移动！大盘压小盘！";
				}
				//判断成功
				if (n == 1) {
					if (game_dst == dst) {
						cct_gotoxy(0, 35);
						cct_setcolor();
						cout << "游戏成功！！！！！！！！！" << endl;
						cin.clear();
						cin.ignore(2000, '\n');
						break;
					}
				}
				else if (nd == n) {
					cct_gotoxy(0, 35);
					cct_setcolor();
					cout << "游戏成功！！！！！！！！！" << endl;
					cin.clear();
					cin.ignore(2000, '\n');
					break;
				}
			}
		}
		cin.clear();
		cin.ignore(2000, '\n');
	}
}

//基础逻辑
void basic(char mode)
{
	initial();
	int n, ifshow = 1;
	char src, tmp, dst;

	//输入
	if (mode != 5) {
		input(&n, &src, &tmp, &dst, &ifshow, mode);
		initial_stacks(n, src, tmp, dst);
	}

	//执行
	//123
	if (mode == '1' || mode == '2' || mode == '3') {
		cct_cls();
		hanoi(n, src, tmp, dst, ifshow, mode);
	}
	//4
	else if (mode == '4') {
		cct_cls();
		cout << "从 " << src << " 移动到 " << dst << "，共 " << n << " 层，延时设置为 " << dt << "，";
		if (ifshow == 1) {
			cout << "显示内部数组值" << endl;
		}
		else {
			cout << "不显示内部数组值" << endl;
		}
		cct_gotoxy(9, 17);
		cout << "=========================" << endl;
		cct_gotoxy(11, 18);
		cout << "A         B         C" << endl;
		if (ifshow == 1) {
			cct_gotoxy(0, 26);
			cout << "初始:" << setw(16) << setfill(' ') << " ";
			out_stack_h(mode);
		}
		out_stack_v(mode);
		hanoi(n, src, tmp, dst, ifshow, mode);
	}
	//5
	if (mode == '5') {
		cct_cls();
		draw_column();
		cct_gotoxy(0, 26);
	}
	//6
	if (mode == '6') {
		cct_cls();
		draw_column();
		draw_plate(n, src);
		cct_gotoxy(0, 26);
	}
	//78
	if (mode == '7' || mode == '8') {
		cct_cls();
		draw_column();
		cct_setcolor();
		cct_gotoxy(9, 28);
		cout << "=========================" << endl;
		cct_gotoxy(11, 29);
		cout << "A         B         C" << endl;
		draw_plate(n, src);

		hanoi(n, src, tmp, dst, ifshow, mode);

		cct_gotoxy(0, 34);
	}
	//9
	if (mode == '9') {
		cct_cls();
		draw_column();
		cct_setcolor();
		cct_gotoxy(9, 28);
		cout << "=========================" << endl;
		cct_gotoxy(11, 29);
		cout << "A         B         C" << endl;

		draw_plate(n, src);
		out_stack_v(mode);
		game(n, src, tmp, dst, ifshow, mode);
	}
	cct_setcolor();
	cout << endl;
	cct_gotoxy(0, 36);
	system("pause");
}