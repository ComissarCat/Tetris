#include <iostream>
#include <Windows.h>
#include <conio.h>
#include <time.h>
using namespace std;

struct cube
{
    int coords[4][2] = {
        { 0, 4 },
        { 0, 5 },
        { 1, 4 },
        { 1, 5 } };
};

struct z_figure
{
    int coords[4][2] = {
        { 0, 4 },
        { 0, 5 },
        { 1, 5 },
        { 1, 6 },
    };
};

struct reverse_z_figure
{
    int coords[4][2] = {
        { 0, 6 },
        { 0, 5 },
        { 1, 5 },
        { 1, 4 },
    };
};

struct stick
{
    int coords[4][2] = {
        { 0, 4 },
        { 0, 5 },
        { 0, 6 },
        { 0, 7 },
    };
};

struct t_figure
{
    int coords[4][2] = {
        { 0, 4 },
        { 1, 3 },
        { 1, 4 },
        { 1, 5 },
    };
};

void draw_field(int field[20][10], int score, int& next_figure);
void add_figure(int figure[4][2], int field[20][10], bool& lose);
void move_down(int figure[4][2], int field[20][10], bool& can_move_down);
void move_left(int figure[4][2], int field[20][10]);
void move_right(int figure[4][2], int field[20][10]);
void rotate(int figure[4][2], int field[20][10], int& type_of_figure);
void press_key(int figure[4][2], int field[20][10], int key, int& type_of_figure, bool& can_move_down, int& score, int& next_figure);
void randomize_figure(int figure[4][2], int& type_of_figure, int& next_figure);
void check_full_line(int field[20][10], int& score, int speed, int& next_figure);

int main()
{
    setlocale(LC_ALL, "Russian");

    int speed = 0;
    do
    {
        system("cls");
        int figure[4][2];
        bool lose = false;
        int type_of_figure = 0, next_figure = rand() % 5;
        int field[20][10] = { 0 };
        int score = 0;
        do
        {
            cout << "Введите скорость от 1 до 10, 0 для выхода: ";
            cin >> speed;
        } while (speed < 0 or speed > 10);
        if (speed)
        {
            srand(time(NULL));
            draw_field(field, score, next_figure);
            do
            {
                randomize_figure(figure, type_of_figure, next_figure);
                add_figure(figure, field, lose);
                draw_field(field, score, next_figure);
                bool can_move_down = true;
                do
                {
                    while (!_kbhit())
                    {
                        if (not can_move_down) break;
                        move_down(figure, field, can_move_down);
                        draw_field(field, score, next_figure);
                        Sleep(1000 / speed);
                    }
                    if (can_move_down) press_key(figure, field, _getch(), type_of_figure, can_move_down, score, next_figure);
                } while (can_move_down);
                check_full_line(field, score, speed, next_figure);
            } while (not lose);
            cout << "\n\nЗрада\n\n";
            system("pause");
        }
    } while (speed);    

    return 0;
}

void draw_field(int field[20][10], int score, int& next_figure)
{
    system("cls");
    cout << "Следующая фигура:\t";    
    switch (next_figure)
    {
    case(0):
    {
        cout << "##\n";
        cout << "\t\t\t##\n\n";
    }
    break;
    case(1):
    {
        cout << "##\n";
        cout << "\t\t\t ##\n\n";
    }
    break;
    case(2):
    {
        cout << " ##\n";
        cout << "\t\t\t##\n\n";
    }
    break;
    case(3):
    {
        cout << "####\n\n\n\n";        
    }
    break;
    case(4):
    {
        cout << " #\n";
        cout << "\t\t\t###\n\n";
    }
    break;
    }
    for (int i = 0; i < 20; i++)
    {
        cout << "|";
        for (int j = 0; j < 10; j++)
        {
            
            if (field[i][j] == 0) cout << " ";
            else cout << "#";
        }
        cout << "|\n";
    }
    cout << "+----------+";
    cout << "\n\nСчёт: " << score;
}

void add_figure(int figure[4][2], int field[20][10], bool& lose)
{    
    for (int i = 0; i < 4; i++)
    {
        if (field[figure[i][0]][figure[i][1]] == 2)
        {
            lose = true;
            break;
        }
    }
    if (not lose)
    {
        for (int i = 0; i < 4; i++)
        {
            field[figure[i][0]][figure[i][1]] = 1;
        }
    }
}

