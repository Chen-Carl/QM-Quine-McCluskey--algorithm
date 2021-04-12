#ifndef __UTIL_H__
#define __UTIL_H__

#include <set>
#include <vector>
#include <string>

namespace util
{

using namespace std;

struct cmp
{
    bool operator()(const set<int> &a, const set<int> &b)
    {
        for (auto it1 = a.begin(), it2 = b.begin(); it1 != a.end(); it1++, it2++)
        {
            if (*it1 < *it2)
                return true;
        }
        return false;
    }
};

// 获取两个字符串的第一个不同位
int cmp_str(const string &a, const string &b);

// 获取二进制表示中1的个数
int number_of_1(int num);

// 获取二进制表示
string to_binary(int num);

string fix_length(string &str, int len);

string new_code(const string &str, int pos);

int isNext(const string &str1, const string &str2);

}

#endif