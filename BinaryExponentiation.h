class BinaryExponentiation
{
  BinaryExponentiation();
  double be(double a, long long p)
  {
    if(p < 0)return 1 / be(a, -p);
    else if(p == 0)return 1;
    else if(p == 1)return a;
    double u = be(a, p / 2);
    if(p % 2 == 1)return u * u * a;
    else return u * u;
  }
};
