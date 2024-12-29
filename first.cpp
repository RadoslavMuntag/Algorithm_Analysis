#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Job{
    int index;
    int deadline;
    int profit;
};

bool get_better_job(const Job& a, const Job& b){
    return a.profit > b.profit;
}

void sort_by_profit(vector<Job>& jobs){
    sort(jobs.begin(), jobs.end(), get_better_job);
}

int get_max_max_deadline(vector<Job>& jobs){
    int max_deadline = 0;
    for (const Job& job : jobs){
        max_deadline = max(max_deadline, job.deadline);
    }
    return max_deadline;
}

int schedule(vector<Job>& jobs, vector<int>& J, int max_deadline){
    int last_unfilled = 1;
    int total_profit = 0;

    for (const Job& job : jobs) {
        if (J[job.deadline] == -1){
            J[job.deadline] = job.index;
            total_profit += job.profit;
        }
        else if(J[job.deadline] > last_unfilled){
            for (int i = job.deadline; i >= last_unfilled; i--) {
                if (J[i] == -1){
                    J[i] = job.index;
                    total_profit += job.profit;
                    break;
                }
            }
        }
        for (int i = last_unfilled; i < max_deadline + 1; i++) {
            if (J[i] == -1) break;
            last_unfilled++;
        }
    }

    return total_profit;
}

int main() {
    // možné inputy --------------------------------
    vector<Job> jobs = {
            {1, 2, 40},
            {2, 4, 15},
            {3, 3, 60},
            {4, 2, 20},
            {5, 3, 10},
            {6, 1, 45},
            {7, 1, 55}
    };

    /*vector<Job> jobs = {
            {1, 2, 50},
            {2, 1, 60},
            {3, 2, 20},
            {4, 1, 30},
            {5, 3, 80}
    };*/

    /*vector<Job> jobs = {
            {1, 4, 70},
            {2, 1, 50},
            {3, 2, 120},
            {4, 3, 40},
            {5, 1, 90},
            {6, 4, 30},
            {7, 2, 60},
            {8, 3, 20},
            {9, 4, 100},
            {10, 2, 10}
    };*/

    /*vector<Job> jobs = {
            {1, 10, 100}, {2, 15, 120}, {3, 5, 200}, {4, 20, 180}, {5, 7, 250},
            {6, 8, 90}, {7, 6, 300}, {8, 25, 80}, {9, 30, 70}, {10, 12, 150},
            {11, 2, 500}, {12, 1, 400}, {13, 3, 220}, {14, 4, 310}, {15, 18, 100},
            {16, 9, 95}, {17, 11, 85}, {18, 22, 400}, {19, 19, 230}, {20, 16, 340},
            {21, 14, 270}, {22, 21, 50}, {23, 13, 120}, {24, 17, 250}, {25, 24, 360},
            {26, 26, 320}, {27, 23, 310}, {28, 28, 200}, {29, 27, 180}, {30, 29, 190},
            {31, 30, 210}, {32, 3, 130}, {33, 7, 90}, {34, 8, 150}, {35, 10, 100},
            {36, 15, 220}, {37, 5, 250}, {38, 20, 180}, {39, 12, 160}, {40, 4, 270},
            {41, 14, 290}, {42, 13, 310}, {43, 2, 380}, {44, 9, 210}, {45, 11, 270},
            {46, 6, 190}, {47, 22, 230}, {48, 19, 300}, {49, 18, 150}, {50, 25, 140},
            {51, 17, 90}, {52, 24, 190}, {53, 26, 250}, {54, 21, 310}, {55, 28, 230},
            {56, 27, 240}, {57, 29, 330}, {58, 1, 340}, {59, 30, 360}, {60, 23, 310},
            {61, 10, 100}, {62, 15, 120}, {63, 5, 200}, {64, 20, 180}, {65, 7, 250},
            {66, 8, 90}, {67, 6, 300}, {68, 25, 80}, {69, 30, 70}, {70, 12, 150},
            {71, 2, 500}, {72, 1, 400}, {73, 3, 220}, {74, 4, 310}, {75, 18, 100},
            {76, 9, 95}, {77, 11, 85}, {78, 22, 400}, {79, 19, 230}, {80, 16, 340},
            {81, 14, 270}, {82, 21, 50}, {83, 13, 120}, {84, 17, 250}, {85, 24, 360},
            {86, 26, 320}, {87, 23, 310}, {88, 28, 200}, {89, 27, 180}, {90, 29, 190},
            {91, 30, 210}, {92, 3, 130}, {93, 7, 90}, {94, 8, 150}, {95, 10, 100},
            {96, 15, 220}, {97, 5, 250}, {98, 20, 180}, {99, 12, 160}, {100, 4, 270},
            {101, 14, 290}, {102, 13, 310}, {103, 2, 380}, {104, 9, 210}, {105, 11, 270},
            {106, 6, 190}, {107, 22, 230}, {108, 19, 300}, {109, 18, 150}, {110, 25, 140},
            {111, 17, 90}, {112, 24, 190}, {113, 26, 250}, {114, 21, 310}, {115, 28, 230},
            {116, 27, 240}, {117, 29, 330}, {118, 1, 340}, {119, 30, 360}, {120, 23, 310}
    };*/


    sort_by_profit(jobs);
    int max_deadline = get_max_max_deadline(jobs);

    vector<int> J(max_deadline + 1, -1);
    int total_profit = schedule(jobs, J, max_deadline);

    cout << "Selected Jobs: ";
    for (int index : J) {
        if (index == -1){
            continue;
        }
        cout << "J" << index << " ";
    }

    cout << endl << "Total profit is " <<total_profit;
    return 0;
}

