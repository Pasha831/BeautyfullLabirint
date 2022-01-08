#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <Windows.h>
#include <time.h>
#define N 50
#define M 100

FILE* init_file(char mode)
{
    FILE* file;
    if (mode == 'r')
        file = fopen("input.txt", "r");
    else
        file = fopen("output.txt", "w");
    return file;
}
void init_playground(char m[N][M])
{
    FILE* fr = init_file('r');
    int k = 0;
    while (fgets(m[k++], M, fr));
}
void print_playgroud(char m[N][M], int crd[], int mx, int my, int prizes, int steps, int all_prizes)
{
    system("cls");
    // printf("\e[1;1H\e[2J");
    char ball = 4;

    for (int i = 0; i < N; i++)
    {
        if (m[i][0] == '\0')
            break;

        for (int j = 0; j < strlen(m[i]); j++)
        {
            if (i == crd[0] && j == crd[1])
            {
                if (m[i][j] == '*')
                    m[i][j] = 2;
                else if (m[i][j] == ' ')
                    m[i][j] = '.';
                printf("%c", ball);
            }
            else
                printf("%c", m[i][j]);
        }
    }

    printf("\nSteps: %d\nCollected prizes: %d/%d\n", steps, prizes, all_prizes);
    if (crd[0] == mx && crd[1] == my)
    {
        system("color 2F");
        printf("\nCongratulations!\n");
    }
    else if (m[crd[0]][crd[1]] == '#')
    {
        system("color 4F");
        printf("\nShit happens...\n");
    }
    Sleep(50);
}
int total_prizes(char m[N][M])
{
    int prizes = 0;
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < strlen(m[i]); j++)
        {
            if (m[i][j] == '*')
            {
                prizes++;
            }
        }
    }
    return prizes;
}
int find_max_x(char m[N][M])
{
    int max_x = 0;
    for (int i = 0; i < N; i++)
    {
        if (m[i][0] != '\0')
            max_x++;
        else
            return max_x - 2;
    }
}
int find_max_y(char m[N][M])
{
    return strlen(m[0]) - 3;
}
void change_coordinates(int cds[], int vec[])
{
    cds[0] += vec[0];
    cds[1] += vec[1];
}
void change_vector(int vec[], char s)
{
    if (s == '\\')
    {
        vec[0] ^= vec[1] ^= vec[0] ^= vec[1];
    }
    else
    {
        vec[0] *= -1;
        vec[1] *= -1;
        vec[0] ^= vec[1] ^= vec[0] ^= vec[1];
    }
}

int main()
{
    char m[N][M] = { 0 };  // our playground
    init_playground(m);

    int all_prizes = total_prizes(m);
    int collected_prizes = 0;

    // endpoint of ball
    int y_max = find_max_y(m);
    int x_max = find_max_x(m);
    int steps = 0;

    int cds[2] = { 1, 1 };  // coordinates of ball
    int vec[2] = { 0, 1 };  // vector of moving

    while (1)
    {
        print_playgroud(m, cds, x_max, y_max, collected_prizes, steps, all_prizes);
        change_coordinates(cds, vec);
        char cell = m[cds[0]][cds[1]];

        if (cell == '#')
        {
            FILE* fw = init_file('w');
            fprintf(fw, "no");
            break;
        }

        else if (cds[0] == x_max && cds[1] == y_max)
        {
            FILE* fw = init_file('w');
            if (collected_prizes == all_prizes)
                fprintf(fw, "yes\nyes");
            else
                fprintf(fw, "yes\nno");
            break;
        }

        else if (cell == '*')
        {
            collected_prizes++;
            //m[cds[0]][cds[1]] = ' ';
        }

        else if (cell == '/' || cell == '\\')
        {
            change_vector(vec, cell);
        }

        steps++;
    }
    print_playgroud(m, cds, x_max, y_max, collected_prizes, steps, all_prizes);
}