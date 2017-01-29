#ifndef MAZE_H
#define MAZE_H

//������ ��� ������� ������
struct Data {
    int N; //������ ����
    int **matr; //����
    int ni, nj, ki, kj; //��������� � �������� �����

    int **check; //������� ���������� ������
    int dir[6]; //����������� ��� ������ ����� (1..6)
    int digit[8]; //����� ��� ������� ����������� (1..8)
};

void new_matr(int ** &m, int n);
void free_matr(int ** &m, int n);
int load_data(char * infile, Data *data);
int best_dir(int i1, int j1, int i2, int j2, int k);
int solve(int pi, int pj, Data *data);
int solve_task(char * infile, char * outfile);

#endif
