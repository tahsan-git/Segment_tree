//problem link: https://codeforces.com/contest/339/problem/D
#include <bits/stdc++.h>
using namespace std;
#define Tahsan ios::sync_with_stdio(false);cin.tie(nullptr);
const int maxN = (1 << 17) + 9;
int arr[maxN];
int segmentTree[4 * maxN];

int merge(int a, int b, int level) {
    // int pw = 0;
    // pw = __lg(len);
    return ((level&1) ? (a | b) : (a ^ b));
}

void build_Tree(int root,int start, int end,int level){
    if(start == end){
        segmentTree[root] = arr[start];
        return;
    }
    int mid = (start + end)/2, left = 2*root, right = 2*root + 1;
    build_Tree(left,start,mid,level-1);
    build_Tree(right,mid+1,end,level-1);
    segmentTree[root] = merge(segmentTree[left],segmentTree[right],level);
}
void update_tree(int root,int start, int end, int idx, int val,int level){
    if(idx < start || idx > end){
        return;
    }
    if(start == end){
        segmentTree[root] = val;
        return;
    }
    int mid = (start + end)/2, left = 2*root, right = 2*root+1;
    update_tree(left,start,mid,idx,val,level-1);
    update_tree(right,mid+1,end,idx,val,level-1);
    segmentTree[root] = merge(segmentTree[left],segmentTree[right], level);
}
int main(){
    int n,m;
    cin >> n >> m;
    for(int i=1; i <= (1<<n); i++){
        cin >> arr[i];
    }
    int size = (1 << n);
    build_Tree(1,1,size,n);
    while(m--){
        int idx,val;
        cin >> idx >> val;
        update_tree(1,1,size,idx,val,n);
        cout << segmentTree[1] << endl;
    }
    return 0;
}