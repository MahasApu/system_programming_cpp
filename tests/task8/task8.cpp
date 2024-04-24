#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "../../tasks/task8/string_io/StringReaderWriter.hpp"
#include "../../tasks/task8/file_io/FileReaderWriter.hpp"
#include <cstdio>
#include <stdio.h>


TEST(IOTest, StringReaderWriterTest) {

    std::string str_src;
    StringReaderWriter rw(str_src);

    int b = 1234;
    int f;
    char c;
    
    rw.write(b);
    rw.read(f);
    std::string str = "wowowow!";
    std::string s;
    rw.write(str);
    rw.read(c);
    rw.read(s);
    std::cout<<f<<" aaaaa"<<std::endl;
    std::cout<<str<<" aaaaa"<<std::endl;
    std::cout<<c<<" aaaaa"<<std::endl;
    std::cout<<s<<" aaaaa"<<std::endl;
}


TEST(IOTest, FileReaderWriterTest) {
    
    FILE* file;
    FileReaderWriter rw("tests/task8/task8.txt");

    int b = 1234;
    int f;
    char c;
    
    rw.write(b);
    rw.read(f);
    std::string str = "wowowow!";
    std::string s;
    rw.write(str);
    rw.read(c);
    rw.read(s);
    std::cout << f << std::endl;
    std::cout << str << std::endl;
    std::cout << c << std::endl;
    std::cout << s << std::endl;
}


int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
    
}