

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 256

void tail(const char* filename, int n) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("mistake open the file: %s\n", filename);
        return;
    }

    // создание двумерного массива lines, куда будем заносить строки
    char** lines = (char**)malloc(sizeof(char*) * n);
    for (int i = 0; i < n; i++) {
        lines[i] = (char*)malloc(sizeof(char) * MAX_LINE_LENGTH);
    }

    int lineCount = 0; // количество прочитанных строк
    int currentLine = 0; // индекс текущей строки

    // Считывание строк из файла
    char buffer[MAX_LINE_LENGTH];
    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        // Копирование строки из буфера в двумерный массив lines по индексу currentLine
        strcpy(lines[currentLine], buffer);

        // Обновление индекса текущей строки и количества строк
        currentLine = (currentLine + 1) % n; // при достижении 5 строки у нас значение будет 0, таким образом больше 5 не обработаем
        lineCount++;
    }

    // Вывод последних N строк
    int startIndex;
    if (lineCount > n) {
        startIndex = currentLine;
    } else {
        startIndex = 0;
    }
    for (int i = 0; i < n; i++) {
        printf("%s", lines[(startIndex + i) % n]);
    }

    // Освобождение памяти
    for (int i = 0; i < n; i++) {
        free(lines[i]);
    }
    free(lines);

    fclose(file);
}

int main(int argc, char* argv[]) {
    if (argc < 2) { //проверка количества аргументов командной строки
        printf("Usage: %s <filename> [N]\n", argv[0]);
        return 1;
    }

    char* filename = argv[1];
    
    int n = 5; // Значение по умолчанию
    if (argc > 2) { // если количество аргументов командной строки > 2, то используем n=этому числу иначе =5
        n = atoi(argv[2]); // Преобразование строки в целое число
    } 

    tail(filename, n);

    return 0;
}
