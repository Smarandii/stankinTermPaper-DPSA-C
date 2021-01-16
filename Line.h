#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>

class Line // Структура описывающая очередь
{
	class Node // Элемент структуры
	{
	public:
		int data[20] = { 0 }; // Статичный вектор
		int size; // Его длина
		Node* next; // Указатель на следующий элемент
		Node* prev; // Указатель на пред элемент

		Node() :next(0), size(0), prev(0)
		{}
	};

	Node* first; // Указатель на следующий элемент
	int max_size; // Дно очереди

	void New(int* mass, int size) // Содание первого элемента
	{
		first = (Node*)malloc(sizeof(Node));
		*first = Node();
		
		for (int i = 0; i < size; i++)
			first->data[i] = mass[i];
		
		first->size = size;
	}

public:
	Line() : first(0), max_size(15)
	{}

	~Line() // Деструктор
	{
		Node* ptr = NULL, * pdel;

		ptr = first;

		while (ptr)
		{
			pdel = ptr;
			ptr = ptr->next;
			free(pdel);
		}
		first = 0;
	}

	void append(int* mas, int size) // Функция добавляющая в конец очереди
	{
		Node* ptr = first;
		if (!first)
		{
			New(mas, size); // Если нет элемент вызывает метод для создания очереди
			return;
		}
		while (ptr->next)
			ptr = ptr->next;

		ptr->next = (Node*)malloc(sizeof(Node)); // Выделяем память под элемент
		ptr->next->prev = ptr; // Сохраняем связь

		ptr = ptr->next;
		ptr->next = 0;		// Обнуляем указатель на след элимент

		for (int i = 0; i < size; i++) // Заносим данные в дату
			ptr->data[i] = mas[i];
		ptr->size = size;
	}

	void del_first() // удаляем начало очереди
	{
		if (!first)
			return;

		Node* ptr = first;

		if (first->next)
		{
			first = first->next;
			first->prev = 0;
			free(ptr);
		}
		else
		{
			free(ptr);
			first = 0;
		}
	}

	bool eof()
	{
		if (first)
			return 1;
		return 0;
	}

	void prmenu()
	{
		puts(" \
            \r1)Сделать очередь пустой						\n\
            \r2)Проверка на пустую очередь					\n\
            \r3)Показать первый вектор						\n\
            \r4)Удалить первый вектор						\n\
            \r5)Взять первый вектор							\n\
            \r6)Изменить первый вектор						\n\
            \r7)Добавить вектор в конец						\n\
            \r8)Вывести очередь								\n\
            \r0)Завершить работу							\n\
            ");
	}

	void print_line() // Выводим всю очередь
	{
		Node* ptr = first;
		while (ptr)
		{
			for (int i = 0; i < ptr->size; i++)
				printf("%d\t", ptr->data[i]);
			puts("");
			ptr = ptr->next;
		}
	}

	void menu()
	{
		int choice, size, * pointer_arr;
		int arr[20];
		do
		{

			puts("1)Начать работу\n\
                \r2)Закончить работу");
			scanf("%d", &choice);
			getchar();
			if (choice == 1)
				do
				{
					prmenu(); // Вызов текста меню
					scanf("%d", &choice);
					getchar();

					switch (choice)
					{
					case 0:
						this->~Line(); // Удаление очереди
						break;
					case 1:
						this->~Line(); // Удаление очереди
						break;
					case 2:
						if (!first) // Проверка
							puts("Очередь пуста");
						else
							puts("В очереди есть элементы");
						break;
					case 3:
						if (first)
							for (int i = 0; i < first->size; i++)
								printf("%d\t", first->data[i]);
						else
							puts("Очередь пуста");
						puts("");
						break;
					case 4:
						if (first)
						{
							del_first(); // Удаляем первый элемент
							print_line(); // Выводим очередь
							putchar('\n');
						}
						else
							puts("Очередь пуста");
						break;
					case 5:
						if (first)
						{
							for (int i = 0; i < first->size; i++)
								arr[i] = first->data[i];
							size = first->size;

							del_first();
							print_line();
							putchar('\n');
							printf("Взятый элемент:\n");

							for (int i = 0; i < size; i++)
								printf("%d\t", arr[i]);
							puts("\n");

						}
						else
							puts("Очередь пуста");
						break;
					case 6:

						do {
							puts("Введите длину вектора");
							scanf("%d", &size);
							if (size > 20 || size <= 0)
								puts("Не корректный размер");
						} while (size > 20 || size <= 0);

						puts("Введите вектора");
						for (int i = 0; i < size; i++)
							scanf("%d", &first->data[i]);
						first->size = size;

						print_line();
						putchar('\n\n');
						break;
					case 7:

						do {
							puts("Введите длину вектора");
							scanf("%d", &size);
							if (size > 20 || size <= 0)
								puts("Не корректный размер");
						} while (size > 20 || size <= 0);

						puts("Введите вектор");
						for (int i = 0; i < size; i++)
							scanf("%d", &arr[i]);

						append(arr, size);
						print_line();
						putchar('\n\n');
						break;
					case 8:
						if (first)
						{
							print_line(); //Вывод очереди
							putchar('\n');
						}
						else
							puts("Очередь пуста");
						break;
					default:
						break;
					}


				} while (choice);
		} while (choice != 2);
	}
};