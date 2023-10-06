#include<cstdio>

template <class T>
class SegmentTree_sum
{
private:
  struct node
  {
    T value, lazy;
    node *left, *right;
    node(T z):value(z), lazy(0), left(nullptr), right(nullptr){}
  }*root;
  int L, R;
  T quaryxy(int ll, int rr, int xx, int yy, node *p)
  {
    if(p == nullptr)return 0;
    if(ll == xx && rr == yy)return p -> value;
    T ans = p -> lazy * (yy - xx + 1);
    int mid = (ll + rr) >> 1;
    if(mid < xx)ans += quaryxy(mid + 1, rr, xx, yy, p -> right);
    else if(mid >= yy)ans += quaryxy(ll, mid, xx, yy, p -> left);
    else ans += quaryxy(ll, mid, xx, mid, p -> left) + quaryxy(mid + 1, rr, mid + 1, yy, p -> right);
    return ans;
  }
  void IntervalInc(int ll, int rr, int xx, int yy, T tar, node *p)
  {
    p -> value += tar * (yy - xx + 1);
    if(ll == xx && rr == yy)
    {
      p -> lazy += tar;
      return;
    }
    int mid = (ll + rr) >> 1;
    if(mid < xx)
    {
      if(p -> right == nullptr)p -> right = new node(0);
      IntervalInc(mid + 1, rr, xx, yy, tar, p -> right);
    }
    else if(mid >= yy)
    {
      if(p -> left == nullptr)p -> left = new node(0);
      IntervalInc(ll, mid, xx, yy, tar, p -> left);
    }
    else
    {
      if(p -> left == nullptr)p -> left = new node(0);
      if(p -> right == nullptr)p -> right = new node(0);
      IntervalInc(ll, mid, xx, mid, tar, p -> left);
      IntervalInc(mid + 1, rr, mid + 1, yy, tar, p -> right);
    }
  }
  T IntervalMod(int ll, int rr, int xx, int yy, T tar, T tot, node *p)
  {
    if(ll == xx && rr == yy)
    {
      T ans = tar * (yy - xx + 1) - p -> value - tot * (yy - xx + 1);
      p -> value = tar * (yy - xx + 1);
      p -> lazy = tar;
      Del(p -> left);
      Del(p -> right);
      return ans;
    }
    int mid = (ll + rr) >> 1;
    T u = p -> lazy, res = 0;
    tot += u;
    p -> lazy = 0;
    if(mid < xx)
    {
      if(u != 0 && p -> left == nullptr)p -> left = new node(0);
      if(p -> right == nullptr)p -> right = new node(0);
      if(u != 0)IntervalInc(ll, mid, ll, mid, u, p -> left);
      res = IntervalMod(mid + 1, rr, xx, yy, tar, tot, p -> right);
    }
    else if(mid >= yy)
    {
      if(u != 0 && p -> right == nullptr)p -> right = new node(0);
      if(p -> left == nullptr)p -> left = new node(0);
      if(u != 0)IntervalInc(mid + 1, rr, mid + 1, rr, u, p -> right);
      res = IntervalMod(ll, mid, xx, yy, tar, tot, p -> left);
    }
    else
    {
      if(p -> left == nullptr)p -> left = new node(0);
      if(p -> right == nullptr)p -> right = new node(0);
      if(u != 0)
      {
        if(ll < xx)IntervalInc(ll, mid, ll, xx - 1, u, p -> left);
        if(rr > yy)IntervalInc(mid + 1, rr, yy + 1, rr, u, p -> right);
      }
      res = IntervalMod(ll, mid, xx, mid, tar, tot, p -> left) + IntervalMod(mid + 1, rr, mid + 1, yy, tar, tot, p -> right);
    }
    p -> value += res;
    return res;
  }
  void Del(node *p)
  {
    if(p == nullptr)return;
    if(p -> left != nullptr)Del(p -> left);
    if(p -> right != nullptr)Del(p -> right);
    delete p;
    p = nullptr;
    return;
  }
public:
  SegmentTree_sum(int x, int y):L(x), R(y), root(new node(0)){}
  SegmentTree_sum():L(0), R(1e9), root(new node(0)){}
  T quary(int x, int y)
  {
    return quaryxy(L, R, x, y, root);
  }
  T quary(int x)
  {
    return quaryxy(L, R, x, x, root);
  }
  void Modxy(int x, int y, T tar)
  {
    IntervalMod(L, R, x, y, tar, 0, root);
  }
  void Increase(int x, int y, T tar)
  {
    IntervalInc(L, R, x, y, tar, root);
  }
  void init()
  {
    Del(root);
    root = new node(0);
    L = 0;
    R = 1e9;
  }
  void init(int ll, int rr)
  {
    Del(root);
    root = new node(0);
    L = ll;
    R = rr;
  }
  ~SegmentTree_sum()
  {
    init();
  }
};
