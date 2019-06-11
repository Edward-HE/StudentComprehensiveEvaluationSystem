#include<stdio.h>
#include<string.h>
#include<windows.h>
#include<conio.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>
#define HEADER  "                             **学生列表**\n"
#define HEADER0 "     -----------------------------------------------------------  \n"
#define HEADER1 "     |     学 号     |    姓  名    | 性别 |    联 系 电 话    |\n"
#define FORMAT1 "     |%-15s|    %-10s|  %-4s|    %-15s|\n"
#define HEADER2 "     |       学  号       |     姓  名     |\n"
#define FORMAT2 "     |   %-15s  |     %-10s |\n"
#define HEADER3 "     |  家 庭 住 址  |"
#define FORMAT3 "    %-35s  |\n"
#define HEADER4 "     | 语文 | 数学 | 英语 | 平均分 | 名次1 |\n"
#define FORMAT4 "     | %-4d | %-4d | %-4d | %-6.2lf |  %-4d |\n"
#define HEADER5 "     | 思品 | 互评 | 师评 | 综合分 | 名次2 |\n"
#define FORMAT5 "     | %-4d | %-4d | %-4d | %-6.2lf |  %-4d |\n"


#define DATA1   p->num,p->name,p->sex,p->phone
#define DATA2   p->num,p->name
#define DATA3   p->address
#define DATA4   p->chinese,p->math,p->english,p->average,p->rank_main
#define DATA5   p->pinde,p->huping,p->teacher,p->score_all,p->rank_all

#define END     "     -----------------------------------------------------------  \n"
//------------------------------- 定义全局变量------------------------------------
int check_result = 0;		//记录检测结果的变量
//------------------------------- 定义学生数据结构体------------------------------------
typedef struct Stuinfo {
	char num[15];			//学号
	char name[10];		//学生名字
	char sex[4];		//性别
	char address[35];	//家庭住址
	char phone[14];		//电话
	int chinese, math, english, pinde;	//语、数、英、思想品德成绩
	int rank_main, rank_all;			//语数英三科名次，综合测评名次
	int huping, teacher;				//互评分，教师评分
	double average, score_all;			//三科平均分，综合总分
	// 每个学生的信息为：学号、姓名、性别、家庭住址、联系电话、语文、数学、外语三门单科成绩、
	// 考试平均成绩、考试名次、同学互评分、品德成绩、任课教师评分、综合测评总分、综合测评名次。
	// 考试平均成绩、同学互评分、品德成绩、任课教师评分分别占综合测评总分的60% ，10% ，10% ，20% 。
	struct Stuinfo* next;
}Stu;
//------------------------------- 函数声明------------------------------------
void color(short x);
void toxy(int x, int y);
void Wrong(int a, int b);
void main_menu(Stu* l, Stu* p, Stu* r);
void teacher_account(Stu* l, Stu* p, Stu* r);
void stu_menu(Stu* l);
void about_us();
int pswd_check();
char mod_pswd();
Stu* Locate(Stu* l, char find_data[], int type_find);
void login_teacher(Stu* l, Stu* p, Stu* r);
void pswd_create();
void teacher_main_menu(Stu* l, Stu* p, Stu* r);
void Add_info(Stu* l);
void Add_score(Stu* l);
void Disp(Stu* l, int i);
void stringinput(char* t, int lens, char* notice);
void printinfo(Stu* pp);
void printscore(Stu* pp);
void Save(Stu* l);
void Modify_info(Stu* l);
void Modify_score(Stu* l);
void Sort(Stu* l, int sel);
void Del(Stu* l);
void Stu_score_feedback(Stu* p);
void look_feedback();
int main();
/*#######################辅助功能函数###############################*/

