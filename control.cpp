#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;

// Constants for the number of days and shifts
const int DAYS_IN_WEEK = 7;
const int SHIFTS_PER_DAY = 3;
const int MAX_SHIFTS_PER_EMPLOYEE = 5;
const int MIN_EMPLOYEES_PER_SHIFT = 2;

struct Employee {
    string name;
    int shiftsAssigned = 0;
    int shiftPreferences[DAYS_IN_WEEK][SHIFTS_PER_DAY]; // Preferences for each day (morning, afternoon, evening)
};

class Scheduler {
private:
    vector<Employee> employees;
    string schedule[DAYS_IN_WEEK][SHIFTS_PER_DAY]; // Schedule for the week

public:
    // Constructor
    Scheduler() {
        srand(time(0)); // For randomization in case of conflict
    }

    // Input: Get employee data and shift preferences
    void inputEmployeeData() {
        int numEmployees;
        cout << "Enter the number of employees: ";
        cin >> numEmployees;

        for (int i = 0; i < numEmployees; i++) {
            Employee emp;
            cout << "\nEnter employee " << i + 1 << " name: ";
            cin.ignore();
            getline(cin, emp.name);

            // Get shift preferences for each day (morning, afternoon, evening)
            for (int j = 0; j < DAYS_IN_WEEK; j++) {
                cout << "Enter shift preferences for day " << j + 1 << " (1 = morning, 2 = afternoon, 3 = evening):\n";
                for (int k = 0; k < SHIFTS_PER_DAY; k++) {
                    cout << "Shift " << k + 1 << " (1, 2, 3): ";
                    cin >> emp.shiftPreferences[j][k];
                }
            }

            employees.push_back(emp);
        }
    }

    // Output: Show the final schedule
    void outputSchedule() {
        cout << "\nFinal Employee Schedule:\n";
        for (int i = 0; i < DAYS_IN_WEEK; i++) {
            cout << "Day " << i + 1 << ":\n";
            for (int j = 0; j < SHIFTS_PER_DAY; j++) {
                cout << "  Shift " << j + 1 << " (";
                if (schedule[i][j] == "") {
                    cout << "No employee assigned)";
                } else {
                    cout << schedule[i][j] << ")";
                }
                cout << endl;
            }
        }
    }

    // Scheduling Logic: Assign shifts for employees
    void assignShifts() {
        for (int i = 0; i < DAYS_IN_WEEK; i++) {
            int shiftCounts[SHIFTS_PER_DAY] = {0}; // To count how many employees are assigned to each shift

            for (int j = 0; j < employees.size(); j++) {
                if (employees[j].shiftsAssigned < MAX_SHIFTS_PER_EMPLOYEE) {
                    // Find the employee's preferred shift for the day
                    int assignedShift = employees[j].shiftPreferences[i][0] - 1; // First preference (0-indexed)
                    if (shiftCounts[assignedShift] < MIN_EMPLOYEES_PER_SHIFT) {
                        // Assign to preferred shift if it's not full
                        schedule[i][assignedShift] = employees[j].name;
                        employees[j].shiftsAssigned++;
                        shiftCounts[assignedShift]++;
                    } else {
                        // If preferred shift is full, try to assign to another shift
                        bool assigned = false;
                        for (int k = 1; k < SHIFTS_PER_DAY && !assigned; k++) {
                            int nextShift = employees[j].shiftPreferences[i][k] - 1;
                            if (shiftCounts[nextShift] < MIN_EMPLOYEES_PER_SHIFT) {
                                schedule[i][nextShift] = employees[j].name;
                                employees[j].shiftsAssigned++;
                                shiftCounts[nextShift]++;
                                assigned = true;
                            }
                        }

                        // If no shifts are available, randomly assign to any open shift
                        if (!assigned) {
                            for (int k = 0; k < SHIFTS_PER_DAY; k++) {
                                if (shiftCounts[k] < MIN_EMPLOYEES_PER_SHIFT) {
                                    schedule[i][k] = employees[j].name;
                                    employees[j].shiftsAssigned++;
                                    shiftCounts[k]++;
                                    break;
                                }
                            }
                        }
                    }
                }
            }
        }
    }
};

int main() {
    Scheduler scheduler;

    // Collect employee information and preferences
    scheduler.inputEmployeeData();

    // Assign shifts based on preferences and availability
    scheduler.assignShifts();

    // Output the final schedule
    scheduler.outputSchedule();

    return 0;
}

