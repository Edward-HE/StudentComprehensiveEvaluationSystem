#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<conio.h>


int saveflag = 0;

typedef struct student {
	int num;			//学号
	char name[15];		//学生名字
	char sex[4];		//性别
	char address[100];	//家庭住址
	char phone[14];		//电话
};

typedef struct studata {
	int num;							//学号
	int chinese, math, english, pinde;	//语、数、英、思想品德成绩
	int rank_main, rank_all;			//语数英三科名次，综合测评名次
	int huping, teacher;				//互评分，教师评分
	float average, score_all;			//三科平均分，综合总分
};

void main_menu() {  //首页面
	printf("=============================================\n");
	printf("\n\t      学生综合测评系统\n\n");
	printf("\t1.教师账户");
	printf("\t2.学生账户\n\n");
	printf("\t3.关于我们");
	printf("\t4.退出系统\n\n");
	printf("\t      请输入对应序号: \n");
	printf("\n=============================================\n");
}

void teacher_menu() {
	printf("=============================================\n");
	printf("\n\t      你是一个\n\n");
	printf("\t1.注	册");
	printf("\t2.登	录\n\n");
	printf("\t3.关于我们");
	printf("\t4.退出系统\n\n");
	printf("\t      请输入对应序号: \n");
	printf("\n=============================================\n");
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
	//users_create();
	int flag_login;
	system("color 8F");
	main_menu();
	int option;
	scanf("%d", &option);
	switch (option) {

	case 1:system("cls"); teacher_menu(); system("cls"); //goto beginning;
	case 2:system("cls"); stu_menu(); system("cls");
		while (1) {
			if (flag_login == 0)
				//goto beginning;
				printf("dd");
			else
				break;
		}
	case 3:system("cls"); about_us(); main();
	}
}