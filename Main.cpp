#include"SDA.h"


int main(void)
{
MainStart:
	system("mode con cols=50 lines=70");			//设置命令行窗体大小为50个字符宽，70行长
	system("color 70");								//将命令行设置成白色背景(e),黑色字体(0)
	ReadClassHTML();								//读取本地课表HTML文件
	ReadHomework();									//读取本地作业
	cout << "今天按[1]明天请随意\n>";
	char IsToday = getchar();
	getchar();										//消除空格
	system("cls");									//清屏
	SystemTime();									//计算并输出当前系统时间
	dy20;
	if (IsToday == '1')
	{
		PutClass("今");								//如果输入[1]，则输出"今"天课表
	}
	else
	{
		PutClass("明");								//如果输入不为[1]，则输出"明"天课表
	}
	CalculateHomework();							//计算本地作业各种时间
	dy20;
	PutHomework();									//输出作业到命令行
	dy20;
	AD();											//广告59s
	dy20;
	FileModTime(Class_File, "本地课表HTML更新日期");//输出本地HTML文件的更新时间
	FileModTime(Homework_File, "本地作业列表更新日期");//输出本地作业列表文件的更新时间
	cout << "\n再来一次请按[1]" << endl;
	char end = getchar();
	getchar();
	if (end == '1')
	{
		goto MainStart;
	}
	else
	{
		return 0;
	}
}

void ReadClassHTML(void)
{

	FILE* fp;
	fopen_s(&fp, Class_File, "r");
	int w;					//星期
	int j;					//节次
	int n = 0;				//结构体序号
	Enter(fp, 10);			//按10次回车，跳转到11行
	for (j = 1; j <= 5; j++)//从第1节遍历到第5节
	{
		for (w = 1; w <= 7; w++, n++)//从星期1遍历到星期7
		{

			ReadClass(fp, stuclass[n].xuefen, stuclass[n].shuxing, stuclass[n].mingcheng, stuclass[n].week, stuclass[n].didian);	//从HTML中读取课程的各种信息
			stuclass[n].xingqi = w;		//写入课程的星期
			stuclass[n].jieci = j;		//写入课程的节次
			Enter(fp, 5);				//回车5行，跳到下一天的同一节课
		}
		Enter(fp, 8);					//回车8行，调到下一节课
	}
	fclose(fp);
	for (int i = 28; i <= Num_Stuclass; i++)
	{
		if (stuclass[i].xingqi == 2 && stuclass[i].jieci == 5 && strcmp(stuclass[i].mingcheng, "0") != 0)		//如果星期2，第5节，并且不是空堂的话
		{
			strcpy(stuclass[i].mingcheng, "自选实体课程");														//那就重命名为"自选实体课程"
		}
		else if (stuclass[i].xingqi == 7 && stuclass[i].jieci == 5 && strcmp(stuclass[i].mingcheng, "0") != 0)	//如果星期7，第5节，并且不是空堂的话
		{
			strcpy(stuclass[i].mingcheng, "自选网络课程");														//那就重命名为"自选网络课程"
		}
	}

}
void ReadClass(FILE* fp, float rxuefen, char rshuxing[L_subject], char rmingcheng[L_subject], char rweek[6], char rdidian[L_subject])
{
	char temp;	//读取文件时的缓存变量
	int i;		//i用于计数'>'，j用于计数'"'
	while (1)
	{
		temp = fgetc(fp);
		if (temp == '"')
		{
			break;
		}
		else if (temp == '\n')
		{
			fseek(fp, -2, 1);
			rxuefen = 0;
			strcpy(rshuxing, "\\");
			strcpy(rmingcheng, "\\");		//名称改为'\'
			strcpy(rdidian, "");			//地点不填
			return;
		}
	}
	fseek(fp, 10, 1);				//快进到课程学分：后面
	char Rxuefen[10];					//创建一个变量用以临时储存学分
	ReadUntilTarget(fp, Rxuefen, '<');			/*读取课程学分*/
	rxuefen = atof(Rxuefen);			//将学分从字符型转换为浮点型	
	strcpy(Rxuefen, "0");				//清空缓存数组
	fseek(fp, 17, 1);				//快进到课程属性：后面
	ReadUntilTarget(fp, rshuxing, '<');			/*读取课程属性*/
	fseek(fp, 14, 1);				//快进到课程名称：后面
	ReadUntilTarget(fp, rmingcheng, '<');		/*读取课程名称*/
	fseek(fp, 16, 1);				//快进到上课时间：第后面
	ReadUntilTarget(fp, rweek, ' ');			/*读取课程周次*/
	fseek(fp, 31, 1);				//快进到上课地点：后面
	ReadUntilTarget(fp, rdidian, '"');			/*读取课程地点*/
	if (strcmp(rdidian, "") == 0)
	{
		strcpy(rdidian, "None");	//如果没有上课地点的话，手动赋值"None"
	}
}
void ReadHomework(void)
{
	FILE* fp;
	fopen_s(&fp, Homework_File, "r");
	Enter(fp, 4);		//跳过4行注释
	int i;
	int feedback;
	for (i = 0;; i++)
	{
		ReadUntilTarget(fp, homework[i].place, '*');										//读取作业的平台
		ReadUntilTarget(fp, homework[i].subject, '*');										//读取作业的科目
		homework[i].strlong = strlen(homework[i].place) + strlen(homework[i].subject);		//赋值作业的字符长度，用于等下填充空格
		feedback = ReadUntilTarget(fp, homework[i].title, '*');								//读取作业的题目
		if (feedback == 10)						//返回值为10意味着文件读完了
		{
			break;
		}
		homework[i].month = ReadHomeworkDate(fp);													//读取作业的月
		homework[i].day = ReadHomeworkDate(fp);														//读取作业的日
		homework[i].hour = ReadHomeworkDate(fp);													//读取作业的小时
		homework[i].minute = ReadHomeworkDate(fp);													//读取作业的分钟
		if (feedback == 10)						//返回值为10意味着文件读完了
		{
			break;
		}
	}
	fclose(fp);
}

