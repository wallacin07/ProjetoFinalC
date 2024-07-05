#ifndef MENU_H
#define MENU_H
#include <string.h>
#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <time.h>

#define BLACK 0
#define DARK_BLUE 1
#define RED 4
#define WHITE 15
#define ORANGE  6
#define CYAN_BLUE 3
#define FOREGROUND_YELLOW (FOREGROUND_RED | FOREGROUND_GREEN)
#define FOREGROUND_LIGHT_YELLOW (FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY)

int menu()
{

    int inicio = 0;
    char pattern[11][80] = {
        "  ____                        _                     ____                  ",
        " | __ )    ___    _ __ ___   | |__     ___   _ __  | __ )    ___    _   _ ",
        " |  _ \\   / _ \\  | '_ ` _ \\  | '_ \\   / _ \\ | '__| |  _ \\   / _ \\  | | | |",
        " | |_) | | (_) | | | | | | | | |_) | |  __/ | |    | |_) | | (_) | | |_| |",
        " |____/   \\___/  |_| |_| |_| |_.__/   \\___| |_|    |____/   \\___/   \\__, |",
        "                                                                    |___/",
        "            __________________________________________________",
        "           |    _    __   _  __  ___ _      _     ___ _  __   |",
        "           |   /_\\  |__| |_ |__|  | |_     |_ |\\ | | |_ |__|  |",
        "           |  /   \\ |    |_ | \\   | |_     |_ | \\| | |_ | \\   |",
        "           |__________________________________________________|"};

    for (int i = 0; i < 11; i++)
    {
        if(strcmp(pattern[i], "__"))
        {
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_LIGHT_YELLOW);
            printf("%s\n", pattern[i]);
        }
    }

    while (inicio == 0)
    {
        if (_kbhit())
        {
            inicio = 1;
        }
    }
    system("cls");

    Sleep(100);

    int n = 0;
    char menu[18][80] = {

        "  _ __ ___     ___   _ __    _   _ ",
        " | '_ ` _ \\   / _ \\ | '_ \\  | | | |",
        " | | | | | | |  __/ | | | | | |_| |",
        " |_| |_| |_|  \\___| |_| |_|  \\__,_|",
        "",
        "  _               ____                    _      _                 ",
        " / |             |  _ \\    __ _   _ __   | | __ (_)  _ __     __ _ ",
        " | |    _____    | |_) |  / _` | | '_ \\  | |/ / | | | '_ \\   / _` |",
        " | |   |_____|   |  _ <  | (_| | | | | | |   <  | | | | | | | (_| |",
        " |_|             |_| \\_\\  \\__,_| |_| |_| |_|\\_\\ |_| |_| |_|  \\__, |",
        "                                                             |___/",
        " ",
        "  ____                    _                                ",
        " |___ \\                  | |   ___     __ _    __ _   _ __ ",
        "   __) |    _____     _  | |  / _ \\   / _` |  / _` | | '__|",
        "  / __/    |_____|   | |_| | | (_) | | (_| | | (_| | | |   ",
        " |_____|              \\___/   \\___/   \\__, |  \\__,_| |_|   ",
        "                                      |___/"};

    for (int i = 0; i < 18; i++)
    {
        printf("%s\n", menu[i]);
    }

    do
    {
        if (_kbhit())
        {
            n = (int)_getch();
            if (n == '1' || n == '2')
            {
                break;
            }
        }
    } while (1);

    Sleep(100);

    system("cls");

    return n - '0';
}
#endif