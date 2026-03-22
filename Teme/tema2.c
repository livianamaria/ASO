#include <windows.h>
#include <stdio.h>

int main(void)
{
    HKEY hKey = HKEY_CURRENT_USER;//cheia aleasa
    LONG lResult;
    DWORD dwIndex = 0;//index pentru subchei
    CHAR szSubKeyName[256];//buffer pentru numele subcheii
    DWORD dwSubKeyNameSize;//dimensiunea bufferului

    printf("Subcheile din HKEY_CURRENT_USER sunt:\n\n");

    while (1)
    {
        dwSubKeyNameSize = sizeof(szSubKeyName);//resetare dimensiune

        lResult = RegEnumKeyExA(
            hKey,//cheia din care citim
            dwIndex,//pozitia subcheii
            szSubKeyName,//numele subcheii
            &dwSubKeyNameSize,//lungimea numelui
            NULL,
            NULL,
            NULL,
            NULL
        );

        if (lResult == ERROR_NO_MORE_ITEMS)//nu mai sunt subchei
        {
            break;
        }

        if (lResult != ERROR_SUCCESS)//eroare la citire
        {
            printf("Eroare la citirea subcheilor.\n");
            return 1;
        }

        printf("%lu. %s\n", dwIndex + 1, szSubKeyName);//afisare subcheie
        dwIndex++;//trecem la urmatoarea
    }

    return 0;
}