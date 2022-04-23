#ifndef PERSONKEEPER_H
#define PERSONKEEPER_H

#include <QString>
#include <QTextStream>
#include <QFile>

#include "person.h"
#include "stack.h"

// паттерн Singleton, в этом классе хранятся личности
class PersonKeeper
{
public:
	static PersonKeeper &Instance(); // функция сделана статической, для того чтобы объект не создавался каждый раз при её вызове.

	void ReadPersons(QString path); // функция для записи ФИО со стека в файл
	void WritePersons(QString path) const; // сфункция для считывания ФИО с файла в стек

	QStringList ToQStringList() const; // экспорт стэка имён в список строк
    void Clear(); // очищение хранилища личностей
	int Size(); // количество хранимых личностей
	

private:
	PersonKeeper(); // класс можно создать только через Instance - конструкторы и оператор присвоения недоступны из вне
	PersonKeeper(const PersonKeeper &); // оставляем конструктор копирования по умолчанию, т. к. все член данные можно скопировать простым присвоением
	~PersonKeeper(); // динамические обьекты отсутствуют

	PersonKeeper &operator=(const PersonKeeper &); // оставляем оператор присовения по умолчанию, по той же причине

	Stack<Person> stack_; // стэк полных имен
};

#endif // PERSONKEEPER_H
