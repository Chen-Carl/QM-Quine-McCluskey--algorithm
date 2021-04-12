#include <iostream>
#include "../src/util.h"
#include "../src/logicalExpr.h"
#include "../src/simplify.h"

void test_util();
void test_class();
void test_simplify();
void print(const LogicalExpr::Karnaugh &table);

int main()
{
    string str = "11001100110011000011111010001100";
    cout << truthtable_to_expr(str);
    return 0;
}

void test_util()
{
    cout << util::isNext("10001", "10000") << endl;
    cout << util::isNext("10001", "10010") << endl;
}

void test_class()
{
    string str = "11001100110011000011111010001100";
    LogicalExpr l(str);

    l.print();
    l.print_map();

    cout << l << endl;
}

void test_simplify()
{
    string str = "11001100110011000011111010001100";
    Simplified s(str);
    cout << s;
    // auto t = s.collabrate();
    // s.print_map();
}

void print(const LogicalExpr::Karnaugh &table)
{
    for (auto &x : table)
    {
        for (auto &y : x)
        {
            for (int z : y)
                cout << z << " ";
            cout << endl;
        }
        cout << endl;
    }
}
