#include<bits/stdc++.h>
using namespace std;
 
typedef long long ull;

vector<ull> ans;

namespace
{
typedef deque<ull> bigint;
const ull base = 9;
const ull base10 = pow(10, base);    
    
class BigInteger
{
public:
    static void print(bigint a)
    {
        for (ull i = 0; i < a.size(); ++i)
        {
            int ndigits = a[i] > 0 ? (int) log10 ((double) a[i]) + 1 : 1;
            if (ndigits < base && i != 0)
            {
                for (int j = 0; j < base - ndigits; ++j)
                    ans.push_back(0);
            }
            ans.push_back(a[i]);
        }
    }
 
    static bigint str_to_bigint(string str)
    {
        bigint res;
        for (ull i = 0; i < str.length(); i += base)
        {
            ull shift = i + base;
            if (shift > str.length()) shift -= shift - str.length();
            string curr_digit_str(str.end() - shift, str.end() - i);
            res.push_front(atoi(curr_digit_str.c_str()));
        }
        return res;
    }
 
    static bigint mul(bigint a, bigint b)
    {
        ull cnt = 0;
        bigint res;
        for (ull i = b.size() - 1; i >= 0; --i)
        {
            bigint r = mul(a, b[i]);
            for (ull i = 0; i < cnt; ++i) { r.push_back(0); }
            res = add(res, r);
            cnt++;
        }
 
        return res;
    }
 
    static bigint mul(bigint a, ull b)
    {
        bigint res;
        ull mem = 0;
        for (ull i = a.size() - 1; i >= 0; --i)
        {
            ull r = a[i] * b + mem;
            res.push_front(r % base10);
            mem = (r - r % base10) / base10;
        }
        if (mem != 0) res.push_front(mem); 
 
        return res;
    }
 
    static bigint add(bigint a, bigint b)
    {
        if (a.size() < b.size()) while (a.size() != b.size()) { a.push_front(0); }
        else if (a.size() > b.size()) while (a.size() != b.size()) { b.push_front(0); }
 
        bigint res;
        ull mem = 0;
        for (ull i = a.size() - 1; i >= 0; --i)
        {
            ull r = a[i] + b[i] + mem;
            res.push_front(r % base10);
            mem = (r - r % base10) / base10;
        }
        if (mem != 0) res.push_front(mem);
 
        return res;
    }
};
 
}


ull t1,t2;
ull n;
bigint first,second;

bigint fibo(int n)
{
    bigint temp;
    for(ull i=1;i<=n-2;i++)
    {
        temp=BigInteger::add(BigInteger::mul(second,second),first);
        first=second;
        second=temp;
    }
    return second;
}

int main() 
{   
    cin>>t1>>t2>>n;
    first.push_back(t1);
    second.push_back(t2);
    
    BigInteger::print(fibo(n));
    
    ull i=0;
    while(ans[i]==0)
        i++;
    
    for(ull j=i;j<ans.size();j++)
        cout<<ans[j];
    cout<<endl;
    
    ans.clear();
    
    return 0;
}
