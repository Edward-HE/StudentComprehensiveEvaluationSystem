#include<stdio.h>
#include<string.h>
#include<windows.h>
#include<conio.h>
#include<stdlib.h>

void Wrong();
void main_menu();
void teacher_menu();
void stu_menu();
void about_us();
int pswd_check();
char mod_pswd();
void login_teacher();
void pswd_create();

int flag_pswd = 0;			//表示教师账户初始密码是否被修改，1是被修改
int check_result = 0;	//记录检测结果的变量

typedef struct student {
	int num;			//学号
	char name[15];		//学生名字
	char sex[4];		//性别
	char address[100];	//家庭住址
	char phone[14];		//电话
}Stu;

typedef struct studata {
	int num;							//学号
	int chinese, math, english, pinde;	//语、数、英、思想品德成绩
	int rank_main, rank_all;			//语数英三科名次，综合测评名次
	int huping, teacher;				//互评分，教师评分
	float average, score_all;			//三科平均分，综合总分
}StuDt;

void Wrong() /*输出按键错误信息*/
{
	system("cls");
	printf("=========================================\n");
	printf("\n\n\n请选择1-4四个选项之一，请不要输入其他选项！\n\n\n");
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

void main_menu() {  //首页面
	printf("=============================================\n");
	printf("\n\t      学生综合测评系统\n\n");
	printf("\t1.教师账户");
	printf("\t2.学生账户\n\n");
	printf("\t3.关于我们");
	printf("\t4.退出系统\n\n");
	printf("\t      请输入对应序号: \n");
	printf("\n=============================================\n");
	int option;
	scanf("%d", &option);
	switch (option) {
	case 1:system("cls"); teacher_menu(); system("cls");
	case 2:system("cls"); stu_menu(); system("cls");
	case 3:system("cls"); about_us(); main();
	case 4:exit(0);
	}
}

void teacher_menu() {
	pswd_create();
	FILE* fp_pswd;
	int i;
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
	case 1:system("cls"); login_teacher();
	case 2:system("cls"); mod_pswd();
	case 3:system("cls"); main();
	case 4:exit(0);
	default:Wrong(); system("pause"); system("cls"); teacher_menu();
	}
}

void login_teacher() {
	char a[16];
	FILE* fp;
	fp = fopen("pswd_teacher", "r"); //打开储存密码的文件
	fread(&a, sizeof(a), 1, fp);	 //读取密码到数组a中	
	printf("===================================\n");
	printf("\t教师登录界面\n");
	if (strcmp(a,"123456")==0) {
		printf("  您仍在使用初始密码，请及时更改密码\n");
	}
	printf("\n请输入密码：");
	pswd_check();
	if (check_result == 1) {
		printf("\n\n登录成功！即将进入教师端\n");
		printf("\n===================================\n");
		system("pause");
		system("cls");
		teacher_menu();
	}
	fclose(fp);
}

int pswd_check() {		//检测密码正确性
	char a[16],b[16];
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
		teacher_menu();
	}
}

void stu_menu() {

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
	system("pause");
	system("cls");
}

int main() {
	int flag_;
	system("color 8F");
	main_menu();

}