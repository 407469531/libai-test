#include <QCoreApplication>

#include "vector1.h"
#include "sort1.h"
#include "list1.h"
#include "string1.h"
#include "io.h"

TEST(SimpleTest, test1) {
    EXPECT_EQ(1,1);
}

int gtest(int argc, char **argv){
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}



int main(int argc, char **argv)
{
    gtest(argc, argv);

    stringtest();
    listtest();
    vectortest();
    sortTest();
    ioTest();
}



