#include <iostream>
#include <fstream>

using namespace std;

#include "Solve.h"

int main(int argc, char* argv[]) {
    if (argc < 3) {
        cout << "Usage: maze.exe <input file> <output file>" << endl;
        return 1;
    }

    char * infile = argv[1];  //имя входного файла
    char * outfile = argv[2];  //имя выходного файла

    return solve_task(infile, outfile);
}
