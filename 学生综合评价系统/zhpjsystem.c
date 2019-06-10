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
#define HEADER2 "     |     学 号     |   姓 名   |\n"
#define FORMAT2 "     |%-15s|%-10s |\n"
#define HEADER3 "     |  家 庭 住 址  |"
#define FORMAT3 "     %-35s |\n"
#define HEADER4 "     |语文|数学|英语|平均分|名次1|\n"
#define FORMAT4 "     |%-4d|%-4d|%-4d|%-6lf|%-4d |\n"
#define HEADER5 "     |思品|互评|师评|综合分|名次2|\n"
#define FORMAT5 "     |%-4d|%-4d|%-4d|%-6lf|%-4d |\n"


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
void Wrong(int a, int b);
void main_menu(Stu* l, Stu* p, Stu* r);
void teacher_account(Stu* l, Stu* p, Stu* r);
void stu_menu();
void about_us();
int pswd_check();
char mod_pswd();
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
int main();

void Wrong(int a, int b) /*输出按键错误信息*/
{
	system("cls");
	printf("=========================================\n");
	printf("\n\n\n请选择%d-%d中的选项之一，请不要输入其他选项！\n\n\n", a, b);
	printf("\n=========================================\n\n\n\n");
}

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
/*************************************************************
作用：用于定位链表中符合要求的节点，并返回指向该节点的指针
参数：find_data表示要查找的内容，type_find表示查找方式
	  在单链表l中查找;
**************************************************************/
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

void Sort(Stu* l, int sel)
{
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
	Save(l);
	system("cls");
	return;
}

//----------------------------------------首页面----------------------------------------
void main_menu(Stu* l, Stu* p, Stu* r) {
	char option;
	while (1) {
		printf("=============================================\n");
		printf("\n\t      学生综合测评系统\n\n");
		printf("\t1.教师账户");
		printf("\t2.学生账户\n\n");
		printf("\t3.关于我们");
		printf("\t4.退出系统\n\n");
		printf("\t      请输入对应序号: \n");
		printf("\n=============================================\n");
		p = r;
		scanf("%c", &option);
		switch (option) {
		case '1':system("cls"); teacher_account(l, p, r); system("cls"); break;
		case '2':system("cls"); stu_menu(); system("cls"); break;
		case '3':system("cls"); about_us(); system("pause"); getchar(); system("cls"); break;
		case '4':exit(0);
		default:Wrong(1, 4); system("pause"); getchar(); system("cls"); break;
		}
	}
}
//----------------------------------------教师端主菜单----------------------------------------
void teacher_account(Stu* l, Stu* p, Stu* r) {
	pswd_create();			//每次进入后确认一次是否存在密码文件		
	int i;
	while (1) {
		printf("=============================================\n");
		printf("\n\t      欢迎使用\n\n");
		printf("\t1.登	录");
		printf("\t2.修改密码\n\n");
		printf("\t3.返回主菜单");
		printf("\t4.退出系统\n\n");
		printf("\t      请输入对应序号: \n");
		printf("\n=============================================\n");
		scanf("%d", &i);
		switch (i) {
		case 1:system("cls"); login_teacher(l, p, r); break;
		case 2:system("cls"); mod_pswd(); break;
		case 3:system("cls"); getchar(); return;
		case 4:exit(0);
		default:Wrong(1, 4); system("pause"); system("cls");
		}

	}
}
//----------------------------------------教师端登录----------------------------------------
void login_teacher(Stu* l, Stu* p, Stu* r) {
	char a[16];				//暂时储存密码的数组	
	char a1[16] = { "123456" }; //储存默认密码的数组
	FILE* fp;
	fp = fopen("pswd_teacher", "r"); //打开储存密码的文件
	fgets(a, 16, fp);	 //读取密码到数组a中
	printf("===================================\n");
	printf("\t教师登录界面\n");
	if (strcmp(a, a1) == 0) {	 //判断是否为初始密码
		printf("  您仍在使用初始密码，请及时更改密码\n");
	}
	printf("\n请输入密码：");
	pswd_check();
	if (check_result == 1) {
		printf("\n\n登录成功！即将进入教师端\n");
		printf("\n===================================\n");
		system("pause");
		system("cls");
		teacher_main_menu(l, p, r);
	}
	fclose(fp);
}

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
			return (check_result);
		}
		else {
			printf("\n密码不正确，请重新输入，您还有%d次机会\n", i);
			printf("请输入密码：");
			i--;
			scanf("%s", &a);
		}
		if (i == 0) {
			printf("您已输错超过3次，即将返回主界面\n");
			printf("\n===================================\n");
			system("pause");
			system("cls");
			main();
		}
	}
	fclose(fp);
}