//------------------------文本颜色-----------------------------------
void color(short x)
{
	if (x >= 0 && x <= 15)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), x);
	}
	else
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), x);
	}
}
//------------------------光标定位-----------------------------------
void toxy(int x, int y)      //将光标移动到X,Y坐标处
{
	COORD pos = { x , y };
	HANDLE Out = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(Out, pos);
}
//---------------------输入错误选项提醒-----------------------------------
void Wrong(int a, int b) /*输出按键错误信息*/
{
	system("cls");
	toxy(35, 12);
	printf("==================================================");
	toxy(39, 15);
	printf("请选择%d-%d中的选项之一，请不要输入其他选项！", a, b);
	toxy(35, 18);
	printf("==================================================");
}
//---------------------教师密码文件创建----------------------------------
void pswd_create()
{
	FILE* fp;
	if ((fp = fopen("pswd_teacher", "rb")) == NULL) //读写方式打开教师密码文件               /*如果此文件不存在*/
	{
		fp = fopen("pswd_teacher", "wb+");			//如果没有找到，新建一个
		if (fp == NULL)
		{
			printf("无法建立文件！\n");
			exit(0);
		}
		fputs("123456", fp);		//设置初始密码123456
	}
	fclose(fp);
}
//------------------------保存到文件-----------------------------------
void Save(Stu* l)
{
	FILE* fp;
	Stu* p;
	int count = 0;
	fp = fopen("student_info.dat", "wb");/*以只写方式打开二进制文件*/
	if (fp == NULL) /*打开文件失败*/
	{
		printf("\n=====>打开错误！\n");
		getchar();
		return;
	}
	p = l->next;

	while (p)
	{
		if (fwrite(p, sizeof(Stu), 1, fp) == 1)/*每次写一条记录或一个节点信息至文件*/
		{
			p = p->next;
			count++;
		}
		else
		{
			break;
		}
	}
	if (count > 0)
	{

	}
	else
	{
		system("cls");
		printf("没有信息被保存！\n");
		getchar();
	}
	fclose(fp); /*关闭此文件*/
}
//-----------------------查找并定位-----------------------------------
Stu* Locate(Stu* l, char find_data[], int type_find)
{
	Stu* r;
	if (type_find == 0) /*按编号查询*/
	{
		r = l->next;
		while (r)
		{
			if (strcmp(r->num, find_data) == 0) /*若找到find_data值的编号*/
				return r;
			r = r->next;
		}
	}
	else if (type_find == 1)  /*按姓名查询*/
	{
		r = l->next;
		while (r)
		{
			if (strcmp(r->name, find_data) == 0)    /*若找到find_data值的教师姓名*/
				return r;
			r = r->next;
		}
	}
	return 0; /*若未找到，返回一个空指针*/
}
//-------------------------排序-----------------------------------
void Sort(Stu* l, int sel)
{
	Stu* temp1;
	temp1 = l->next; /*l存储的是单链表中头结点的指针，该头结点没有存储教师信息，指针域指向的后继结点才有教师信息*/
	if (!temp1)  /*p==NULL,NUll在stdlib中定义为0*/
	{
		printf("\n\t\t\t\t\t\t=====>文件中没有数据！\n");
		getchar();
		system("pause");
		system("cls");
		return;
	}
	Stu* p, * pre, * tail, * temp;
	tail = NULL;
	pre = l;
	int i = 1;
	p = (Stu*)malloc(sizeof(Stu));
	while ((l->next->next) != tail)
	{
		p = l->next;
		pre = l;
		while (p->next != tail)
		{
			if (sel == 0)
			{
				if (strcmp(p->next->num, p->num) < 0)
				{
					pre->next = p->next;
					temp = p->next->next;
					p->next->next = p;
					p->next = temp;
					p = pre->next;
				}
			}
			else if (sel == 1)
			{
				if ((p->average) < (p->next->average))
				{
					pre->next = p->next;
					temp = p->next->next;
					p->next->next = p;
					p->next = temp;
					p = pre->next;
				}
			}
			else if (sel == 2)
			{
				if ((p->score_all) < (p->next->score_all))
				{
					pre->next = p->next;
					temp = p->next->next;
					p->next->next = p;
					p->next = temp;
					p = pre->next;
				}
			}

			p = p->next;
			pre = pre->next;
		}
		tail = p;
	}
	p = l->next;           /*已排好序的头指针赋给p，准备填写名次*/
	while (p != NULL)  /*当p不为空时，进行下列操作*/
	{
		if (sel == 1)
			p->rank_main = i;
		else if (sel == 2)
			p->rank_all = i;
		i++;       /*结点序号*/
		p = p->next;   /*指针后移*/

	}
	Save(l);
	return;
}
//-----------------------数据表格化显示---------------------------------
void Disp(Stu* l, int i)  /*显示单链表l中存储的教师记录，内容为teacher结构中定义的内容*/
{
	Stu* p;
	p = l->next; /*l存储的是单链表中头结点的指针，该头结点没有存储教师信息，指针域指向的后继结点才有教师信息*/

	if (!p)  /*p==NULL,NUll在stdlib中定义为0*/
	{
		system("cls");
		toxy(49, 12);
		printf("=====>文件中没有数据！\n");
		getchar();
		toxy(54, 14);
		system("pause");
		return;
	}

	printf("\n\n");
	toxy(27, 4);
	printf(HEADER);
	toxy(27, 5);
	printf(HEADER0);
	while (p)    /*逐条输出链表中存储的教师信息*/
	{
		if (i == 0)
			printinfo(p);
		else if (i == 1)
			printscore(p);
		else if (i == 2)
		{
			printf("\t\t\t\t     ");
			printf(HEADER2);
			printf("\t\t\t\t     ");
			printf(FORMAT2, DATA2);
			printf("\t\t\t\t     ");
			printf(HEADER4);
			printf("\t\t\t\t     ");
			printf(FORMAT4, DATA4);
		}
		else if (i == 3)
		{
			printf("\t\t\t\t     ");
			printf(HEADER2);
			printf("\t\t\t\t     ");
			printf(FORMAT2, DATA2);
			printf("\t\t\t\t     ");
			printf(HEADER5);
			printf("\t\t\t\t     ");
			printf(FORMAT5, DATA5);
		}
		else if (i == 4)
		{
			printf("\t\t\t   ");
			printf(HEADER1);
			printf("\t\t\t   ");
			printf(FORMAT1, DATA1);
			printf("\t\t\t   ");
			printf(HEADER3);
			printf(FORMAT3, DATA3);
			printf("\t\t\t   \t\t\t\t\t\t\t\t  |\r");
			printf("\t\t\t   ");
			printf(HEADER4);
			printf("\t\t\t   \t\t\t\t\t\t\t\t  |\r");
			printf("\t\t\t   ");
			printf(FORMAT4, DATA4);
			printf("\t\t\t   \t\t\t\t\t\t\t\t  |\r");
			printf("\t\t\t   ");
			printf(HEADER5);
			printf("\t\t\t   \t\t\t\t\t\t\t\t  |\r");
			printf("\t\t\t   ");
			printf(FORMAT5, DATA5);
		}
		p = p->next;  /*移动直下一个结点*/
		printf("\t\t\t   ");
		printf(END);
	}
	getchar();
}
//-----------------------信息格式化输出----------------------------------
void printinfo(Stu* pp) /*格式化输出表中数据*/
{
	Stu* p;
	p = pp;
	printf("\t\t\t   ");
	printf(HEADER1);
	printf("\t\t\t   ");
	printf(FORMAT1, DATA1);
	printf("\t\t\t   ");
	printf(HEADER3);
	printf(FORMAT3, DATA3);
}
//-----------------------成绩格式化输出-----------------------------------
void printscore(Stu* pp) /*格式化输出表中数据*/
{
	Stu* p;
	p = pp;
	printf("\t\t\t\t     ");
	printf(HEADER2);
	printf("\t\t\t\t     ");
	printf(FORMAT2, DATA2);
	printf("\t\t\t\t     ");
	printf(HEADER4);
	printf("\t\t\t\t     ");
	printf(FORMAT4, DATA4);
	printf("\t\t\t\t     ");
	printf(HEADER5);
	printf("\t\t\t\t     ");
	printf(FORMAT5, DATA5);
}
//---------------------带长度控制的内容输入-----------------------------------
void stringinput(char* t, int lens, char* notice)
{
	char n[255];
	do {
		printf(notice);  /*显示提示信息*/
		scanf("%s", n);  /*输入字符串*/
		if (strlen(n) > lens)printf("\n exceed the required length! \n"); /*进行长度校验，超过lens值重新输入*/
	} while (strlen(n) > lens);
	strcpy(t, n); /*将输入的字符串拷贝到字符串t中*/
}

