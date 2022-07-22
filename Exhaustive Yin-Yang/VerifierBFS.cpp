#include <iostream>
#include <algorithm>
#include <vector>
#include <sstream>
#include <stack>
#include <queue>
#include <array>
#include <chrono>
#include <string>

using namespace std;
using namespace std::chrono;

int m = 0;
int n = 0;

bool compare_2by2(string s)
{
    return ((s.compare("0000") == 0) || (s.compare("1111") == 0) || (s.compare("0110") == 0) || (s.compare("1001") == 0));
}

bool check_2by2(vector<vector<char>> pb)
{
    string s;
    for (size_t i = 0; i < m-1; i++)
    {
        for (size_t j = 0; j < n-1; j++)
        {
            stringstream ss;
            ss << pb[i][j] << pb[i][j+1] << pb[i+1][j] << pb[i+1][j+1];
            ss >> s;
            if (compare_2by2(s))
            {
                return false;
            }
        }
    }
    return true;
}

bool valid_cell(int r, int c)
{
    return ((r >= 0) && (r < m ) && (c >=0) && (c < n));
}

int check_connected_dfs(vector<vector<char>> pb, int r, int c, char type)
{
    vector<vector<int>> checklist(m, vector<int> (n, 0));
    checklist[r][c] = 1;
    stack<array<int, 2>> stack;
    stack.push({r,c});
    //Row and Column Directions representing (row, col + 1), (row + 1, col), (row, col - 1), and (row - 1, col)
    int dr[] = {0,1,0,-1};
    int dc[] = {1,0,-1,0};
    int count = 1;
    while (!stack.empty())
    {
        array<int, 2> temp = stack.top();
        stack.pop();
        int row = temp[0];
        int col = temp[1];
        for (size_t i = 0; i < 4; i++)
        {
            int adj_row = row + dr[i];
            int adj_col = col + dc[i];
            if (valid_cell(adj_row, adj_col) && (checklist[adj_row][adj_col] == 0))
            {
                checklist[adj_row][adj_col] = 1;
                if (pb[adj_row][adj_col] == type)
                {
                    stack.push({adj_row,adj_col});
                    count++;
                }
            }
        }
    }
    return count;
}

int check_connected_bfs(vector<vector<char>> pb, int r, int c, char type)
{
    vector<vector<int>> checklist(m, vector<int> (n, 0));
    checklist[r][c] = 1;
    queue<array<int, 2>> queue;
    queue.push({r,c});
    //Row and Column Directions representing (row, col + 1), (row + 1, col), (row, col - 1), and (row - 1, col)
    int dr[] = {0,1,0,-1};
    int dc[] = {1,0,-1,0};
    int count = 1;
    while (!queue.empty())
    {
        array<int, 2> temp = queue.front();
        queue.pop();
        int row = temp[0];
        int col = temp[1];
        for (size_t i = 0; i < 4; i++)
        {
            int adj_row = row + dr[i];
            int adj_col = col + dc[i];
            if (valid_cell(adj_row, adj_col) && (checklist[adj_row][adj_col] == 0))
            {
                checklist[adj_row][adj_col] = 1;
                if (pb[adj_row][adj_col] == type)
                {
                    queue.push({adj_row,adj_col});
                    count++;
                }
            }
        } 
    }
    return count;
}

array<int, 2> find_first(vector<vector<char>> pb, char type)
{
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (pb[i][j] == type)
            {
                return {i, j};
            }
        }  
    }
    return {-1, -1};
}

bool verify(vector<vector<char>> pb)
{
    int b_count = 0;
    int w_count = 0;
    for(auto& v: pb)
    {
        b_count += count(v.begin(), v.end(), '0');
        w_count += count(v.begin(), v.end(), '1');
    }
    array<int, 2> b_start = find_first(pb, '0');
    array<int, 2> w_start = find_first(pb, '1');
    int b_valid = 0;
    int w_valid = 0;
    if(b_start[0] != -1)
    {
        b_valid = check_connected_bfs(pb, b_start[0], b_start[1], '0');
    }
    if(w_start[0] != -1)
    {
        w_valid = check_connected_bfs(pb, w_start[0], w_start[1], '1');
    }
    if ((b_valid == b_count) && (w_valid == w_count))
    {
        return true;
    }
    else
    {
        return false;
    }
}

int main()
{
    char x;
    cin >> m >> n;
    vector<vector<char>> playboardtemp(m, vector<char> (n));
    for (size_t i = 0; i < m; i++)
    {
        for (size_t j = 0; j < n; j++)
        {
            cin >> x;
            playboardtemp[i][j] = x;
        }
    }
    vector<vector<char>> playboard(m, vector<char> (n));
    for (size_t i = 0; i < 3; i++)
    {
        playboard = playboardtemp;
        auto start = high_resolution_clock::now();
        // codes
        if (verify(playboard))
        {
            cout << "Configuration is a solution" << endl;
        }
        else
        {
            cout << "Configuration is NOT a solution" << endl;
        }
        // codes
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(stop - start);
        cout << "Duration : " << duration.count() * 0.000001 << " seconds" << endl;
    }
    return 0;
}