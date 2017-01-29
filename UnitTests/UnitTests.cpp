#include <gtest/gtest.h>
#include "../Maze/Solve.h"

class CTest_load_data : public ::testing::Test {
};

class CTest_best_dir : public ::testing::Test {
};

class CTest_solve : public ::testing::Test {
};

//тест функции load_data
TEST_F(CTest_load_data, CheckPerimeter) {
    Data data;
    //вызов фукнкции
    ASSERT_EQ(0, load_data("test3_1_i.txt", &data));

    //проверка прочитанных из файла данных
    ASSERT_EQ(5, data.N);

    ASSERT_EQ(1, data.matr[0][0]);
    ASSERT_EQ(3, data.matr[0][1]);
    ASSERT_EQ(0, data.matr[0][2]);
    ASSERT_EQ(3, data.matr[0][3]);
    ASSERT_EQ(1, data.matr[0][4]);

    ASSERT_EQ(0, data.matr[1][0]);
    ASSERT_EQ(5, data.matr[1][1]);
    ASSERT_EQ(6, data.matr[1][2]);
    ASSERT_EQ(3, data.matr[1][3]);
    ASSERT_EQ(3, data.matr[1][4]);

    ASSERT_EQ(6, data.matr[2][0]);
    ASSERT_EQ(2, data.matr[2][1]);
    ASSERT_EQ(2, data.matr[2][2]);
    ASSERT_EQ(4, data.matr[2][3]);
    ASSERT_EQ(0, data.matr[2][4]);

    ASSERT_EQ(0, data.matr[3][0]);
    ASSERT_EQ(5, data.matr[3][1]);
    ASSERT_EQ(6, data.matr[3][2]);
    ASSERT_EQ(2, data.matr[3][3]);
    ASSERT_EQ(6, data.matr[3][4]);

    ASSERT_EQ(0, data.matr[4][0]);
    ASSERT_EQ(1, data.matr[4][1]);
    ASSERT_EQ(5, data.matr[4][2]);
    ASSERT_EQ(5, data.matr[4][3]);
    ASSERT_EQ(0, data.matr[4][4]);

    ASSERT_EQ(2, data.ni);
    ASSERT_EQ(2, data.nj);

    ASSERT_EQ(4, data.ki);
    ASSERT_EQ(1, data.kj);

    free_matr(data.matr, data.N);
}

//тест функции best_dir
TEST_F(CTest_best_dir, CheckPerimeter) {
    //первый вариант направления
    ASSERT_EQ(1, best_dir(6, 3, 4, 3, 0));
    ASSERT_EQ(3, best_dir(8, 3, 8, 5, 0));
    ASSERT_EQ(4, best_dir(2, 4, 8, 5, 0));
    ASSERT_EQ(5, best_dir(3, 2, 4, 2, 0));
    ASSERT_EQ(6, best_dir(10, 30, 30, 20, 0));
    ASSERT_EQ(7, best_dir(4, 8, 4, 5, 0));
    ASSERT_EQ(8, best_dir(8, 3, 1, 0, 0));

    //все варианты направлений 
    ASSERT_EQ(2, best_dir(8, 3, 4, 5, 0));
    ASSERT_EQ(3, best_dir(8, 3, 4, 5, 1));
    ASSERT_EQ(1, best_dir(8, 3, 4, 5, 2));
    ASSERT_EQ(4, best_dir(8, 3, 4, 5, 3));
    ASSERT_EQ(8, best_dir(8, 3, 4, 5, 4));
    ASSERT_EQ(5, best_dir(8, 3, 4, 5, 5));
    ASSERT_EQ(7, best_dir(8, 3, 4, 5, 6));
    ASSERT_EQ(6, best_dir(8, 3, 4, 5, 7));

    //все варианты направлений 
    ASSERT_EQ(5, best_dir(3, 2, 4, 2, 0));
    ASSERT_EQ(6, best_dir(3, 2, 4, 2, 1));
    ASSERT_EQ(4, best_dir(3, 2, 4, 2, 2));
    ASSERT_EQ(7, best_dir(3, 2, 4, 2, 3));
    ASSERT_EQ(3, best_dir(3, 2, 4, 2, 4));
    ASSERT_EQ(8, best_dir(3, 2, 4, 2, 5));
    ASSERT_EQ(2, best_dir(3, 2, 4, 2, 6));
    ASSERT_EQ(1, best_dir(3, 2, 4, 2, 7));
}

//тест функции solve
TEST_F(CTest_solve, CheckPerimeter) {
    Data data;

    //путь существует

    data.N = 4;
    new_matr(data.matr, data.N);
    data.matr[0][0] = 3; data.matr[0][1] = 1; data.matr[0][2] = 3; data.matr[0][3] = 2;
    data.matr[1][0] = 4; data.matr[1][1] = 5; data.matr[1][2] = 5; data.matr[1][3] = 0;
    data.matr[2][0] = 3; data.matr[2][1] = 4; data.matr[2][2] = 1; data.matr[2][3] = 3;
    data.matr[3][0] = 1; data.matr[3][1] = 0; data.matr[3][2] = 2; data.matr[3][3] = 1;
    data.ki = 3;
    data.kj = 3;
    new_matr(data.check, data.N);
    memset(data.dir, 0, sizeof(data.dir));
    memset(data.digit, 0, sizeof(data.digit));

    //вызов функции
    ASSERT_EQ(1, solve(0,0,&data));

    free_matr(data.matr, data.N);
    free_matr(data.check, data.N);

    //путь не существует

    data.N = 4;
    new_matr(data.matr, data.N);
    data.matr[0][0] = 3; data.matr[0][1] = 1; data.matr[0][2] = 3; data.matr[0][3] = 2;
    data.matr[1][0] = 4; data.matr[1][1] = 5; data.matr[1][2] = 5; data.matr[1][3] = 0;
    data.matr[2][0] = 3; data.matr[2][1] = 4; data.matr[2][2] = 0; data.matr[2][3] = 0;
    data.matr[3][0] = 1; data.matr[3][1] = 0; data.matr[3][2] = 0; data.matr[3][3] = 1;
    data.ki = 3;
    data.kj = 3;
    new_matr(data.check, data.N);
    memset(data.dir, 0, sizeof(data.dir));
    memset(data.digit, 0, sizeof(data.digit));

    //вызов функции
    ASSERT_EQ(0, solve(0, 0, &data));

    free_matr(data.matr, data.N);
    free_matr(data.check, data.N);
}


int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    int res = RUN_ALL_TESTS();
    system("pause");
    return res;
}

