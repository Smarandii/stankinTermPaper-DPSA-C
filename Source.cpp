#include <iostream>
#include <ctime>
#define _CRT_SECURE_NO_WARNINGS

class List
{
    class Node
    {
    public:
        char str[80];
        Node* next;
        Node* prev;
    };

    Node* first;
    Node* cursor;
    Node* last;

public:
    List() : last(NULL), first(NULL), cursor(NULL)
    {}

    ~List()
    {
        Node* ptr = NULL, * pdel; //     Два указателя птр указатель с помошью которого мы переходим от элемента к элементу,
                                 //     а pdel указатель элемента который удаляем

        ptr = first;

        while (ptr != last)
        {
            pdel = ptr;
            ptr = ptr->next;
            free(pdel);
        }
        free(last);

    }

    void StartSet()
    {
        cursor = first;
    }

    void EndSet()
    {
        cursor = last;
    }

    int GetCursor()
    {
        Node* ptr = first;
        int pos = 0;

        while (ptr != last && ptr != cursor)
        {
            ptr = ptr->next;
            pos++;
        }

        return pos;
    }

    int GetLenght() // Функция возвращает длину листа
    {
        Node* ptr = first;
        int lenght = 0;

        if (!first)
            return 0;

        while (ptr != last)
        {
            ptr = ptr->next;
            lenght++;
        }

        return lenght + 1;
    }

    void Next()
    {
        if (!cursor->next)
            printf("None\n");
        else
        {
            cursor = cursor->next;
        }
    }

    void Back()
    {
        if (!cursor->prev)
            printf("None\n");
        else
        {
            cursor = cursor->prev;
        }
    }

    void NewArr(char* c)
    {
        Node* ptr;
        ptr = (Node*)malloc(sizeof(Node));

        if (!ptr)
        {
            printf("Out of memory\n");
            exit(1);
        }

        strcpy(ptr->str, c);
        ptr->next = NULL;
        ptr->prev = NULL;
        first = last = cursor = ptr;
        return;
    }

    char* GetData(long count)
    {
        long i;
        Node* ptr;

        if (count >= GetLenght())
            count -= GetLenght();

        if (count < 0)
            count += GetLenght();

        if (count > GetLenght())
        {
            printf("Out of bounds of an array\n");
            exit(1);
        }

        if (GetLenght() / 2 > count)
        {
            i = 0;
            ptr = first;
            while (i != count && ptr)
            {
                ptr = ptr->next;
                i++;
            }
        }
        else
        {
            i = GetLenght() - 1;
            ptr = last;
            while (i != count && ptr)
            {
                ptr = ptr->prev;
                i--;
            }
        }

        if (count == count && ptr)
            return ptr->str;
        else
        {
            printf("Out of bounds of an array\n");
            exit(1);
        }
    }

    void DelRight()
    {
        long i;
        Node* ptr = cursor->next, * prevptr = 0;

        if (ptr)
            prevptr = ptr->prev;

        if (ptr == last)
            last = prevptr;

        if (ptr == first)
            first = first->next;

        if (prevptr)prevptr->next = ptr->next;
        if (ptr->next)
            ptr->next->prev = prevptr;

        if (prevptr && ptr->next == prevptr)
        {
            prevptr->next = 0;
            prevptr->prev = 0;
        }
        free(ptr);
    }

    void Del()
    {
        Node* ptr = cursor, * prevptr = 0;
        if (ptr)
            prevptr = ptr->prev;

        cursor = ptr->next;

        if (ptr == last)
            last = prevptr;

        if (ptr == first)
            first = first->next;

        if (prevptr)
            prevptr->next = ptr->next;
        else
            first = ptr->next;

        if (ptr->next)
            ptr->next->prev = prevptr;
        else
        {
            last = prevptr;
            cursor = prevptr;
        }

        if (prevptr && ptr->next == prevptr)
        {
            prevptr->next = 0;
            prevptr->prev = 0;
        }
        free(ptr);

        if (!GetLenght())
        {
            first = 0;
            last = 0;
            cursor = 0;
        }
    }

