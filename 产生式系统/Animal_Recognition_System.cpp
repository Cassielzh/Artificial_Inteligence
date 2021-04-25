#include <stdio.h>
#include <iostream>

using namespace std;

//存放推理规则的结构体
typedef struct {
	int codition[5];
	int name;
}Rule;
//初始化综合数据库
string feature[] = { "有毛","有奶","有羽毛","会飞","会下蛋","吃肉","有犬齿",//0,1,2,3,4,5,6

"有爪","眼睛盯前方","有蹄","反刍","黄褐色","有暗斑点","有黑色条纹","长脖","长腿",//7,8,9,10,11,12,13,14,15

"不会飞","会游泳","黑白两色","善飞","哺乳动物","鸟类","肉食类","蹄类",//16,17,18,19,20,21,22,23

"企鹅","信天翁","鸵鸟","斑马","长颈鹿","虎","金钱豹" };//24,25,26,27,28,29,30

//规则库
Rule rule[15] = {
	{{0,-1},20},//1
	{{1,-1},20},//2
	{{2,-1},21},//3
	{{3,4,-1},21},//4
	{{5,-1},22},//5
	{{6,7,8,-1},22},//6
	{{20,9,-1},23},//7
	{{20,10,-1},23},//8
	{{20,5,11,12,-1},30},//9
	{{20,5,11,13,-1},29},//10
	{{23,14,15,12,-1},28},//11
	{{23,13,-1},27},//12
	{{21,14,15,16,-1},26},//13
	{{21,17,16,18,-1},24},//14
	{{21,19,-1},25}//15
};

int flag[23] = { 0 };//标记各个特征是否被选择
void menu();
int isAnimal(int a);
void input();
int inference();

//菜单
void menu() {
	for (int i = 0; i < 31; i++) {
		if (i % 4 == 0 && i != 0)
			cout << endl;
		cout << i << "." << feature[i] << "  \t";
	}
}

//判断是否是动物
int isAnimal(int a) {
	if (a >= 24 && a <= 30)
		return 1;
	else
		return 0;
}

//输入函数
void input()
{
	int ti = 0;
	for (int i = 0; i < 24; i++)
	{
		flag[i] = 0;
	}
	cout << "\n输入序号以选择特征，输入-1结束输入：";
	while (ti != -1)
	{
		cin >> ti;
		if (ti >= 0 && ti <= 23)
			flag[ti] = 1;
		else if (ti != -1)
		{
			cout << "请输入0-24之间的数字" << endl;
			cin.clear();//清空cin里面的数据流
			cin.sync();//清空缓冲区
		}
	}
}
//推理
int inference()
{
	int ti;
	int i, j;
	int tres;
	cout << endl;
	for (i = 0; i < 15; i++)
	{
		j = 0;
		ti = rule[i].codition[j];
		while (ti != -1)
		{
			if (flag[ti] == 0)//如果这个条件没有被选择直接跳出循环
				break;
			j++;
			ti = rule[i].codition[j];
		}
		if (ti == -1)//如果满足规则库
		{
			tres = rule[i].name;//标记推理的结果
			flag[tres] = 1;//把推理出的结果作为条件加入规则库
			printf("运用了规则%d：", i);
			j = 0;
			while (rule[i].codition[j] != -1) {//
				cout << feature[rule[i].codition[j]] << " ";
				j++;
			}
			cout << "====>" << feature[tres] << endl;
			if (isAnimal(tres)) {//判断是否得出解，若是，结束。若不是，继续执行循环体
				return 1;
			}
		}
	}
	printf("无法判断出这种动物");
	return -1;
}

int main()
{
	char x;

	do {
		menu();
		input();
		inference();
		cout << "\n继续？（Y/N）" << endl;
		cin >> x;
		system("cls"); //清屏
	} while (x != 'n');
	return 0;
}

