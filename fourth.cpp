#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <unordered_map>

using namespace std;

typedef struct Character{
    char self{};
    float prob{};
    int code{};
    int rank{};
    vector<Character*> merged;
}Character;

bool get_more_frequent(Character& a, Character& b){
    return a.prob > b.prob;
}

void print_binary(Character& a,unordered_map<string,char>& look_up_table){
    string code;
    for (int i = a.rank - 1; i >= 0; --i) {
        int current = ((a.code>>i)&1);
        code += current + '0';
        cout << current;
    }
    look_up_table[code] = a.self;
}

void print_inverse_binary(Character& a , unordered_map<string,char>& look_up_table){
    int n = a.code;
    string code;
    for (int i = 0; i < a.rank; ++i) {
        cout << n%2;
        code += n%2 + '0';
        n = n >> 1;
    }
    look_up_table[code] = a.self;
}

void merge_characters(Character* a, Character* b, Character* out){
    out->merged.resize(2 + b->merged.size() + a->merged.size());
    int out_index = 0;

    a->code = a->code << 1;
    a->rank++;
    out->merged[out_index] = a;
    out_index++;

    for (Character* sub_a: a->merged){
        sub_a->code = sub_a->code << 1;
        sub_a->rank++;
        out->merged[out_index] = sub_a;
        out_index++;
    }

    b->code = (b->code << 1) + 1;
    b->rank++;
    out->merged[out_index] = b;
    out_index++;

    for (Character* sub_b: b->merged){
        sub_b->code = (sub_b->code << 1) + 1;
        sub_b->rank++;
        out->merged[out_index] = sub_b;
        out_index++;
    }
    out->prob = a->prob + b->prob;
}

void huffman_merging(vector<Character>& table){
    auto custom_cmp = [](const Character* a, const Character* b){
        return a->prob > b->prob;
    };
    priority_queue<Character*, vector<Character*>, decltype(custom_cmp)> minHeap(custom_cmp);

    for (auto & current : table) {
        minHeap.push(&current);
    }

    while (!minHeap.empty()){
        Character *a = minHeap.top();
        minHeap.pop();

        if (minHeap.empty()) break;
        Character *b = minHeap.top();
        minHeap.pop();

        auto *out = new Character;
        out->self = '\0';
        out->code = 0;
        out->prob = 0;
        out->rank = 0;
        out->merged = {};

        merge_characters(a, b, out);
        minHeap.push(out);
    }
}

void decode_from_table(string bits, unordered_map<string,char>& look_up_table){
    string decoded;
    string buffer;
    cout << "Dekodovanie: ";
    for(char bit: bits){
        buffer += bit;

        if (look_up_table.find(buffer) != look_up_table.end()) {
            decoded += look_up_table.at(buffer);
            buffer.clear();
        }
    }
    cout << decoded << endl;
}

void standard(vector<Character>& table, unordered_map<string,char>& look_up_table){
    huffman_merging(table);

    cout << "Standard Huffman Codes" << endl;
    for (Character& current: table) {
        cout << current.self << " ";
        print_inverse_binary(current, look_up_table);
        cout << endl;
    }
}

void canonical(vector<Character>& table, unordered_map<string,char>& look_up_table){
    if (table[0].rank == 0){
        huffman_merging(table);
    }
    int binary = 0;
    int last_rank = 0;

    cout << "Canonical Huffman Codes" << endl;
    for (Character& current: table) {
        cout << current.self << " ";
        if (last_rank != 0){
            binary += 1;
            if(last_rank < current.rank){
                binary = binary << (current.rank - last_rank);
            }
        }
        current.code = binary;
        last_rank = current.rank;

        print_binary(current, look_up_table);

        cout << endl;
    }
}

void frequency_based_approximation(vector<Character>& table, unordered_map<string,char>& look_up_table){

    cout << "Frequency Based Approximation" << endl;
    for (int i = 0; i < table.size(); ++i) {
        table[i].code = (1 << (i + 1)) - 1;
        table[i].rank = i;
        if(i != table.size() - 1){
            table[i].code = table[i].code << 1;
            table[i].rank += 1;
        }

        cout << table[i].self << " ";
        print_binary(table[i], look_up_table);
        cout << endl;
    }
}

int main(){
    // možné inputy --------------------------------
    vector<char> char_table = {'A', 'B', 'C', 'D', 'E', 'F'};
    vector<int> freq_table = {45, 13, 12, 16, 9, 5};

    /*vector<char> char_table = {'A', 'B', 'C', 'D'};
    vector<int> freq_table = {10, 1, 15, 7};*/

    /*vector<char> char_table = {
            'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P'
    };
    vector<int> freq_table = {
            45, 13, 12, 16, 9, 5, 25, 30, 22, 18, 10, 14, 50, 7, 11, 8
    };*/

    int sum = 0;
    for (int& freq : freq_table){
        sum += freq;
    }
    vector<Character> table;
    unordered_map<string,char> look_up_table;

    table.resize(char_table.size());

    for (int i = 0; i < char_table.size(); ++i) {
        Character *current = &table[i];
        current->self = char_table[i];
        current->prob = (float)freq_table[i] / (float)sum;
        current->code = 0;
        current->rank = 0;
        current->merged = {};
    }

    sort(table.begin(), table.end(), get_more_frequent);

    standard(table, look_up_table);
    decode_from_table("1010101000", look_up_table);
    canonical(table, look_up_table);
    decode_from_table("1010101000", look_up_table);
    frequency_based_approximation(table, look_up_table);
    decode_from_table("1010101000", look_up_table);

}

