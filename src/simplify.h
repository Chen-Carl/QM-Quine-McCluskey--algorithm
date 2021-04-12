#ifndef __SIMPLIFY_H__
#define __SIMPLIFY_H__
#include "logicalExpr.h"
#include "util.h"

class Simplified : public LogicalExpr
{
private:
    LogicalExpr::Karnaugh process;
    LogicalExpr::Karnaugh collabrate(int m_len);
    vector<string> select();

    vector<string> generate_item();
    vector<vector<int>> generate_prime_table();
    vector<vector<int>> find_key_point(const vector<vector<int>> &graph);
    vector<set<int>> get_remain_graph(const vector<vector<int>> &graph);
    int find_max_row(const vector<vector<int>> &graph, const vector<set<int>> &remain_row_col);
    
public:
    Simplified(const string &str = "");
    string toString() const { return expr; }

    void print_process() const
    {
        for (auto &x : process)
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

    friend ostream &operator<<(ostream &os, const Simplified &s);
};

std::string truthtable_to_expr(const std::string& truth_table);

#endif