#include <stdio.h>

int main(void)
{
    char szFilePath[260];
    FILE* pFile = NULL;
    int nChar;

    printf("Introduceti path-ul relativ al fisierului: ");
    fgets(szFilePath, sizeof(szFilePath), stdin);

    for (int i = 0; szFilePath[i] != '\0'; i++)
    {
        if (szFilePath[i] == '\n')
        {
            szFilePath[i] = '\0';
            break;
        }
    }

    if (fopen_s(&pFile, szFilePath, "r") != 0 || pFile == NULL)
    {
        printf("Eroare: fisierul nu exista sau nu a putut fi deschis.\n");
        return 1;
    }

    while ((nChar = fgetc(pFile)) != EOF)
    {
        putchar(nChar);
    }

    fclose(pFile);

    return 0;
}