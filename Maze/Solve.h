#ifndef MAZE_H
#define MAZE_H

//данные для решения задачи
struct Data {
    int N; //размер поля
    int **matr; //поле
    int ni, nj, ki, kj; //начальная и конечная точки

    int **check; //отметка пройденных клеток
    int dir[6]; //направление для каждой цифры (1..6)
    int digit[8]; //цифра для каждого направления (1..8)
};

void new_matr(int ** &m, int n);
void free_matr(int ** &m, int n);
int load_data(char * infile, Data *data);
int best_dir(int i1, int j1, int i2, int j2, int k);
int solve(int pi, int pj, Data *data);
int solve_task(char * infile, char * outfile);

#endif

