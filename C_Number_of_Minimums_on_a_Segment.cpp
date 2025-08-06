//problem link:https://codeforces.com/edu/course/2/lesson/4/1/practice/contest/273169/problem/C
#include <bits/stdc++.h>
using namespace std;
#define Tahsan ios::sync_with_stdio(false);cin.tie(nullptr);
const int inf = 1e9+5;

class Vertex{
    public:
    int min,count;
};
//global vector
const int maxN = 1e5+9;
Vertex segmentTree[maxN * 4];
int arr[maxN];

Vertex merge(Vertex left_child, Vertex right_child){
    Vertex ans;
    ans.min = min(left_child.min,right_child.min);
    ans.count = 0;
    if(ans.min == left_child.min){
        ans.count += left_child.count;
    }
    if(ans.min == right_child.min){
        ans.count += right_child.count;
    }
    return ans;
}

void build_tree(int root,int left, int right){
    if(left == right){
        segmentTree[root].min = arr[left];
        segmentTree[root].count = 1;
        return;
    }
    int mid = left + (right - left) / 2, left_child = 2*root + 1, right_child = 2*root+2;
    build_tree(left_child,left, mid);
    build_tree(right_child,mid+1,right);
    segmentTree[root] = merge(segmentTree[left_child],segmentTree[right_child]);
}
void update_tree(int root, int left, int right, int idx, int val){
    if(right < idx || left > idx){
        return;
    }
    if(left == right){
        segmentTree[root].min = val;
        segmentTree[root].count = 1;
        return;
    }
    int mid = left + (right - left) / 2, left_child = 2*root + 1, right_child = 2*root + 2;
    update_tree(left_child,left,mid,idx,val);
    update_tree(right_child,mid+1,right,idx,val);
    segmentTree[root] = merge(segmentTree[left_child],segmentTree[right_child]);
}

Vertex query(int root,int arr_left, int arr_right, int q_left, int q_right){
    // 1st case out of range
    if(q_left > arr_right || q_right < arr_left){
        return {inf,0};
    }
    // inner case
    if(q_left <= arr_left && q_right >= arr_right){
        return segmentTree[root];
    }
    //intersectional case
    int mid = (arr_left + arr_right)/2, left_child = 2*root + 1, right_child = 2*root + 2;
    return merge(query(left_child,arr_left,mid,q_left,q_right),
    query(right_child,mid+1,arr_right,q_left,q_right));
    

}


int main(){
    Tahsan
    int n,m;
    cin >> n >> m;
    for(int i=0;i<n;i++){
        cin >> arr[i];
    }
    build_tree(0,0,n-1);
    while(m--){
        int operation_type;
        cin >> operation_type;
        if(operation_type == 1){
            int idx, val;
            cin >> idx >> val;
            update_tree(0,0,n-1,idx,val);
        }
        else{
            int left,right;
            cin >> left >> right;
            Vertex result = query(0,0,n-1,left,right-1);
            cout<< result.min << " " << result.count << '\n';
        }
    }
    
    return 0;
}