void PutClass(const char JinorMing[3])
{
	int i, t, NoneClass;

	int tempoptweekday;
	char Classweek[10];
	if (strcmp(JinorMing, "今") == 0)
	{
		tempoptweekday = Date.weekday;
	}
	else if (strcmp(JinorMing, "明") == 0)
	{
		if (Date.weekday == 7)
		{
			tempoptweekday = 1;
		}
		else
		{
			tempoptweekday = Date.weekday + 1;
		}
	}
	for (i = 0, NoneClass = 0; i < Num_Stuclass; i++)
	{
		if (stuclass[i].xingqi == tempoptweekday && strcmp(stuclass[i].mingcheng, "None") == 0)
		{
			NoneClass++;			//空节次计算器
		}
	}
	for (i = 0; i <= Num_Stuclass; i++)			//读取当前HTML中的课表周数
	{
		if (strcmp(stuclass[i].week,"0") )
		{
			strcpy(Classweek , stuclass[i].week);
			break;
		}
	}
	switch (tempoptweekday)
	{
	case 1:cout << JinorMing << "天は第" << Classweek << "星期一：" << endl; break;
	case 2:cout << JinorMing << "天は第" << Classweek << "星期二：" << endl; break;
	case 3:cout << JinorMing << "天は第" << Classweek << "星期三：" << endl; break;
	case 4:cout << JinorMing << "天は第" << Classweek << "星期四：" << endl; break;
	case 5:cout << JinorMing << "天は第" << Classweek << "星期五：" << endl; break;
	case 6:cout << JinorMing << "天は第" << Classweek << "星期六：" << endl; break;
	case 7:cout << JinorMing << "天は第" << Classweek << "星期日：" << endl; break;
	}
	if (NoneClass == 5)			//如果为5节空堂，则不输出课程表
	{
		printf("\n");
	}
	else if (NoneClass < 5)		//如果有课，则输出课程表
	{
		for (i = 0, t = 1; i < Num_Stuclass; i++)
		{
			if (stuclass[i].xingqi == tempoptweekday)
			{
				if (t == 1)
					cout << "【第一节】";
				else if (t == 2)
					cout << "【第二节】";
				else if (t == 3)
					cout << "【第三节】";
				else if (t == 4)
					cout << "【第四节】";
				else if (t == 5)
					cout << "【第五节】";
				cout << stuclass[i].mingcheng << "\n          ";
				if (strcmp(stuclass[i].didian, "") != 0)
				{
					cout << '[' << stuclass[i].didian << ']' << endl;	//如果不是空地点那么就输出"[地点]"
				}
				else
				{
					cout << endl;
				}
				t++;
			}
		}
	}
}
void PutHomework()
{
	int i, j;
	for (i = 0; i < Num_Homework; i++)
	{
		puttemp[i] = homework[i];
	}
	int detetivehomework=0;
	for (i = 0; i < Num_Homework; i++,detetivehomework++)
	{
		if (strcmp(puttemp[i].subject, "0") == 0)
		{
			break;
		}
	}
	int maxi[Num_Homework];
	int max;
	for (i = 0; i < detetivehomework; i++)
	{
		max = -32766;
		for (j = 0; j < detetivehomework; j++)
		{
			if (puttemp[j].lasttime > max)
			{
				maxi[i] = j;
				max = puttemp[j].lasttime;
			}
		}
		puttemp[maxi[i]].lasttime = -32760;
	}
	int mini[Num_Homework];
	for (j = 0; j<detetivehomework; j++);
	for (i = 0, j--;j>-1; )
	{
		mini[i] = maxi[j];
		i++;
		j--;
	}
	int day, hour;
	for (j = 0; ; j++)
	{
		if (strcmp(homework[j].subject, "0") == 0)
		{
			break;
		}
		day = (homework[mini[j]].lasttime / 24);
		hour = homework[mini[j]].lasttime - (day * 24);
		cout << "■" << homework[mini[j]].subject;
		if (homework[mini[j]].place[0]!='\0')
		{
			//AutoSpace(strlen(homework[mini[j]].subject));
			AutoSpace(homework[mini[j]].strlong);
			cout << "◆→" << homework[mini[j]].place;
		}
		cout << "\n□" << homework[mini[j]].title << endl;
		if (homework[mini[j]].month == 11 && homework[mini[j]].day == 11 && homework[mini[j]].hour == 11 && homework[mini[j]].minute == 11)
		{
			cout << ">>收作业时间未知" << endl;
		}
		else
		{
			printf(">>%2d月%2d日", homework[mini[j]].month, homework[mini[j]].day);
			if (homework[mini[j]].hour < 10)
			{
				printf("0%d:", homework[mini[j]].hour);
			}
			else
			{
				printf("%d:", homework[mini[j]].hour);
			}
			if (homework[mini[j]].minute < 10)
			{
				printf("0%d", homework[mini[j]].minute);
			}
			else
			{
				printf("%d", homework[mini[j]].minute);
			}

			if (day >= 0 && hour >= 0)
			{
				cout << "收/剩" << day << "天" << hour << "小时" << endl;
			}
			else
			{
				cout << "收/  已过期  " << endl;
			}
		}
	}

}

