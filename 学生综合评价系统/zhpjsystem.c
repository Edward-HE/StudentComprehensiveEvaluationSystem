#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<conio.h>


int saveflag = 0;

typedef struct student {
	int num;//学号
	char name[15];//学生名字
	char sex[4];//性别
	char address[100];//家庭住址
	char phone[14];//电话
};

typedef struct studata {
	int num;//学号
	int chinese, math, english, pinde;//语、数、英、思想品德成绩
	int rank_main, rank_all;//语数英三科名次，综合测评名次
	int huping, teacher;//互评分，教师评分
	float average, score_all;//三科平均分，综合总分
};

