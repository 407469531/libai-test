#include <QCoreApplication>

#include "sort1.h"
#include "list1.h"
#include "io.h"

int gtest(int argc, char **argv){
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

int main(int argc, char **argv)
{
    gtest(argc, argv);

    listtest();

    sortTest();
    ioTest();
}



