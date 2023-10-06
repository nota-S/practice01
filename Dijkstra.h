#include<vector>

template <typename T>
T Dijkstra(int n, int s, int e, std::vector<std::vector<std::pair<int, T>>> &maps)
{
  std::vector<T> dis(n, 1e9);
  std::vector<bool> vis(n, false);
  dis[s] = 0;
  while(!vis[e])
  {
    T u = 1e9, v = -1;
    for(int i = 0; i < n; i ++)
    {
      if(vis[i])continue;
      if(u > dis[i])
      {
        u = dis[i];
        v = i;
      }
    }
    if(v == -1)break;
    vis[v] = true;
    for(std::pair<int, T> &i : maps[v])
    {
      dis[i.first] = std::max(dis[i.first], u + i.second);
    }
  }
  return dis[e] == 1e9 ? -1 : dis[e];
}
