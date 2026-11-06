#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAX_PATH_LEN 512
#define MAX_SIZE 20
#define FOLDER "\\Desktop\\Lab8Files\\"
#define PATH_IN  "in"
#define PATH_OUT "out"

static int BuildFilePath(const char* direction, const char* file_name,
    char* out_path, size_t out_size) {
    char* user_profile = getenv("USERPROFILE");
    if (user_profile == NULL) {
        printf("Error: USERPROFILE not found!\n");
        return 0;
    }
    snprintf(out_path, out_size, "%s\\Desktop\\Lab8Files\\%s\\%s",
        user_profile, direction, file_name);
    return 1;
}

void CreateStudentFileEz(void) {
    char full_path[MAX_PATH_LEN];
    if (!BuildFilePath(PATH_OUT, "8.1.1.txt", full_path, sizeof(full_path))) return;

    FILE* file = fopen(full_path, "w");
    if (file == NULL) {
        printf("Error opening file!\n");
        return;
    }

    fprintf(file, "Кузьмин Тимофей ПИбд-11");
    fclose(file);
    printf("8.1.1 generated.\n");
}

void GenerateHelloC(void) {
    char full_path[MAX_PATH_LEN];
    if (!BuildFilePath(PATH_OUT, "8.1.1_buffed.c", full_path, sizeof(full_path))) return;

    FILE* file = fopen(full_path, "w");
    if (file == NULL) {
        printf("Error opening file!\n");
        return;
    }

    fprintf(file, "#include <stdio.h>\n\n");
    fprintf(file, "int main(void) {\n");
    fprintf(file, "    printf(\"Author: Kuzmin Timofey PIbd-11\\n\");\n");
    fprintf(file, "    return 0;\n");
    fprintf(file, "}\n");

    fclose(file);
    printf("8.1.1* generated.\n");
}

void FindMaxOfThree(void) {
    char path_in[MAX_PATH_LEN];
    char path_out[MAX_PATH_LEN];
    if (!BuildFilePath(PATH_IN, "in2.txt", path_in, sizeof(path_in)))  return;
    if (!BuildFilePath(PATH_OUT, "8.1.2.txt", path_out, sizeof(path_out))) return;

    FILE* fin = fopen(path_in, "r");
    if (fin == NULL) {
        printf("Error opening input file!\n");
        return;
    }
    FILE* fout = fopen(path_out, "w");
    if (fout == NULL) {
        printf("Error opening output file!\n");
        fclose(fin);
        return;
    }

    int a, b, c;
    if (fscanf_s(fin, "%d %d %d", &a, &b, &c) == 3) {
        int max_val = a;
        if (b > max_val) max_val = b;
        if (c > max_val) max_val = c;
        fprintf(fout, "%d", max_val);
    }

    fclose(fin);
    fclose(fout);
    printf("8.1.2 generated.\n");
}

void SaveArrayToFile(int* arr, int size, const char* file_name) {
    char full_path[MAX_PATH_LEN];
    if (!BuildFilePath(PATH_OUT, file_name, full_path, sizeof(full_path))) return;

    FILE* file = fopen(full_path, "w");
    if (file == NULL) {
        printf("SaveArrayToFile Error opening file!\n");
        return;
    }

    fprintf(file, "%d\n", size);
    for (int i = 0; i < size; ++i) {
        fprintf(file, "%d ", arr[i]);
    }
    fclose(file);
}

void LoadArrayFromFile(int* arr, int max_size, int* out_size, const char* file_name) {
    char full_path[MAX_PATH_LEN];
    if (!BuildFilePath(PATH_IN, file_name, full_path, sizeof(full_path))) return;

    FILE* file = fopen(full_path, "r");
    if (file == NULL) {
        printf("LoadArrayFromFile Error opening file!\n");
        return;
    }

    int size = 0;
    if (fscanf_s(file, "%d", &size) == 1 && size <= max_size) {
        for (int i = 0; i < size; ++i) {
            fscanf_s(file, "%d", &arr[i]);
        }
        *out_size = size;
    }
    fclose(file);
}

void ProcessArrayVariant19(void) {
    char path_in[MAX_PATH_LEN];
    char path_out[MAX_PATH_LEN];
    if (!BuildFilePath(PATH_IN, "in19.txt", path_in, sizeof(path_in))) return;
    if (!BuildFilePath(PATH_OUT, "8.1.4.txt", path_out, sizeof(path_out))) return;

    FILE* fin = fopen(path_in, "r");
    if (fin == NULL) {
        printf("ProcessArrayVariant19 Error opening input file!\n");
        return;
    }

    int n = 0;
    if (fscanf_s(fin, "%d", &n) != 1 || n <= 0 || n > MAX_SIZE) {
        printf("Invalid array size!\n");
        fclose(fin);
        return;
    }

    int arr[MAX_SIZE] = { 0 };
    for (int i = 0; i < n; ++i) {
        if (fscanf_s(fin, "%d", &arr[i]) != 1) {
            printf("Error reading array element!\n");
            fclose(fin);
            return;
        }
    }
    fclose(fin);

    int first_odd = -1;
    int last_odd = -1;
    for (int i = 0; i < n; ++i) {
        if (arr[i] % 2 != 0) {
            if (first_odd == -1) first_odd = i;
            last_odd = i;
        }
    }

    if (first_odd != -1 && last_odd != -1 && first_odd < last_odd) {
        for (int i = first_odd + 1; i < last_odd; ++i) {
            if (arr[i] % 4 == 0) {
                arr[i] *= 5;
            }
        }
    }

    FILE* fout = fopen(path_out, "w");
    if (fout == NULL) {
        printf("Error opening output file!\n");
        return;
    }

    fprintf(fout, "%d\n", n);
    for (int i = 0; i < n; ++i) {
        fprintf(fout, "%d ", arr[i]);
    }

    fclose(fout);
    printf("8.1.4 generated.\n");
}

