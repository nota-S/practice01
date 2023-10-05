#include<cstdlib>

class Sort
{
public:
  template <typename T>
  void Swap(T &a, T &b)
  {
    a ^= b;
    b ^= a;
    a ^= b;
  }

  template <typename T>
  void QuickSort(T a[], int x, int y)
  {
    if(x >= y)return;
    int l = x, r = y;
    T u = a[(rand() % (y - x + 1)) + x];
    while(l < r)
    {
      while(l < r && a[r] > u)r --;
      while(l < r && a[l] < u)l ++;
      if(l != r)Swap(a[l], a[r]);
    }
    QuickSort(a, x, l - 1);
    QuickSort(a, l + 1, y);
    return;
  }
};
