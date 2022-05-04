#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<windows.h>
#include<iomanip>
#include<stdio.h>
#include<string>
#include<fstream>
using namespace std;
enum Pozn
{
	casual,
	comfort,
	expres
};

struct Electr
{
	char prizn[20];
	Pozn poznach;
	int time[2];
};

void ToFile(Electr& stud, const int N, char* filename);
void CreateAndAdd(Electr& stud, const int N, char* filename)
{
	fstream f("Student1.bit", ios::binary,ios::app);
	int poznach,a;
	for (int i = 0; i < N; i++)
	{
		cin.get(); cin.sync();
		cout << "������ ���� �����������: "; cin.getline(stud.prizn,20);
		do
		{
			if (strpbrk(stud.prizn, "0 123456789") != NULL)
			{
				//stud.prizv.erase(0, -1);
				cout << "�� ����� ������ �����������, ���������� �����: " << endl;
				cout << "�����������: "; cin.getline(stud.prizn, 20);
			}
		} while (strpbrk(stud.prizn, "0 123456789") != NULL);
		cout << "������ ��������: ";
		cout << " �������� (0 - ��������� , 1 - ���������� ��������, 2 - ��������� �������):";
		cin >> poznach;
		if (cin.fail() || poznach < 0 || poznach>2)
		{
			do
			{
				cin.clear();
				cin.ignore(255, '\n');
				cout << "�� ����� ������ �����, ���������� �����: " << endl;
				cout << " �������� (0 - ��������� , 1 - ���������� ��������, 2 - ��������� �������): ";
				cin >> poznach;
			} while (cin.fail() || poznach < 0 || poznach>2);
		}
		stud.poznach = (Pozn)poznach;
		cout << "������ ������: "; cin >> a;
		if (cin.fail() || a < 1 || a>24)
		{
			do
			{
				cin.clear();
				cin.ignore(255, '\n');
				cout << "�� ����� ������ �����, ���������� �����: " << endl;
				cout << " ������ ������: "; cin >> a;
			} while (cin.fail() || a < 1 || a>24);
		}
		stud.time[0] = a;
		cout << "������ �������: "; cin >> a;
		if (cin.fail() || a < 0 || a>60)
		{
			do
			{
				cin.clear();
				cin.ignore(255, '\n');
				cout << "�� ����� ������ �����, ���������� �����: " << endl;
				cout << " ������ �������: "; cin >> a;
			} while (cin.fail() || a < 0 || a>60);
		}
		stud.time[1] = a;
		cout << endl;
		ToFile(stud, N, filename);
	}
	f.close();

}
void ToFile(Electr& stud, const int N, char* filename)
{
	ofstream f(filename, ios::binary | ios::app);
	f.write((char*)&stud, sizeof(Electr));
	f.close();
}
void PrintFromFile(Electr& stud, const int N, string* List, char* filename)
{
	ifstream f(filename, ios::binary);
	int num = 1;
	cout << "========================================================="
		<< endl;
	cout << "| � |    �����������    |          ���          |  ���  |"
		<< endl;
	cout << "---------------------------------------------------------"
		<< endl;
	while (f.read((char*)&stud, sizeof(Electr)))
	{
		cout << "| " << setw(1) << right << num++ << " ";
		cout << "| " << setw(18) << left << stud.prizn
			<< "| " << setw(22) << left << List[stud.poznach];
		cout << "| " << setw(2) << right << to_string(stud.time[0]) << ":" <<
			setw(2) << left << to_string(stud.time[1]) << " |" << endl;
	}
	cout << "========================================================="
		<< endl;
	cout << endl;
}
void Remove(char* filename,const int no)
{
	ifstream f(filename, ios::binary);
	/*if (!f.is_open())
	{
		cout << "������ ����� �� ����" << endl;
		are_open = false;
		return;
	}*/
	ofstream t("TMP.bin", ios::binary);
	Electr stud;
	int num = 1;
	char old[8]{ "TMP.bin"};
	char* tmp = old;
	f.seekg(0);
	while (f.read((char*)&stud, sizeof(Electr))) 
	{
		if (num != no)
		{
			t.write((char*)&stud, sizeof(Electr));
		}
		num++;
	} // ������� ������� ����
	//t.write((char*)&stud, sizeof(Electr)); // �� ������� ��������
	f.close(); // ��� ��������� � ��������������
	t.close(); // ����� ����� ���� ������
	remove(filename); // ������� ������� ����
	rename(tmp, filename); // ������������� ���������� ����
}
void Zamina(char* filename, Electr& stud, const int N)
{
	fstream f(filename, ios::binary | ios::in | ios::out);
	/*if (!f.is_open())
	{
		cout << "������ ����� �� ����" << endl;
		are_open = false;
		return;
	}*/
	int row, col, poznach;
	char prizn[20];
	int time2[2];
	cout << "������ ����� �����, ���� �� ������ �������: "; cin >> row;
	if (cin.fail() || row < 0 || row>N)
	{
		do
		{
			cin.clear();
			cin.ignore(255, '\n');
			cout << "�� ����� ������ �����, ���������� �����: " << endl;
			cout << " ������ ����� �����, ���� �� ������ �������:";
			cin >> row;
		} while (cin.fail() || row < 0 || row>N);
	}
	row--;
	f.seekg(row * sizeof(Electr));
	cout << "������, ���� �� ������ ������� ��������(0-�����������,1-���,2-���): "; cin >> col;
	if (cin.fail() || col < 0 || col>2)
	{
		do
		{
			cin.clear();
			cin.ignore(255, '\n');
			cout << "�� ����� ������ �����, ���������� �����: " << endl;
			cout << " ������, ���� �� ������ ������� ��������(0-�����������,1-���,2-���):";
			cin >> col;
		} while (cin.fail() || col < 0 || col>2);
	}
	cin.get(); cin.sync();
	switch (col)
	{
	case 0:
		cout << "������ ���� ���� �����������: "; cin.getline(prizn,20);
		do
		{
			if (strpbrk(prizn, "0 123456789") != NULL)
			{
				//stud.prizv.erase(0, -1);
				cout << "�� ����� ������ �����������, ���������� �����: " << endl;
				cout << " �����������: "; cin.getline(prizn, 20);
			}
		} while (strpbrk(prizn, "0 123456789") != NULL);
		f.read((char*)&stud, sizeof(Electr));
		strcpy(stud.prizn,prizn);
		f.seekg(row * sizeof(Electr));
		f.write((char*)&stud, sizeof(Electr));
		break;
	case 1:
		cout << "������ ���� �������� (0 - ��������� , 1 - ���������� ��������, 2 - ��������� �������): ";
		cin >> poznach;
		if (cin.fail() || poznach < 0 || poznach>2)
		{
			do
			{
				cin.clear();
				cin.ignore(255, '\n');
				cout << "�� ����� ������ �����, ���������� �����: " << endl;
				cout << " �������� (0 - ��������� , 1 - ���������� ��������, 2 - ��������� �������):";
				cin >> poznach;
			} while (cin.fail() || poznach < 0 || poznach>2);
		}
		f.read((char*)&stud, sizeof(Electr));
		stud.poznach = (Pozn)poznach;
		//strcpy(stud.poznach, (Pozn)poznach);
		f.seekg(row * sizeof(Electr));
		f.write((char*)&stud, sizeof(Electr));
		break;
	case 2:
		cout << "������ ����� ��� �����������:\n������: "; cin >> time2[0];
		if (cin.fail() || time2[0] < 1 || time2[0]>24)
		{
			do
			{
				cin.clear();
				cin.ignore(255, '\n');
				cout << "�� ����� ����� ���, ���������� �����: " << endl;
				cout << " ������: "; cin >> time2[0];
			} while (cin.fail() || time2[0] < 1 || time2[0]>24);
		}
		f.read((char*)&stud, sizeof(Electr));
		stud.time[0] = time2[0];
		//f.seekg(row * sizeof(Electr));
		//f.write((char*)&stud, sizeof(Electr));
		cin.get(); cin.sync();

		cout << "�������: "; cin >> time2[1];
		if (cin.fail() || time2[1] < 1 || time2[1]>60)
		{
			do
			{
				cin.clear();
				cin.ignore(255, '\n');
				cout << "�� ����� ����� ���, ���������� �����: " << endl;
				cout << " �������: "; cin >> time2[1];
			} while (cin.fail() || time2[1] < 1 || time2[1]>60);
		}
		//f.read((char*)&stud, sizeof(Electr));
		stud.time[1] = time2[1];
		f.seekg(row * sizeof(Electr));
		f.write((char*)&stud, sizeof(Electr));
		break;
	}
}
void fWrite(fstream& f, const int i, Electr x)
{
	f.seekp(i * (long)sizeof(Electr)); // ���������� ��������
	f.write((char*)&x, sizeof(Electr)); // �������� ��������
}

