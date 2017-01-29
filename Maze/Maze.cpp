#include <iostream>
#include <fstream>

using namespace std;

#include "Solve.h"

int main(int argc, char* argv[]) {
    if (argc < 3) {
        cout << "Usage: maze.exe <input file> <output file>" << endl;
        return 1;
    }

    char * infile = argv[1];  //��� �������� �����
    char * outfile = argv[2];  //��� ��������� �����

    return solve_task(infile, outfile);
}
