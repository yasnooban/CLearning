#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    int fd;  // Объявление файлового дескриптора
    int StrCount = 0;  // Счетчик строк, инициализируется нулем
    int BufLength;  // Длина буфера, который будет прочитан из файла
    char *StrOut;  // Указатель на строку для чтения данных из файла
    char *StrTmp;  // Временный указатель на строку для хранения прочитанных данных
    char name[] = "file.fifo";  // Имя файла FIFO (именованный канал)

    // Устанавливаем маску создания файлов в 0, чтобы у файлов были все разрешения (777)
    umask(0);

    // Открытие файла FIFO для чтения
    if((fd = open(name, O_RDONLY)) < 0){
        // Если открыть файл не удалось, выводим сообщение об ошибке и выходим с кодом -1
        printf("error\n");
        return -1;
    } else {
        // Читаем длину буфера из файла
        if (sizeof(int) == read(fd, &BufLength, sizeof(int))){
            // Выделяем память для строковых буферов
            StrOut = malloc(BufLength * sizeof(char));
            StrTmp = malloc(BufLength * sizeof(char));
            // Выводим размер буфера
            printf("Buffer size: %d\n", BufLength);
            // Читаем данные из файла FIFO в течение трех итераций
            while (StrCount++ < 3){
                // Читаем данные из FIFO в StrOut
                if (read(fd, StrOut, BufLength) > strlen(StrTmp)){
                    // Освобождаем память, выделенную для StrTmp, и копируем новую строку
                    free(StrTmp);
                    StrTmp = strdup(StrOut);
                }
                // Выводим строку, прочитанную из FIFO
                printf("FIFO: %s\n", StrOut);
            }
            // Закрываем файл FIFO
            close(fd);
        }
    }
    return 0;  // Возвращаем 0, указывая на успешное завершение программы
}