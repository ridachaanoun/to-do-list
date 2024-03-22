#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_TASKS 50
#define MAX_TITLE_LENGTH 50
#define MAX_DESCRIPTION_LENGTH 500

// Task structure
 struct Task {
    char title[MAX_TITLE_LENGTH];
    char description[MAX_DESCRIPTION_LENGTH];
    int priority;
    int completed;
};

struct Task tasks[MAX_TASKS];
int num_tasks = 0;

// Function prototypes
void addTask();
void editTask();
void deleteTask();
void viewAllTasks();
void markTaskAsComplete();
void filterTasksByPriority();
void saveTasksToFile();
void loadTasksFromFile();

int main() {
    int choice;
    loadTasksFromFile();

    while (true){
        printf("\nTask Management Menu:\n");
        printf("1. Add Task\n");
        printf("2. Edit Task\n");
        printf("3. Delete Task\n");
        printf("4. View All Tasks\n");
        printf("5. Mark Task as Complete\n");
        printf("6. Filter Tasks by Priority\n");
        printf("7. Save Tasks to File\n");
        printf("8. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
     getchar();

        switch (choice) {
            case 1:
                addTask();
                break;
            case 2:
                editTask();
                break;
            case 3:
                deleteTask();
                break;
            case 4:
                viewAllTasks();
                break;
            case 5:
                markTaskAsComplete();
                break;
            case 6:
                filterTasksByPriority();
                break;
            case 7:
                saveTasksToFile();
                break;
            case 8:
                printf("Exiting the program.\n");
                return 0 ;
            default:
                printf("Invalid choice. Please enter a number between 1 and 8.\n");
        }

    }
    return 0;
}

void addTask() {
    if (num_tasks >= MAX_TASKS) {
        printf("Cannot add more tasks. Task list is full.\n");
        return 0;
    }

    printf("Enter task details:\n");
    printf("Title: ");
    scanf(" %[^\n]", tasks[num_tasks].title); // to add it with spase
    printf("description :");
    scanf(" %[^\n]", tasks[num_tasks].description);
    printf("Priority (1-5): ");
    scanf(" %d", &tasks[num_tasks].priority);
    tasks[num_tasks].completed = 0;

    num_tasks++;
    printf("Task added successfully.\n");
}

void editTask() {
    viewAllTasks();
    int index;
    printf("Enter the index of the task to edit (0-%d): ", num_tasks - 1);
    scanf("%d", &index);

    if (index < 0 || index >= num_tasks) {
        printf("Invalid index. Please enter a valid index.\n");
        return;
    }

    printf("Enter new task details:\n");
    printf("Title: ");
    scanf(" %[^\n]", tasks[index].title);
    printf("description:");
    scanf(" %[^\n]", tasks[num_tasks].description);
    printf("Priority (1-5): ");
    scanf("%d", &tasks[index].priority);

        viewAllTasks();

    printf("Task edited successfully.\n");
}

void deleteTask() {
    viewAllTasks();
    int index;
    printf("Enter the index of the task to delete (0-%d): ", num_tasks - 1);
    scanf("%d", &index);

    if (index < 0 || index >= num_tasks) {
        printf("Invalid index. Please enter a valid index.\n");
        return;
    }

    for (int i = index; i < num_tasks - 1; i++) {
        tasks[i] = tasks[i + 1];
    }

    num_tasks--;

        viewAllTasks();

    printf("the Task was deleted successfully.!\n");

    viewAllTasks();

}

void filterTasksByPriority() {
    int priority;
    printf("Enter priority to filter (1-5): ");
    scanf(" %d", &priority);

    printf("Tasks with priority %d :\n", priority);
    for (int i = 0; i < num_tasks; i++) {
        if (tasks[i].priority == priority) {
            printf("\nTitle: %s\n", tasks[i].title);
            printf("Priority: %d\n", tasks[i].priority);
            printf("description: %s\n", tasks[i].description);
            printf("Completed: %s\n", tasks[i].completed ? "Yes" : "No");
            printf("\n");
        }
    }
}

void viewAllTasks() {
    printf("All Tasks:\n");
    for (int i = 0; i < num_tasks; i++) {
        printf("Index: %d\n", i);
        printf("Title: %s\n", tasks[i].title);
        printf("description:%s \n", tasks[i].description);
        printf("Priority: %d\n", tasks[i].priority);

        if (tasks[i].completed)
            printf("Completed: %s\n","YES" );
        else
            printf("Completed: %s\n","NO" );
        printf("\n");
    }
}

void markTaskAsComplete() {
    int index;
    printf("Enter the index of the task to mark as complete (0-%d): ", num_tasks - 1);
    scanf("%d", &index);

    if (index < 0 || index >= num_tasks) {
        printf("Invalid index. Please enter a valid index.\n");
        return;
    }

    tasks[index].completed = 1;
    printf("Task marked as complete.\n");
}

void saveTasksToFile() {
    FILE *file = fopen("tasks.txt", "w");

    if (file == NULL) printf("Error opening file for writing.\n");

    for (int i = 0; i < num_tasks; i++) {
        fprintf(file, "%s;%s;%d;%d\n", tasks[i].title,tasks[i].description,tasks[i].priority, tasks[i].completed);
    }

    fclose(file);
    printf("Tasks saved to file.\n");
}

void loadTasksFromFile() {
    FILE *file = fopen("tasks.txt", "r");
    if (file == NULL) {
        printf("No tasks file found. Creating a new one.\n");
        return;
    }
    //feof is a function used to check whether the and of file indicator has been set for a file
    while (!feof(file)) {
        if (num_tasks >= MAX_TASKS) {
            printf("Cannot load more tasks.\n");
            break;
        }

        fscanf(file, "%[^;];%[^;];%d;%d\n",
                tasks[num_tasks].title,
                 tasks[num_tasks].description,
                  &tasks[num_tasks].priority,
                   &tasks[num_tasks].completed);
        num_tasks++;
    }

    fclose(file);
    printf("Tasks loaded from file.\n");
}
