#include <algorithm>
#include <iostream>
#include <limits>
#include <queue>
#include <stack>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

struct Task {
    int id;
    string name;
    int priority;
};

unordered_map<int, Task> taskMap;
stack<Task> undoStack;
queue<Task> taskQueue;
vector<Task> taskList;

void addTask(int id, const string& name, int priority) {
    Task task{id, name, priority};
    taskMap[id] = task;

    auto it = find_if(taskList.begin(), taskList.end(),
                      [id](const Task& currentTask) { return currentTask.id == id; });

    if (it != taskList.end()) {
        *it = task;
    } else {
        taskList.push_back(task);
    }

    taskQueue.push(task);
}

void deleteTask(int id) {
    auto mapIt = taskMap.find(id);
    if (mapIt == taskMap.end()) {
        cout << "Task not found.\n";
        return;
    }

    undoStack.push(mapIt->second);
    taskMap.erase(mapIt);

    taskList.erase(remove_if(taskList.begin(), taskList.end(),
                             [id](const Task& task) { return task.id == id; }),
                   taskList.end());

    cout << "Task deleted.\n";
}

void undoDelete() {
    if (undoStack.empty()) {
        cout << "Nothing to undo.\n";
        return;
    }

    Task task = undoStack.top();
    undoStack.pop();
    addTask(task.id, task.name, task.priority);
    cout << "Task restored.\n";
}

void searchTask(int id) {
    auto it = taskMap.find(id);
    if (it != taskMap.end()) {
        cout << "Found: " << it->second.id << " " << it->second.name << " "
             << it->second.priority << '\n';
    } else {
        cout << "Task not found.\n";
    }
}

void sortTasks() {
    sort(taskList.begin(), taskList.end(),
         [](const Task& first, const Task& second) {
             if (first.priority == second.priority) {
                 return first.id < second.id;
             }
             return first.priority > second.priority;
         });

    cout << "Tasks sorted by priority.\n";
}

void processTasks() {
    if (taskQueue.empty()) {
        cout << "No tasks to process.\n";
        return;
    }

    while (!taskQueue.empty()) {
        Task task = taskQueue.front();
        taskQueue.pop();

        if (taskMap.find(task.id) != taskMap.end()) {
            cout << "Processing: " << task.name << '\n';
        }
    }
}

void displayTasks() {
    if (taskList.empty()) {
        cout << "No tasks available.\n";
        return;
    }

    cout << "ID  Name  Priority\n";
    for (const Task& task : taskList) {
        cout << task.id << "  " << task.name << "  " << task.priority << '\n';
    }
}

int readInt(const string& prompt) {
    int value;

    while (true) {
        cout << prompt;
        if (cin >> value) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return value;
        }

        cout << "Invalid number. Try again.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

string readLine(const string& prompt) {
    string value;
    cout << prompt;
    getline(cin, value);
    return value;
}

void printMenu() {
    cout << "\nTask Manager Menu\n";
    cout << "1. Add Task\n";
    cout << "2. Delete Task\n";
    cout << "3. Undo Delete\n";
    cout << "4. Search Task\n";
    cout << "5. Sort Tasks by Priority\n";
    cout << "6. Process Tasks\n";
    cout << "7. Display Tasks\n";
    cout << "8. Exit\n";
}

int main() {
    while (true) {
        printMenu();
        int choice = readInt("Enter your choice: ");

        if (choice == 1) {
            int id = readInt("Enter task id: ");
            string name = readLine("Enter task name: ");
            int priority = readInt("Enter priority: ");
            addTask(id, name, priority);
            cout << "Task added.\n";
        } else if (choice == 2) {
            int id = readInt("Enter task id to delete: ");
            deleteTask(id);
        } else if (choice == 3) {
            undoDelete();
        } else if (choice == 4) {
            int id = readInt("Enter task id to search: ");
            searchTask(id);
        } else if (choice == 5) {
            sortTasks();
        } else if (choice == 6) {
            processTasks();
        } else if (choice == 7) {
            displayTasks();
        } else if (choice == 8) {
            cout << "Exiting...\n";
            break;
        } else {
            cout << "Invalid choice. Try again.\n";
        }
    }

    return 0;
}
