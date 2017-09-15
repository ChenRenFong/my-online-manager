#ifndef UTINPUTSTREAM_H_INCLUDED
#define UTINPUTSTREAM_H_INCLUDED
#include <string>
#include <sstream>
#include <iostream>

using namespace std;

TEST (getline, first) {
    string s("[ 0 2 2 ]");
    stringstream ss(s);
    string temp;

    getline(ss,temp,' ');
    EXPECT_EQ("[",temp);
    getline(ss,temp,' ');
    EXPECT_EQ("0",temp);
    getline(ss,temp,' ');
    EXPECT_EQ("2",temp);
    getline(ss,temp,' ');
    EXPECT_EQ("2",temp);
    getline(ss,temp,']');
    EXPECT_EQ("",temp);
    EXPECT_EQ("[ 0 2 2 ]",ss.str());
}

TEST (getline, second) {
    string s("[ 0 2 2 ]");
    stringstream ss(s);
    string temp, temp2;
    getline(ss,temp,']');
    EXPECT_EQ("[ 0 2 2 ",temp);
    stringstream cs(temp);

    getline(cs,temp2,' ');
    EXPECT_EQ("[",temp2);
    getline(cs,temp2,' ');
    EXPECT_EQ("0",temp2);
    getline(cs,temp2,' ');
    EXPECT_EQ("2",temp2);
    getline(cs,temp2,' ');
    EXPECT_EQ("2",temp2);
}

TEST (getline, third) {
    string s(" 0 2 2 ");
    stringstream ss(s);
    string temp;
    double comp;

    // leading space
    EXPECT_TRUE(getline(ss,temp,' '));
    EXPECT_EQ("",temp);
    EXPECT_FALSE(stringstream(temp)>> comp);

    // space after '0'
    EXPECT_TRUE(getline(ss,temp,' '));
    EXPECT_EQ("0",temp);
    EXPECT_TRUE(stringstream(temp)>> comp);
    EXPECT_EQ(0, comp);

    // space after '2'
    EXPECT_TRUE(getline(ss,temp,' '));
    EXPECT_EQ("2",temp);
    EXPECT_TRUE(stringstream(temp)>> comp);
    EXPECT_EQ(2, comp);

    EXPECT_TRUE(getline(ss,temp,' '));
    EXPECT_EQ("2",temp);
    EXPECT_TRUE(stringstream(temp)>> comp);
    EXPECT_EQ(2, comp);
}

TEST (getline, threePointOne) {
    string s(" 0 2 2 ");
    stringstream ss(s);
    string temp;

    // if delimiter cannot be found,
    // it will just read the whole line until '\n'
    EXPECT_TRUE(getline(ss,temp,']'));
    EXPECT_EQ(s, temp);
    // detail: see http://www.cplusplus.com/reference/ios/ios/good/
    // eof encountered: therefore !good()
    EXPECT_TRUE(!ss.good());
    // eof is not a failure

    EXPECT_TRUE(!ss.fail());
}

TEST (getline, fourth) {
    string s("        0 2 2 ");
    stringstream ss(s);
    string temp;
    double a[256],comp;
    int dim = 0;
    while (getline(ss,temp,' '))
        if (stringstream(temp)>> comp) {
            a[dim] = comp;
            dim ++;
        }
    EXPECT_EQ(0,a[0]);
    EXPECT_EQ(2,a[1]);
    EXPECT_EQ(2,a[2]);
    EXPECT_EQ(3,dim);
}

TEST (getline, fifth) {
    string s("   [ 0 2 2 ");
    stringstream ss(s);
    string temp;
    char c;
    ss >> c;
    EXPECT_EQ('[',c);
    double a[256],comp;
    int dim = 0;
    while (getline(ss,temp,' '))
        if (stringstream(temp)>> comp) {
            a[dim] = comp;
            dim ++;
        }
    EXPECT_EQ(0,a[0]);
    EXPECT_EQ(2,a[1]);
    EXPECT_EQ(2,a[2]);
    EXPECT_EQ(3,dim);
}

TEST (getline, sixth) {
    string s("   [ 0 2 2 ");
    stringstream ss(s);
    string temp;
    char c;
    ss.get(c);
    EXPECT_EQ(' ',c);
}

TEST (sstream, readingPosition) {
    std::string input = " 1 2 ]";
    std::stringstream ss(input);

    EXPECT_EQ(' ', input[0]);
    EXPECT_EQ('1', input[1]);
    EXPECT_EQ(' ', input[2]);
    EXPECT_EQ('2', input[3]);
    EXPECT_EQ(' ', input[4]);
    EXPECT_EQ(']', input[5]);
    EXPECT_EQ('\0', input[6]);
    EXPECT_EQ(0, input[6]);

    EXPECT_EQ(' ', ss.get());
    EXPECT_EQ('1', ss.get());
    EXPECT_EQ(' ', ss.get());
    EXPECT_EQ('2', ss.get());
    EXPECT_EQ(' ', ss.get());
    EXPECT_EQ(']', ss.get());
    EXPECT_EQ(-1, ss.get()); // value of EOF is -1

    EXPECT_TRUE(!ss.good());
    EXPECT_TRUE(ss.eof());
    EXPECT_TRUE(ss.fail());
    EXPECT_TRUE(!ss.bad());
}
#endif // UTINPUTSTREAM_H_INCLUDED
