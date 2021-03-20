#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<iostream>
#include<stdlib.h>

#include<time.h>
#include <ctime>   
#include <sys/types.h>    
#include <sys/stat.h> 
#include<string.h>

using namespace std;

#define dy20 printf("======================\n")
#define L_subject 101
#define Num_Stuclass 40
#define Num_Homework 50
char Homework_File[100] = "F:\\C pj\\Study Drak assisst\\Files Rescoure\\homework.txt";
char Class_File[100] = "F:\\C pj\\Study Drak assisst\\Files Rescoure\\weekclass.html";
char AD_File[100] = "F:\\C pj\\Study Drak assisst\\Files Rescoure\\AD.txt";

struct Stuclass
{
	float xuefen;
	char shuxing[L_subject];
	char mingcheng[L_subject];
	char week[6]="0";
	int xingqi;
	int jieci;
	char didian[L_subject];
}stuclass[Num_Stuclass];

struct DateStuct
{
	int day;
	int month;
	int year;
	int weekday;
	int hour;
	int minute;
}Date;

struct Homework
{
	int month;
	int day;
	int hour;
	int minute;
	char subject[L_subject] = "0";
	char title[L_subject] = "0";
	char place[L_subject] = "0";
	int strlong;
	int lasttime;
}homework[Num_Homework], puttemp[Num_Homework];

//PreLoad Files Function
void ReadClassHTML(void);
void ReadClass(FILE* fp, float rxuefen, char rshuxing[L_subject], char rmingcheng[L_subject], char rweek[6], char rdidian[L_subject]);
void ReadHomework(void);
//Output msg Function
void PutClass(const char JinorMing[3]);
void PutHomework();
//AD
void AD(void);
//Homework time calculate function
void CalculateHomework(void);
int CalculateDay(int i);
int CalculateTime(int i);
int ReadHomeworkDate(FILE* fp);
//Time calculate function
void SystemTime(void);
int CaculateNowWeekday(int y, int m, int d);

void FileModTime(char filename[], const char frontstr[]);

//Custom function
int ReadUntilTarget(FILE* fp, char address[L_subject], char target);
void Enter(FILE* fp, int EnterNum);
void AutoSpace(int strlength);
void CutConstCharPart(char Res_str[], char store_str[], int from, int to);
