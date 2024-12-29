#include <iostream>
#include <queue>
#include <vector>

using namespace std;

void two_way_merge(vector<int>& a, vector<int>& b, vector<int>& out){
    out.resize(a.size() + b.size());
    int a_index = 0;
    int b_index = 0;

    for (int & i : out) {
        if(a_index >= a.size()){
            i = b[b_index];
            b_index++;
            continue;
        }
        else if(b_index >= b.size()){
            i = a[a_index];
            a_index++;
            continue;
        }

        if(a[a_index] <= b[b_index]){
            i = a[a_index];
            a_index ++;
        }
        else{
            i = b[b_index];
            b_index++;
        }
    }
}

int main(){
    // možné inputy --------------------------------
    /*vector<vector<int>> files = {
            {11, 12, 13, 14, 15},
            {1, 2, 3},
            {10},
            {4, 5},
            {6, 7, 8, 9}
    };*/

    vector<vector<int>> files = {
            {},
            {1, 2, 3},
            {4},
            {5, 6, 7, 8, 9, 10},
            {11, 12},
            {},
            {13, 14, 15, 16, 17, 18, 19},
            {20, 21, 22, 23},
            {24},
            {25, 26, 27, 28, 29, 30, 31, 32},
            {33},
            {34, 35, 36},
            {37, 38, 39, 40, 41, 42, 43, 44, 45}
    };

    auto custom_cmp = [](const vector<int>& a, const vector<int>& b){
        return a.size() > b.size();
    };
    priority_queue<vector<int>, vector<vector<int>>, decltype(custom_cmp)> fileHeap(custom_cmp);

    for (vector<int>& file: files){
        fileHeap.push(file);
    }

    vector<int> out;

    while(!fileHeap.empty()){
        vector<int> a = fileHeap.top();
        fileHeap.pop();

        if(fileHeap.empty()){
            out = a;
            break;
        }

        vector<int> b = fileHeap.top();
        fileHeap.pop();

        vector<int> merge_out = {};
        //cout << "a_f_size: " << a.size() << " b_f_size: " << b.size() << " sum: ";
        two_way_merge(a, b, merge_out);
        //cout << merge_out.size() << endl << endl;
        fileHeap.push(merge_out);
    }

    for(int& e: out){
        cout << e << " " ;
    }

}