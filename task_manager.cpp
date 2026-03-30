#include <bits/stdc++.h>
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

// Add Task
void addTask(int id, string name, int priority) {
    if(taskMap.count(id)) {
        cout << "❌ Task with this ID already exists!\n";
        return;
    }

    Task t = {id, name, priority};
    taskMap[id] = t;
    taskList.push_back(t);
    taskQueue.push(t);

    cout << "✅ Task added successfully!\n";
}

// Delete Task
void deleteTask(int id) {
    if(taskMap.find(id) == taskMap.end()) {
        cout << "❌ Task not found!\n";
        return;
    }

    undoStack.push(taskMap[id]);
    taskMap.erase(id);

    taskList.erase(remove_if(taskList.begin(), taskList.end(),
        [id](Task t){ return t.id == id; }), taskList.end());

    cout << "🗑️ Task deleted (can undo)\n";
}

// Undo Delete
void undoDelete() {
    if(undoStack.empty()) {
        cout << "❌ Nothing to undo!\n";
        return;
    }

    Task t = undoStack.top();
    undoStack.pop();
    addTask(t.id, t.name, t.priority);

    cout << "↩️ Undo successful!\n";
}

// Search Task
void searchTask(int id) {
    if(taskMap.find(id) != taskMap.end()) {
        Task t = taskMap[id];
        cout << "🔍 Found → ID: " << t.id 
             << ", Name: " << t.name 
             << ", Priority: " << t.priority << endl;
    } else {
        cout << "❌ Task not found!\n";
    }
}

// Sort Tasks
void sortTasks() {
    sort(taskList.begin(), taskList.end(), [](Task a, Task b) {
        return a.priority > b.priority;
    });

    cout << "\n📊 Tasks sorted by priority:\n";
    for(auto t : taskList) {
        cout << "ID: " << t.id 
             << " | Name: " << t.name 
             << " | Priority: " << t.priority << endl;
    }
}

// Process Tasks
void processTasks() {
    if(taskQueue.empty()) {
        cout << "❌ No tasks to process!\n";
        return;
    }

    cout << "\n⚙️ Processing Tasks:\n";
    while(!taskQueue.empty()) {
        Task t = taskQueue.front();
        taskQueue.pop();
        cout << "➡️ " << t.name << endl;
    }
}

// Display Tasks
void display() {
    if(taskList.empty()) {
        cout << "❌ No tasks available!\n";
        return;
    }

    cout << "\n📋 All Tasks:\n";
    for(auto t : taskList) {
        cout << "ID: " << t.id 
             << " | Name: " << t.name 
             << " | Priority: " << t.priority << endl;
    }
}

int main() {
    int choice;

    while(true) {
        cout << "\n========== TASK MANAGER ==========\n";
        cout << "1. Add Task\n";
        cout << "2. Delete Task\n";
        cout << "3. Undo Delete\n";
        cout << "4. Search Task\n";
        cout << "5. Sort by Priority\n";
        cout << "6. Process Tasks\n";
        cout << "7. Display All Tasks\n";
        cout << "8. Exit\n";
        cout << "Enter choice: ";

        cin >> choice;

        if(choice == 1) {
            int id, priority;
            string name;

            cout << "Enter Task ID: ";
            cin >> id;

            cout << "Enter Task Name (no spaces): ";
            cin >> name;

            cout << "Enter Priority (higher = important): ";
            cin >> priority;

            addTask(id, name, priority);
        }
        else if(choice == 2) {
            int id;
            cout << "Enter Task ID to delete: ";
            cin >> id;
            deleteTask(id);
        }
        else if(choice == 3) {
            undoDelete();
        }
        else if(choice == 4) {
            int id;
            cout << "Enter Task ID to search: ";
            cin >> id;
            searchTask(id);
        }
        else if(choice == 5) {
            sortTasks();
        }
        else if(choice == 6) {
            processTasks();
        }
        else if(choice == 7) {
            display();
        }
        else if(choice == 8) {
            cout << "👋 Exiting...\n";
            break;
        }
        else {
            cout << "❌ Invalid choice!\n";
        }
    }
}