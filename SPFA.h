#include<vector>
#include<queue>

template <typename T>
T SPFA(int n, int s, int e, std::vector<std::vector<std::pair<int, T>>> &maps)
{
  std::vector<T> dis(n, 1e9);
  std::vector<bool> vis(n, false);
  dis[s] = 0;
  std::queue<int> que;
  que.push(s);
  int count = 0;
  while(!que.empty())
  {
    count ++;
    if(count > 2 * n)break;
    int u = que.front();
    que.pop();
    vis[u] = false;
    for(std::pair<int, T> &i : maps[u])
    {
      if(dis[i.first] > dis[u] + i.second)
      {
        dis[i.first] = dis[u] + i.second;
        if(!vis[i.first])
        {
          vis[i.first] = true;
          que.push(i.first);
        }
      }
    }
  }
  return dis[e] == 1e9 ? -1 : dis[e];
}
