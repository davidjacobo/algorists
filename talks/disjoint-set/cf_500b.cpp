#include <iostream>
#include <cstdio>

#define N 303

using namespace std;

int p[N], a[N], n;
char m[ N ];

int find(int x) {
    if(p[x]!=x)
        p[x]=find(p[x]);
    return p[x];
}

int main() {
    int n;
    scanf("%d",&n);
    for(int i=1; i <= n; ++i) {
        scanf("%d",&a[i]);
        p[i]=i;
    }
    for(int i=1; i<=n; ++i) {
        scanf("%s",m);
        for(int j=0; j<n; ++j) {
            if(m[j]=='1') {
                int jj = j+1;
                p[find(i)] = find(jj);
            }
        }
    }
    for(int i=1;i<=n; ++i) {
        for(int j=i+1; j<=n; ++j) {
            if(find(i)==find(j) && a[i]>a[j]) {
                swap(a[j], a[i]);
            }
        }
    }
    for( int i=1; i<=n; ++i) {
        printf("%d%c",a[i]," \n"[i==n]);
    }
    return 0;
}

/** fflush(stdout); **/