void AD(void)
{
	FILE* fp;
	fopen_s(&fp, AD_File, "r");
	char str[500];
	while (feof(fp) == 0)
	{
		fgets(str, 499, fp);
		printf("%s", str);
	}
	fclose(fp);
	cout << "\n" << endl;
}

void CalculateHomework(void)
{
	int day;
	int hour;
	for (int i = 0; i <= Num_Homework; i++)
	{
		if (strcmp(homework[i].subject, "0") == 0)
			break;
		day = CalculateDay(i);
		hour = CalculateTime(i);
		homework[i].lasttime = day * 24 + hour;
	}
}
int CalculateDay(int i)
{
	time_t t1;
	time_t t2;
	struct tm HomeworkTime;
	struct tm NowTime;
	memset(&HomeworkTime, 0x0, sizeof(tm));
	HomeworkTime.tm_year = 120;// 2010 年表示为 2010 - 1900 = 110
	HomeworkTime.tm_mon = homework[i].month;
	HomeworkTime.tm_mday = homework[i].day;
	memset(&NowTime, 0x0, sizeof(tm));
	NowTime.tm_year = 120;// 2011 年表示为 2011 - 1900 = 111
	NowTime.tm_mon = Date.month;
	NowTime.tm_mday = Date.day;
	t1 = mktime(&NowTime);
	t2 = mktime(&HomeworkTime);
	int day;
	day = (t2 - t1) / (24 * 3600);
	return day;
}
int CalculateTime(int i)
{
	int ss1, ss2;
	int hour, min;
	int minus;
	ss1 = Date.minute * 60 + Date.hour * 3600;
	ss2 = homework[i].minute * 60 + homework[i].hour * 3600;
	minus = ss2 - ss1;
	hour = minus / 3600;
	min = (minus % 3600) / 60;
	if (min<0 && min>-60)
	{
		hour = hour - 1;
	}
	return hour;


	//answer = minus - hour * 3600 - min * 60;

}
int ReadHomeworkDate(FILE* fp)
{
	char num[L_subject];
	/*
	for (int i = 0;; i++)
	{
		if (fp == NULL)
		{
			return 10;
			break;
		}
		num[i] = fgetc(fp);
		if (num[i] == EOF)
		{
			return 10;
			break;
		}
		else if (num[i] == '.')
		{
			num[i] = '\0';
			break;
		}
		else if (num[i] == '\n')
		{
				num[i] = '\0';
				break;
		}
	}*/
	ReadUntilTarget(fp, num, '.');
	int date;
	date = atoi(num);
	return date;
}

