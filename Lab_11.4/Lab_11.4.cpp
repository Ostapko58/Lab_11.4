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
		cout << "Введіть місце призначення: "; cin.getline(stud.prizn,20);
		do
		{
			if (strpbrk(stud.prizn, "0 123456789") != NULL)
			{
				//stud.prizv.erase(0, -1);
				cout << "Ви ввели невірне призначення, попробуйте знову: " << endl;
				cout << "Призначення: "; cin.getline(stud.prizn, 20);
			}
		} while (strpbrk(stud.prizn, "0 123456789") != NULL);
		cout << "Введіть позначку: ";
		cout << " Позначка (0 - звичайний , 1 - підвищеного комфорту, 2 - швидкісний експрес):";
		cin >> poznach;
		if (cin.fail() || poznach < 0 || poznach>2)
		{
			do
			{
				cin.clear();
				cin.ignore(255, '\n');
				cout << "Ви ввели невірне число, попробуйте знову: " << endl;
				cout << " Позначка (0 - звичайний , 1 - підвищеного комфорту, 2 - швидкісний експрес): ";
				cin >> poznach;
			} while (cin.fail() || poznach < 0 || poznach>2);
		}
		stud.poznach = (Pozn)poznach;
		cout << "Введіть годину: "; cin >> a;
		if (cin.fail() || a < 1 || a>24)
		{
			do
			{
				cin.clear();
				cin.ignore(255, '\n');
				cout << "Ви ввели невірне число, попробуйте знову: " << endl;
				cout << " Введіть годину: "; cin >> a;
			} while (cin.fail() || a < 1 || a>24);
		}
		stud.time[0] = a;
		cout << "Введіть хвилину: "; cin >> a;
		if (cin.fail() || a < 0 || a>60)
		{
			do
			{
				cin.clear();
				cin.ignore(255, '\n');
				cout << "Ви ввели невірне число, попробуйте знову: " << endl;
				cout << " Введіть хвилину: "; cin >> a;
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
	cout << "| № |    Призначення    |          Тип          |  Час  |"
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
		cout << "Такого файла не існує" << endl;
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
	} // скануємо заданий файл
	//t.write((char*)&stud, sizeof(Electr)); // які потрібно залишити
	f.close(); // для вилучення і перейменування
	t.close(); // файли мають бути закриті
	remove(filename); // знищуємо заданий файл
	rename(tmp, filename); // перейменовуємо тимчасовий файл
}
void Zamina(char* filename, Electr& stud, const int N)
{
	fstream f(filename, ios::binary | ios::in | ios::out);
	/*if (!f.is_open())
	{
		cout << "Такого файла не існує" << endl;
		are_open = false;
		return;
	}*/
	int row, col, poznach;
	char prizn[20];
	int time2[2];
	cout << "Введіть номер рядка, який ви хочете замінити: "; cin >> row;
	if (cin.fail() || row < 0 || row>N)
	{
		do
		{
			cin.clear();
			cin.ignore(255, '\n');
			cout << "Ви ввели невірне число, попробуйте знову: " << endl;
			cout << " Введіть номер рядка, який ви хочете замінити:";
			cin >> row;
		} while (cin.fail() || row < 0 || row>N);
	}
	row--;
	f.seekg(row * sizeof(Electr));
	cout << "Введіть, який ви хочете замінити стовпчик(0-Призначення,1-Тип,2-Час): "; cin >> col;
	if (cin.fail() || col < 0 || col>2)
	{
		do
		{
			cin.clear();
			cin.ignore(255, '\n');
			cout << "Ви ввели невірне число, попробуйте знову: " << endl;
			cout << " Введіть, який ви хочете замінити стовпчик(0-Призначення,1-Тип,2-Час):";
			cin >> col;
		} while (cin.fail() || col < 0 || col>2);
	}
	cin.get(); cin.sync();
	switch (col)
	{
	case 0:
		cout << "Введіть нове місце призначення: "; cin.getline(prizn,20);
		do
		{
			if (strpbrk(prizn, "0 123456789") != NULL)
			{
				//stud.prizv.erase(0, -1);
				cout << "Ви ввели невірне призначення, попробуйте знову: " << endl;
				cout << " Призначення: "; cin.getline(prizn, 20);
			}
		} while (strpbrk(prizn, "0 123456789") != NULL);
		f.read((char*)&stud, sizeof(Electr));
		strcpy(stud.prizn,prizn);
		f.seekg(row * sizeof(Electr));
		f.write((char*)&stud, sizeof(Electr));
		break;
	case 1:
		cout << "Введіть нову позначку (0 - звичайний , 1 - підвищеного комфорту, 2 - швидкісний експрес): ";
		cin >> poznach;
		if (cin.fail() || poznach < 0 || poznach>2)
		{
			do
			{
				cin.clear();
				cin.ignore(255, '\n');
				cout << "Ви ввели невірне число, попробуйте знову: " << endl;
				cout << " Позначка (0 - звичайний , 1 - підвищеного комфорту, 2 - швидкісний експрес):";
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
		cout << "Введіть новий час відправлення:\nГодина: "; cin >> time2[0];
		if (cin.fail() || time2[0] < 1 || time2[0]>24)
		{
			do
			{
				cin.clear();
				cin.ignore(255, '\n');
				cout << "Ви ввели невірні дані, попробуйте знову: " << endl;
				cout << " Година: "; cin >> time2[0];
			} while (cin.fail() || time2[0] < 1 || time2[0]>24);
		}
		f.read((char*)&stud, sizeof(Electr));
		stud.time[0] = time2[0];
		//f.seekg(row * sizeof(Electr));
		//f.write((char*)&stud, sizeof(Electr));
		cin.get(); cin.sync();

		cout << "Хвилина: "; cin >> time2[1];
		if (cin.fail() || time2[1] < 1 || time2[1]>60)
		{
			do
			{
				cin.clear();
				cin.ignore(255, '\n');
				cout << "Ви ввели невірні дані, попробуйте знову: " << endl;
				cout << " Хвилина: "; cin >> time2[1];
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
	f.seekp(i * (long)sizeof(Electr)); // встановили вказівник
	f.write((char*)&x, sizeof(Electr)); // записали значення
}

Electr fRead(fstream& f, const int i)
{
	Electr tmp;
	//char x;
	f.seekg(i * (long)sizeof(Electr)); // встановили вказівник
	f.read((char*)&tmp, sizeof(Electr)); // прочитали значення
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
	cout << " Введіть потрібен вам час:\nГодина: "; cin >> tmp[0];
	if (cin.fail() || tmp[0] < 1 || tmp[0]>24)
	{
		do
		{
			cin.clear();
			cin.ignore(255, '\n');
			cout << "Ви ввели невірні дані, попробуйте знову: " << endl;
			cout << " Година: "; cin >> tmp[0];
		} while (cin.fail() || tmp[0] < 1 || tmp[0]>24);
	}
	cin.get(); cin.sync();
	cout << "Хвилина: "; cin >> tmp[1];
	if (cin.fail() || tmp[1] < 0 || tmp[1]>60)
	{
		do
		{
			cin.clear();
			cin.ignore(255, '\n');
			cout << "Ви ввели невірні дані, попробуйте знову: " << endl;
			cout << " Хвилина: "; cin >> tmp[1];
		} while (cin.fail() || tmp[1] < 0 || tmp[1]>60);
	}
	cout << endl;
	cout << "Список поїздів, які відходять після введеного часу:" << endl;
	cout << endl;
	cout << "========================================================="
		<< endl;
	cout << "| № |    Призначення    |          Тип          |  Час  |"
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
		"звичайний",
		"підвищеного комфорту",
		"швидкісний експрес"
	};
	cout << "Введіть ім'я файлу: "; cin.getline(filename, 20);
	int N;
	cout << "Введіть N: "; cin >> N;
	do
	{
		if (cin.fail())
		{
			cin.clear();
			cin.ignore(255, '\n');
			cout << "Ви ввели невірні дані, попробуйте знову: " << endl;
			cout << "Введіть N: "; cin >> N;
		}
	} while (cin.fail());
	int menuItem;
	do {
		cout << endl << endl << endl;
		cout << "Виберіть дію:" << endl << endl;
		cout << " [1] - введення даних з клавіатури" << endl;
		cout << " [2] - вивід даних на екран" << endl;
		cout << " [3] - доповнити існуючий файл" << endl;
		cout << " [4] - вилучити елемент з файлу" << endl;
		cout << " [5] - редагування файлу" << endl;
		cout << " [6] - сортування за станцією" << endl;
		cout << " [7] - сортування за часом" << endl;
		cout << " [8] - поїзди які відходять після введеного часу" << endl;
		cout << " [0] - вихід та завершення роботи програми" << endl << endl;
		cout << "Введіть значення: "; cin >> menuItem;
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
			cout << "Введіть кількість елементів для доповнення: "; cin >> No;
			do
			{
				if (cin.fail())
				{
					cin.clear();
					cin.ignore(255, '\n');
					cout << "Ви ввели невірні дані, попробуйте знову: " << endl;
					cout << "Введіть N: "; cin >> No;
				}
			} while (cin.fail());
			/*do
			{
				cout << "Введіть назву файлу: "; cin >> filename;
				are_open = true;
				CreateAndAdd(stud, No, filename);
			} while (!are_open);*/
			CreateAndAdd(stud, No, filename);
			N += No;
			break;
		case 4:
			cout << "Введіть номер рядка: "; cin >> no;
			do
			{
				if (cin.fail())
				{
					cin.clear();
					cin.ignore(255, '\n');
					cout << "Ви ввели невірні дані, попробуйте знову: " << endl;
					cout << "Введіть номер рядка: "; cin >> no;
				}
			} while (cin.fail());
			/*do
			{
				cout << "Введіть назву файлу: "; cin >> filename;
				are_open = true;
				Remove(filename, no, are_open);
			} while (!are_open);*/
			Remove(filename, no/*, are_open*/);
			N--;
			break;
		case 5:
			/*do
			{
				cout << "Введіть назву файлу: "; cin >> filename;
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
			cout << "Ви ввели помилкове значення! Введіть номер вибраного пункту меню" << endl;
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