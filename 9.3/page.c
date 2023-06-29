#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void page(const char* filename, int linesPerPage, int maxLineLength) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Unable to open the file: %s\n", filename);
        return;
    }

    char* line = (char*)malloc(sizeof(char) * (maxLineLength + 1));  // Буфер для чтения строки
    int lineCount = 0;  // Счетчик строк
    int pageCount = 1;  // Счетчик страниц

    while (fgets(line, maxLineLength + 1, file) != NULL) {
        lineCount++;

        if (lineCount > linesPerPage) {
            pageCount++;
            lineCount = 1;
        }

        printf("Page %d, Line %d: %s", pageCount, lineCount, line);
    }

    free(line);
    fclose(file);
}

int main(int argc, char* argv[]) {
    if (argc < 4) {
        printf("Usage: %s <filename> <lines_per_page> <max_line_length>\n", argv[0]);
        return 1;
    }

    char* filename = argv[1];
    int linesPerPage = atoi(argv[2]);
    int maxLineLength = atoi(argv[3]);

    page(filename, linesPerPage, maxLineLength);

    return 0;
}
