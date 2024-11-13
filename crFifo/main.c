#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main()
{
    char BufLength;  // Объявление переменной для хранения данных, которые будут записаны в FIFO
    int fd;  // Объявление файлового дескриптора
    int StrCount = 0;  // Счетчик строк, инициализируется нулем
    char name[] = "4";  // Имя файла FIFO (именованный канал)

    umask(0);  // Установка маски создания файлов в 0, чтобы у файлов были все разрешения (777)

    // Создание именованного канала (FIFO) с именем 'name' и правами доступа 0666
    if (mkfifo(name, S_IFIFO | 0666) < 0) {
        printf("Can't create FIFO\n");  // Если не удалось создать FIFO, выводим сообщение об ошибке
        exit(-1);  // Завершение программы с кодом ошибки -1
    } else {
        // Открытие файла FIFO для записи
        if ((fd = open(name, O_WRONLY)) < 0) {
            printf("Can't open FIFO\n");  // Если не удалось открыть FIFO, выводим сообщение об ошибке
            exit(-1);  // Завершение программы с кодом ошибки -1
        } else {
            // Запись длины буфера в FIFO
            write(fd, &BufLength, sizeof(int));

            // Чтение данных из стандартного ввода и запись их в FIFO в течение трех итераций
            while (StrCount++ < 3) {
                printf("write: ");  // Вывод приглашения для ввода данных
                scanf("%s", &BufLength);  // Чтение строки из стандартного ввода в переменную BufLength
                write(fd, &BufLength, strlen(&BufLength));  // Запись строки в FIFO
            }
            close(fd);  // Закрытие файлового дескриптора
        }
    }
    return 0;  // Возвращение 0, указывая на успешное завершение программы
}


