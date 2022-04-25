#include "main_window.h"

#include <QApplication>

// файлы для тестирования:
// input_1.txt - большой список имен, разделенных пробелами
// input_2.txt - небольшой список имен, имеющих лишние пробелы в начале и между словами, также присутствуют пустые строки
// input_3 и input_4 
// автоматически сгенерированный файл, без изменений
int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	MainWindow w;
	w.show();
	return a.exec();
}
