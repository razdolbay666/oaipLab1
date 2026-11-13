#include <stdio.h>

#define MAX_SIZE 20

void CreateStudentFileEz(void);
void GenerateHelloC(void);
void FindMaxOfThree(void);
void SaveArrayToFile(int* arr, int size, const char* file_name);
void LoadArrayFromFile(int* arr, int max_size, int* out_size, const char* file_name);
void ProcessArrayVariant19(void);

void ReplaceTabsWithPercent(void);
void MakeLatinUppercase(void);
void AddHashForLatinLines(void);
void ReplacePunctuationVariant19(void);
void CountSemicolonsPrefix(void);

void CreateSimpleHtml(void);
void CreateCategorizedHtmlVariant19(void);

int main(void) {
    // ---- 8.1 ----
    CreateStudentFileEz();          // 8.1.1  (файл о студенте)
    GenerateHelloC();               // 8.1.1* (генерация hello.c)
    FindMaxOfThree();               // 8.1.2  (максимум из трёх)

    int demo_arr[MAX_SIZE] = { 10, 15, 20, 25 }; // 8.1.3
    int demo_size = 4;
    SaveArrayToFile(demo_arr, demo_size, "array_state19_saved.txt");

    int loaded_arr[MAX_SIZE];
    int loaded_size = 0;
    LoadArrayFromFile(loaded_arr, MAX_SIZE, &loaded_size, "array_state19.txt");

    printf("8.1.3 Loaded array (size=%d): ", loaded_size);
    for (int i = 0; i < loaded_size; ++i) printf("%d ", loaded_arr[i]);
    printf("\n");

    ProcessArrayVariant19();        //8.1.4

    // ---- 8.2 ----
    ReplaceTabsWithPercent();       // 8.2.1  (табуляции - '%')
    MakeLatinUppercase();           // 8.2.2  (латиница - верхний регистр)
    AddHashForLatinLines();         // 8.2.3* ('#' перед строками с латиницей)
    ReplacePunctuationVariant19();  // 8.2.4  (все знаки препинания заменить на '_')
    CountSemicolonsPrefix();        // 8.2.5* (счётчик ';' в начале каждой строки)

    // ---- 8.3 ----
    CreateSimpleHtml();                  // 8.3.1  (HTML)
    CreateCategorizedHtmlVariant19();    // 8.3.2  (<b> для слов ≤3 букв, <i> для слов из маленьких букв)



    double temperature1 = 36;
    double temperature2 = temperature1 * 9 / 5 + 32;
    printf("%f\n", temperature2);

    double power = 3;
    printf("%f\n", power*power*power);

    unsigned int factorial = 4;
    printf("%u\n", 2*3*4);

    double mulBy10 = 1;
    printf("%f\n", mulBy10*10);
    return 0;
}