// ---------- 8.2

void ReplaceTabsWithPercent(void) {
    char path_in[MAX_PATH_LEN];
    char path_out[MAX_PATH_LEN];
    if (!BuildFilePath(PATH_IN, "text1.txt", path_in, sizeof(path_in))) return;
    if (!BuildFilePath(PATH_OUT, "8.2.1.txt", path_out, sizeof(path_out))) return;

    FILE* fin = fopen(path_in, "r");
    if (fin == NULL) {
        printf("Error opening input file!\n");
        return;
    }
    FILE* fout = fopen(path_out, "w");
    if (fout == NULL) {
        printf("Error opening output file!\n");
        fclose(fin);
        return;
    }

    char line[1024];
    while (fgets(line, sizeof(line), fin) != NULL) {
        for (int i = 0; line[i] != '\0'; ++i) {
            if (line[i] == '\t') {
                line[i] = '%';
            }
        }
        fputs(line, fout);
    }
    fclose(fin);
    fclose(fout);
    printf("8.2.1 generated.\n");
}

void MakeLatinUppercase(void) {
    char path_in[MAX_PATH_LEN];
    char path_out[MAX_PATH_LEN];
    if (!BuildFilePath(PATH_IN, "text2.txt", path_in, sizeof(path_in))) return;
    if (!BuildFilePath(PATH_OUT, "8.2.2.txt", path_out, sizeof(path_out))) return;

    FILE* fin = fopen(path_in, "r");
    if (fin == NULL) {
        printf("Error opening input file!\n");
        return;
    }
    FILE* fout = fopen(path_out, "w");
    if (fout == NULL) {
        printf("Error opening output file!\n");
        fclose(fin);
        return;
    }

    char line[1024];
    while (fgets(line, sizeof(line), fin) != NULL) {
        for (int i = 0; line[i] != '\0'; ++i) {
            if (line[i] >= 'a' && line[i] <= 'z') {
                line[i] = (char)toupper((unsigned char)line[i]);
            }
        }
        fputs(line, fout);
    }
    fclose(fin);
    fclose(fout);
    printf("8.2.2 generated.\n");
}

void AddHashForLatinLines(void) {
    char path_in[MAX_PATH_LEN];
    char path_out[MAX_PATH_LEN];
    if (!BuildFilePath(PATH_IN, "text3.txt", path_in, sizeof(path_in))) return;
    if (!BuildFilePath(PATH_OUT, "8.2.3.txt", path_out, sizeof(path_out))) return;

    FILE* fin = fopen(path_in, "r");
    if (fin == NULL) {
        printf("Error opening input file!\n");
        return;
    }
    FILE* fout = fopen(path_out, "w");
    if (fout == NULL) {
        printf("Error opening output file!\n");
        fclose(fin);
        return;
    }

    char line[1024];
    while (fgets(line, sizeof(line), fin) != NULL) {
        int has_latin = 0;
        for (int i = 0; line[i] != '\0'; ++i) {
            if (isalpha((unsigned char)line[i]) && line[i] < 128) {
                has_latin = 1;
                break;
            }
        }
        if (has_latin) {
            fputc('#', fout);
        }
        fputs(line, fout);
    }
    fclose(fin);
    fclose(fout);
    printf("8.2.3 generated.\n");
}

void ReplacePunctuationVariant19(void) {
    char path_in[MAX_PATH_LEN];
    char path_out[MAX_PATH_LEN];
    if (!BuildFilePath(PATH_IN, "text4.txt", path_in, sizeof(path_in))) return;
    if (!BuildFilePath(PATH_OUT, "8.2.4.txt", path_out, sizeof(path_out))) return;

    FILE* fin = fopen(path_in, "r");
    if (fin == NULL) { printf("Error opening input file!\n"); return; }
    FILE* fout = fopen(path_out, "w");
    if (fout == NULL) { printf("Error opening output file!\n"); fclose(fin); return; }

    const char* punct = ".,!?;:-—\"'()[]{}<>";
    char line[1024];

    while (fgets(line, sizeof(line), fin) != NULL) {
        for (int i = 0; line[i] != '\0'; ++i) {
            if (strchr(punct, line[i]) != NULL) {
                line[i] = '_';
            }
        }
        fputs(line, fout);
    }
    fclose(fin);
    fclose(fout);
    printf("8.2.4 generated.\n");
}