Electr fRead(fstream& f, const int i)
{
	Electr tmp;
	//char x;
	f.seekg(i * (long)sizeof(Electr)); // ���������� ��������
	f.read((char*)&tmp, sizeof(Electr)); // ��������� ��������
	return tmp;
}

void fChange(fstream& f, const int i, const int j)
{
	Electr x = fRead(f, i);
	Electr y = fRead(f, j);
	fWrite(f, i, y);
	fWrite(f, j, x);
}

void TimeSort(Electr& stud, const int N, char* filename)
{
	fstream f(filename, ios::binary | ios::in | ios::out);
	f.seekg(0, ios::end);
	//int size = f.tellg();
	f.seekg(0, ios::beg);

	for (int i0 = 0; i0 < N - 1; i0++)
	{
		for (int i1 = 0; i1 < N - i0 - 1; i1++)
		{
			Electr a = fRead(f, i1);
			Electr b = fRead(f, i1 + 1);
			if ((a.time[0] > b.time[0])
				||
				(a.time[0] == b.time[0] &&
					a.time[1] > b.time[1]))
			{
				fChange(f, i1, i1 + 1);
			}
		}
	}
	f.seekp(0, ios::end);
}
void PriznSort(Electr& stud, const int N, char* filename)
{
	fstream f(filename, ios::binary | ios::in | ios::out);
	f.seekg(0, ios::end);
	//int size = f.tellg();
	f.seekg(0, ios::beg);

	for (int i0 = 0; i0 < N - 1; i0++)
	{
		for (int i1 = 0; i1 < N - i0 - 1; i1++)
		{
			Electr a = fRead(f, i1);
			Electr b = fRead(f, i1 + 1);
			if ((a.prizn[0] > b.prizn[0])|| (a.prizn[0] == b.prizn[0]&& a.prizn[1] > b.prizn[1]))
			{
				fChange(f, i1, i1 + 1);
			}
		}
	}
	f.seekp(0, ios::end);
}