/*#######################主要功能函数###############################*/

//-------------------------首页面-----------------------------------
void main_menu(Stu* l, Stu* p, Stu* r) {
	int option;
	while (1) {
		option = -1;
		color(3);
		toxy(35, 12);
		printf("==================================================");
		color(9);
		toxy(52, 14);
		printf("学生综合测评系统");
		color(3);
		toxy(48, 18);
		printf("1.教师账户");
		printf("\t2.学生账户");
		toxy(48, 20);
		printf("3.关于我们");
		printf("\t0.退出系统");
		toxy(52, 22);
		printf("请输入对应序号: ");
		toxy(35, 24);
		printf("==================================================");
		p = r;
		toxy(60, 25);
		scanf("%d", &option);
		switch (option) {
		case 1:
			system("cls"); 
			teacher_account(l, p, r); 
			system("cls"); 
			break;
		case 2:
			system("cls"); 
			stu_menu(l); 
			system("cls");  
			break;
		case 3:
			system("cls"); 
			about_us();
			toxy(54, 28);
			system("pause"); 
			getchar(); 
			system("cls"); 
			break;
		case 0:
			exit(0);
		default:
			Wrong(0, 3);
			toxy(52, 20);
			system("pause"); 
			char wrg[100];
			gets(wrg);
			system("cls"); 
			break;
		}
	}
}
//------------------------教师端主菜单-------------------------------
void teacher_account(Stu* l, Stu* p, Stu* r) {
	pswd_create();			//每次进入后确认一次是否存在密码文件		
	int i;
	while (1) {
		i = -1;
		color(11);
		toxy(35, 12);
		printf("==================================================");
		toxy(44, 14);
		printf("欢迎使用学生综合测评系统(教师端)");
		toxy(48, 18);
		printf("1.登	录");
		printf("\t2.修改密码");
		toxy(48, 20);
		printf("3.返回主菜单");
		printf("\t4.退出系统");
		toxy(52, 22);
		printf("请输入对应序号：");
		toxy(35, 24);
		printf("==================================================");
		toxy(60, 25);
		scanf("%d", &i);
		switch (i) {
		case 1:
			system("cls"); 
			login_teacher(l, p, r); 
			break;
		case 2:
			system("cls"); 
			mod_pswd(); 
			break;
		case 3:
			system("cls"); 
			getchar(); 
			return;
		case 4:
			exit(0);
		default:
			Wrong(1, 4);
			toxy(52, 20);
			system("pause"); 
			char wrg[100];
			gets(wrg);
			system("cls");
		}

	}
}
//------------------------教师端登录---------------------------------
void login_teacher(Stu* l, Stu* p, Stu* r) {
	char a[16];				//暂时储存密码的数组	
	char a1[16] = { "123456" }; //储存默认密码的数组
	FILE* fp;
	fp = fopen("pswd_teacher", "r"); //打开储存密码的文件
	fgets(a, 16, fp);	 //读取密码到数组a中
	toxy(35, 12);
	printf("==================================================");
	toxy(54, 14);
	printf("教师登录界面");
	if (strcmp(a, a1) == 0) {	 //判断是否为初始密码
		toxy(42, 15);
		printf("您仍在使用初始密码，请及时更改密码！");
	}
	toxy(52, 16);
	printf("请输入密码：");
	pswd_check();
	if (check_result == 1) {
		toxy(48, 22);
		printf("登录成功！即将进入教师端");
		toxy(35, 24);
		printf("==================================================");
		toxy(54, 26);
		system("pause");
		system("cls");
		teacher_main_menu(l, p, r);
	}
	else if (check_result == 0)
	{
		return;
	}
	fclose(fp);
}
//-----------------------教师密码检测-----------------------------------
int pswd_check() {		//检测密码正确性
	char a[16], b[16];
	FILE* fp;
	fp = fopen("pswd_teacher", "r"); //打开储存密码的文件
	fgets(b, 16, fp);	 //读取密码到数组a中
	scanf("%s", &a);
	int i = 3;
	while (1) {
		if (strcmp(a, b) == 0) {
			check_result = 1;//检测通过
			fclose(fp);
			return (check_result);
		}
		else {
			toxy(41, 18);
			printf("密码不正确，请重新输入，您还有%d次机会!\n", i);
			toxy(54, 20);
			printf("请输入密码：");
			i--;
			scanf("%s", &a);
		}
		if (i == 0) {
			toxy(45, 22);
			printf("您已输错超过3次，即将返回主界面\n");
			toxy(35, 24);
			printf("==================================================");
			fclose(fp);
			toxy(54, 26);
			system("pause");
			system("cls");
			check_result = 0;
			return (check_result);
		}
	}
}
//-------------------------修改密码----------------------------------
char mod_pswd() {	//修改密码
	char b[16];		//临时储存新密码的变量
	FILE* fp;
	toxy(35, 12);
	printf("==================================================");
	toxy(53, 14);
	printf("教师端密码修改");
	toxy(53, 16);
	printf("请输入旧密码：");
	pswd_check();
	if (check_result == 0)
		return;
	toxy(53, 22);
	printf("请输入新密码：");
	fp = fopen("pswd_teacher", "w");
	scanf("%s", &b);
	fputs(b, fp);
	fclose(fp);
	toxy(53, 24);
	printf("请确认新密码：");
	pswd_check();
	if (check_result == 1) {
		toxy(53, 26);
		printf("修改密码成功！");
		toxy(35, 28);
		printf("==================================================");
		toxy(54, 30);
		system("pause");
		system("cls");
		return;
	}
}
//------------------------学生信息添加----------------------------------
void Add_info(Stu* l)
{
	Stu* p, * r, * s;  /*实现添加操作的临时的结构体指针变量*/
	char ch, flag = 0, num[15];
	r = l;
	s = l->next;
	system("cls");
	Disp(l, 0); /*先打印出已有的教师信息*/
	printf("\n\t\t\t\t\t\t      添加学生信息\n");
	while (r->next != NULL)
		r = r->next; /*将指针移至于链表最末尾，准备添加记录*/
	while (1) /*一次可输入多条记录，直至输入编号为0的记录结点添加操作*/
	{

		while (1) /*输入编号，保证该编号没有被使用，若输入编号为0，则退出添加记录操作*/
		{
			printf("\t\t\t\t\t\t\t ");
			stringinput(num, 15, "请输入\n\t\t\t\t\t      学号(输入0退出)："); /*格式化输入编号并检验*/
			flag = 0;
			if (strcmp(num, "0") == 0) /*输入为0，则退出添加操作，返回主界面*/
			{
				Save(l);
				return;
			}
			s = l->next;
			while (s) /*查询该编号是否已经存在，若存在则要求重新输入一个未被占用的编号*/
			{
				if (strcmp(s->num, num) == 0)
				{
					flag = 1;
					break;
				}
				s = s->next;
			}

			if (flag == 1) /*提示用户是否重新输入*/

			{
				getchar();
				printf("\t=====>学号 %s 的信息已被录入，要不要换一个呢？(y/n):", num);
				scanf("%c", &ch);
				if (ch == 'y' || ch == 'Y')
					continue;
				else
					return;
			}
			else
			{
				break;
			}
		}

		p = (Stu*)malloc(sizeof(Stu)); /*申请内存空间*/
		if (!p)
		{
			printf("\n 内存申请失败！请尝试获取更高权限！ "); /*如没有申请到，打印提示信息*/
			return;             /*返回主界面*/
		}
		strcpy(p->num, num); /*将字符串num拷贝到p->data.num中*/
		printf("\t\t\t\t\t\t      ");
		stringinput(p->name, 10, "姓名：");
		printf("\t\t\t\t\t\t\t");
		printf("性别：");
		scanf("%s", p->sex);
		printf("\t\t\t\t\t      ");
		printf("家庭住址：");
		scanf("%s", p->address);
		printf("\t\t\t\t\t\t   ");
		printf("电话：");
		scanf("%s", p->phone);
		p->chinese = p->math = p->english = p->average = p->pinde = p->rank_all = p->rank_main = p->score_all = p->teacher = p->huping = -1;

		p->next = NULL; /*表明这是链表的尾部结点*/
		r->next = p;  /*将新建的结点加入链表尾部中*/
		r = p;
	}

	return;
}
//------------------------学生信息修改----------------------------------
void Modify_info(Stu* l)
{
	Stu* p, * t;  /*实现添加操作的临时的结构体指针变量*/
	char find_data[20];
	char ch[30] = "\0", chy;
temp:
	if (!l->next)
	{
		system("cls");
		toxy(49, 12);
		printf("=====>文件中没有数据！\n");
		getchar();
		return;
	}
	system("cls");
	Disp(l, 0);
	printf("\n\t\t\t\t\t\t      修改学生信息\n");
	printf("\t\t\t\t\t\t\t ");
	stringinput(find_data, 15, "请输入\n\t\t\t\t\t      学号(输入0退出)："); /*输入并检验该编号*/
	p = Locate(l, find_data, 0); /*查询到该节点*/
	if (p) /*若p!=NULL,表明已经找到该节点*/
	{
		system("cls");
		toxy(52, 6);
		printf("已找到该生信息：\n\n");
		printinfo(p);
		toxy(37, 12);
		printf("请根据提示输入要修改的信息，输入0则不修改此项：");
		toxy(51, 14);
		printf("学号：");
		gets();
		gets(ch);
		if (strcmp(ch, "0") != 0) {
			while (t = Locate(l, ch, 0)) {
				toxy(45, 15);
				printf("此学号已存在，请尝试其他学号！");
				toxy(51, 16);
				printf("学号：");
				gets(ch);
			}
			strcpy(p->num, ch);
		}
		toxy(54, 17);
		printf("名字：");
		gets(ch);
		if (strcmp(ch, "0") != 0)
			strcpy(p->name, ch);
		toxy(56, 18);
		printf("性别：");
		gets(ch);
		if (strcmp(ch, "0") != 0)
			strcpy(p->sex, ch);
		toxy(46, 19);
		printf("家庭住址：");
		gets(ch);
		if (strcmp(ch, "0") != 0)
			strcpy(p->address, ch);
		toxy(51, 20);
		printf("电话：");
		gets(ch);
		if (strcmp(ch, "0") != 0)
			strcpy(p->phone, ch);
		toxy(48, 22);
		printf("修改成功！修改后信息为：\n\n");
		printinfo(p);
		Save(l);
		toxy(54, 28);
		system("pause");
		system("cls");
		return;
	}
	else
	{
		getchar();
		printf("\n\n\t\t\t\t");
		printf("学号 %s 的信息还未被录入，要不要换一个呢？(y/n):", find_data);
		scanf("%c", &chy);
		if (chy == 'y' || chy == 'Y') {
			system("cls");
			goto temp;
		}
		else {
			system("cls");
			return;
		}
	}
}
//------------------------学生信息删除----------------------------------
void Del(Stu* l)
{
	int sel;
	Stu* p, * r;
	char find_data[20], chy;
temp_del:
	if (!l->next)
	{
		system("cls");
		toxy(49, 16);
		printf("=====>文件中没有数据！\n");
		getchar();
		return;
	}
	system("cls");
	Disp(l, 0);
	printf("\n\t\t\t\t\t\t\t删除学生数据\n");
	printf("\n\t\t\t\t      1.按学号删除\t2.按姓名删除\t0.返回上一级\n");
	printf("\n\t\t\t\t\t\t 请输入你的选择[0,2]:");
	scanf("%d", &sel);
	if (sel == 0)
		return;
	else if (sel == 1)
	{
		printf("\n\t\t\t\t\t  ");
		stringinput(find_data, 15, "请输入要删除学生的学号：");
		p = Locate(l, find_data, 0);
	}
	else if (sel == 2) /*先按姓名查询到该记录所在的节点*/
	{
		printf("\n\t\t\t\t\t     ");
		stringinput(find_data, 10, "请输入要删除学生的姓名：");
		p = Locate(l, find_data, 1);
	}
	else
	{
		Wrong(1, 2);
		system("pause");
		getchar();
		goto temp_del;
	}
	if (p)  /*p!=NULL*/
	{
		system("cls");
		toxy(52, 10);
		printf("已找到该生数据：\n\n");
		printf("\t\t\t   ");
		printf(HEADER0);
		printf("\t\t\t   ");
		printf(HEADER1);
		printf("\t\t\t   ");
		printf(FORMAT1, DATA1);
		printf("\t\t\t   ");
		printf(HEADER3);
		printf(FORMAT3, DATA3);
		printf("\t\t\t   \t\t\t\t\t\t\t\t  |\r");
		printf("\t\t\t   ");
		printf(HEADER4);
		printf("\t\t\t   \t\t\t\t\t\t\t\t  |\r");
		printf("\t\t\t   ");
		printf(FORMAT4, DATA4);
		printf("\t\t\t   \t\t\t\t\t\t\t\t  |\r");
		printf("\t\t\t   ");
		printf(HEADER5);
		printf("\t\t\t   \t\t\t\t\t\t\t\t  |\r");
		printf("\t\t\t   ");
		printf(FORMAT5, DATA5);
		printf("\t\t\t   ");
		printf(END);
		printf("\n\t\t\t\t\t      ");
		printf("是否确认删除该条数据？(y/n)：");
		getchar();
		scanf("%c", &chy);
		if (chy == 'y' || chy == 'Y')
		{
			r = l;
			while (r->next != p)
				r = r->next;
			r->next = p->next;/*将p所指节点从链表中去除*/
			free(p); /*释放内存空间*/
			printf("\n\t\t\t\t\t\t      ");
			printf("已成功删除！\n");
			getchar();
			Save(l);
			printf("\n\t\t\t\t\t\t      ");
			system("pause");
			system("cls");
			return;
		}
		else
		{
			system("cls");
			goto temp_del;
		}
	}
	else
	{
		getchar();
		printf("\n\n\t\t\t\t");
		printf("%s 的信息还未被录入，要不要换一个呢？(y/n):", find_data);
		scanf("%c", &chy);
		if (chy == 'y' || chy == 'Y')
		{
			system("cls");
			goto temp_del;
		}
		else
		{
			system("cls");
			return;
		}
	}
}
//------------------------学生成绩录入----------------------------------
void Add_score(Stu* l)
{
	Stu* p;  /*实现添加操作的临时的结构体指针变量*/
	char find_data[20];
	char ch;
	if (!l->next)
	{
		toxy(49, 12);
		printf("=====>文件中没有数据！\n");
		getchar();
		return;
	}
	system("cls");
	Disp(l, 1);
	printf("\n\t\t\t\t\t\t      录入学生成绩\n");
	while (1) /*一次可输入多条记录，直至输入编号为0的记录结点添加操作*/
	{
		printf("\n\t\t\t\t\t\t\t ");
		stringinput(find_data, 15, "请输入\n\t\t\t\t\t      学号(输入0退出)："); /*输入并检验该编号*/
		if (strcmp(find_data, "0") == 0) /*输入为0，则退出添加操作，返回主界面*/
		{
			Save(l);
			return;
		}
		p = Locate(l, find_data, 0); /*查询到该节点*/
		if (p) /*若p!=NULL,表明已经找到该节点*/
		{
			printf("\n\n\t\t\t\t\t  ");
			printf("学号：%s\t姓名：%s\n", p->num, p->name);
			if (p->chinese != -1) 
			{
				getchar();
				printf("\n\n\t\t\t\t");
				printf("此学生的成绩已经被录入，要不要换一个呢？(y/n):");
				scanf("%c", &ch);
				if (ch == 'y' || ch == 'Y')
					continue;
				else
					return;
			}
			printf("\n\t\t\t\t\t\t\t");
			printf("语文：");
			scanf("%d", &p->chinese);
			printf("\n\t\t\t\t\t\t\t");
			printf("数学：");
			scanf("%d", &p->math);
			printf("\n\t\t\t\t\t\t\t");
			printf("英语：");
			scanf("%d", &p->english);
			printf("\n\t\t\t\t\t\t    ");
			printf("思想品德：");
			scanf("%d", &p->pinde);
			printf("\n\t\t\t\t\t\t\t");
			printf("互评：");
			scanf("%d", &p->huping);
			printf("\n\t\t\t\t\t\t\t");
			printf("师评：");
			scanf("%d", &p->teacher);

			p->average = ((p->chinese) + (p->math) + (p->english)) / 3;//计算平均分
			/*计算综合测评得分，语数英平均分60%，思想品德10%，互评10%，师评20%，*/
			p->score_all = (p->average) * 0.6 + (p->huping) * 0.1 + (p->pinde) * 0.1 + (p->teacher) * 0.2;

			printf("\n\t\t\t\t\t\t    ");
			printf("平均成绩：%.2lf", p->average);
			printf("\n\t\t\t\t\t\t");
			printf("综合测评得分：%.2lf", p->score_all);
			printf("\n");
		}
		else
		{
			getchar();
			printf("\n\n\t\t\t\t");
			printf("学号 %s 的信息还未被录入，要不要换一个呢？(y/n):", find_data);
			scanf("%c", &ch);
			if (ch == 'y' || ch == 'Y')
				continue;
			else
				return;
		}
	}
}
//------------------------学生成绩修改----------------------------------
void Modify_score(Stu* l)
{
	Stu* p, * t;  /*实现添加操作的临时的结构体指针变量*/
	char find_data[20];
	char chy,ch;
	int tmp;
temp:
	if (!l->next)
	{
		system("cls");
		toxy(49, 16);
		printf("=====>文件中没有数据！\n");
		getchar();
		return;
	}
	system("cls");
	Disp(l, 1);
	printf("\n\t\t\t\t\t\t      修改学生成绩\n");
	printf("\n\t\t\t\t\t  ");
	stringinput(find_data, 15, "请输入要修改学生的学号："); /*输入并检验该编号*/
	p = Locate(l, find_data, 0); /*查询到该节点*/
	if (p) /*若p!=NULL,表明已经找到该节点*/
	{
		if (p->chinese == -1) 
		{
			getchar();
			printf("\n\n\t\t\t\t");
			printf("学号 %s 的成绩还未被录入，要不要换一个呢？(y/n):", find_data);
			scanf("%c", &ch);
			if (ch == 'y' || ch == 'Y')
				goto temp;
			else
				return;
		}
		
		system("cls");
		toxy(52, 6);
		printf("已找到该生成绩：\n\n");
		printf("\t\t\t   ");
		printf(HEADER0);
		printscore(p);
		printf("\t\t\t   ");
		printf(END);
		toxy(37, 17);
		printf("请根据提示输入要修改的成绩，输入-1则不修改此项：");
		toxy(56, 19);
		printf("语文：");
		scanf("%d", &tmp);
		if (tmp != -1)
			p->chinese = tmp;
		toxy(56, 20);
		printf("数学：");
		scanf("%d", &tmp);
		if (tmp != -1)
			p->math = tmp;
		toxy(56, 21);
		printf("英语：");
		scanf("%d", &tmp);
		if (tmp != -1)
			p->english = tmp;
		toxy(56, 22);
		printf("思想品德：");
		scanf("%d", &tmp);
		if (tmp != -1)
			p->pinde = tmp;
		toxy(56, 23);
		printf("互评：");
		scanf("%d", &tmp);
		if (tmp != -1)
			p->huping = tmp;
		toxy(56, 24);
		printf("师评：");
		scanf("%d", &tmp);
		if (tmp != -1)
			p->teacher = tmp;
		p->average = ((p->chinese) + (p->math) + (p->english)) / 3;//计算平均分
			/*计算综合测评得分，语数英平均分60%，思想品德10%，互评10%，师评20%，*/
		p->score_all = (p->average) * 0.6 + (p->huping) * 0.1 + (p->pinde) * 0.1 + (p->teacher) * 0.2;
		Sort(l, 1);
		Sort(l, 2);
		toxy(48, 26);
		printf("修改成功！修改后成绩为：\n\n");
		printf("\t\t\t   ");
		printf(HEADER0);
		printscore(p);
		printf("\t\t\t   ");
		printf(END);
		Save(l);
		toxy(52, 38);
		system("pause");
		system("cls");
		return;
	}
	else
	{
		getchar();
		printf("\n\n\t\t\t\t");
		printf("学号 %s 的信息还未被录入，要不要换一个呢？(y/n):", find_data);
		scanf("%c", &chy);
		if (chy == 'y' || chy == 'Y') {
			system("cls");
			goto temp;
		}
		else {
			system("cls");
			return;
		}
	}
}
//---------------------查看学生申诉反馈留言----------------------------------
void look_feedback()
{
	FILE* fp;
	char comment[256];
	fp = fopen("score_feedback.dat", "a+");
	toxy(48, 6);
	printf("**学生成绩申诉反馈信息**\n");
	toxy(35, 8);
	printf("==================================================");
	toxy(0, 10);
	while (!feof(fp))
	{
		fgets(comment,256, fp);
		printf("\t\t\t\t\t  %s", comment);
	}
	fclose(fp);
	printf("\n\n");
	printf("\n\t\t\t\t\t\t      ");
	system("pause");
	system("cls");
	return;
}
//------------------------教师端功能菜单----------------------------------
void teacher_main_menu(Stu* l, Stu* p, Stu* r) {
	int option;
	while (1) {
		option = -1;
		toxy(35, 5);
		printf("==================================================");
		toxy(44, 7);
		printf("欢迎使用学生综合测评系统(教师端)");
		toxy(36, 10);
		printf("-----学生信息管理-----   -----学生成绩管理-----");
		toxy(36, 11);
		printf("|                    |   |                    |");
		toxy(36, 12);
		printf("|  1. 添加学生信息   |   |  5. 录入成绩数据   |");
		toxy(36, 13);
		printf("|  2. 修改学生信息   |   |  6. 修改成绩数据   |");
		toxy(36, 14);
		printf("|  3. 删除学生信息   |   |  7. 查看成绩信息   |");
		toxy(36, 15);
		printf("|  4. 查看学生信息   |   |  8. 查看成绩反馈   |");
		toxy(36, 16);
		printf("|                    |   |                    |");
		toxy(36, 17);
		printf("----------------------   ----------------------");
		toxy(36, 19);
		printf("   9. 排名（平均分）       10. 排名（综合分）");
		toxy(36, 20);
		printf("  11. 显示全部学生数据     12. 返回上一级");
		toxy(55, 21);
		printf("0.退出系统");
		toxy(47, 23);
		printf("请输入你的选择（0--11）：");
		toxy(35, 25);
		printf("==================================================");
		p = r;
		toxy(60, 26);
		scanf("%d", &option);
		switch (option)
		{
		case 0:
			exit(0);
		case 1:
			Add_info(l);
			Sort(l, 0);
			system("cls");
			break;
		case 2:
			Modify_info(l);
			Sort(l, 0);
			system("cls");
			break;
		case 3:
			Del(l);
			system("cls");
			break;
		case 4:
			system("cls");
			Sort(l, 0);
			Disp(l, 0);
			printf("\t\t\t\t\t\t   ");
			system("pause");
			system("cls");
			break;
		case 5:
			Add_score(l);
			Sort(l, 1);
			Sort(l, 2);
			Sort(l, 0);
			system("cls");
			break;
		case 6:
			Modify_score(l);
			Sort(l, 1);
			Sort(l, 2);
			Sort(l, 0);
			system("cls");
			break;
		case 7:
			system("cls");
			Sort(l, 0);
			Disp(l, 1);
			printf("\t\t\t\t\t\t   ");
			system("pause");
			system("cls");
			break;
		case 8:
			system("cls");
			look_feedback();
			break;
		case 9:
			Sort(l, 1);
			system("cls");
			Disp(l, 2);
			printf("\t\t\t\t\t\t   ");
			system("pause");
			system("cls");
			break;
		case 10:
			Sort(l, 2);
			system("cls");
			Disp(l, 3);
			printf("\n\t\t\t\t\t\t      ");
			system("pause");
			system("cls");
			break;
		case 11:
			Sort(l, 0);
			Disp(l, 4);
			printf("\n\t\t\t\t\t\t      ");
			system("pause");
			system("cls");
			break;
		case 12:
			system("cls");
			return;
		default:
			Wrong(0, 11);
			toxy(52, 20);
			system("pause");
			char wrg[100];
			gets(wrg);
			system("cls");
			break;
		}
	}
	system("pause");
}
//-----------------------学生成绩申诉反馈----------------------------------
void Stu_score_feedback(Stu* p)
{
	FILE* fp;
	char i;
	fp = fopen("score_feedback.dat", "ab+");
	toxy(50, 6);
	printf("**学生成绩申诉反馈**");
	toxy(35, 8);
	printf("==================================================");
	toxy(35, 10);
	printf("如果你对你的成绩有疑问，可以在这里给老师留言反馈。");
	toxy(40, 11);
	printf("直接按i键开始输入反馈，按其他键可返回：");
	i = getch();
	if (i != 'i')
	{
		fclose(fp);
		system("cls");
		return;
	}
	else
	{
		system("cls");
		toxy(50, 6);
		printf("**学生成绩申诉反馈**");
		toxy(35, 8);
		printf("==================================================");
		toxy(40, 10);
		printf("请输入你的申诉留言，完成后按回车键结束：\n");
		fputs("------------------------------------\n", fp);
		char fdbk[512], tmp2[256];
		memset(tmp2, 0, sizeof(tmp2));
		time_t timep;
		struct tm* t;
		time(&timep);
		t = gmtime(&timep);
		sprintf(tmp2, "%d年%d月%d日 %d:%d:%d\n学号：%s 姓名：%s\n", 1900 + t->tm_year, 1 + t->tm_mon, t->tm_mday, 8 + t->tm_hour, t->tm_min, t->tm_sec, p->num, p->name);//记录反馈时间
		fwrite(tmp2, 1, strlen(tmp2), fp);
		toxy(35, 12);
		scanf("%s", fdbk);
		fputs(fdbk, fp);
		fputs("\n------------------------------------\n", fp);
		fclose(fp);
		toxy(43,18);
		printf("=>成绩申诉已提交给老师，请耐心等待<=");
		toxy(52, 20);
		system("pause");
		system("cls");
		return;
	}
}
//------------------------学生功能菜单----------------------------------
void stu_menu(Stu* l)
{

	Stu* p, * t;  /*实现添加操作的临时的结构体指针变量*/
	char find_data[20];
	char chy;
temp_stu:
	color(7);
	toxy(35, 12);
	printf("==================================================");
	toxy(52, 14);
	printf("学生系统登录界面");
	if (!l->next)
	{
		system("cls");
		toxy(49, 12);
		printf("=====>暂时没有学生数据！");
		getchar();
		toxy(54, 14);
		system("pause");
		return;
	}
	toxy(50, 16);
	stringinput(find_data, 15, "请输入学号："); /*输入并检验该编号*/
	p = Locate(l, find_data, 0); /*查询到该节点*/
	if (p) /*若p!=NULL,表明已经找到该节点*/
	{
		int i;
		while (1)
		{
			i = -1;
			system("cls");
			toxy(35, 12);
			printf("==================================================");
			toxy(44, 14);
			printf("欢迎使用学生综合测评系统(学生端)");
			toxy(47, 16);
			printf("%15s %-10s", p->num, p->name);
			toxy(48, 18);
			printf("1.成绩查询");
			printf("\t2.成绩申诉");
			toxy(48, 20);
			printf("3.返回登录");
			printf("\t0.退出系统");
			toxy(50, 22);
			printf("请输入对应序号[0-3]：");
			toxy(35, 24);
			printf("==================================================");
			toxy(60, 25);
			scanf("%d", &i);
			switch (i) {
			case 1:
				system("cls"); 
				toxy(44, 10);
				printf("欢迎使用学生综合测评系统(学生端)");
				toxy(56,12);
				printf("成绩查询\n");
				printf("\t\t\t   ");
				printf(HEADER0);
				printscore(p);
				printf("\t\t\t   ");
				printf(END);
				toxy(52, 24);
				system("pause"); 
				system("cls"); 
				break;
			case 2:
				system("cls"); 
				Stu_score_feedback(p); 
				break;
			case 3:
				system("cls");  
				goto temp_stu; 
				break;
			case 0:
				exit(0);
			default:
				Wrong(0, 3); 
				toxy(52, 20);
				system("pause"); 
				char wrg[100];
				gets(wrg);
				system("cls");
			}

		}
	}
	else
	{
		getchar();
		printf("\n\n\t\t\t\t");
		printf("学号 %s 不存在，要不要换一个呢？(y/n):", find_data);
		scanf("%c", &chy);
		if (chy == 'y' || chy == 'Y') {
			system("cls");
			goto temp_stu;
		}
		else {
			system("cls");
			getchar();
			return;
		}
	}
}
//------------------------关于我们----------------------------------
void about_us() {
	color(14);
	toxy(35, 12);
	printf("==================================================");
	toxy(53,14);
	printf("关  于  我  们");
	toxy(35, 16);
	printf("    本系统是为方便学生信息和成绩管理而设计的学生综");
	toxy(35, 17);
	printf("合测评系统。系统基于C语言编写，分为教师端和学生端，");
	toxy(35, 18);
	printf("教师端可方便教师管理学生信息及成绩，了解学生发展状");
	toxy(35, 19);
	printf("况，学生端查询成绩并可对自己的成绩疑问向老师进行申");
	toxy(35, 20);
	printf("诉反馈留言。该系统界面美观，菜单选项清晰明了，使用");
	toxy(35, 21);
	printf("便利，可以极大提高学校管理效率。");
	toxy(35, 22);
	printf("注：教师端初始密码为123456，请及时修改密码。");
	toxy(61, 23);
	printf("Powered by Edward_du&ssj");
	toxy(76, 24);
	printf("2019.6.11");
	toxy(35, 26);
	printf("==================================================");

}
//------------------------main函数----------------------------------
int main() {
	Stu* l;      /*定义链表*/
	FILE* fp, * fpp;    /*文件指针*/
	int select;     /*保存选择结果变量*/
	char ch;     /*保存(y,Y,n,N)*/
	int count = 0; /*保存文件中的记录条数（或结点个数）*/
	Stu* p, * r;   /*定义记录指针变量*/


	l = (Stu*)malloc(sizeof(Stu));
	if (!l)
	{
		printf("\n 内存申请失败！请尝试获取更高权限！ "); /*如没有申请到，打印提示信息*/
		return;             /*返回主界面*/
	}
	l->next = NULL;
	r = l;
	fp = fopen("student_info.dat", "ab+"); /*以追加方式打开一个二进制文件，可读可写，若此文件不存在，会创建此文件*/
	if (fp == NULL)
	{
		printf("\n=====>无法打开文件，请重试！\n");
		exit(0);
	}

	fpp = fopen("score_feedback.dat", "ab+"); /*以追加方式打开一个二进制文件，可读可写，若此文件不存在，会创建此文件*/
	if (fpp == NULL)
	{
		printf("\n=====>无法打开文件，请重试！\n");
		exit(0);
	}

	while (!feof(fp))
	{
		p = (Stu*)malloc(sizeof(Stu));
		if (!p)
		{
			printf("\n 内存申请失败！请尝试获取更高权限！ \n");    /*没有申请内存成功*/
			exit(0);       /*退出*/
		}

		if (fread(p, sizeof(Stu), 1, fp) == 1) /*一次从文件中读取一条教师人事记录*/
		{
			p->next = NULL;
			r->next = p;
			r = p;                            /*r指针向后移一个位置*/
			count++;
		}
	}

	fclose(fp); /*关闭文件*/
	fclose(fpp);
	system("mode con cols=120");
	main_menu(l, p, r);

}