//problem link: https://codeforces.com/edu/course/2/lesson/4/1/practice/contest/273169/problem/A
#include <bits/stdc++.h>
using namespace std;
#define Tahsan ios::sync_with_stdio(false);cin.tie(nullptr);
const int maxN = 1e5 + 9;
long long arr[maxN], segmentTree[4 * maxN];

void buildTree(int root,int left, int right){
    if(left == right){
        segmentTree[root] = arr[left];
        return;
    }
    int mid =  left + (right - left) / 2;
    int left_child = 2*root + 1;
    int right_child = 2*root + 2;
    buildTree(left_child, left , mid);
    buildTree(right_child, mid+1, right);
    segmentTree[root] = segmentTree[left_child] + segmentTree[right_child];
}

void updateTree(int root, int left, int right, int idx, int val){
    //3 case.
    // 1 -> out of bound.
    if(right < idx || left > idx){
        return;
    }
    //2 -> leaf node + idx node.
    if(left == right){
        segmentTree[root] = val;
        return;
    }
    //3 -> intersect or overlapping.
    int left_child, right_child, mid;
    left_child = 2*root + 1;
    right_child = 2*root + 2;
    mid = left + (right - left) / 2;
    updateTree(left_child, left, mid, idx, val);
    updateTree(right_child, mid+1,right,idx,val);
    segmentTree[root] = segmentTree[left_child] + segmentTree[right_child];
}
long long get_sum(int root, int left, int right, int range_left, int range_right){
    //3 situations.
    //1 -> inner range.
    if(left>= range_left && right <= range_right){
        return segmentTree[root];
    }
    //2 -> outer range.
    if(left > range_right || right < range_left){
        return 0;
    }
    //3 -> intersect range.
    int mid = left + (right - left) / 2;
    return get_sum(2*root + 1,left,mid,range_left, range_right) + get_sum(2*root + 2,mid+1,right,range_left,range_right);
}
int main(){
    Tahsan
    int n,m;
    cin >> n >> m;
    for(int i=0;i<n;i++){
        cin>>arr[i];
    }
    buildTree(0,0,n-1);
    while(m--){
        int operation,i,v;
        cin >> operation >> i >> v;
        //rename for clarification.
        int range_left,range_right;
        if(operation == 2){
            range_left = i;
            range_right = v;
        }
        if(operation == 1){
            updateTree(0,0,n-1,i,v);
        }
        else if(operation==2){
            cout<< get_sum(0,0,n-1,range_left,range_right-1) <<'\n';
        }
    }
    return 0;
}