void SystemTime(void)
{
	time_t timep;
	struct tm* p;
	time(&timep);
	p = gmtime(&timep);
	Date.year = 1900 + p->tm_year;
	Date.month = 1 + p->tm_mon;
	Date.day = p->tm_mday;
	Date.hour = 8 + p->tm_hour;
	Date.minute = p->tm_min;
	if (Date.hour > 24)
	{
		Date.day++;
		Date.hour = Date.hour - 24;
	}
	Date.weekday = CaculateNowWeekday(Date.year, Date.month, Date.day);
	printf("现在是%d年%d月%d日", Date.year, Date.month, Date.day);
	printf(" %2d:", Date.hour);
	if (Date.minute < 10)
	{
		cout << "0" << Date.minute << endl;
	}
	else
	{
		cout << Date.minute << endl;
	}
	//cout << " 学期第" << CaculateTermWeek() << "周" << endl;
}
int CaculateNowWeekday(int y, int m, int d)
{
	if (m == 1 || m == 2) {
		m += 12;
		y--;
	}
	int iWeek = (d + 2 * m + 3 * (m + 1) / 5 + y + y / 4 - y / 100 + y / 400) % 7;
	switch (iWeek)
	{
	case 0: return 1; break;
	case 1: return 2; break;
	case 2: return 3; break;
	case 3: return 4; break;
	case 4: return 5; break;
	case 5: return 6; break;
	case 6: return 7; break;
	}
}