    void DelLeft()
    {
        long i;
        Node* ptr = cursor->prev, * prevptr = 0;

        if (ptr)
            prevptr = ptr->prev;

        if (ptr == last)
            last = prevptr;

        if (ptr == first)
            first = first->next;

        if (prevptr)
            prevptr->next = ptr->next;
        else
            first = ptr->next;
        ptr->next->prev = prevptr;

        if (prevptr && ptr->next == prevptr)
        {
            prevptr->next = 0;
            prevptr->prev = 0;
        }

        free(ptr);
    }

    void PushLeftCursor(char* ch)
    {
        long i = 0;
        Node* ptr = cursor;

        if (!ptr)
        {
            NewArr(ch);
            return;
        }

        Node* p = ptr->prev;

        ptr->prev = (Node*)malloc(sizeof(Node));
        if (!ptr->prev)
        {
            printf("Out of memory\n");
            exit(1);
        }

        ptr->prev->next = ptr;
        ptr = ptr->prev;

        strcpy(ptr->str, ch);
        ptr->prev = p;

        if (p)
        {
            p->next = ptr;
            if (cursor == first)
            {
                first = ptr;
            }
        }
        else
        {
            first->next = ptr;
            first->prev = ptr;
            last = ptr;
            last->prev = first;
        }



        if (GetCursor() == GetLenght())
            last = ptr;

    }

    void PushRightCursor(char* ch)
    {
        Node* ptr = cursor;

        if (!ptr)
        {
            NewArr(ch);
            return;
        }

        Node* p = ptr->next;

        ptr->next = 0;
        ptr->next = (Node*)malloc(sizeof(Node));

        if (!ptr->next)
        {
            printf("Out of memory\n");
            exit(1);
        }

        ptr->next->prev = ptr;
        ptr = ptr->next;

        strcpy(ptr->str, ch);
        ptr->next = p;

        if (p)
        {
            p->prev = ptr;
            if (cursor == last)
            {
                last = ptr;
            }
        }
        else
        {
            first->next = ptr;
            first->prev = ptr;
            last = ptr;
            last->next = first;
        }


    }

    bool eofstr(long count = 0)
    {
        if (GetLenght() > count)
            return 1;
        return 0;
    }

    void printRev()
    {
        Node* ptr = last;
        int i = GetLenght();
        do
        {
            i--;
            printf("%s", ptr->str);
            if (i == GetCursor())
                printf(" <-");
            putchar('\n');
            ptr = ptr->prev;
        } while (ptr && ptr != last);

        printf("\n");
    }

    void showMas()
    {
        Node* ptr = first;
        int i = 0;
        if (!ptr)
            return;
        printf("\n Лист в прямом порядке:\n");
        do
        {
            printf("%s", ptr->str);
            if (i == GetCursor())
                printf(" <-");
            putchar('\n');
            ptr = ptr->next;
            i++;
        } while (ptr && ptr != first);
        printf("\n Лист в обратном порядке:\n");

        printRev();
    }
};

void menu(bool access_granted)
{
    printf("\n\n****\n");
    if (access_granted)
    {
        printf("\
            \r1. Сделать пустой список\n \
            \r2. Показать весь массив\n \
            \r3. Проверка на пустой список\n \
            \r4. Установить рабочий указатель в начало списка\n \
            \r5. Установить рабочий указатель в конец списка\n \
            \r6. Проверка указателя на местонахождение : в начале списка\n \
            \r7. Проверка указателя на местонахождение : в конце списка\n \
            \r8. Передвинуть указатель вперёд\n \
            \r9. Передвинуть указатель назад\n \
            \r12. Показать значение до указателя\n \
            \r13. Показать значение после указателя\n \
            \r14. Удалить элемент списка до указателя\n \
            \r15. Удалить элемент после указателя\n \
            \r16. Удалить элемент \n \
            \r17. Взять элемент структуры до указателя\n \
            \r18. Взять элемент структуры после указателя\n \
            \r19. Изменить элемент до указателя\n \
            \r20. Изменить элемент после указателя\n \
            \r21. Добавить элемент до указателя\n \
            \r22. Добавить элемент после указателя\n \
            \r23. Завершить работу с структурой\n");
    }
    else
        printf("1. Начало работы со списком\n \
                \r2. Завершить работу\n");
    printf("****\n\n");
}

