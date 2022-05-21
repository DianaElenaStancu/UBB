
#include <iostream>
#include <fstream>
#include <vector>
#include <stack>

using namespace std;

ifstream fin("2-in.txt");
ofstream fout("out.txt");

const int NMAX = 1e5 + 5;
int n, m;
vector < pair <int, int> > muc;
vector <bool> exist;
vector <int> g[NMAX], sol;
stack <int> stiva;

void citire()
{
    fin >> n >> m;
    int i, a, b;

    for(i = 1; i <= m; ++i)
    {
        fin >> a >> b;
        muc.push_back({a, b});
        exist.push_back(true);
        g[a].push_back(muc.size() - 1);
        g[b].push_back(muc.size() - 1);
    }
}

bool check()
{
    int i;
    for(i = 1; i <= n; ++i)
        if(g[i].size() % 2 == 1)
            return false;

    return true;
}

void fleury()
{
    int top;
    stiva.push(0);
    while(stiva.empty() == false)
    {
        top = stiva.top();

        //nu am unde sa merg
        if(g[top].size() == 0)
        {
            sol.push_back(top);
            stiva.pop();
        }
        else
        {
            int indexMuc = g[top].back();
            g[top].pop_back();

            if(exist[indexMuc] == true)
            {
                exist[indexMuc] = false;
                stiva.push(top ^ muc[indexMuc].first ^ muc[indexMuc].second);
            }
        }
    }
}

int main()
{
    citire();

    if(check() == false)
    {
        fout << "-1";
        return 0;
    }

    fleury();
    sol.pop_back();
    for(auto &it: sol)
        fout << it << ' ';

    return 0;
}