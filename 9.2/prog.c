#include <stdio.h>

#define MAX_LINE_LENGTH 256

void prog(const char* file1, const char* file2) {
    FILE* fp1 = fopen(file1, "r");  // Открываем первый файл для чтения
    FILE* fp2 = fopen(file2, "r");  // Открываем второй файл для чтения

    if (fp1 == NULL || fp2 == NULL) {
        printf("Unable to open the files.\n");
        return;
    }

    char line1[MAX_LINE_LENGTH];  // Буфер для строки из первого файла
    char line2[MAX_LINE_LENGTH];  // Буфер для строки из второго файла
    int isFile1End = 0;  // Флаг, указывающий, закончился ли первый файл
    int isFile2End = 0;  // Флаг, указывающий, закончился ли второй файл

    while (!isFile1End || !isFile2End) {  // Пока есть строки хотя бы в одном из файлов
        if (!isFile1End && fgets(line1, sizeof(line1), fp1) != NULL) {
            printf("%s", line1);  // Выводим строку из первого файла
        } else {
            isFile1End = 1;  // Устанавливаем флаг, если первый файл закончился
        }

        if (!isFile2End && fgets(line2, sizeof(line2), fp2) != NULL) {
            printf("%s", line2);  // Выводим строку из второго файла
        } else {
            isFile2End = 1;  // Устанавливаем флаг, если второй файл закончился
        }
    }

    fclose(fp1);  // Закрываем первый файл
    fclose(fp2);  // Закрываем второй файл
}

int main(int argc, char* argv[]) {
    if (argc < 3) {
        printf("Usage: %s <file1> <file2>\n", argv[0]);
        return 1;
    }

    char* file1 = argv[1];  // Имя первого файла из аргументов командной строки
    char* file2 = argv[2];  // Имя второго файла из аргументов командной строки

    prog(file1, file2);  // Вызов функции для перекрестного вывода строк из файлов

    return 0;
}
