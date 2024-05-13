#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
using namespace std;
class User;
class Task;
class TaskManagementSystem;
class Task
{
    string id;
    string title;
    string description;

public:
    Task(string id, string title, string description)
    {
        this->id = id;
        this->title = title;
        this->description = description;
    }
    string getID()
    {
        return id;
    }
    string getTitle()
    {
        return title;
    }
    string getDescription()
    {
        return description;
    }
};
class User
{
    string userName;
    string password;
    vector<Task> tasks;

public:
    User(string userName, string password)
    {
        this->userName = userName;
        this->password = password;
    }
    string getUserName()
    {
        return userName;
    }
    string getPassword()
    {
        return password;
    }
    void viewTasks()
    {
        cout << "\n--------------------------------------------------------------------";
        cout << "\n\t" << setw(5) << "ID" << setw(20) << "Task Name" << setw(30) << "Task Description";
        cout << "\n--------------------------------------------------------------------";
        for (int i = 0; i < tasks.size(); i++)
        {
            cout << "\n\t" << setw(5) << tasks[i].getID() << setw(20) << tasks[i].getTitle() << setw(30) << tasks[i].getDescription();
        }
        cout << "\n--------------------------------------------------------------------";
        cout << endl << endl;
    }
    void addTask(Task &task)
    {
        tasks.push_back(task);
    }
    void deleteTask(string id)
    {
        for (int i = 0; i < tasks.size(); i++)
        {
           if(tasks[i].getID() == id)
           {
            tasks.erase(tasks.begin()+i);
            break;
           }
        }
    }
};

class TaskManagementSystem
{
    vector<User> users;

    int authenticateUser(string username, string password)
    {
        int i;
        for (i = 0; i < users.size(); i++)
        {
            if (users[i].getUserName() == username)
            {
                if (users[i].getPassword() == password)
                {
                    cout << "\t\tLogin Successful\n";
                    return i;
                }
            }
        }
        return -1;
    }
    void addTask(int i)
    {
        string inputID;
        string inputTaskName;
        string inputTaskDescription;
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
        cout << "\n\t\tEnter the task ID to be added:";
        getline(cin, inputID);
        cout << "\n\t\tEnter the task name to be added:";
        getline(cin, inputTaskName);
        cout << "\n\t\tEnter the task description to be added:";
        getline(cin, inputTaskDescription);
        Task temp(inputID, inputTaskName, inputTaskDescription);
        users[i].addTask(temp);
    }
    void manageTasks(int i)
    {
        while (true)
        {
            cout << "\n\t\t1. Add Task";
            cout << "\n\t\t2. Delete Task";
            cout << "\n\t\t3. View Tasks";
            cout << "\n\t\t4. Logout";
            int choice;
            cout << "\n\n\t\tEnter your choice:";
            cin >> choice;
            if (choice == 1)
            {
                addTask(i);
            }
            else if (choice == 2)
            {
                string deleteID;
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
                cout << "\n\t\tEnter the task ID to be deleted:";
                getline(cin, deleteID);
                users[i].deleteTask(deleteID);
            }
            else if (choice == 3)
            {
                users[i].viewTasks();
            }
            else if (choice == 4)
            {
                run();
            }
        }
    }

public:
    void run()
    {
        while (true)
        {
            cout << "\t\t--------------------Welcome to Task Management System--------------------------\n";
            cout << "\t\t\t1. Register\n";
            cout << "\t\t\t2. Login\n";
            cout << "\t\t\t3. Exit\n";
            int choice;
            cout << "Enter your choice:";
            cin >> choice;
            if (choice == 1)
            {
                string username, password;
                cout << "\t\tEnter Username:";
                cin >> username;
                cout << "\t\tEnter Password:";
                cin >> password;
                users.push_back(User(username, password));
                cout << "\n\t\tUser Registered Successfully\n";
            }
            else if (choice == 2)
            {
                string username, password;
                cout << "\t\tEnter Username:";
                cin >> username;
                cout << "\t\tEnter Password:";
                cin >> password;
                int userID = authenticateUser(username, password);
                if (userID >= 0)
                {
                    manageTasks(userID);
                }
                else
                {
                    cout << "\t\tEntered Wrong username or password\n";
                }
            }
            else if (choice == 3)
            {
                exit(0);
            }
        }
    }
};
int main()
{
    TaskManagementSystem obj;
    obj.run();
}