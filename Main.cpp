#include"SDA.h"


int main(void)
{
MainStart:
	system("mode con cols=50 lines=70");			//���������д����СΪ50���ַ���70�г�
	system("color 70");								//�����������óɰ�ɫ����(e),��ɫ����(0)
	ReadClassHTML();								//��ȡ���ؿα�HTML�ļ�
	ReadHomework();									//��ȡ������ҵ
	cout << "���찴[1]����������\n>";
	char IsToday = getchar();
	getchar();										//�����ո�
	system("cls");									//����
	SystemTime();									//���㲢�����ǰϵͳʱ��
	dy20;
	if (IsToday == '1')
	{
		PutClass("��");								//�������[1]�������"��"��α�
	}
	else
	{
		PutClass("��");								//������벻Ϊ[1]�������"��"��α�
	}
	CalculateHomework();							//���㱾����ҵ����ʱ��
	dy20;
	PutHomework();									//�����ҵ��������
	dy20;
	AD();											//���59s
	dy20;
	FileModTime(Class_File, "���ؿα�HTML��������");//�������HTML�ļ��ĸ���ʱ��
	FileModTime(Homework_File, "������ҵ�б��������");//���������ҵ�б��ļ��ĸ���ʱ��
	cout << "\n����һ���밴[1]" << endl;
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
	int w;					//����
	int j;					//�ڴ�
	int n = 0;				//�ṹ�����
	Enter(fp, 10);			//��10�λس�����ת��11��
	for (j = 1; j <= 5; j++)//�ӵ�1�ڱ�������5��
	{
		for (w = 1; w <= 7; w++, n++)//������1����������7
		{

			ReadClass(fp, stuclass[n].xuefen, stuclass[n].shuxing, stuclass[n].mingcheng, stuclass[n].week, stuclass[n].didian);	//��HTML�ж�ȡ�γ̵ĸ�����Ϣ
			stuclass[n].xingqi = w;		//д��γ̵�����
			stuclass[n].jieci = j;		//д��γ̵Ľڴ�
			Enter(fp, 5);				//�س�5�У�������һ���ͬһ�ڿ�
		}
		Enter(fp, 8);					//�س�8�У�������һ�ڿ�
	}
	fclose(fp);
	for (int i = 28; i <= Num_Stuclass; i++)
	{
		if (stuclass[i].xingqi == 2 && stuclass[i].jieci == 5 && strcmp(stuclass[i].mingcheng, "0") != 0)		//�������2����5�ڣ����Ҳ��ǿ��õĻ�
		{
			strcpy(stuclass[i].mingcheng, "��ѡʵ��γ�");														//�Ǿ�������Ϊ"��ѡʵ��γ�"
		}
		else if (stuclass[i].xingqi == 7 && stuclass[i].jieci == 5 && strcmp(stuclass[i].mingcheng, "0") != 0)	//�������7����5�ڣ����Ҳ��ǿ��õĻ�
		{
			strcpy(stuclass[i].mingcheng, "��ѡ����γ�");														//�Ǿ�������Ϊ"��ѡ����γ�"
		}
	}

}
void ReadClass(FILE* fp, float rxuefen, char rshuxing[L_subject], char rmingcheng[L_subject], char rweek[6], char rdidian[L_subject])
{
	char temp;	//��ȡ�ļ�ʱ�Ļ������
	int i;		//i���ڼ���'>'��j���ڼ���'"'
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
			strcpy(rmingcheng, "\\");		//���Ƹ�Ϊ'\'
			strcpy(rdidian, "");			//�ص㲻��
			return;
		}
	}
	fseek(fp, 10, 1);				//������γ�ѧ�֣�����
	char Rxuefen[10];					//����һ������������ʱ����ѧ��
	ReadUntilTarget(fp, Rxuefen, '<');			/*��ȡ�γ�ѧ��*/
	rxuefen = atof(Rxuefen);			//��ѧ�ִ��ַ���ת��Ϊ������	
	strcpy(Rxuefen, "0");				//��ջ�������
	fseek(fp, 17, 1);				//������γ����ԣ�����
	ReadUntilTarget(fp, rshuxing, '<');			/*��ȡ�γ�����*/
	fseek(fp, 14, 1);				//������γ����ƣ�����
	ReadUntilTarget(fp, rmingcheng, '<');		/*��ȡ�γ�����*/
	fseek(fp, 16, 1);				//������Ͽ�ʱ�䣺�ں���
	ReadUntilTarget(fp, rweek, ' ');			/*��ȡ�γ��ܴ�*/
	fseek(fp, 31, 1);				//������Ͽεص㣺����
	ReadUntilTarget(fp, rdidian, '"');			/*��ȡ�γ̵ص�*/
	if (strcmp(rdidian, "") == 0)
	{
		strcpy(rdidian, "None");	//���û���Ͽεص�Ļ����ֶ���ֵ"None"
	}
}
void ReadHomework(void)
{
	FILE* fp;
	fopen_s(&fp, Homework_File, "r");
	Enter(fp, 4);		//����4��ע��
	int i;
	int feedback;
	for (i = 0;; i++)
	{
		ReadUntilTarget(fp, homework[i].place, '*');										//��ȡ��ҵ��ƽ̨
		ReadUntilTarget(fp, homework[i].subject, '*');										//��ȡ��ҵ�Ŀ�Ŀ
		homework[i].strlong = strlen(homework[i].place) + strlen(homework[i].subject);		//��ֵ��ҵ���ַ����ȣ����ڵ������ո�
		feedback = ReadUntilTarget(fp, homework[i].title, '*');								//��ȡ��ҵ����Ŀ
		if (feedback == 10)						//����ֵΪ10��ζ���ļ�������
		{
			break;
		}
		homework[i].month = ReadHomeworkDate(fp);													//��ȡ��ҵ����
		homework[i].day = ReadHomeworkDate(fp);														//��ȡ��ҵ����
		homework[i].hour = ReadHomeworkDate(fp);													//��ȡ��ҵ��Сʱ
		homework[i].minute = ReadHomeworkDate(fp);													//��ȡ��ҵ�ķ���
		if (feedback == 10)						//����ֵΪ10��ζ���ļ�������
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
	if (strcmp(JinorMing, "��") == 0)
	{
		tempoptweekday = Date.weekday;
	}
	else if (strcmp(JinorMing, "��") == 0)
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
			NoneClass++;			//�սڴμ�����
		}
	}
	for (i = 0; i <= Num_Stuclass; i++)			//��ȡ��ǰHTML�еĿα�����
	{
		if (strcmp(stuclass[i].week,"0") )
		{
			strcpy(Classweek , stuclass[i].week);
			break;
		}
	}
	switch (tempoptweekday)
	{
	case 1:cout << JinorMing << "��ϵ�" << Classweek << "����һ��" << endl; break;
	case 2:cout << JinorMing << "��ϵ�" << Classweek << "���ڶ���" << endl; break;
	case 3:cout << JinorMing << "��ϵ�" << Classweek << "��������" << endl; break;
	case 4:cout << JinorMing << "��ϵ�" << Classweek << "�����ģ�" << endl; break;
	case 5:cout << JinorMing << "��ϵ�" << Classweek << "�����壺" << endl; break;
	case 6:cout << JinorMing << "��ϵ�" << Classweek << "��������" << endl; break;
	case 7:cout << JinorMing << "��ϵ�" << Classweek << "�����գ�" << endl; break;
	}
	if (NoneClass == 5)			//���Ϊ5�ڿ��ã�������γ̱�
	{
		printf("\n");
	}
	else if (NoneClass < 5)		//����пΣ�������γ̱�
	{
		for (i = 0, t = 1; i < Num_Stuclass; i++)
		{
			if (stuclass[i].xingqi == tempoptweekday)
			{
				if (t == 1)
					cout << "����һ�ڡ�";
				else if (t == 2)
					cout << "���ڶ��ڡ�";
				else if (t == 3)
					cout << "�������ڡ�";
				else if (t == 4)
					cout << "�����Ľڡ�";
				else if (t == 5)
					cout << "������ڡ�";
				cout << stuclass[i].mingcheng << "\n          ";
				if (strcmp(stuclass[i].didian, "") != 0)
				{
					cout << '[' << stuclass[i].didian << ']' << endl;	//������ǿյص���ô�����"[�ص�]"
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
		cout << "��" << homework[mini[j]].subject;
		if (homework[mini[j]].place[0]!='\0')
		{
			//AutoSpace(strlen(homework[mini[j]].subject));
			AutoSpace(homework[mini[j]].strlong);
			cout << "����" << homework[mini[j]].place;
		}
		cout << "\n��" << homework[mini[j]].title << endl;
		if (homework[mini[j]].month == 11 && homework[mini[j]].day == 11 && homework[mini[j]].hour == 11 && homework[mini[j]].minute == 11)
		{
			cout << ">>����ҵʱ��δ֪" << endl;
		}
		else
		{
			printf(">>%2d��%2d��", homework[mini[j]].month, homework[mini[j]].day);
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
				cout << "��/ʣ" << day << "��" << hour << "Сʱ" << endl;
			}
			else
			{
				cout << "��/  �ѹ���  " << endl;
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
	HomeworkTime.tm_year = 120;// 2010 ���ʾΪ 2010 - 1900 = 110
	HomeworkTime.tm_mon = homework[i].month;
	HomeworkTime.tm_mday = homework[i].day;
	memset(&NowTime, 0x0, sizeof(tm));
	NowTime.tm_year = 120;// 2011 ���ʾΪ 2011 - 1900 = 111
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
	printf("������%d��%d��%d��", Date.year, Date.month, Date.day);
	printf(" %2d:", Date.hour);
	if (Date.minute < 10)
	{
		cout << "0" << Date.minute << endl;
	}
	else
	{
		cout << Date.minute << endl;
	}
	//cout << " ѧ�ڵ�" << CaculateTermWeek() << "��" << endl;
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
		strcpy(modtime.Full, ctime(&buf.st_mtime));				//���ļ��޸�ʱ�临�Ƶ��ṹ�崢�����У�����ʡ���������������
		/*
		! ����ļ��Ĵ�С���ֽ�Ϊ��λ
		cout << "size of the file in bytes: " << buf.st_size << endl;
		! ����ļ�������ʱ��
		cout << "time of creation of the file: " << ctime(&buf.st_ctime) << endl;
		! ������һ�η��ʵ�ʱ��
		cout << "time of last access of the file: " << ctime(&buf.st_atime) << endl;
		*/
		CutConstCharPart(modtime.Full, modtime.weekday, 0, 2);	//�����ڱ��浽modtime.weekday��
		CutConstCharPart(modtime.Full, modtime.Month_ENG, 4, 6);//��Ӣ���·ݱ��浽modtime.Month_ENG��
		CutConstCharPart(modtime.Full, modtime.Day, 8, 9);		//���ձ��浽modtime.Day��
		CutConstCharPart(modtime.Full, modtime.Hour, 11, 12);	//��ʱ�䱣�浽modtime.Hour��
		CutConstCharPart(modtime.Full, modtime.Minute, 14, 15);	//��ʱ�䱣�浽modtime.Minute��
		CutConstCharPart(modtime.Full, modtime.Second, 17, 18);	//��ʱ�䱣�浽modtime.Second��
		CutConstCharPart(modtime.Full, modtime.Year, 20, 23);	//����ݱ��浽modtime.Year��
		const char MonthMap[12][4] =								//����һ��12��4�е�������Ϊ�·��ֵ�
		{ "Jan","Feb","Mar","Apr","May","Jun","Jul","Aug","Sep","Oct","Nov","Dec" };
		for (int i = 0; i < 12; i++)		//��Ӣ���·�ת��Ϊ�����·�
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
		cout << "#" << frontstr << "��" << modtime.Month_Num << "-";
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