void Pisla(char* filename,Electr stud,const int N,string* List)
{
	ifstream f(filename, ios::binary);
	int tmp[2];
	int num = 1;
	cout << " ������ ������� ��� ���:\n������: "; cin >> tmp[0];
	if (cin.fail() || tmp[0] < 1 || tmp[0]>24)
	{
		do
		{
			cin.clear();
			cin.ignore(255, '\n');
			cout << "�� ����� ����� ���, ���������� �����: " << endl;
			cout << " ������: "; cin >> tmp[0];
		} while (cin.fail() || tmp[0] < 1 || tmp[0]>24);
	}
	cin.get(); cin.sync();
	cout << "�������: "; cin >> tmp[1];
	if (cin.fail() || tmp[1] < 0 || tmp[1]>60)
	{
		do
		{
			cin.clear();
			cin.ignore(255, '\n');
			cout << "�� ����� ����� ���, ���������� �����: " << endl;
			cout << " �������: "; cin >> tmp[1];
		} while (cin.fail() || tmp[1] < 0 || tmp[1]>60);
	}
	cout << endl;
	cout << "������ �����, �� �������� ���� ��������� ����:" << endl;
	cout << endl;
	cout << "========================================================="
		<< endl;
	cout << "| � |    �����������    |          ���          |  ���  |"
		<< endl;
	cout << "---------------------------------------------------------"
		<< endl;
	while (f.read((char*)&stud, sizeof(Electr)))
	{
		if ((stud.time[0] > tmp[0])
			||
			(stud.time[0] == tmp[0] &&
				stud.time[1] > tmp[1]))
		{
			cout << "| " << setw(1) << right << num++ << " ";
			cout << "| " << setw(18) << left << stud.prizn
				<< "| " << setw(22) << left << List[stud.poznach];
			//<< "| " << setw(5) << right << to_string(stud[i].time)<< " |" << endl;
			cout << "| " << setw(2) << right << to_string(stud.time[0]) << ":" <<
				setw(2) << left << to_string(stud.time[1]) << " |" << endl;
		}
	}
	cout << "========================================================="
		<< endl;
	cout << endl;
}

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	bool are_open;
	int no,No;
	char filename[20];

	Electr stud;
	string List[] =
	{
		"���������",
		"���������� ��������",
		"��������� �������"
	};
	cout << "������ ��'� �����: "; cin.getline(filename, 20);
	int N;
	cout << "������ N: "; cin >> N;
	do
	{
		if (cin.fail())
		{
			cin.clear();
			cin.ignore(255, '\n');
			cout << "�� ����� ����� ���, ���������� �����: " << endl;
			cout << "������ N: "; cin >> N;
		}
	} while (cin.fail());
	int menuItem;
	do {
		cout << endl << endl << endl;
		cout << "������� ��:" << endl << endl;
		cout << " [1] - �������� ����� � ���������" << endl;
		cout << " [2] - ���� ����� �� �����" << endl;
		cout << " [3] - ��������� �������� ����" << endl;
		cout << " [4] - �������� ������� � �����" << endl;
		cout << " [5] - ����������� �����" << endl;
		cout << " [6] - ���������� �� ��������" << endl;
		cout << " [7] - ���������� �� �����" << endl;
		cout << " [8] - ����� �� �������� ���� ��������� ����" << endl;
		cout << " [0] - ����� �� ���������� ������ ��������" << endl << endl;
		cout << "������ ��������: "; cin >> menuItem;
		cout << endl << endl << endl;
		switch (menuItem)
		{
		case 1:
			CreateAndAdd(stud, N,filename);
			break;
		case 2:
			PrintFromFile(stud, N, List,filename);
			break;
		case 3:
			cout << "������ ������� �������� ��� ����������: "; cin >> No;
			do
			{
				if (cin.fail())
				{
					cin.clear();
					cin.ignore(255, '\n');
					cout << "�� ����� ����� ���, ���������� �����: " << endl;
					cout << "������ N: "; cin >> No;
				}
			} while (cin.fail());
			/*do
			{
				cout << "������ ����� �����: "; cin >> filename;
				are_open = true;
				CreateAndAdd(stud, No, filename);
			} while (!are_open);*/
			CreateAndAdd(stud, No, filename);
			N += No;
			break;
		case 4:
			cout << "������ ����� �����: "; cin >> no;
			do
			{
				if (cin.fail())
				{
					cin.clear();
					cin.ignore(255, '\n');
					cout << "�� ����� ����� ���, ���������� �����: " << endl;
					cout << "������ ����� �����: "; cin >> no;
				}
			} while (cin.fail());
			/*do
			{
				cout << "������ ����� �����: "; cin >> filename;
				are_open = true;
				Remove(filename, no, are_open);
			} while (!are_open);*/
			Remove(filename, no/*, are_open*/);
			N--;
			break;
		case 5:
			/*do
			{
				cout << "������ ����� �����: "; cin >> filename;
				are_open = true;
				Zamina(filename,stud,N,are_open);
			} while (!are_open);*/
			Zamina(filename, stud, N/*, are_open*/);
			break;
		case 6:
			PriznSort(stud,N,filename);
			break;
		case 7:
			TimeSort(stud, N, filename);
			break;
		case 8:
			Pisla(filename,stud,N,List);
			break;
		case 0:
			break;
		default:
			cout << "�� ����� ��������� ��������! ������ ����� ��������� ������ ����" << endl;
		}
	} while (menuItem != 0);

	//CreateAndAdd(stud, N, filename);
	//PrintFromFile(stud, N, List, filename);
	//TimeSort(stud, N, filename);
	//Zamina(filename, stud, N);
//	PrintFromFile(stud, N, List, filename);
	//Pisla(filename, stud, N, List);
	return 0;
}