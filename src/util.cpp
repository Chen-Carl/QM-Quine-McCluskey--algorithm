#include "util.h"

namespace util
{

// 获取两个字符串的第一个不同位
int cmp_str(const string &a, const string &b)
{
    for (size_t i = 0; i < a.size(); i++)
    {
        if (a[i] != b[i])
            return i;
    }
    return -1;
}

// 获取二进制表示中1的个数
int number_of_1(int num)
{
    int count = 0;
    while (num)
    {
        count++;
        num = num & (num - 1);
    }
    return count;
}

// 获取二进制表示
string to_binary(int num)
{
    string res = "";
    while (num != 0)
    {
        res = to_string(num % 2) + res;
        num /= 2;
    }
    return res;
}

string fix_length(string &str, int len)
{
    int size = str.size();
    for (int i = 0; i < len - size; i++)
    {
        str = "0" + str;
    }
    return str;
}

string new_code(const string &str, int pos)
{
    string res = str;
    res[pos] = '-';
    return res;
}

int isNext(const string &str1, const string &str2)
{
    int count = 0;
    int pos = -1;
    for (size_t i = 0; i < str1.size(); i++)
    {
        if (str1[i] != str2[i])
        {
            count++;
            pos = i;
        }
    }
    if (count == 1)
        return pos;
    return -1;
}

}