void move_down(int figure[4][2], int field[20][10], bool& can_move_down)
{    
    for (int i = 0; i < 4; i++)
    {
        if (figure[i][0] == 19)
        {
            can_move_down = false;
            break;
        }
    }
    if (can_move_down)
    {
        for (int i = 0; i < 4; i++)
        {
            if (field[figure[i][0] + 1][figure[i][1]] == 2)
            {
                can_move_down = false;
                break;
            }
        }
    }
    if (can_move_down)
    {
        for (int i = 0; i < 4; i++)
        {
            field[figure[i][0]][figure[i][1]] = 0;
        }
        for (int i = 0; i < 4; i++)
        {
            figure[i][0]++;
        }
        for (int i = 0; i < 4; i++)
        {
            field[figure[i][0]][figure[i][1]] = 1;
        }
    }
    if (not can_move_down)
    {
        for (int i = 0; i < 4; i++)
        {
            field[figure[i][0]][figure[i][1]] = 2;
        }
    }
}

void move_left(int figure[4][2], int field[20][10])
{
    bool can_move_left = true;
    for (int i = 0; i < 4; i++)
    {
        if (figure[i][1] == 0)
        {
            can_move_left = false;
            break;
        }
    }
    if (can_move_left)
    {
        for (int i = 0; i < 4; i++)
        {
            if (field[figure[i][0]][figure[i][1] - 1] == 2)
            {
                can_move_left = false;
                break;
            }
        }
    }
    if (can_move_left)
    {
        for (int i = 0; i < 4; i++)
        {
            field[figure[i][0]][figure[i][1]] = 0;
        }
        for (int i = 0; i < 4; i++)
        {
            figure[i][1]--;
        }
        for (int i = 0; i < 4; i++)
        {
            field[figure[i][0]][figure[i][1]] = 1;
        }
    }
}

void move_right(int figure[4][2], int field[20][10])
{
    bool can_move_right = true;
    for (int i = 0; i < 4; i++)
    {
        if (figure[i][1] == 9)
        {
            can_move_right = false;
            break;
        }
    }
    if (can_move_right)
    {
        for (int i = 0; i < 4; i++)
        {
            if (field[figure[i][0]][figure[i][1] + 1] == 2)
            {
                can_move_right = false;
                break;
            }
        }
    }
    if (can_move_right)
    {
        for (int i = 0; i < 4; i++)
        {
            field[figure[i][0]][figure[i][1]] = 0;
        }
        for (int i = 0; i < 4; i++)
        {
            figure[i][1]++;
        }
        for (int i = 0; i < 4; i++)
        {
            field[figure[i][0]][figure[i][1]] = 1;
        }
    }
}

