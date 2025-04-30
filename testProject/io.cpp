#include "pub.h"


void ioTest(){

   char data[100];

   // 以写模式打开文件
   ofstream outfile;
   outfile.open("afile.dat");

   cout << "Writing to the file" << endl;
   cout << "Enter your name: ";
   cin.getline(data, 100);

   // 向文件写入用户输入的数据
   outfile << data << endl;

   cout << "Enter your age: ";
   cin >> data;
   cin.ignore();

   // 再次向文件写入用户输入的数据
   outfile << data << endl;

   // 关闭打开的文件
   outfile.close();

   // 以读模式打开文件
   ifstream infile;
   infile.open("afile.dat");

   cout << "Reading from the file" << endl;
   infile >> data;

   // 在屏幕上写入数据
   cout << data << endl;

   // 再次从文件读取数据，并显示它
   infile >> data;
   cout << data << endl;

   // 关闭打开的文件
   infile.close();

}
TEST(io_test, test1){
//    ioTest();
}
/* test 2 ********** 测试大端数据转换 *********/
namespace BIGENDIAN {
int16_t getShort(unsigned char* data){
    return (data[0] << 8 | data[1]);
}
uint16_t getUShort(unsigned char* data) {
    return (data[0] << 8 | data[1]);
}
int16_t getShort(char* data){
    return (data[0] << 8 | data[1]);
}
uint16_t getUShort(char* data) {
    return (data[0] << 8 | data[1]);
}


int32_t getInt(unsigned char* data){
    return (data[0] << 24 | data[1] << 16 | data[2] << 8 | data[3]);
}
uint32_t getUInt(unsigned char* data){
    return (data[0] << 24 | data[1] << 16 | data[2] << 8 | data[3]);
}





int16_t getShort(int16_t data){
    return (data << 8 | data);
}

};


TEST(io_test, test2){
    unsigned char data1[] = {0xff,0xff};
    EXPECT_EQ(BIGENDIAN::getShort(data1), -1);
    EXPECT_EQ(BIGENDIAN::getUShort(data1), 65535);
    data1[0] = 0x00; data1[1] = 0x01;
    EXPECT_EQ(BIGENDIAN::getShort(data1), 1);
    EXPECT_EQ(BIGENDIAN::getUShort(data1), 1);
    data1[0] = 0xff; data1[1] = 0xfe;
    EXPECT_EQ(BIGENDIAN::getShort(data1), -2);
    EXPECT_EQ(BIGENDIAN::getUShort(data1), 65534);


    char data2[] = {char(0xff),char(0xff)};
    EXPECT_EQ(BIGENDIAN::getShort(data2), -1);
    EXPECT_EQ(BIGENDIAN::getUShort(data2), 65535);
    data2[0] = 0x00; data2[1] = 0x01;
    EXPECT_EQ(BIGENDIAN::getShort(data2), 1);
    EXPECT_EQ(BIGENDIAN::getUShort(data2), 1);
    data2[0] = 0xff; data2[1] = 0xfe;
    EXPECT_EQ(BIGENDIAN::getShort(data2), -2);
    EXPECT_EQ(BIGENDIAN::getUShort(data2), 65534);

    int16_t data3 = 0xffff;
    EXPECT_EQ(BIGENDIAN::getShort(data3), -1);


    unsigned char data11[] = {0xff,0xff,0xff,0xff};
    EXPECT_EQ(BIGENDIAN::getInt(data11), -1);
    EXPECT_EQ(BIGENDIAN::getUInt(data11), 4294967295);
    data11[0] = 0x00; data11[1] = 0x00; data11[2] = 0x00; data11[3] = 0x01;
    EXPECT_EQ(BIGENDIAN::getInt(data11), 1);
    EXPECT_EQ(BIGENDIAN::getUInt(data11), (uint32_t)1);
    data11[0] = 0xff; data11[1] = 0xff; data11[2] = 0xff; data11[3] = 0xfe;
    EXPECT_EQ(BIGENDIAN::getInt(data11), -2);
    EXPECT_EQ(BIGENDIAN::getUInt(data11), (uint32_t)4294967294);


}

/* test 3 ********** 测试小端数据转换 *********/
namespace LITTLEENDIAN {
int16_t getShort(unsigned char* data){
    return (data[1] << 8 | data[0]);
}
uint16_t getUShort(unsigned char* data) {
    return (data[1] << 8 | data[0]);
}
int16_t getShort(char* data){
    return (data[1] << 8 | data[0]);
}
uint16_t getUShort(char* data) {
    return (data[1] << 8 | data[0]);
}


int32_t getInt(unsigned char* data){
    return (data[0] << 16 | data[1] << 24 | data[2] | data[3] << 8 );
}
uint32_t getUInt(unsigned char* data){
    return (data[0] << 16 | data[1] << 24 | data[2] | data[3]  << 8 );
}
};

TEST(io_test, test3){
    unsigned char data1[] = {0xff,0xff};
    EXPECT_EQ(LITTLEENDIAN::getShort(data1), -1);
    EXPECT_EQ(LITTLEENDIAN::getUShort(data1), 65535);
    data1[0] = 0x00; data1[1] = 0x01;
    EXPECT_EQ(LITTLEENDIAN::getShort(data1), 256);
    EXPECT_EQ(LITTLEENDIAN::getUShort(data1), 256);
    data1[0] = 0xff; data1[1] = 0xfe;
    EXPECT_EQ(LITTLEENDIAN::getShort(data1), -257);
    EXPECT_EQ(LITTLEENDIAN::getUShort(data1), 65279);


    unsigned char data11[] = {0xff,0xff,0xff,0xff};
    EXPECT_EQ(LITTLEENDIAN::getInt(data11), -1);
    EXPECT_EQ(LITTLEENDIAN::getUInt(data11), 4294967295);

}
