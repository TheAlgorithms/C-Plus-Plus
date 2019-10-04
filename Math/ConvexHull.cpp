#include<bits/stdc++.h>
using namespace std;

typedef long long lli;
typedef pair<lli,lli> point;
#define x first
#define y second

point conv[50100];
point ul;

lli dist(point a, point b){
    return (a.x-b.x)*(a.x-b.x) + (a.y-b.y)*(a.y-b.y);
}
int isleft(point t, point a, point b) {
    lli res = (a.y-t.y)*(b.x-t.x)-(b.y-t.y)*(a.x-t.x);
    if (res < 0) return 1; // left
    else if (res > 0) return 0; // right
    else return 2;
}

bool slope(point a, point b) {
    if (isleft(ul, a, b) == 2) return dist(ul, a) < dist(ul, b);
    else return isleft(ul, a, b);
}

bool cmp (point a, point b){
    if (a.x != b.x) return a.x < b.x;
    return a.y > b.y;
}

point s[50100];
int top = 0;

int main(){
    int n;
    scanf("%d", &n);
    for(int i = 1; i <= n; i++){
        scanf("%lld %lld", &conv[i].x, &conv[i].y);
    }
    sort(conv+1, conv+n+1, cmp); // find upperleft
    ul = conv[1];
    sort(conv+2, conv+n+1, slope);

    //for(int i = 1; i <= n; i++) cerr << conv[i].x << ' ' << conv[i].y << endl;

    s[++top] = ul;
    s[++top] = conv[2];

    for(int i = 3; i <= n; i++) {
        while (top > 1 && (isleft(s[top-1], s[top], conv[i])==0 || isleft(s[top-1], s[top], conv[i])==2)) top--;
        s[++top] = conv[i];
    }

    if(isleft(s[top-1], s[top], conv[1])==0 || isleft(s[top-1], s[top], conv[1])==2) top--;

    printf("%d\n", top);
    for(int i = 1; i <= top; i++) {
        printf("%lld %lld\n", s[i].x, s[i].y);
    }

    return 0;
}