/*
Worker: Фамилия и инициалы, Должность, Год поступления на работу, Зарплата. Создать массив объектов. Вывести:
а) список работников, стаж работы которых на данном предпри-ятии превышает заданное число лет;
б) список работников, зарплата которых больше заданной;
в) список работников, занимающих заданную должность.
*/
#include <iostream>
#include <fstream>
#include <ctime>

using namespace std;
ifstream fin("worker.txt"); // открыли файл для чтения

class Worker {
private:
	char name[30];
	char position[30]; //должность
	int joiningYear;   //год поступления на работу
	int salary;        //зарплата
public:
	Worker();
	int getSalary();
	int getJoiningYear();
	char* getPosition();
	void show();

};

Worker::Worker()
{
	char temp[1];
	fin.getline(name, 50);
	fin.getline(position, 30);
	fin >> joiningYear;
	fin >> salary;
	fin.getline(temp, 1);//для перехода на новую строку

}
void Worker::show()
{
	cout << "**********************************" << endl;
	cout << "Фамилия и инициалы: " << name << endl;
	cout << "Должность: " << position << endl;
	cout << "Год поступления на работу: " << joiningYear << endl;
	cout << "Зарплата: " << salary << "$" << endl;

}

int Worker::getSalary()
{
	return salary;
}

int Worker::getJoiningYear()
{
	return joiningYear;
}

char* Worker::getPosition()
{
	return position;
}

void showAll(Worker worker_spis[], int n)
{
	for (int i = 0; i < n; i++) {
		worker_spis[i].show(); 
	}
	cout << endl;
}

void sortBySeniority(Worker worker_spis[], int n)
{
	struct tm nowLocal;//Функция для получения сегодняшней даты
	__time64_t long_time;
	_time64(&long_time);
	_localtime64_s(&nowLocal, &long_time);
	int year = nowLocal.tm_year + 1900;
	int month = nowLocal.tm_mon + 1;

	int seniority; //стаж
	cout << "Задайте стаж: ";
	cin >> seniority;
	for (int i = 0; i < n; i++) {
		if (year - worker_spis[i].Worker::getJoiningYear() >= seniority) {
			worker_spis[i].Worker::show();
		}
	}
}

void sortBySalary(Worker worker_spis[], int n)
{
	int salary;
	cout << "Задайте зарплату: ";
	cin >> salary;
	for (int i = 0; i < n; i++) {
		if (worker_spis[i].Worker::getSalary() >= salary) {
			worker_spis[i].Worker::show();
		}
	}
}

void sortByPosition(Worker worker_spis[], int n)
{
	char position[30];
	cout << "Задайте должность: ";
	cin.get();
	cin.getline(position, 30);
	for (int i = 0; i < n; i++) {
		if (!_stricmp(worker_spis[i].Worker::getPosition(), position)) {//сравнение строк без учёта регистра
			worker_spis[i].Worker::show();
		}
	}
}

int main()
{

	Worker* worker_spis; // указатель на тип Worker
	int n = 8;
	worker_spis = new Worker[n]; // объявляем массив N объектов класса worker (оператор new обеспечивает выделение динамической памяти в куче)

	int pick;
	do {
		cout << endl << "1. Показать весь список\n";
		cout << "2. Отсортировать по стажу\n";
		cout << "3. Отсортировать по зарплате\n";
		cout << "4. Отсортировать по должности\n";
		cout << "0. Выход\n";
		cin >> pick;
		switch (pick) {
		case 0: {return 1; }
		case 1: {
			system("cls");
			showAll(worker_spis, n);
			break;
		}
		case 2: {
			system("cls");
			sortBySeniority(worker_spis, n);
			break;
		}
		case 3: {
			system("cls");
			sortBySalary(worker_spis, n);
			break;
		}
		case 4: {
			system("cls");
			sortByPosition(worker_spis, n);
			break;
		}
		default: {cout << "Ошибка! Попробуйте снова\n"; break; }
		}
	} while (pick != 0);
	delete []worker_spis;
	cin.get();
	return 0;
}
