#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<iostream>
#include<stdlib.h>

#include<time.h>
#include <ctime>   
#include <sys/types.h>    
#include <sys/stat.h> 

using namespace std;

#define dy20 printf("======================\n")
#define L_subject 101
#define Num_Stuclass 40
#define Num_Homework 50
char Homework_File[100] = "F:\\C pj\\Study Drak assisst\\Files Rescoure\\homework.txt";
char Class_File[100] = "F:\\C pj\\Study Drak assisst\\Files Rescoure\\weekclass.html";
char AD_File[100] = "F:\\C pj\\Study Drak assisst\\Files Rescoure\\AD.txt";

struct stuclass
{

	float xuefen;
	char shuxing[L_subject];
	char kemu[L_subject];
	int week;
	int xingqi;		//定位
	int jieci;		//定位
	char location[L_subject];
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
struct Homework *ph = puttemp;

void PutTodayClass(void);
void PutTomorrowClass(void);

void PutHomework();

void AD(void);

void ReadClassHTML(void);
void ReadHomework(void);

void CalculateHomework(void);
int CalculateDay(int i);
int CalculateTime(int i);

void SystemTime(void);
int CaculateNowWeekday(int y, int m, int d);
int CaculateTermWeek(void);
void FileModTime(char filename[], const char frontstr[]);

int ReadClass(FILE* fp, char StoreClass[50]);
int ReadStar(FILE* fp, char address[L_subject]);
int ReadDate(FILE* fp);

void Enter(FILE* fp, int EnterNum);
void AutoSpace(int strlength);
void CutConstCharPart(char Res_str[], char store_str[], int from, int to);