char mod_pswd() {	//修改密码
	char b[16];		//临时储存新密码的变量
	FILE* fp;

	printf("===================================\n");
	printf("\t教师端密码修改\n");
	printf("请输入旧密码：");
	pswd_check();
	printf("请输入新密码：");
	fp = fopen("pswd_teacher", "w");
	scanf("%s", &b);
	fputs(b, fp);
	fclose(fp);
	printf("请确认新密码：");
	pswd_check();
	if (check_result == 1) {
		printf("\n\n修改密码成功！\n");
		printf("\n===================================\n");
		system("pause");
		system("cls");
		return;
	}
}


void Disp(Stu* l, int i)  /*显示单链表l中存储的教师记录，内容为teacher结构中定义的内容*/
{
	Stu* p;
	p = l->next; /*l存储的是单链表中头结点的指针，该头结点没有存储教师信息，指针域指向的后继结点才有教师信息*/

	if (!p)  /*p==NULL,NUll在stdlib中定义为0*/
	{
		printf("\n=====>Not teacher record!\n");
		getchar();
		return;
	}

	printf("\n\n");
	printf(HEADER);
	printf(HEADER0);
	while (p)    /*逐条输出链表中存储的教师信息*/
	{
		if (i == 0)
			printinfo(p);
		else
			printscore(p);
		p = p->next;  /*移动直下一个结点*/
		printf(END);
	}
	getchar();
}

void printinfo(Stu* pp) /*格式化输出表中数据*/
{
	Stu* p;
	p = pp;
	printf(HEADER1);
	printf(FORMAT1, DATA1);
	printf(HEADER3);
	printf(FORMAT3, DATA3);
}

void printscore(Stu* pp) /*格式化输出表中数据*/
{
	Stu* p;
	p = pp;
	printf(HEADER2);
	printf(FORMAT2, DATA2);
	printf(HEADER4);
	printf(FORMAT4, DATA4);
	printf(HEADER5);
	printf(FORMAT5, DATA5);
}

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

