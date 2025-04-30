#include <QCoreApplication>
#include <ctime>
#include "pub.h"

int gtest(int argc, char **argv){
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
void curtime(){
    time_t now = time(0);
    char* currentTime = ctime(&now);
    std::cout << "当前时间为: " << currentTime;
}
int main(int argc, char **argv)
{
    gtest(argc, argv);
    curtime();
}