void CountSemicolonsPrefix(void) {
    char path_in[MAX_PATH_LEN];
    char path_out[MAX_PATH_LEN];
    if (!BuildFilePath(PATH_IN, "text5.txt", path_in, sizeof(path_in))) return;
    if (!BuildFilePath(PATH_OUT, "8.2.5.txt", path_out, sizeof(path_out))) return;

    FILE* fin = fopen(path_in, "r");
    if (fin == NULL) { printf("Error opening input file!\n"); return; }
    FILE* fout = fopen(path_out, "w");
    if (fout == NULL) { printf("Error opening output file!\n"); fclose(fin); return; }

    char line[1024];
    while (fgets(line, sizeof(line), fin) != NULL) {
        int count = 0;
        for (int i = 0; line[i] != '\0'; ++i) {
            if (line[i] == ';') count++;
        }
        fprintf(fout, "%d:%s", count, line);
    }
    fclose(fin);
    fclose(fout);
    printf("8.2.5 generated.\n");
}

// ---------- 8.3

void CreateSimpleHtml(void) {
    char path_in[MAX_PATH_LEN];
    char path_out[MAX_PATH_LEN];
    if (!BuildFilePath(PATH_IN, "text.txt", path_in, sizeof(path_in))) return;
    if (!BuildFilePath(PATH_OUT, "8.3.1.html", path_out, sizeof(path_out))) return;

    FILE* fin = fopen(path_in, "r");
    if (fin == NULL) { printf("Error opening input file!\n"); return; }
    FILE* fout = fopen(path_out, "w");
    if (fout == NULL) { printf("Error opening output file!\n"); fclose(fin); return; }

    fprintf(fout, "<!DOCTYPE html><html><head><meta charset=\"utf-8\">"
        "<title>Kuzmin Timofey PIbd-11</title></head><body>\n");

    int ch;
    while ((ch = getc(fin)) != EOF) {
        if (ch == '\n') fprintf(fout, "<br>\n");
        else fputc(ch, fout);
    }

    fprintf(fout, "\n</body></html>");
    fclose(fin);
    fclose(fout);
    printf("8.3.1 generated.\n");

}

static int IsCategory1Variant19(const char* word) { //var 5
    size_t len = strlen(word);
    return (len >= 1 && len <= 3) ? 1 : 0;
}

static int IsCategory2Variant19(const char* word) { //var 5
    size_t len = strlen(word);
    if (len == 0) return 0;
    for (size_t i = 0; i < len; ++i) {
        if (!islower((unsigned char)word[i])) return 0;
    }
    return 1;
}

void CreateCategorizedHtmlVariant19(void) {
    char path_in[MAX_PATH_LEN];
    char path_out[MAX_PATH_LEN];
    if (!BuildFilePath(PATH_IN, "text2.txt", path_in, sizeof(path_in)))  return;
    if (!BuildFilePath(PATH_OUT, "8.3.2.html", path_out, sizeof(path_out))) return;

    FILE* fin = fopen(path_in, "r");
    if (fin == NULL) { printf("Error opening input file!\n"); return; }
    FILE* fout = fopen(path_out, "w");
    if (fout == NULL) { printf("Error opening output file!\n"); fclose(fin); return; }

    fprintf(fout, "<!DOCTYPE html><html><head><meta charset=\"utf-8\">"
        "<title>Kuzmin Timofey PIbd-11</title></head><body>\n");

    int ch;
    char word[100];
    int word_len = 0;

    while ((ch = getc(fin)) != EOF) {
        if (isalpha((unsigned char)ch)) {
            if (word_len < 99) 
                word[word_len++] = (char)ch;
        }
        else {
            if (word_len > 0) {
                word[word_len] = '\0';

                int is_cat1 = IsCategory1Variant19(word);
                int is_cat2 = IsCategory2Variant19(word);

                if (is_cat1) 
                    fputs("<b>", fout);
                if (is_cat2) 
                    fputs("<i>", fout);

                fputs(word, fout);

                if (is_cat2) 
                    fputs("</i>", fout);
                if (is_cat1) 
                    fputs("</b>", fout);

                word_len = 0;
            }
            if (ch == '\n') fprintf(fout, "<br>\n");
            else fputc(ch, fout);
        }
    }

    if (word_len > 0) {
        word[word_len] = '\0';

        int is_cat1 = IsCategory1Variant19(word);
        int is_cat2 = IsCategory2Variant19(word);

        if (is_cat1) 
            fputs("<b>", fout);
        if (is_cat2) 
            fputs("<i>", fout);

        fputs(word, fout);

        if (is_cat2) 
            fputs("</i>", fout);
        if (is_cat1) 
            fputs("</b>", fout);
    }

    fprintf(fout, "\n</body></html>");
    fclose(fin);
    fclose(fout);
    printf("8.3.2 generated.");
}