void FileModTime(char filename[], const char frontstr[])
{
	struct stat buf;
	int result;
	result = stat(filename, &buf);
	if (result != 0)
	{
		perror("Failed ^_^");
	}
	else
	{
		struct FileModTime
		{
			char Full[30];
			char Year[10];
			char Month_ENG[10];
			char Month_Num[10];
			char weekday[10];
			char Day[10];
			char Hour[10];
			char Minute[10];
			char Second[10];
		}modtime;
		strcpy(modtime.Full, ctime(&buf.st_mtime));				//将文件修改时间复制到结构体储存器中，下面省略了其他输出类型
		/*
		! 输出文件的大小，字节为单位
		cout << "size of the file in bytes: " << buf.st_size << endl;
		! 输出文件创建的时间
		cout << "time of creation of the file: " << ctime(&buf.st_ctime) << endl;
		! 输出最近一次访问的时间
		cout << "time of last access of the file: " << ctime(&buf.st_atime) << endl;
		*/
		CutConstCharPart(modtime.Full, modtime.weekday, 0, 2);	//将星期保存到modtime.weekday中
		CutConstCharPart(modtime.Full, modtime.Month_ENG, 4, 6);//将英语月份保存到modtime.Month_ENG中
		CutConstCharPart(modtime.Full, modtime.Day, 8, 9);		//将日保存到modtime.Day中
		CutConstCharPart(modtime.Full, modtime.Hour, 11, 12);	//将时间保存到modtime.Hour中
		CutConstCharPart(modtime.Full, modtime.Minute, 14, 15);	//将时间保存到modtime.Minute中
		CutConstCharPart(modtime.Full, modtime.Second, 17, 18);	//将时间保存到modtime.Second中
		CutConstCharPart(modtime.Full, modtime.Year, 20, 23);	//将年份保存到modtime.Year中
		const char MonthMap[12][4] =								//定义一个12行4列的数组作为月份字典
		{ "Jan","Feb","Mar","Apr","May","Jun","Jul","Aug","Sep","Oct","Nov","Dec" };
		for (int i = 0; i < 12; i++)		//将英文月份转化为中文月份
		{
			if (strcmp(MonthMap[i], modtime.Month_ENG) == 0)
			{
				if (i < 10)
				{
					modtime.Month_Num[0] = '0';
					_itoa((i + 1), &modtime.Month_Num[1], 10);
				}
				else
				{
					_itoa((i + 1), modtime.Month_Num, 10);
				}
			}
		}
		cout << "#" << frontstr << "：" << modtime.Month_Num << "-";
		if (modtime.Day[0]==' ')
		{
			modtime.Day[0] = '0';
		}
		cout << modtime.Day  << " " << modtime.weekday << " "
			 << modtime.Hour << ":" << modtime.Minute  << "#" << endl;
	}
}

int ReadUntilTarget(FILE* fp, char address[L_subject],char target)
{
ReadStar_Start:
	char str[L_subject] = { '0' };
	for (int i = 0;; i++)
	{
		if (fp == NULL)
		{
			return 10;
			break;
		}
		str[i] = fgetc(fp);
		if (str[i] == EOF)
		{
			return 10;
			break;
		}
		else if (str[i] == target)
		{
			str[i] = '\0';
			strcpy(address, str);
			break;
		}
		else if (str[i] == '\n')
		{
			if (i != 0)
			{
				str[i] = '\0';
				strcpy(address, str);
				break;
			}
			else if (i == 0)
			{
				goto ReadStar_Start;
			}
		}
	}
}


void Enter(FILE* fp, int EnterNum)
{
	for (int i = 1; i <= EnterNum; i++)
	{
		while (1)
		{
			if (fgetc(fp) == '\n')
				break;
			else if (feof(fp) == 1)
				break;
			else if (fgetc(fp) == '\n')
				break;
		}
	}
}
void AutoSpace(int strlength)
{
	int m;
	m = 26 - strlength;
	if (m > 0)
	{
		for (int i = 0; i < m; i++)
		{
			printf(" ");
		}
	}
}
void CutConstCharPart(char Res_str[], char store_str[], int from, int to)
{
	int i;
	for (i = 0; from <= to; i++, from++)
	{
		store_str[i] = Res_str[from];
	}
	store_str[i++] = '\0';
}