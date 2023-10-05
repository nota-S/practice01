#include<vector>

class DS
{
private:
  std::vector<int> f, num;
public:
  DS(int n)
  {
    f.resize(n + 1);
    num.resize(n + 1);
    for(int i = 1; i <= n; i ++)
    {
      num[i] = 1;
      f[i] = i;
    }
  }
  int findx(int x)
  {
    if(f[x] == x)return x;
    f[x] = findx(f[x]);
    return f[x];
  }
  void bind(int a, int b)
  {
    a = findx(a);
    b = findx(b);
    if(a == b)return;
    if(num[a] > num[b])
    {
      a ^= b;
      b ^= a;
      a ^= b;
    }
    f[a] = b;
    num[b] += num[a];
  }
};
