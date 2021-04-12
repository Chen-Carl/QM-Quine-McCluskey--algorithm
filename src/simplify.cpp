#include "simplify.h"

Simplified::Simplified(const string &str) : LogicalExpr(str)
{
    process = table;
    int i = len;
    while (!process.empty())
    {
        process = collabrate(i--);
    }
    // print_map();
    vector<string> simp_expr = select();

    expr = "";
    for (size_t j = 0; j < simp_expr.size(); j++)
    {
        expr += simp_expr[j];
        expr += " + ";
    }
    expr.pop_back();
    expr.pop_back();
    expr.pop_back();
}

LogicalExpr::Karnaugh Simplified::collabrate(int m_len)
{
    LogicalExpr::Karnaugh res(m_len);
    /*
        res[0]
            2, 3
            2, 10
            2, 18
        res[1]
        ...
        res[len]
    */
    set<set<int>, util::cmp> covered;

    for (int i = 0; i < m_len; i++)
    {
        // cout << i << "-th iteration" << endl;
        set<set<int>, util::cmp> item;
        for (auto &x : process[i])
        {
            for (auto &y : process[i + 1])
            {
                int pos;
                if ((pos = isNext(x, y)) >= 0)
                {
                    covered.insert(x);
                    covered.insert(y);
                    string code = util::new_code(to_code[x], pos);
                    auto tmp = x;
                    tmp.insert(y.begin(), y.end());
                    to_code[tmp] = code;
                    item.insert(tmp);
                }
            }
        }
        res[i] = item;
    }

    for (auto &x : covered)
        to_code.erase(x);

    return res;
}

vector<string> Simplified::generate_item()
{
    vector<string> res_item;
    string var = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    for (auto &x : to_code)
    {
        string item;
        for (auto it = x.second.rbegin(); it != x.second.rend(); it++)
        {
            if (*it == '1')
                item.insert(item.end(), var[it - x.second.rbegin()]);
            else if (*it == '0')
            {
                item.insert(item.end(), var[it - x.second.rbegin()]);
                item.insert(item.end(), '\'');
            }
        }
        res_item.push_back(item);
    }
    return res_item;
}

vector<vector<int>> Simplified::generate_prime_table()
{
    // 将每一项映射为自然数
    map<int, int> to_seq;
    set<int> xdata;
    for (auto &x : to_code)
    {
        for (int y : x.first)
            xdata.insert(y);
    }
    int i = 0;
    for (int y : xdata)
    {
        to_seq[y] = i;
        i++;
    }
    
    // vector<set<set<int>, util::cmp>>

    vector<vector<int>> graph(to_code.size());
    for (size_t j = 0; j < to_code.size(); j++)
    {
        graph[j] = vector<int>(i);
    }

    // map<set<int>, string>
    int j = 0;
    for (auto &x : to_code)
    {
        for (int y : x.first)
            graph[j][to_seq[y]] = 1;
        j++;
    }

    return graph;
}

vector<vector<int>> Simplified::find_key_point(const vector<vector<int>> &graph)
{
    vector<vector<int>> res;
    vector<int> col_with_1;
    vector<int> sum;
    for (size_t k = 0; k < graph[0].size(); k++)
    {
        int tmp_sum = 0;
        for (size_t t = 0; t < graph.size(); t++)
        {
            tmp_sum += graph[t][k];
        }
        sum.push_back(tmp_sum);
    }

    for (size_t k = 0; k < sum.size(); k++)
    {
        if (sum[k] == 1)
            col_with_1.push_back(k);
    }

    for (auto k : col_with_1)
    {
        // 获取当前满足条件的1所在的行
        int row;
        for (row = 0; row < int(graph.size()); row++)
            if (graph[row][k])
                break;

        res.push_back({row, k});
    }

    return res;
}

vector<set<int>> Simplified::get_remain_graph(const vector<vector<int>> &graph)
{
    set<int> row;
    set<int> col;

    for (size_t i = 0; i < graph.size(); i++)
    {
        for (size_t j = 0; j < graph[0].size(); j++)
        {
            if (graph[i][j])
            {
                row.insert(i);
                col.insert(j);
            }
        }
    }

    vector<set<int>> res;
    res.push_back(row);
    res.push_back(col);
    return res;
}

int Simplified::find_max_row(const vector<vector<int>> &graph, const vector<set<int>> &remain_row_col)
{
    int max = 0;
    map<int, int> row_to_sum;
    for (int row : remain_row_col[0])
    {
        int sum = 0;
        for (int col : remain_row_col[1])
        {
            sum += graph[row][col];
        }
        row_to_sum[row] = sum;
        if (sum > max)
            max = sum;
    }

    for (int row : remain_row_col[0])
    {
        if (row_to_sum[row] == max)
            return row;
    }

    return *(remain_row_col[0].begin());
}

vector<string> Simplified::select()
{
    vector<string> res_item = generate_item();
    vector<vector<int>> graph = generate_prime_table();
    vector<vector<int>> key_point = find_key_point(graph);

    set<int> res_index;
    for (auto &x : key_point)
    {
        res_index.insert(x[0]);
        graph[x[0]][x[1]] = 0;
        for (size_t col = 0; col < graph[0].size(); col++)
        {
            if (graph[x[0]][col])
            {
                graph[x[0]][col] = 0;
                for (size_t row = 0; row < graph.size(); row++)
                {
                    if (graph[row][col])
                        graph[row][col] = 0;
                }
            }
        }
    }

    vector<set<int>> remain_row_col = get_remain_graph(graph);

    // 寻找最大行
    while (!remain_row_col[0].empty())
    {
        int max_row = find_max_row(graph, remain_row_col);
        res_index.insert(max_row);

        for (int col : remain_row_col[1])
        {
            if (graph[max_row][col] == 1)
            {
                graph[max_row][col] = 0;
                for (int row : remain_row_col[0])
                {
                    if (graph[row][col] == 1)
                        graph[row][col] = 0;
                }
            }
        }

        remain_row_col = get_remain_graph(graph);
    }

    vector<string> res;

    for (int i : res_index)
    {
        res.push_back(res_item[i]);
    }

    return res;
}

ostream &operator<<(ostream &os, const Simplified &s)
{
    os << s.expr;
    return os;
}

std::string truthtable_to_expr(const std::string& truth_table)
{
    int len = truth_table.size();
    while (len > 1)
    {
        len = len / 2;
    }
    if (len == 0)
    {
        cout << "error: invalid truth table" << endl;
        return "";
    }

    Simplified s(truth_table);
    return s.toString();
}