void rotate(int figure[4][2], int field[20][10], int& type_of_figure)
{
    bool can_rotate = true;
    switch (type_of_figure)
    {
    case(1):
    {
        if (figure[0][0] == figure[1][0])
        {
            if (figure[0][0] == 0 or figure[0][1] == 9 or figure[2][0] == 0 or figure[2][1] == 0 or figure[3][1] == 1) can_rotate = false;
            if (can_rotate)
            {
                if (field[figure[0][0] - 1][figure[0][1] + 1] == 2) can_rotate = false;                
                if (field[figure[2][0] - 1][figure[2][1] - 1] == 2) can_rotate = false;                
                if (field[figure[3][0]][figure[3][1] - 2] == 2) can_rotate = false;
            }
            if (can_rotate)
            {
                for (int i = 0; i < 4; i++)
                {
                    field[figure[i][0]][figure[i][1]] = 0;
                }
                figure[0][0]--;
                figure[0][1]++;
                figure[2][0]--;
                figure[2][1]--;
                figure[3][1] -= 2;
                for (int i = 0; i < 4; i++)
                {
                    field[figure[i][0]][figure[i][1]] = 1;
                }
            }
        }
        else
        {
            if (figure[0][0] == 19 or figure[0][1] == 0 or figure[2][0] == 19 or figure[2][1] == 9 or figure[3][1] == 8) can_rotate = false;
            if (can_rotate)
            {
                if (field[figure[0][0] + 1][figure[0][1] - 1] == 2) can_rotate = false;                
                if (field[figure[2][0] + 1][figure[2][1] + 1] == 2) can_rotate = false;                
                if (field[figure[3][0]][figure[3][1] + 2] == 2) can_rotate = false;
            }
            if (can_rotate)
            {
                for (int i = 0; i < 4; i++)
                {
                    field[figure[i][0]][figure[i][1]] = 0;
                }
                figure[0][0]++;
                figure[0][1]--;
                figure[2][0]++;
                figure[2][1]++;
                figure[3][1] += 2;
                for (int i = 0; i < 4; i++)
                {
                    field[figure[i][0]][figure[i][1]] = 1;
                }
            }
        }
    }
    break;
    case(2):
    {
        if (figure[0][0] == figure[1][0])
        {
            if (figure[0][0] == 0 or figure[0][1] == 0 or figure[2][0] == 0 or figure[2][1] == 9 or figure[3][1] == 9) can_rotate = false;
            if (can_rotate)
            {
                if (field[figure[0][0] - 1][figure[0][1] - 1] == 2) can_rotate = false;                
                if (field[figure[2][0] - 1][figure[2][1] + 1] == 2) can_rotate = false;                
                if (field[figure[3][0]][figure[3][1] + 2] == 2) can_rotate = false;
            }
            if (can_rotate)
            {
                for (int i = 0; i < 4; i++)
                {
                    field[figure[i][0]][figure[i][1]] = 0;
                }
                figure[0][0]--;
                figure[0][1]--;
                figure[2][0]--;
                figure[2][1]++;
                figure[3][1] += 2;
                for (int i = 0; i < 4; i++)
                {
                    field[figure[i][0]][figure[i][1]] = 1;
                }
            }
        }
        else
        {
            if (figure[0][0] == 19 or figure[0][1] == 9 or figure[2][0] == 19 or figure[2][1] == 0 or figure[3][1] == 1) can_rotate = false;
            if (can_rotate)
            {
                if (field[figure[0][0] + 1][figure[0][1] + 1] == 2) can_rotate = false;                
                if (field[figure[2][0] + 1][figure[2][1] - 1] == 2) can_rotate = false;                
                if (field[figure[3][0]][figure[3][1] - 2] == 2) can_rotate = false;
            }
            if (can_rotate)
            {
                for (int i = 0; i < 4; i++)
                {
                    field[figure[i][0]][figure[i][1]] = 0;
                }
                figure[0][0]++;
                figure[0][1]++;
                figure[2][0]++;
                figure[2][1]--;
                figure[3][1] -= 2;
                for (int i = 0; i < 4; i++)
                {
                    field[figure[i][0]][figure[i][1]] = 1;
                }
            }
        }
    }
    break;
    case(3):
    {
        if (figure[0][0] == figure[1][0])
        {
            if (figure[3][0] == 2) can_rotate = false;
            if (can_rotate)
            {
                if (field[figure[1][0] - 1][figure[1][1] - 1] == 2) can_rotate = false;
                if (field[figure[2][0] - 2][figure[2][1] - 2] == 2) can_rotate = false;
                if (field[figure[3][0] - 3][figure[3][1] - 3] == 2) can_rotate = false;
            }
            if (can_rotate)
            {
                for (int i = 0; i < 4; i++)
                {
                    field[figure[i][0]][figure[i][1]] = 0;
                }
                figure[1][0]--;
                figure[1][1]--;
                figure[2][0] -= 2;
                figure[2][1] -= 2;
                figure[3][0] -= 3;
                figure[3][1] -= 3;
                for (int i = 0; i < 4; i++)
                {
                    field[figure[i][0]][figure[i][1]] = 1;
                }
            }
        }
        else
        {
            if (figure[3][1] == 7) can_rotate = false;
            if (can_rotate)
            {
                if (field[figure[1][0] + 1][figure[1][1] + 1] == 2) can_rotate = false;
                if (field[figure[2][0] + 2][figure[2][1] + 2] == 2) can_rotate = false;
                if (field[figure[3][0] + 3][figure[3][1] + 3] == 2) can_rotate = false;
            }
            if (can_rotate)
            {
                for (int i = 0; i < 4; i++)
                {
                    field[figure[i][0]][figure[i][1]] = 0;
                }
                figure[1][0]++;
                figure[1][1]++;
                figure[2][0] += 2;
                figure[2][1] += 2;
                figure[3][0] += 3;
                figure[3][1] += 3;
                for (int i = 0; i < 4; i++)
                {
                    field[figure[i][0]][figure[i][1]] = 1;
                }
            }
        }
    }
    break;
    case(4):
    {
        if (figure[1][0] == figure[3][0])
        {
            if (figure[1][0] == 19 or figure[1][1] == 9) can_rotate = false;
            if (can_rotate) if (field[figure[1][0] + 1][figure[1][1] + 1] == 2) can_rotate = false;
            if (can_rotate)
            {
                for (int i = 0; i < 4; i++)
                {
                    field[figure[i][0]][figure[i][1]] = 0;
                }
                figure[1][0]++;
                figure[1][1]++;                
                for (int i = 0; i < 4; i++)
                {
                    field[figure[i][0]][figure[i][1]] = 1;
                }
            }
        }
        else if (figure[0][1] == figure[1][1])
        {
            if (figure[0][0] == 19 or figure[0][1] == 0) can_rotate = false;
            if (can_rotate) if (field[figure[0][0] + 1][figure[0][1] - 1] == 2) can_rotate = false;
            if (can_rotate)
            {
                for (int i = 0; i < 4; i++)
                {
                    field[figure[i][0]][figure[i][1]] = 0;
                }
                figure[0][0]++;
                figure[0][1]--;
                for (int i = 0; i < 4; i++)
                {
                    field[figure[i][0]][figure[i][1]] = 1;
                }
            }
        }
        else if (figure[0][0] == figure[3][0])
        {
            if (figure[3][0] == 0 or figure[3][1] == 0) can_rotate = false;
            if (can_rotate) if (field[figure[3][0] - 1][figure[3][1] - 1] == 2) can_rotate = false;
            if (can_rotate)
            {
                for (int i = 0; i < 4; i++)
                {
                    field[figure[i][0]][figure[i][1]] = 0;
                }
                figure[3][0]--;
                figure[3][1]--;
                for (int i = 0; i < 4; i++)
                {
                    field[figure[i][0]][figure[i][1]] = 1;
                }
            }
        }
        else
        {
            if (figure[0][0] == 0 or figure[0][1] == 9 or figure[1][0] == 0 or figure[1][1] == 0 or figure[3][0] == 19 or figure[3][1] == 9) can_rotate = false;
            if (can_rotate)
            {
                if (field[figure[0][0] - 1][figure[0][1] + 1] == 2) can_rotate = false;
                if (field[figure[1][0] - 1][figure[1][1] - 1] == 2) can_rotate = false;
                if (field[figure[3][0] + 1][figure[3][1] + 1] == 2) can_rotate = false;
            }
            if (can_rotate)
            {
                for (int i = 0; i < 4; i++)
                {
                    field[figure[i][0]][figure[i][1]] = 0;
                }
                figure[0][0]--;
                figure[0][1]++;
                figure[1][0]--;
                figure[1][1]--;
                figure[3][0]++;
                figure[3][1]++;
                for (int i = 0; i < 4; i++)
                {
                    field[figure[i][0]][figure[i][1]] = 1;
                }
            }
        }
    }
    break;
    }
}

