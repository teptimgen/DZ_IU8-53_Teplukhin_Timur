#include <iostream>
#include <fstream>

using namespace std;

#include "Solve.h"

//��������� ������ ��� �������
void new_matr(int ** &m, int n) {
    m = new int*[n];
    for (int i = 0; i < n; i++) {
        m[i] = new int[n];
        memset(m[i], 0, sizeof(int)*n);
    }
}

//������������ ������ ���������� �������
void free_matr(int ** &m, int n) {
    if (m != NULL) {
        for (int i = 0; i < n; i++)
            if (m[i] != NULL) delete[] m[i];
        delete[] m;
    }
    m = NULL;
}


//����������� k-�� �� ���������� ����������� �� ������ i1,j1 � ������ i2,j2
int best_dir(int i1, int j1, int i2, int j2, int k) {
    int di = i2 - i1;
    int dj = j2 - j1;
    int best;

    //����� ������� �����������
    if (di == 0) {
        if (dj > 0)
            best = 3;
        else
            best = 7;
    } else
        if (dj == 0) {
            if (di > 0)
                best = 5;
            else
                best = 1;
        } else
            if (di < 0) {
                if (dj < 0)
                    best = 8;
                else
                    best = 2;
            } else {
                if (dj < 0)
                    best = 6;
                else
                    best = 4;
            }

    //������ ������������
    if (k == 0) return best;

    if (k & 1) { //k - ��������
        best += (k + 1) / 2;
        if (best > 8) best -= 8;
    } else { //k - ������
        best -= (k + 1) / 2;
        if (best < 1) best += 8;
    }
    return best;
}

//�������� ������� ������
int load_data(char * infile, Data *data) {
    ifstream fin(infile);
    if ((fin.rdstate() & std::ifstream::failbit) != 0) return 1;
    fin >> data->N;
    if ((fin.rdstate() & std::ifstream::failbit) != 0 || data->N<1) return 2;

    //��������� ������ ��� ���� N �� N ������
    new_matr(data->matr,data->N);

    //������ �������� ����
    for (int i = 0; i<data->N; i++)
        for (int j = 0; j < data->N; j++) {
            fin >> data->matr[i][j];
            if ((fin.rdstate() & std::ifstream::failbit) != 0 
                || data->matr[i][j]<0 || data->matr[i][j]>6) return 3;
        }

    //������ ��������� � �������� �����
    fin >> data->ni >> data->nj;
    if ((fin.rdstate() & std::ifstream::failbit) != 0 || data->ni<0 || data->nj<0 
        || data->ni >= data->N || data->nj >= data->N || data->matr[data->ni][data->nj]==0) return 4;
    fin >> data->ki >> data->kj;
    if ((fin.rdstate() & std::ifstream::failbit) != 0  || data->ki<0 || data->kj<0 
        || data->ki >= data->N || data->kj >= data->N || data->matr[data->ki][data->kj] == 0) return 5;

    fin.close();
    return 0;
}

int solve(int pi, int pj, Data *data) {
    if (pi == data->ki && pj == data->kj)
        return 1; //������ � �������� ������
    int v = data->matr[pi][pj]; //�������� � ������� ������
    int gi, gj;
    if (data->dir[v - 1] > 0) {  //�������� ������������ �����������
        //���������� ��������� ������
        gi = pi;
        gj = pj;
        switch (data->dir[v - 1]) {
            case 1: gi--;       break;
            case 2: gi--; gj++; break;
            case 3:       gj++; break;
            case 4: gi++; gj++; break;
            case 5: gi++;       break;
            case 6: gi++; gj--; break;
            case 7:       gj--; break;
            case 8: gi--; gj--; break;
        }
        //���������� ������������ �� ������� ����������� - �����
        if (gi < 0 || gj < 0 || gi >= data->N || gj >= data->N
            || data->matr[gi][gj] == 0 || data->check[gi][gj] != 0) return 0;
        data->check[gi][gj] = 1;
        //������������ � �������� �����������
        if (solve(gi, gj, data)) return 1;
        data->check[gi][gj] = 0;
        return 0;
    } else {
        //8 ��������� �����������
        for (int i = 0; i < 8; i++) {
            int bdir = best_dir(pi, pj, data->kj, data->kj, i);
            if (data->digit[bdir - 1] > 0) continue; //����������� ��� ��������� ������ �����
            //���������� ��������� ������
            gi = pi;
            gj = pj;
            switch (bdir) {
                case 1: gi--;       break;
                case 2: gi--; gj++; break;
                case 3:       gj++; break;
                case 4: gi++; gj++; break;
                case 5: gi++;       break;
                case 6: gi++; gj--; break;
                case 7:       gj--; break;
                case 8: gi--; gj--; break;
            }
            //���������� ������������ �� ������� ����������� - � ��������� ��������
            if (gi < 0 || gj < 0 || gi >= data->N || gj >= data->N
                || data->matr[gi][gj] == 0 || data->check[gi][gj] != 0) continue;
            data->dir[v - 1] = bdir;
            data->digit[bdir - 1] = v;
            data->check[gi][gj] = 1;
            //������������ � �������� �����������
            if (solve(gi, gj, data)) return 1; //������� �������
            data->dir[v - 1] = 0;
            data->digit[bdir - 1] = 0;
            data->check[gi][gj] = 0;
        }
        return 0; //������� �� �������
    }
}

int solve_task(char * infile, char * outfile) {
    Data data;

    //��������� ������ �� �����
    int res = load_data(infile,&data);

    ofstream fout(outfile);

    if (res > 0) {
        fout << "-1" << endl;
        fout << res << endl;
        return 1;
    }

    //��� ���� ���� ����������� �� ������
    for (int i = 0; i < 6; i++) data.dir[i] = 0;
    //��� ���� ����������� ����� �� ������
    for (int i = 0; i < 8; i++) data.digit[i] = 0;

    //��������� ������ ��� ������� ������ (������ N �� N)
    new_matr(data.check, data.N);

    if (solve(data.ni, data.nj, &data)) {

        //������ ���������������� ������ ��������� �����������
        for (int i = 0; i < 6; i++) {
            if (data.dir[i] == 0) {
                for (int j = 0; j<8; j++)
                    if (data.digit[j] == 0) {
                        data.dir[i] = j + 1;
                        data.digit[j] = i + 1;
                        break;
                    }
            }
        }

        fout << "1" << endl;
        for (int i = 0; i<6; i++)
            fout << i + 1 << " " << data.dir[i] << endl;
    } else {
        fout << "0" << endl;
    }
    fout.close();

    //������������ ������
    free_matr(data.matr, data.N);
    free_matr(data.check, data.N);
    return 0;
}
