#include"SDA.h"

int main(void)
{
MainStart:
	system("mode con cols=50 lines=70");
	ReadClassHTML();
	ReadHomework();
	cout << "今天按[1]明天请随意\n>";
	char IsToday = getchar();
	getchar();
	if (IsToday == '1')
	{
		system("cls");
		SystemTime();
		dy20;
		PutTodayClass();
	}
	else
	{
		system("cls");
		SystemTime();
		dy20;
		PutTomorrowClass();
	}
	CalculateHomework();
	dy20;
	PutHomework();
	dy20;
	AD();
	dy20;
	FileModTime(Class_File, "本地课表HTML更新日期");
	FileModTime(Homework_File, "本地作业列表更新日期");
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

void PutTodayClass(void)
{
	int i, t, NoneClass, Classweek;
	for (i = 0, NoneClass = 0; i < Num_Stuclass; i++)
	{
		if (stuclass[i].xingqi == Date.weekday && strcmp(stuclass[i].kemu, "None") == 0)
		{
			NoneClass++;
		}
	}
	for (i = 0; i <= Num_Stuclass; i++)			//读取当前HTML中的课表周数
	{
		if (stuclass[i].week != 0)
		{
			Classweek = stuclass[i].week;
			break;
		}
	}
	switch (Date.weekday)
	{
	/*
	case 1:cout << "今天[" << Classweek << "]周星期一：  (共" << 5 - NoneClass << "节)" << endl; break;
	case 2:cout << "今天[" << Classweek << "]周星期二：	 (共" << 5 - NoneClass << "节)" << endl; break;
	case 3:cout << "今天[" << Classweek << "]周星期三：  (共" << 5 - NoneClass << "节)" << endl; break;
	case 4:cout << "今天[" << Classweek << "]周星期四：  (共" << 5 - NoneClass << "节)" << endl; break;
	case 5:cout << "今天[" << Classweek << "]周星期五：  (共" << 5 - NoneClass << "节)" << endl; break;
	case 6:cout << "今天[" << Classweek << "]周星期六：  (共" << 5 - NoneClass << "节)" << endl; break;
	case 7:cout << "今天[" << Classweek << "]周星期日：  (共" << 5 - NoneClass << "节)" << endl; break;
	*/
	case 1:cout << "今天是第[" << Classweek << "]周星期一：" << endl; break;
	case 2:cout << "今天是第[" << Classweek << "]周星期二：" << endl; break;
	case 3:cout << "今天是第[" << Classweek << "]周星期三：" << endl; break;
	case 4:cout << "今天是第[" << Classweek << "]周星期四：" << endl; break;
	case 5:cout << "今天是第[" << Classweek << "]周星期五：" << endl; break;
	case 6:cout << "今天是第[" << Classweek << "]周星期六：" << endl; break;
	case 7:cout << "今天是第[" << Classweek << "]周星期日：" << endl; break;
	default: break;
	}
	for (i = 0, t = 1; i < Num_Stuclass; i++)
	{
		if (stuclass[i].xingqi == Date.weekday)
		{
			if (strcmp(stuclass[i].kemu, "None") == 0)
			{
				NoneClass++;
			}
			if (t == 1)
				printf("08:00-09:40	");
			else if (t == 2)
				printf("10:00-11:40	");
			else if (t == 3)
				printf("\n14:00-15:40	");
			else if (t == 4)
				printf("16:00-17:40	");
			else if (t == 5)
				printf("\n19:00-20:40	");
			printf("%s\n", stuclass[i].kemu);
			t++;
		}
	}


}
void PutTomorrowClass(void)
{
	int i, t, NoneClass, Classweek;
	int Tomorrow_weekday;
	if (Date.weekday == 7)
	{
		Tomorrow_weekday = 1;
	}
	else
	{
		Tomorrow_weekday = Date.weekday + 1;
	}
	for (i = 0, NoneClass = 0; i < Num_Stuclass; i++)
	{
		if (stuclass[i].xingqi == Tomorrow_weekday && strcmp(stuclass[i].kemu, "None") == 0)
		{
			NoneClass++;			//空节次计算器
		}
	}
	for (i = 0; i <= Num_Stuclass; i++)			//读取当前HTML中的课表周数
	{
		if (stuclass[i].week != 0)
		{
			Classweek = stuclass[i].week;
			break;
		}
	}
	switch (Tomorrow_weekday)
	{
	/*
	case 1:cout << "明天[" << Classweek << "]周星期一：  (共" << 5 - NoneClass << "节)" << endl; break;
	case 2:cout << "明天[" << Classweek << "]周星期二：	 (共" << 5 - NoneClass << "节)" << endl; break;
	case 3:cout << "明天[" << Classweek << "]周星期三：	 (共" << 5 - NoneClass << "节)" << endl; break;
	case 4:cout << "明天[" << Classweek << "]周星期四：  (共" << 5 - NoneClass << "节)" << endl; break;
	case 5:cout << "明天[" << Classweek << "]周星期五：  (共" << 5 - NoneClass << "节)" << endl; break;
	case 6:cout << "明天[" << Classweek << "]周星期六：  (共" << 5 - NoneClass << "节)" << endl; break;
	case 7:cout << "明天[" << Classweek << "]周星期日：  (共" << 5 - NoneClass << "节)" << endl; break;
	*/
	case 1:cout << "明天—第[" << Classweek << "]周星期一：" << endl; break;
	case 2:cout << "明天—第[" << Classweek << "]周星期二：" << endl; break;
	case 3:cout << "明天—第[" << Classweek << "]周星期三：" << endl; break;
	case 4:cout << "明天—第[" << Classweek << "]周星期四：" << endl; break;
	case 5:cout << "明天—第[" << Classweek << "]周星期五：" << endl; break;
	case 6:cout << "明天—第[" << Classweek << "]周星期六：" << endl; break;
	case 7:cout << "明天—第[" << Classweek << "]周星期日：" << endl; break;
	}
	if (NoneClass == 5)			//如果为5节空堂，则不输出课程表
	{
		printf("\n");
	}
	else if (NoneClass < 5)		//如果有课，则输出课程表
	{
		for (i = 0, t = 1; i < Num_Stuclass; i++)
		{
			if (stuclass[i].xingqi == Tomorrow_weekday)
			{
				if (t == 1)
					printf("08:00-09:40	");
				else if (t == 2)
					printf("10:00-11:40	");
				else if (t == 3)
					printf("\n14:00-15:40	");
				else if (t == 4)
					printf("16:00-17:40	");
				else if (t == 5)
					printf("\n19:00-20:40	");
				printf("%s\n", stuclass[i].kemu);
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

void ReadClassHTML(void)
{

	FILE* fp;
	fopen_s(&fp, Class_File, "r");
	int w;			//星期
	int j;			//节次
	int n = 0;			//结构体序号
	Enter(fp, 10);  //按10次回车，跳转到11行
	for (j = 1; j <= 5; j++)
	{
		for (w = 1; w <= 7; w++, n++)
		{
			stuclass[n].xingqi = w;
			stuclass[n].jieci = j;
			stuclass[n].week = ReadClass(fp, stuclass[n].kemu);
			Enter(fp, 5);
		}
		Enter(fp, 8);
	}
	fclose(fp);
	for (int i = 28; i <= Num_Stuclass; i++)
	{
		if (stuclass[i].xingqi == 2 && stuclass[i].jieci == 5 && strcmp(stuclass[i].kemu, "0") != 0)
		{
			strcpy(stuclass[i].kemu, "自选实体课程");
		}
		else if (stuclass[i].xingqi == 7 && stuclass[i].jieci == 5 && strcmp(stuclass[i].kemu, "0") != 0)
		{
			strcpy(stuclass[i].kemu, "自选网络课程");
		}
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
		ReadStar(fp, homework[i].place);
		ReadStar(fp, homework[i].subject);
		homework[i].strlong = strlen(homework[i].place) + strlen(homework[i].subject);
		feedback = ReadStar(fp, homework[i].title);
		if (feedback == 10)
		{
			break;
		}
		homework[i].month = ReadDate(fp);
		homework[i].day = ReadDate(fp);
		homework[i].hour = ReadDate(fp);
		homework[i].minute = ReadDate(fp);
		if (feedback == 10)
		{
			break;
		}
	}
	fclose(fp);
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
int CaculateTermWeek(void)
{
	int Monthday_number[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
	int day_number = 0, nowweek, termweek;
	for (int i = 0; i < Date.month - 1; i++)			//计算当前月数所代表的的天书
	{
		day_number = day_number + Monthday_number[i];
	}
	day_number = day_number + Date.day;					//加上当前的日期得到总天数
	if (nowweek = day_number % 7 != 0)
	{
		nowweek = (day_number / 7) + 1;
	}
	else
	{
		nowweek = day_number / 7;							//计算出当天是第几周
	}
	termweek = nowweek - 10 + 1;
	return termweek;
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

int ReadClass(FILE* fp, char StoreClass[50])
{
	char Class[50] = "0";
	char week[5] = "0";
	char temp;
	int i, return_week;
	for (i = 0; i < 3; i++)
	{
		while (1)
		{
			temp = fgetc(fp);
			if (temp == '>')
			{
				break;
			}
			else if (temp == '\n')
			{
				fseek(fp, -2, 1);
				strcpy(Class, "None");
				strcpy(StoreClass, Class);
				return 1;
			}
		}
	}
	for (i = 0; i < 10; i++)
	{
		fgetc(fp);			//清除“课程名称：”5个字fu
	}
	for (i = 0;; i++)
	{
		temp = fgetc(fp);
		if (temp == '<')
		{
			break;
		}
		Class[i] = temp;
	}
	strcpy(StoreClass, Class);
	for (i = 0; i < 16; i++)
	{
		fgetc(fp);			//清除“br/>上课时间：第”16个字fu
	}
	for (i = 0; i < 2; i++)
	{
		week[i] = fgetc(fp);
	}
	return_week = atoi(week);
	return return_week;
}
int ReadStar(FILE* fp, char address[L_subject])
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
		else if (str[i] == '*')
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
int ReadDate(FILE* fp)
{
	char num[L_subject];
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
	}
	int date;
	date = atoi(num);
	return date;
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