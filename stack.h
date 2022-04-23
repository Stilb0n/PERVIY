#ifndef STACK_H
#define STACK_H

#include <functional>

#include "e_stack_exception.h"
#include "e_stack_empty.h"

template <class T>
class Stack
{
public:
	~Stack(); // деструктор

	void Push(const T &value); // Функция которая кладёт значение в стек
	const T Pop(); // Функция извлекающая значение из стека

	void ForEach(std::function<void(const T &value)> f) const; // функция перебора всех хранящихся значений, для вывода на экран например

	int Size(); // размер стека
	void Clear(); // удаление из стека всех узлов

private:
	struct Node // звено
	{
		const T value_; // храним  значение (константное)

		Node *prev_ = nullptr; // указатель на предыдущее звено стека
	};

	Node *back_ = nullptr; // последний элемент стека

	int size_ = 0;
};

// класс шаблонный и вынести определения в отдельный файл не представляется возможным, поэтому они внутри заголовка

// деструктор
template <class T>
Stack<T>::~Stack()
{
	Clear();
}

// Функция, кладущая значение в стек
template <class T>
void Stack<T>::Push(const T &value)
{
	Node *node = new Node{ value, back_ }; // создаем новое звено, предыдущее для которого - последнее на данный момент звено

	if (node == nullptr) // если память под новое звено не выделилась
	{
		throw EStackException("Lack of memory."); // возвращаем исключение, которое говорит о том что память закончилась
	}

	back_ = node; // делаем только что созданное звено последним

	size_++; // увеличиваем размер стека на единицу
}

// функция извлекающая значение из стека
// сначала значение запоминается, потом удаляется из стека, и потом возвращается из функции
// значение взвраащается не по ссылке, т. к. значения хранящееся в стэке, удаляется и ссылаться не на что
template <class T>
const T Stack<T>::Pop()
{
	if (back_ == nullptr) // если стек пуст, возвращаем исключение
	{
		throw EStackEmpty();
	}

	const T value = back_->value_; // сохраняем значение звена

	Node *tmp = back_; // сохраняем ссылку на звено

	back_ = back_->prev_; // перемещаем конец стэка на предпоследнее звено

	delete tmp; // удаляем звено

	size_--; // уменьшаем размер стека

	return value; // возвращаем сохраненое значение звена
}

// функция перебора всех элементов стека, используется для вывода в файл.
// значения передаются по ссылке, т. к. в отличии от Pop, они не удаляются
template <class T>
void Stack<T>::ForEach(std::function<void(const T &value)> f) const
{
	Node *it = back_; // перебор всех элементов, начиная с последнего

	while (it != nullptr) // заканчивая первым
	{
		f(it->value_); // вызов функции обратной связи

		it = it->prev_;
	}
}

template <class T>
int Stack<T>::Size()
{
	return size_; // размер стека
}

template <class T>
void Stack<T>::Clear()
{
	while (back_ != nullptr) // пока в стеке есть элементы
	{
		Node *tmp = back_; // сохраняем последний элемент

		back_ = back_->prev_; // делаем последним элементом предпоследний

		delete tmp; // удаляем сохранённый последний элемент
	}
}

#endif // STACK_H
