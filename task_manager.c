#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct Task {
    int id;
    char name[100];
    char description[100];
    int isComplete;
} Task;

typedef struct Node {
    Task task;
    struct Node* next;
} Node;

typedef struct LinkedList {
    Node* head;
} LinkedList;

Task* createTask(int id, char name[], char description[]) {
    Task* newTask = (Task*)malloc(sizeof(Task));
    newTask->id = id;
    strcpy(newTask->name, name);
    strcpy(newTask->description, description);
    newTask->isComplete = 0;
    return newTask;
}

Node* createNode(Task* task) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->task = *task;
    newNode->next = NULL;
    return newNode;
}

void insertTask(LinkedList* list, Task* task) {
    Node* newNode = createNode(task);

    if (list->head == NULL) {
        list->head = newNode;
    } else {
        Node* curr = list->head;
        while (curr->next != NULL) {
            curr = curr->next;
        }
        curr->next = newNode;
    }

    printf("Task added successfully.\n");
}

void removeTask(LinkedList* list, int taskId) {
    if (list->head == NULL) {
        printf("Task list is empty.\n");
        return;
    }

    Node* curr = list->head;
    Node* prev = NULL;

    while (curr != NULL) {
        if (curr->task.id == taskId) {
            if (prev == NULL) {

                list->head = curr->next;
            } else {
                prev->next = curr->next;
            }
            free(curr);
            printf("Task removed successfully.\n");
            return;
        }
        prev = curr;
        curr = curr->next;
    }

    printf("Task with ID %d not found.\n", taskId);
}

void markTaskAsComplete(LinkedList* list, int taskId) {
    Node* curr = list->head;

    while (curr != NULL) {
        if (curr->task.id == taskId) {
            curr->task.isComplete = 1;
            printf("Task marked as complete.\n");
            return;
        }
        curr = curr->next;
    }

    printf("Task with ID %d not found.\n", taskId);
}

void displayTasks(LinkedList* list) {
    if (list->head == NULL) {
        printf("Task list is empty.\n");
        return;
    }

    Node* curr = list->head;

    printf("Task ID\t\tName\t\tDescription\t\tStatus\n");
    while (curr != NULL) {
        printf("%d\t\t%s\t\t%s\t\t%s\n", curr->task.id, curr->task.name, curr->task.description, (curr->task.isComplete ? "Complete" : "Incomplete"));
        curr = curr->next;
    }
}

void displayMenu() {
    printf("\nTask Manager Menu\n");
    printf("1. Add a task\n");
    printf("2. Remove a task\n");
    printf("3. Mark a task as complete\n");
    printf("4. Display all tasks\n");
    printf("5. Exit\n");
    printf("Enter your choice: ");
}

int getUserChoice() {
    int choice;
    scanf("%d", &choice);
    return choice;
}

void clearInputBuffer() {
    while (getchar() != '\n');
}

Task* getTaskDetailsFromUser() {
    Task* task = (Task*)malloc(sizeof(Task));
    
    printf("Enter Task ID: ");
    scanf("%d", &(task->id));
    clearInputBuffer();

    printf("Enter Task Name: ");
    fgets(task->name, 100, stdin);
    task->name[strcspn(task->name, "\n")] = '\0';

    printf("Enter Task Description: ");
    fgets(task->description, 100, stdin);
    task->description[strcspn(task->description, "\n")] = '\0';

    task->isComplete = 0;

    return task;
}

int main() {
    LinkedList taskManager;
    taskManager.head = NULL;

    while (1) {
        displayMenu();
        int choice = getUserChoice();

        switch (choice) {
            case 1: {
                Task* task = getTaskDetailsFromUser();
                insertTask(&taskManager, task);
                break;
            }
            case 2: {
                int taskId;
                printf("Enter Task ID to remove: ");
                scanf("%d", &taskId);
                clearInputBuffer();
                removeTask(&taskManager, taskId);
                break;
            }
            case 3: {
                int taskId;
                printf("Enter Task ID to mark as complete: ");
                scanf("%d", &taskId);
                clearInputBuffer();
                markTaskAsComplete(&taskManager, taskId);
                break;
            }
            case 4:
                displayTasks(&taskManager);
                break;
            case 5:
                printf("Exiting the program.\n");
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}