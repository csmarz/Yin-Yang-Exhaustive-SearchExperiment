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
int total = 0;

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

int check_connected_dfs(vector<vector<char>> pb, int r, int c, char type)
{
    vector<vector<int>> checklist(m, vector<int> (n, 0));
    checklist[r][c] = 1;
    stack<array<int, 2>> stack;
    stack.push({r,c});
    int count = 1;
    while (!stack.empty())
    {
        array<int, 2> temp = stack.top();
        stack.pop();
        int row = temp[0];
        int col = temp[1];
        int right = col + 1;
        int down = row + 1;
        int left = col - 1;
        int up = row - 1;
        if ((right < n) && (checklist[row][right] == 0))
        {
            checklist[row][right] = 1;
            if (pb[row][right] == type)
            {
                stack.push({row,right});
                count++;
            }
        }
        if ((down < m) && (checklist[down][col] == 0))
        {
            checklist[down][col] = 1;
            if (pb[down][col] == type)
            {
                stack.push({down,col});
                count++;
            }
        }
        if ((left >= 0) && (checklist[row][left] == 0))
        {
            checklist[row][left] = 1;
            if (pb[row][left] == type)
            {
                stack.push({row,left});
                count++;
            } 
        }
        if ((up >= 0) && (checklist[up][col] == 0))
        {
            checklist[up][col] = 1;
            if (pb[up][col] == type)
            {
                stack.push({up,col});
                count++;
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
    int count = 1;
    while (!queue.empty())
    {
        array<int, 2> temp = queue.front();
        queue.pop();
        int row = temp[0];
        int col = temp[1];
        int right = col + 1;
        int down = row + 1;
        int left = col - 1;
        int up = row - 1;
        if ((right < n) && (checklist[row][right] == 0))
        {
            checklist[row][right] = 1;
            if (pb[row][right] == type)
            {
                queue.push({row,right});
                count++;
            }
        }
        if ((down < m) && (checklist[down][col] == 0))
        {
            checklist[down][col] = 1;
            if (pb[down][col] == type)
            {
                queue.push({down,col});
                count++;
            }
        }
        if ((left >= 0) && (checklist[row][left] == 0))
        {
            checklist[row][left] = 1;
            if (pb[row][left] == type)
            {
                queue.push({row,left});
                count++;
            } 
        }
        if ((up >= 0) && (checklist[up][col] == 0))
        {
            checklist[up][col] = 1;
            if (pb[up][col] == type)
            {
                queue.push({up,col});
                count++;
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
        b_valid = check_connected_dfs(pb, b_start[0], b_start[1], '0');
    }
    if(w_start[0] != -1)
    {
        w_valid = check_connected_dfs(pb, w_start[0], w_start[1], '1');
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

bool check_surround_2by2(vector<vector<char>> pb, int r, int c)
{
    int right = c + 1;
    int down = r + 1;
    int left = c - 1;
    int up = r - 1;
    string s;
    if (up >= 0)
    {
        if (left >=0)
        {
            stringstream ss;
            ss << pb[r][c] << pb[r][left] << pb[up][c] << pb[up][left];
            ss >> s;
            if (compare_2by2(s))
            {
                return false;
            }
        }
        if (right < n)
        {
            stringstream ss;
            ss << pb[r][c] << pb[r][right] << pb[up][c] << pb[up][right];
            ss >> s;
            if (compare_2by2(s))
            {
                return false;
            }
        }
    }
    if (down < m)
    {
        if (left >=0)
        {
            stringstream ss;
            ss << pb[r][c] << pb[r][left] << pb[down][c] << pb[down][left];
            ss >> s;
            if (compare_2by2(s))
            {
                return false;
            }
        }
        if (right < n)
        {
            stringstream ss;
            ss << pb[r][c] << pb[r][right] << pb[down][c] << pb[down][right];
            ss >> s;
            if (compare_2by2(s))
            {
                return false;
            }
        }
    }
    return true;
}

vector<vector<vector<char>>> get_config(vector<vector<char>> pb)
{
    vector<vector<vector<char>>> configs;
    vector<vector<char>> config = pb;
    configs.push_back(config);
    for (size_t i = 0; i < m; i++)
    {
        for (size_t j = 0; j < n; j++)
        {
            if (pb[i][j] == '*')
            {
                vector<vector<vector<char>>> new_list;
                while (!configs.empty())
                {
                    vector<vector<char>> new_config = configs.back();
                    configs.pop_back();
                    new_config[i][j] = '0';
                    if (check_surround_2by2(new_config, i, j))
                    {
                        new_list.push_back(new_config);
                    }
                    new_config[i][j] = '1';
                    if (check_surround_2by2(new_config, i, j))
                    {
                        new_list.push_back(new_config);
                    }
                }
                configs = new_list;
            }
            
        }
        
    }
    return configs;
}

void show_config(vector<vector<char>> pb)
{
    cout << endl;
    for (size_t i = 0; i < m; i++)
    {
        for (size_t j = 0; j < n; j++)
        {
            cout << pb[i][j] << " ";
        }
        cout << endl;
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
            playboardtemp[i][j] = '*';
        }
    }
    vector<vector<char>> playboard(m, vector<char> (n));
    for (size_t i = 0; i < 3; i++)
    {
        total = 0;
        playboard = playboardtemp;
        auto start = high_resolution_clock::now();
        if (check_2by2(playboard) == true)
        {
            vector<vector<vector<char>>> configs = get_config(playboard);
            vector<vector<vector<char>>> solutions;
            for (auto &config : configs)
            {
                bool valid = verify(config);
                if (valid)
                {
                    total++;
                    solutions.push_back(config);
                }
            }
        }
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(stop - start);
        cout << total << endl;
        cout << "Duration : " << duration.count() * 0.000001 << " seconds" << endl;
    }
    return 0;
}