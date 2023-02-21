#include <stdio.h>
#include <stdbool.h>

int dept_assignments[5] = {-1, -1, -1, -1, -1}; //establishing an array for the final programmer assignments to each department
bool prog_assigned[5] = {true, true, true, true, true}; //array of booleans to check if each programmer is assigned yet

int main() {
    //opening the input file to grab and make the arrays
    FILE *fp;
    fp = fopen("input.txt", "r");

    int dept_pref[5][5];
    int prog_pref[5][5];
    //iterates row first then goes through each column 5 at a time so the array is correct
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
    //setting a boolean to equal false automatically
    bool completed = false;
    while (!completed) {  //as long as completed isnt true the loop will continue
        completed = true;
        for (int i = 0; i < 5; i++) { //checking each iteration to see if the algorithm is complete
            if (dept_assignments[i] == -1) {
                completed = false;
                for (int j = 0; j < 5; j++) { //running through algorithm
                    if (prog_assigned[dept_pref[i][j] - 1] == true) { //if programmer is not assigned
                        dept_assignments[i] = dept_pref[i][j] - 1; //assign them
                        prog_assigned[dept_pref[i][j] - 1] = false;//they do not need to be assigned for the mean time
                        break;
                    } 
	            else {
                        int curr_prog = dept_assignments[dept_pref[i][j] - 1];
                        int cur_dept = 0;
                        int new_dept = 0;
                        for (int k = 0; k < 5; k++) {// checks to see where the cur department and the new department appear on the cur programmers preference list
                            if (prog_pref[dept_pref[i][j] - 1][k] == i + 1) {
                                new_dept = k;
                            }
                            if (prog_pref[dept_pref[i][j] - 1][k] == curr_prog + 1) {
                                cur_dept = k;
                            }
                    }
                        if (new_dept < cur_dept) { //if the programmer prefers the new department over the current department
                            dept_assignments[i] = dept_pref[i][j] - 1; //assign that programmer to the department
                            prog_assigned[dept_pref[i][j] - 1] = false;//they do not need to be assigned for the mean time
                            dept_assignments[curr_prog] = -1;//make the original assignment null since they ahve been reassigned
                            break;
                        }
                    }
                }
            }
        }
    }
    for (int i = 0; i < 5; i++) {
        printf("Department %d will get Programmer %d\n", i + 1, dept_assignments[i] + 1); //print out results
    }
    return 0;
}

