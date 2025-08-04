#include <bits/stdc++.h>
using namespace std;
#define Tahsan ios::sync_with_stdio(false);cin.tie(nullptr);
const int maxN = 1e5 + 9;
const int inf = 1e9 + 5;
int arr[maxN],segmentTree[4*maxN];

void buildTree(int root,int left, int right){
    if(left == right){
        segmentTree[root] = arr[left];
        return;
    }
    int mid = left + (right - left)/2, left_child = 2*root + 1, right_child = 2*root + 2;
    buildTree(left_child,left,mid);
    buildTree(right_child,mid+1,right);
    segmentTree[root] = min(segmentTree[left_child],segmentTree[right_child]);
}

void updateTree(int root,int start, int end, int idx, int val){
    if(idx < start || idx > end){
        return;
    }
    if(start == end){
        segmentTree[root] = val;
        return;
    }
    int mid = start + (end - start) / 2, l_child = 2*root + 1, r_child = 2*root + 2;
    updateTree(l_child,start,mid,idx,val);
    updateTree(r_child,mid+1,end,idx,val);
    segmentTree[root] = min(segmentTree[l_child],segmentTree[r_child]);
}

int get_min(int root,int segment_left, int segment_right, int range_left, int range_right){
    if(range_left > segment_right || range_right < segment_left){
        return inf;
    }
    if(segment_left >= range_left && segment_right <= range_right){
        return segmentTree[root];
    }
    int mid = segment_left + (segment_right - segment_left) / 2;
    int l_side = 2*root + 1;
    int r_side = l_side+1;
    return min(get_min(l_side,segment_left,mid,range_left,range_right),get_min(r_side,mid+1,segment_right,range_left,range_right));
}

int main(){
    Tahsan
    int n, m;
    cin >> n >> m;
    for(int i=0;i<n;i++){
        cin >> arr[i];
    }
    buildTree(0,0,n-1);
    while(m--){
        int operation;
        cin >> operation;
        if(operation == 1){
            int idx,val;
            cin >> idx >> val;
            updateTree(0,0,n-1,idx,val);
        }
        else{
            int left,right;
            cin >> left >> right;
            int result = get_min(0,0,n-1,left,right-1);
            cout<<result<<'\n';
        }
    }
    return 0;
}