void Add_info(Stu* l)
{
	Stu* p, * r, * s;  /*实现添加操作的临时的结构体指针变量*/
	char ch, flag = 0, num[15];
	r = l;
	s = l->next;
	system("cls");
	Disp(l, 0); /*先打印出已有的教师信息*/
	while (r->next != NULL)
		r = r->next; /*将指针移至于链表最末尾，准备添加记录*/
	while (1) /*一次可输入多条记录，直至输入编号为0的记录结点添加操作*/
	{

		while (1) /*输入编号，保证该编号没有被使用，若输入编号为0，则退出添加记录操作*/
		{
			stringinput(num, 15, "请输入\n学号："); /*格式化输入编号并检验*/
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
				printf("=====>学号 %s 的信息已被录入，要不要换一个呢？(y/n):", num);
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
		stringinput(p->name, 10, "姓名：");
		printf("性别：");
		scanf("%s", p->sex);
		printf("家庭住址：");
		scanf("%s", p->address);
		printf("电话：");
		scanf("%s", p->phone);
		p->chinese = p->math = p->english = p->average = p->pinde = p->rank_all = p->rank_main = p->score_all = p->teacher = p->huping = -1;

		p->next = NULL; /*表明这是链表的尾部结点*/
		r->next = p;  /*将新建的结点加入链表尾部中*/
		r = p;
	}

	return;
}

void Modify_info(Stu* l)
{
	Stu* p, * t;  /*实现添加操作的临时的结构体指针变量*/
	char find_data[20];
	char ch[30] = "\0", chy;
temp:
	if (!l->next)
	{
		system("cls");
		printf("\n=====>No teacher record!\n");
		getchar();
		return;
	}
	system("cls");
	Disp(l, 0);
	stringinput(find_data, 15, "请输入要修改学生的学号："); /*输入并检验该编号*/
	p = Locate(l, find_data, 0); /*查询到该节点*/
	if (p) /*若p!=NULL,表明已经找到该节点*/
	{
		system("cls");
		printf("已找到该生信息：\n");
		printf(HEADER1);
		printf(FORMAT1, DATA1);
		printf(HEADER3);
		printf(FORMAT3, DATA3);
		printf("\n请根据提示输入要修改的信息，输入0则不修改此项：");
		printf("\n学号：");
		gets();
		gets(ch);
		if (strcmp(ch, "0") != 0) {
			while (t = Locate(l, ch, 0)) {
				printf("\n此学号已存在，请尝试其他学号！");
				printf("\n学号：");
				gets(ch);
			}
			strcpy(p->num, ch);
		}
		printf("\n名字：");
		gets(ch);
		if (strcmp(ch, "0") != 0)
			strcpy(p->name, ch);
		printf("\n性别：");
		gets(ch);
		if (strcmp(ch, "0") != 0)
			strcpy(p->sex, ch);
		printf("\n家庭住址：");
		gets(ch);
		if (strcmp(ch, "0") != 0)
			strcpy(p->address, ch);
		printf("\n电话：");
		gets(ch);
		if (strcmp(ch, "0") != 0)
			strcpy(p->phone, ch);
		printf("\n=====>修改成功！修改后信息为：\n");
		printf(HEADER1);
		printf(FORMAT1, DATA1);
		printf(HEADER3);
		printf(FORMAT3, DATA3);
		Save(l);

		system("pause");
		system("cls");
		return;
	}
	else
	{
		getchar();
		printf("=====>学号 %s 的信息还未被录入，要不要换一个呢？(y/n):", find_data);
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

void Del(Stu* l)
{
	int sel;
	Stu* p, * r;
	char find_data[20], chy;
temp_del:
	if (!l->next)
	{
		system("cls");
		printf("\n=====>No teacher record!\n");
		getchar();
		return;
	}
	system("cls");
	Disp(l, 0);
	printf("\n        =====>1 按照学号删除   =====>2 按照姓名删除   =====>0 返回上一级\n");
	printf("       请输入你的选择[0,2]:");
	scanf("%d", &sel);
	if (sel == 0)
		return;
	else if (sel == 1)
	{
		stringinput(find_data, 15, "请输入要删除学生的学号：");
		p = Locate(l, find_data, 0);
	}
	else if (sel == 2) /*先按姓名查询到该记录所在的节点*/
	{
		stringinput(find_data, 10, "请输入要删除学生的姓名：");
		p = Locate(l, find_data, 1);
	}
	else
	{
		Wrong(1, 2);
		system("pause");
		goto temp_del;
	}
	if (p)  /*p!=NULL*/
	{
		system("cls");
		printf("已找到该生数据：\n");
		printf(HEADER1);
		printf(FORMAT1, DATA1);
		printf(HEADER3);
		printf(FORMAT3, DATA3);
		printf(HEADER4);
		printf(FORMAT4, DATA4);
		printf(HEADER5);
		printf(FORMAT5, DATA5);
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
			printf("\n=====>已成功删除！\n");
			getchar();
			Save(l);
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
		printf("=====>%s 的信息还未被录入，要不要换一个呢？(y/n):", find_data);
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


void Add_score(Stu* l)
{
	Stu* p;  /*实现添加操作的临时的结构体指针变量*/
	char find_data[20];
	char ch;
	if (!l->next)
	{
		system("cls");
		printf("\n=====>No teacher record!\n");
		getchar();
		return;
	}
	system("cls");
	Disp(l, 1);
	while (1) /*一次可输入多条记录，直至输入编号为0的记录结点添加操作*/
	{

		stringinput(find_data, 15, "请输入学号："); /*输入并检验该编号*/
		if (strcmp(find_data, "0") == 0) /*输入为0，则退出添加操作，返回主界面*/
		{
			Save(l);
			return;
		}
		p = Locate(l, find_data, 0); /*查询到该节点*/
		if (p) /*若p!=NULL,表明已经找到该节点*/
		{
			printf("学号：%s\t姓名：%s\n", p->num, p->name);
			printf("语文：");
			scanf("%d", &p->chinese);
			printf("数学：");
			scanf("%d", &p->math);
			printf("英语：");
			scanf("%d", &p->english);
			printf("思想品德：");
			scanf("%d", &p->pinde);
			printf("互评：");
			scanf("%d", &p->huping);
			printf("师评：");
			scanf("%d", &p->teacher);

			p->average = ((p->chinese) + (p->math) + (p->english)) / 3;//计算平均分
			/*计算综合测评得分，语数英平均分60%，思想品德10%，互评10%，师评20%，*/
			p->score_all = (p->average) * 0.6 + (p->huping) * 0.1 + (p->pinde) * 0.1 + (p->teacher) * 0.2;

			printf("平均成绩：%.2lf", p->average);
			printf("综合测评得分：%.2lf", p->score_all);
		}
		else
		{
			getchar();
			printf("=====>学号 %s 的信息还未被录入，要不要换一个呢？(y/n):", find_data);
			scanf("%c", &ch);
			if (ch == 'y' || ch == 'Y')
				continue;
			else
				return;
		}
	}
}

void Modify_score(Stu* l)
{
	Stu* p, * t;  /*实现添加操作的临时的结构体指针变量*/
	char find_data[20];
	char chy;
	int tmp;
temp:
	if (!l->next)
	{
		system("cls");
		printf("\n=====>No teacher record!\n");
		getchar();
		return;
	}
	system("cls");
	Disp(l, 1);
	stringinput(find_data, 15, "请输入要修改学生的学号："); /*输入并检验该编号*/
	p = Locate(l, find_data, 0); /*查询到该节点*/
	if (p) /*若p!=NULL,表明已经找到该节点*/
	{
		system("cls");
		printf("已找到该生成绩：\n");
		printf(HEADER2);
		printf(FORMAT2, DATA2);
		printf(HEADER4);
		printf(FORMAT4, DATA4);
		printf(HEADER5);
		printf(FORMAT5, DATA5);
		printf("\n请根据提示输入要修改的成绩，输入-1则不修改此项：");
		printf("\n语文：");
		scanf("%d", &tmp);
		if (tmp != -1)
			p->chinese = tmp;
		printf("\n数学：");
		scanf("%d", &tmp);
		if (tmp != -1)
			p->math = tmp;
		printf("\n英语：");
		scanf("%d", &tmp);
		if (tmp != -1)
			p->english = tmp;
		printf("\n思想品德：");
		scanf("%d", &tmp);
		if (tmp != -1)
			p->pinde = tmp;
		printf("\n互评：");
		scanf("%d", &tmp);
		if (tmp != -1)
			p->huping = tmp;
		printf("\n师评：");
		scanf("%d", &tmp);
		if (tmp != -1)
			p->teacher = tmp;
		p->average = ((p->chinese) + (p->math) + (p->english)) / 3;//计算平均分
			/*计算综合测评得分，语数英平均分60%，思想品德10%，互评10%，师评20%，*/
		p->score_all = (p->average) * 0.6 + (p->huping) * 0.1 + (p->pinde) * 0.1 + (p->teacher) * 0.2;
		printf("\n=====>修改成功！修改后信息为：\n");
		printf(HEADER2);
		printf(FORMAT2, DATA2);
		printf(HEADER4);
		printf(FORMAT4, DATA4);
		printf(HEADER5);
		printf(FORMAT5, DATA5);
		Save(l);

		system("pause");
		system("cls");
		return;
	}
	else
	{
		getchar();
		printf("=====>学号 %s 的信息还未被录入，要不要换一个呢？(y/n):", find_data);
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

void teacher_main_menu(Stu* l, Stu* p, Stu* r) {
	int option;
	while (1) {
		printf("===================================\n");
		printf("\n\t欢迎使用学生综合测评系统\n\n");
		printf("-----学生信息管理-----   -----学生成绩管理-----\n");
		printf("|                    |   |                    |\n");
		printf("|  1. 添加学生信息   |   |  5. 录入成绩数据   |\n");
		printf("|  2. 修改学生信息   |   |  6. 修改成绩数据   |\n");
		printf("|  3. 删除学生信息   |   |  7. 查看成绩信息   |\n");
		printf("|  4. 查看学生信息   |   |  8. 查看成绩反馈   |\n");
		printf("|                    |   |                    |\n");
		printf("----------------------   ----------------------\n\n");
		printf("   9. 排名（平均分）       10. 排名（综合分）\n");
		printf("  11. 显示全部学生数据      0. 退出系统\n");
		printf("\n请输入你的选择（0--11）：\n");
		printf("\n===================================\n");

		p = r;
		scanf("%d", &option);
		switch (option)
		{
		case 0:exit(0);
		case 1:Add_info(l); Sort(l, 0); system("cls"); break;
		case 2:Modify_info(l); Sort(l, 0); system("cls"); break;
		case 3:Del(l); system("cls"); break;
		case 4:system("cls"); Sort(l, 0); Disp(l, 0); system("pause"); system("cls"); break;
		case 5:Add_score(l); Sort(l, 1); Sort(l, 2); Sort(l, 0); system("cls"); break;
		case 6:Modify_score(l); Sort(l, 1); Sort(l, 2); Sort(l, 0); system("cls"); break;
		case 7:system("cls"); Disp(l, 1); system("pause"); system("cls"); break;
		case 8:
		case 9:Sort(l, 1); system("cls"); Disp(l, 1); system("pause"); system("cls"); break;
		case 10:Sort(l, 2); system("cls"); Disp(l, 1); system("pause"); system("cls"); break;
		case 11:Sort(l, 0); system("cls");
		default:Wrong(0, 11); system("pause"); system("cls"); break;
		}

	}


	system("pause");
}

void stu_menu() 
{
	printf("===================================\n");
	printf("\t学生系统界面\n");
	printf("\n请输入学号：");

}
void about_us() {
	printf("==============================================\n");
	printf("\n\t      关  于  我  们\n\n");
	printf("      系统为适用于小学生的四则运算练习系统，\n");
	printf("  系统由C语言编写，可以进行100以内的四则运算\n");
	printf("  练习，每次练习可以任意指定题目数量，每题有\n");
	printf("  两次答题机会，第一次答对得满分，第二次答对\n");
	printf("  得一半的分，答错不得分。练习后可查看每次练\n");
	printf("  习的错题。\n");
	printf("\n\t   Powered by Edward_du\n");
	printf("\n\t   \t2019.4.19\n");
	printf("\n==============================================\n");

}

int main() {
	Stu* l;      /*定义链表*/
	FILE* fp;    /*文件指针*/
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
	//printf("\n=====>open file sucess,the total records number is : %d.\n", count);

	system("color 8F");
	main_menu(l, p, r);

}