void press_key(int figure[4][2], int field[20][10], int key, int& type_of_figure, bool& can_move_down, int& score, int& next_figure)
{
    switch (key)
    {
    case 0x4B: move_left(figure, field);
        break;    
    case 0x4D: move_right(figure, field);
        break;    
    case 0x48: rotate(figure, field, type_of_figure);
        break;
    case 0x50: move_down(figure, field, can_move_down);
        break;
    }
    draw_field(field, score, next_figure);
}

void randomize_figure(int figure[4][2], int& type_of_figure, int& next_figure)
{    
    type_of_figure = next_figure;
    int counter = 0;
    do
    {
        next_figure = rand() % 5;
        counter++;
        if (counter == 10) break;
    } while (next_figure == type_of_figure);
    switch (type_of_figure)
    {
    case(0):
    {
        cube new_figure;
        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 2; j++)
            {
                figure[i][j] = new_figure.coords[i][j];
            }
        }
    }
        break;
    case(1):
    {
        z_figure new_figure;
        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 2; j++)
            {
                figure[i][j] = new_figure.coords[i][j];
            }
        }
    }
        break;
    case(2):
    {
        reverse_z_figure new_figure;
        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 2; j++)
            {
                figure[i][j] = new_figure.coords[i][j];
            }
        }
    }
        break;
    case(3):
    {
        stick new_figure;
        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 2; j++)
            {
                figure[i][j] = new_figure.coords[i][j];
            }
        }
    }
        break;
    case(4):
    {
        t_figure new_figure;
        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 2; j++)
            {
                figure[i][j] = new_figure.coords[i][j];
            }
        }
    }
    break;
    }
}

void check_full_line(int field[20][10], int& score, int speed, int& next_figure)
{
    int number_of_full_lines = 0;
    for (int i = 19; i >= 0; i--)
    {        
        bool line_is_full = true;
        for (int j = 0; j < 10; j++)
        {
            if (field[i][j] == 0)
            {
                line_is_full = false;
                break;
            }
        }
        if (line_is_full)
        {
            for (int k = i; k > 0; k--)
            {
                for (int j = 0; j < 10; j++)
                {
                    field[k][j] = field[k - 1][j];
                }
            }
            number_of_full_lines++;
            score += 100 * speed * number_of_full_lines;
            i++;
            draw_field(field, score, next_figure);
        }
    }    
}