void main()
{
    bool access_granted = false;
    char ch[80];
    int choice;

    List arr;
    while (1)
    {
        menu(access_granted);
        scanf("%s", ch);
        choice = 0;
        for (int i = 0; ch[i] != '\0' && isdigit(ch[i]); i++)
            choice = choice * 10 + ch[i] - '0';

        if (access_granted && !array_is_empty(arr))
        {
            if (choice == 1) {
                arr.~List();
                arr = List();
                printf("*Список обнулен*");
                }
            if (choice == 2) {
                arr.showMas();
            }
            if (choice == 3) {
                if (arr.eofstr())
                    printf("В массие есть %d элементы\n", arr.GetLenght());
                else
                    printf("Массив пуст\n");
            }
            if (choice == 4) {
                arr.StartSet();
                printf("Указатель в начале списка\n");
            }
            if (choice == 5) {
                arr.EndSet();
                printf("Указатель в конце списка\n");
            }
            if (choice == 6) {
                if (!arr.eofstr())
                {
                    printf("Массив пуст\n");
                }
                if (arr.GetCursor() == 0)
                    printf("Указатель в начале\n");
                else
                    printf("Указатель не в начале\n");
            }
            if (choice == 7) {

                if (!arr.eofstr())
                {
                    printf("Массив пуст\n");
                }
                if (arr.GetCursor() == arr.GetLenght() - 1)
                    printf("Указатель в конце\n");
                else
                    printf("Указатель не в конце\n");

            }
            if (choice == 8) {
                if (!arr.eofstr()) printf("Массив пуст\n");
                arr.Next();
                arr.showMas();
            }

            if (choice == 9) {
                if (!arr.eofstr())
                {
                    printf("Массив пуст\n");
                }
                arr.Back();
                arr.showMas();
            }
            if (choice == 12) {
                if (!arr.eofstr())
                {
                    printf("Массив пуст\n");
                }
                printf("Значение перед указателем: %s", arr.GetData(arr.GetCursor() - 1));
            }
            if (choice == 13) {
                if (!arr.eofstr())
                {
                    printf("Массив пуст\n");
                }
                printf("Значение после указателем: %s", arr.GetData(arr.GetCursor() + 1));
            }
            if (choice == 14) {
                if (!arr.eofstr())
                {
                    printf("Массив пуст\n");
                }
                arr.DelLeft();
                printf("Элемент удален\n");
                arr.showMas();
            }
            if (choice == 15) {
                if (!arr.eofstr())
                {
                    printf("Массив пуст\n");
                }
                arr.DelRight();
                printf("Элемент удален\n");
                arr.showMas();
            }
            if (choice == 16) {
                if (!arr.eofstr())
                {
                    printf("Массив пуст\n");
                }
                arr.Del();
                printf("Элемент удален\n");
                arr.showMas();
            }
            if (choice == 17) {
                if (!arr.eofstr())
                {
                    printf("Массив пуст\n");
                }
                strcpy(ch, arr.GetData(arr.GetCursor() - 1));
                arr.DelLeft();
                arr.showMas();
                printf("Значение перед указателем: %s", ch);
            }
            if (choice == 18) {
                if (!arr.eofstr())
                {
                    printf("Массив пуст\n");
                }
                strcpy(ch, arr.GetData(arr.GetCursor() + 1));
                arr.DelRight();
                arr.showMas();
                printf("Значение перед указателем: %s", ch);
            }
            if (choice == 19) {
                if (!arr.eofstr())
                {
                    printf("Массив пуст\n");
                }
                printf("Введите значени\n");
                scanf("%s", ch);

                strcpy(arr.GetData(arr.GetCursor() - 1), ch);
                arr.showMas();
            }
            if (choice == 20) {
                if (!arr.eofstr())
                {
                    printf("Массив пуст\n");
                }

                printf("Введите значени\n");
                scanf("%s", ch);

                strcpy(arr.GetData(arr.GetCursor() + 1), ch);
                arr.showMas();
            }
            if (choice == 21) {

                printf("Введите значени\n");
                scanf("%s", ch);

                arr.PushLeftCursor(ch);
                arr.showMas();
            }
            if (choice == 22) {
                printf("Введите значени\n");
                scanf("%s", ch);

                arr.PushRightCursor(ch);
                arr.showMas();
            }
            if (choice == 23) {
                arr.~List();
                access_granted = !access_granted;
            }
        }
        else
        {
            
            if (choice == 1) 
            {
                access_granted = !access_granted;
                arr = List();
            }
            if (choice == 2) {
                break;
            }
        }

    }
}

