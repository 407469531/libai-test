#include <QCoreApplication>
#include "pub.h"

//int main(int argc, char *argv[])
//{
//    QCoreApplication a(argc, argv);

//    return a.exec();

//}
int main(){
    {
        MemStamp ms("test");
    }
    printf("end\n");
}
