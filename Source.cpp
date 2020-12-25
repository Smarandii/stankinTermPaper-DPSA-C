#include <iostream>
#include <ctime>
#define _CRT_SECURE_NO_WARNINGS

class Line {

    class Node
    {
    public:
        int vector[10];
        Node* next;
        Node* prev;
    };
    
    Node* START;
    Node* END;

    void check_memory(Node* ptr) {
        if (!ptr)
        {
            printf("[!] Ошибка выделения памяти [!]\n");
            exit(1);
        }
    }

    void write_vector(Node* ptr, int* x) {
        for (int i = 0; i < 10; i++)
            ptr->vector[i] = x[i];
    }

    void print_vector(Node* ptr) {
        for (int i = 0; i < 10; i++) printf("\n%d, ", ptr->vector[i]);
    }

public:
    bool is_started = false;

    Line() : START(NULL), END(NULL), is_started(true) {}

    ~Line() {
        Node* ptr, * pdel; 
        ptr = END;
        while (ptr != START)
        {
            pdel = ptr;
            ptr = ptr->next;
            free(pdel);
        }
        free(START);

    }

    int is_empty() { 
        if (START == NULL && END == NULL) printf("[!] ОЧЕРЕДЬ ПУСТА [!]");
        return START == NULL && END == NULL; }

    void print_value_from_start() { print_vector(START); }

    void delete_value_from_start() 
    {
        Node* ptr = START; 
        START = ptr->next;
        free(ptr);
    }

    int* cut_value_from_start() {
        Node* ptr = START;
        int* x;
        x = START->vector;
        START = ptr->next;
        free(ptr);
        return x;
    }

    void edit_value_from_start(int* x) {
        Node* ptr = START;
        write_vector(ptr, x);
        START = ptr; 
    }

    void add_value_to_end(int* x) {
        Node* ptr;
        ptr = (Node*)malloc(sizeof(Node));
        check_memory(ptr);
        write_vector(ptr, x);
        ptr->next = END;
        END = ptr;
    }

    void print() {
        Node* ptr = END;
        while (ptr != NULL)
        {
            if (ptr == END) printf("\nEND: ");
            if (ptr == START) printf("\nSTART: ");
            print_vector(ptr);
            ptr = ptr->next;
        }    
    }

    void end_work() { is_started = false; }

};

int* get_vector_from_user() {
    int vector[10];
    printf("\n[!] ВВЕДИТЕ 10 ЭЛЕМЕНТОВ ЧЕРЕЗ ПРОБЕЛ [!]: "); 
    for (int i = 0; i < 10; i++) {
        scanf("%d ", vector[i]);
    }
    return vector;
}


void menu(bool access_granted)
{
    if (access_granted)
    {
        printf("\n\
            \r1. Сделать очередь пустой\n \
            \r2. Проверка на пустоту\n \
            \r3. Показать значение элемента в начале очереди\n \
            \r4. Удалить начало очереди\n \
            \r5. Взять элемент из начала очереди\n \
            \r6. Изменить значение элемента в начале очереди\n \
            \r7. Добавить элемент в конец очереди\n \
            \r8. Распечатать очередь\n \
            \r9. Закончить работу с очередью\n\n");
    }
    else
        printf("\n\r1. Начать работу с очередью\n \
                \r2. Закончить работу с программой\n\n");
}
    

void main()
{
    bool access_granted = false;
    int* x;
    int choice;

    Line line;
    while (true)
    {
        menu(access_granted);
        scanf("%d", choice);
        choice = 0;

        if (access_granted && !line.is_empty())
        {
            if (choice == 1) {
                line.~Line();
                line = Line();
                printf("\n[!] ОЧЕРЕДЬ ОПУСТОШЕНА [!]\n");
                }
            if (choice == 2) {
                if (!line.is_empty()) printf("[!] ОЧЕРЕДЬ НЕ ПУСТА [!]");
            }
            if (choice == 3) {
                line.print_value_from_start();
            }
            if (choice == 4) {
                line.delete_value_from_start();
            }
            if (choice == 5) {
                x = line.cut_value_from_start();
            }
            if (choice == 6) {
                x = get_vector_from_user();
                line.edit_value_from_start(x);
            }
            if (choice == 7) {
                x = get_vector_from_user();
                line.add_value_to_end(x);
            }
            if (choice == 8) {
                line.print();
            }

            if (choice == 9) {
                line.end_work();
                access_granted = line.is_started;
            }
        }
        else
        {
            
            if (choice == 1) 
            {
                line = Line();
                access_granted = line.is_started;
            }
            if (choice == 2) {
                break;
            }
        }

    }
}

