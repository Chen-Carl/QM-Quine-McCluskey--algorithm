#ifndef __LOGICALEXPR_H__
#define __LOGICALEXPR_H__

#include <iostream>
#include <cmath>
#include <map>
#include "util.h"

using namespace std;

class LogicalExpr
{
public:
    typedef vector<set<set<int>, util::cmp>> Karnaugh;

protected:
    int len;
    string truth_table;
    string expr;
    map<set<int>, string> to_code;
    Karnaugh table;

    int isNext(const set<int> &s1, const set<int> &s2)
    {
        return util::isNext(to_code[s1], to_code[s2]);
    }

public:
    LogicalExpr(const string &tru = "");

    static Karnaugh create_table(const string &str);
    static map<set<int>, string> initialize_codemap(Karnaugh &table, int len);

    void print() const
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

    void print_map() const
    {
        cout << to_code.size() << " records: " << endl;
        for (auto it = to_code.begin(); it != to_code.end(); it++)
        {
            for (int x : it->first)
            {
                cout << x << " ";
            }
            cout << ": ";
            cout << it->second << endl;
        }
    }

    friend ostream &operator<<(ostream &os, const LogicalExpr &e);
};

#endif