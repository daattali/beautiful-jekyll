---
layout: post
title: Maximum Palindromes (Hackerrank)
subtitle: Elementary Combinatorics with Data Structure
cover-img: /assets/img/1_s6hhrgR5_tXpO_j7uKaHMw.png
thumbnail-img: /assets/img/1_s6hhrgR5_tXpO_j7uKaHMw.png
share-img: /assets/img/social media preview.png
comments: true
tags: [hackerrank, data structure, combinatorics]
---
<!-- Google Tag Manager (noscript) -->
<noscript><iframe src="https://www.googletagmanager.com/ns.html?id=GTM-KZRMQJ3"
height="0" width="0" style="display:none;visibility:hidden"></iframe></noscript>
<!-- End Google Tag Manager (noscript) -->

[problem statement](https://www.hackerrank.com/challenges/maximum-palindromes/problem)

The problem statement is clear and it states a query problem. We will be given a string and some queries l and r. For each query, we have to determine how many palindromes can be generated using the characters between and inclusive [l,r]. So, we need to calculate the character frequencies between [l,r] at first. It can be determined using a simple 2D cumulative sum array structure. But I have used a comparatively long implementaion of segment tree because I wanted to solve a segment tree problem at that time &#128516; Now when we have character frequencies between range [l,r], we need to choose which characters we can use to generate palindromes. Note that - in a palindrome each character must occur an even number of time unless it's an odd length palindrome. so we need to count characters that occurs even number of times and odd number of times separately.

Let's get back to an elementay combinatorics. Suppose you have a string ABBAC. In how many ways can you reorder this string. It contains 5 characters, where A repeats 2 times, B repeats 2 times, C repeats 1 time. So, number of ways to rearrange this string will be - 

<img src="https://latex.codecogs.com/gif.latex?\frac{5!}{2!2!}" title="\frac{5!}{2!2!}" />

Notice that you are building palindromes. When you are rearranging the first half of the palindrome, the second half is already fixed and you can only rearrange it in one way. So, we will only take half of the frequencies of those even times occured characters. Now calculate the number of ways you can rearrange these characters using the combinatorics formula. We have to do a little extra work as the problem requires mod the answer by 1000000007. we need to use inverse mod of factorials for the denominators in the above formula. Finally, we will consider remaining characters that appears odd number of times and multiply with our ans resulting in odd length palindromes. Hence, total number of palindromes will be calculated.

{% highlight cpp linenos %}

#include <bits/stdc++.h>
#define sz 400000
using namespace std;

class Arr
{
  public:
  int arr[26];
  Arr()
  {
      memset(arr,0,sizeof(arr));
  }  
};

Arr tree[sz];
long long int fact[(sz>>2)+7],inv_fact[(sz>>2)+7];
string s;

long long int bigmod(long long int n, long long int k, long long int mod )
{
    long long int ans=1;
    while(k)
    {
        if(k&1)
            ans=(ans*n)%mod;
        k=k>>1;
        n=(n*n)%mod;
    }
    return ans;
}

void build(int v,int tl,int tr)
{
    if(tl>tr) return;
    if(tl==tr) 
    {
        tree[v].arr[s[tl]-'a']=1;
        return;
    }
    
    int tm=(tl+tr)>>1;
    build(v<<1,tl,tm);
    build((v<<1)+1,tm+1,tr);
    
    for(int i=0;i<26;i++)
    {
        tree[v].arr[i]=tree[v<<1].arr[i]+tree[(v<<1)+1].arr[i];
    }
    return;
}

Arr query(int v,int tl,int tr,int l,int r)
{
    if(tl>r or tr<l) return Arr();
    if(tl>=l and tr<=r) return tree[v];
    
    int tm=(tl+tr)>>1;
    
    Arr lc=query(v<<1, tl, tm , l , r);
    Arr rc=query((v<<1)+1 , tm+1 , tr , l , r);
    
    Arr x;
    
    for(int i=0;i<26;i++)
    x.arr[i]=lc.arr[i]+rc.arr[i];
    
    return x;
}

int main()
{
    int n,q,i,k,l,r;
    long long int M=1e9+7;
    
    cin >> s;
    n=s.length();
    
    memset(tree,0,sizeof(tree));
    
    fact[0]=1;
    inv_fact[0]=1;
    for(long long int i=1;i<(sz>>2);i++)
    {
        fact[i]=(fact[i-1]*i)%M;
        inv_fact[i]=bigmod(fact[i],M-2,M);
    }
    
    build(1,0,n-1);
    
    cin >> q;
    
    while(q--)
    {
        cin >> l >> r;
        Arr x = query(1,0,n-1,l-1,r-1);
        
        long long int ans=1;
        int even=0,odd=0;
        for(int i=0;i<26;i++)
        {
            if(x.arr[i])
            {
                if(x.arr[i]&1)
                odd++;
                even+=(x.arr[i]>>1);
                ans=(ans*inv_fact[x.arr[i]>>1])%M;
            }
        }
        
        
        ans=(ans*fact[even])%M;
        
        if(odd) ans=(ans*odd)%M;
        cout << ans << endl;
        
    }
    
    return 0;
}

{% endhighlight %}
