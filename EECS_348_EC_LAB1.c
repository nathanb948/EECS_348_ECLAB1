#include <stdio.h>
#include <stdbool.h>

int dept_assignments[5] = {-1, -1, -1, -1, -1}; 
bool prog_assigned[5] = {true, true, true, true, true}; 

int main() {
    FILE *fp;
    fp = fopen("input.txt", "r");

    int dept_pref[5][5];
    int prog_pref[5][5];

    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            fscanf(fp, "%d", &dept_pref[j][i]);
        }
    }

    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            fscanf(fp, "%d", &prog_pref[j][i]);
        }
    }

    bool completed = false;
    while (!completed) {
        completed = true;
        for (int i = 0; i < 5; i++) {
            if (dept_assignments[i] == -1) {
                completed = false;
                for (int j = 0; j < 5; j++) {
                    if (prog_assigned[dept_pref[i][j] - 1] == true) { 
                        dept_assignments[i] = dept_pref[i][j] - 1;
                        prog_assigned[dept_pref[i][j] - 1] = false;
                        break;
                    } 
	            else {
                        int curr_prog = dept_assignments[dept_pref[i][j] - 1];
                        int cur_dept = 0;
                        int new_dept = 0;
                        for (int k = 0; k < 5; k++) {
                            if (prog_pref[dept_pref[i][j] - 1][k] == i + 1) {
                                new_dept = k;
                            }
                            if (prog_pref[dept_pref[i][j] - 1][k] == curr_prog + 1) {
                                cur_dept = k;
                            }
                    }
                        if (new_dept < cur_dept) {
                            dept_assignments[i] = dept_pref[i][j] - 1;
                            prog_assigned[dept_pref[i][j] - 1] = false;
                            dept_assignments[curr_prog] = -1;
                            break;
                        }
                    }
                }
            }
        }
    }
    for (int i = 0; i < 5; i++) {
        printf("Department %d will get Programmer %d\n", i + 1, dept_assignments[i] + 1);
    }
    return 0;
}

