#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "../../tasks/task8/string_io/string_reader_writer/StringReaderWriter.hpp"
#include "../../tasks/task8/file_io/file_reader_writer/FileReaderWriter.hpp"
#include <cstdio>
#include <stdio.h>


TEST(IOTest, StringReaderWriterTest) {

    std::string str_src;
    StringReaderWriter rw(str_src);

    char a = 'a';
    int b = 1;
    std::string c("abc");

    std::cout <<"w char: " << rw.write(a) << std::endl;
    std::cout <<"w int: " << rw.write(b) << std::endl;
    std::cout <<"w str: " << rw.write(c) << std::endl;

    std::cout << "current state: " << str_src << std::endl;

    char d;
    int e;
    std::string f;

    std::cout <<"r char: "<< rw.read(d) << ", out: " << d << std::endl;
    std::cout <<"r int: " << rw.read(e) << ", out: " << e << std::endl;
    std::cout <<"r str: " << rw.read(f) << ", out: " << f << std::endl;
}



TEST(IOTest, FileReaderWriterTest) {
    
    FILE* file;
    FileReaderWriter rw("tests/task8/task8.txt");

    char a = 'a';
    int b = 1;
    std::string c("abc");

    std::cout <<"w char: " << rw.write(a) << std::endl;
    std::cout <<"w int: " << rw.write(b) << std::endl;
    std::cout <<"w str: " << rw.write(c) << std::endl;

    char d;
    int e;
    std::string f;

    std::cout <<"r char: "<< rw.read(d) << ", out: " << d << std::endl;
    std::cout <<"r int: " << rw.read(e) << ", out: " << e << std::endl;
    std::cout <<"r str: " << rw.read(f) << ", out: " << f << std::endl;
}


int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
    
}