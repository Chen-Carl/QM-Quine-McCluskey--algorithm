#include <algorithm>
#include "logicalExpr.h"
#include "util.h"

using namespace std;

/*
    首先按照二进制码中1的个数分类，每一类是一个vector
    每一类中有很多项，组成一个set（丢弃重复项）
    一些项是进行合并的，合并成一个set（有序排列）
    表格形式为vector<set<set<int>>>
*/

LogicalExpr::Karnaugh LogicalExpr::create_table(const string &str)
{
    // 单个项单独成为一个set
    int bit = log2(str.size());
    vector<set<set<int>, util::cmp>> res(bit + 1);
    set<set<int>, util::cmp> v_item;
    for (size_t i = 0; i < str.size(); i++)
    {
        // 存在这一项，最高位其实是最大编码
        int code = str.size() - i - 1;
        if (str[i] == '1')
        {
            res[util::number_of_1(code)].insert({code});
        }
    }
    return res;
}

map<set<int>, string> LogicalExpr::initialize_codemap(LogicalExpr::Karnaugh &table, int len)
{
    map<set<int>, string> to_code;
    for (auto &x : table)
    {
        for (auto &y : x)
        {
            auto tmp = util::to_binary(*(y.begin()));
            to_code[y] = util::fix_length(tmp, len);
        }
    }
    return to_code;
}


LogicalExpr::LogicalExpr(const string &tru) : truth_table(tru)
{
    len = log2(tru.size());
    // 成员变量table初始化
    table = create_table(tru);
    // 成员变量to_code初始化
    to_code = initialize_codemap(table, len);
    
    for (auto &x : table)
    {
        for (auto &y : x)
        {
            for (int z : y)
                expr = expr + to_string(z) + ",";
        }
    }
    expr.pop_back();
}

ostream &operator<<(ostream &os, const LogicalExpr &e)
{
    os << e.expr;
    return os;
}
