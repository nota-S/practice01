class ExtraGcd
{
public:
  long long exgcd(long long a, long long b, long long &x, long long &y)
  {
    if(b == 0)
    {
      x = 1;
      y = 0;
      return a;
    }
    long long res = exgcd(b, a % b, y, x);
    y -= a / b * x;
    return res;
  }
  long long inv(long long a, long long p)
  {
    long long x, y;
    long long z = exgcd(a, p, x, y);
    return (x % p + p) % p;
  }
};
