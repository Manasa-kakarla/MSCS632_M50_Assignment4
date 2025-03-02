import random

# Step 1: Data structures for employee names and shifts.
days_of_week = ['Monday', 'Tuesday', 'Wednesday', 'Thursday', 'Friday', 'Saturday', 'Sunday']
shifts = ['Morning', 'Afternoon', 'Evening']

# Employee data (name and preferences for each day)
employees = []
employee_shifts = {}

# Step 2: Input Collection
def collect_input():
    print("Enter employee names and their shift preferences (Morning, Afternoon, Evening) for each day of the week.")
    while True:
        name = input("\nEnter employee name (or type 'done' to finish): ")
        if name.lower() == 'done':
            break
        preferences = {}
        for day in days_of_week:
            shift = input(f"Enter preferred shift for {day} (Morning/Afternoon/Evening): ")
            preferences[day] = shift.capitalize()
        employees.append(name)
        employee_shifts[name] = preferences

# Step 3: Schedule Assignment Logic
def assign_shifts():
    # Initialize the schedule for each day
    schedule = {day: {'Morning': [], 'Afternoon': [], 'Evening': []} for day in days_of_week}

    # Track how many days each employee is assigned
    employee_day_count = {name: 0 for name in employees}

    # Assign employees based on preferences
    for name in employees:
        for day in days_of_week:
            preferred_shift = employee_shifts[name][day]
            if len(schedule[day][preferred_shift]) < 2 and employee_day_count[name] < 5:
                schedule[day][preferred_shift].append(name)
                employee_day_count[name] += 1
                break

    # Step 4: Handling conflicts and filling empty shifts
    for day in days_of_week:
        for shift in shifts:
            # Keep trying to fill the shift until there are 2 employees or no available employees
            attempts = 0
            while len(schedule[day][shift]) < 2 and attempts < 10:
                available_employees = [name for name in employees if employee_day_count[name] < 5]
                if available_employees:
                    selected_employee = random.choice(available_employees)
                    schedule[day][shift].append(selected_employee)
                    employee_day_count[selected_employee] += 1
                else:
                    break  # If no available employees, exit the loop
                attempts += 1
            # If after attempts we still don't have enough employees, report the issue
            if len(schedule[day][shift]) < 2:
                print(f"Warning: Could not fill shift {shift} on {day} with 2 employees.")

    return schedule

# Step 5: Output the final schedule
def print_schedule(schedule):
    print("\nFinal Employee Schedule for the Week:")
    for day in days_of_week:
        print(f"\n{day}:")
        for shift in shifts:
            employees_on_shift = ', '.join(schedule[day][shift])
            print(f"  {shift}: {employees_on_shift}")

# Main execution flow
def main():
    collect_input()
    schedule = assign_shifts()
    print_schedule(schedule)

if __name__ == '__main__':
    main()
