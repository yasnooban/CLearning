#include <stdio.h>
#include <unistd.h>

int main()
{
    int new_ppid = getpid();  // Получение идентификатора текущего процесса (PID) и присвоение его переменной new_ppid
    int old_ppid = getpid();  // Получение идентификатора текущего процесса (PID) и присвоение его переменной old_ppid

    printf("id: %dn ", old_ppid);  // Вывод идентификатора процесса, хранящегося в переменной old_ppid
    printf("id: %dn", new_ppid);  // Вывод идентификатора процесса, хранящегося в переменной new_ppid

};

