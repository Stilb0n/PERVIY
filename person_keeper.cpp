#include "person_keeper.h"

PersonKeeper::PersonKeeper()
{

}

PersonKeeper::~PersonKeeper()
{
	// динамические обьекты отсутствуют
}

//  возвращает ссылку на единственный обьект класса
PersonKeeper &PersonKeeper::Instance()
{
	static PersonKeeper instance; // static, чтобы обьект не создавался каждый раз при вызове функции

	return instance;
}

// функция,  для записи значения из файла по заданному пути в стек
void PersonKeeper::ReadPersons(QString path)
{
	QFile file(path);

	if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) // Принимается попытка открыть файл на чтение
	{
		throw "Error: readPersons(): Couldn't open a file!"; // если файл не открылся, выбрасываем исключение
	}

	QTextStream stream(&file); // поток текстовых данных файла
	QString line; // буфер в который считываются строки

	while (stream.readLineInto(&line)) // считываем каждую строку, пока файл не закончится
	{
		stack_.Push(Person(line)); //  используя конструктор создаем личность ,у конструктора в аргументах одна строкой в которой должно содержаться полное имя и добавляем её в стек
	}

	file.close(); // закрытие файла
}

// функция записи информации из хранителя в файл
void PersonKeeper::WritePersons(QString path) const
{
	QFile file(path);

	if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) // пытаемся открыть файл на запись
	{
		throw "Error: writePersons(): Couldn't open a file!"; // если файл не открылся, выбрасываем исключение
	}

	QTextStream stream(&file); // поток текстовых данных файла

	stack_.ForEach([&](const Person &value) // перебираем все значения, находящиеся в хранителе
	{
		stream << value.last_name() << '\t' << value.first_name() << '\t' << value.patronymic() << Qt::endl; // записываем значения в файл для каждой строки
	});

	file.close(); // закрываем файл
}

// экспорт стэка имён в список строк
QStringList PersonKeeper::ToQStringList() const
{
	QStringList string_list; // создаем список строк

	stack_.ForEach([&](const Person &value) // перебираем все личности
	{
		string_list.prepend(value.last_name() + " " + value.first_name() + " " + value.patronymic()); // записываем в начало списка строк новую строку, состоящую из всех частей имени личности
	});

	return string_list;
}

int PersonKeeper::Size()
{
	return stack_.Size();
}

void PersonKeeper::Clear()
{
	return stack_.Clear();
}
