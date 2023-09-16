#include <bits/stdc++.h>
#include <stdexcept>
#include <stdio.h>
#include <string>


using namespace std;

string in, pi, sn, sh, mu;

class task_manager
{
private:
    string image_name;
    string pid;
    string session_name;
    string session_hash;
    string mem_usage;
    friend bool compare_mem(task_manager &a, task_manager &b);
    friend bool compare_name(task_manager &a, task_manager &b);
    friend bool compare_pid(task_manager &a, task_manager &b);
public:
    task_manager(string in, string pi, string sn, string sh,string mu)
    {
        image_name = in;
        pid = pi;
        session_name = sn;
        session_hash = sh;
        mem_usage = mu;
    }
    string get_image_name()
    {
        return image_name;
    }
    string get_pid()
    {
        return pid;
    }
    string get_session_name()
    {
        return session_name;
    }
    string get_session_hash()
    {
        return session_hash;
    }
    string get_mem_usage()
    {
        return mem_usage;
    }
};

void image_name_set(string line)
{
    for(int i = 0; i < 29; i++)
    {
        in = in + line[i];
    }

}

void pid_set(string line)
{
    for(int i = 29; i < 34; i++)
    {
        pi = pi + line[i];
    }
}

void session_name_set(string line)
{
    for(int i = 34; i < 43; i++)
    {
        sn = sn + line[i];
    }
}

void session_hash_set(string line)
{
    for(int i = 43; i < 63; i++)
    {
        sh = sh + line[i];
    }
}

void memory_usage_set(string line)
{
    for (int i = 63; i < line.length(); i++)
    {
        mu = mu + line[i];
    }
}

bool compare_mem(task_manager &a, task_manager &b)
{
    if(a.mem_usage.size() == b.mem_usage.size())
        return a.mem_usage < b.mem_usage;
    else
        return a.mem_usage.size() < b.mem_usage.size();
}

bool compare_name(task_manager &a, task_manager &b)
{
    return a.image_name < b.image_name;
}
bool compare_pid(task_manager &a, task_manager &b)
{
    if(a.pid.size() ==  b.pid.size())
        return a.pid < b.pid;
    else
        return a.pid.size() < b.pid.size();
}

std::string exec(const char* cmd)
{
    char buffer[128];
    std::string result = "";
    FILE* pipe = popen(cmd, "r");
    if (!pipe) throw std::runtime_error("popen() failed!");
    try
    {
        while (fgets(buffer, sizeof buffer, pipe) != NULL)
        {
            result += buffer;
        }
    }
    catch (...)
    {
        pclose(pipe);
        throw;
    }
    pclose(pipe);
    return result;
}
int main()
{
    int choice;
    string task = exec("tasklist");
    string header, data;
    int counter = 0;
    for(int i = 0; i < task.length(); i++)
    {
        if(task[i] == '\n')
            counter++;
        if (counter < 3)
            header = header + task[i];
        else
            data = data + task[i];

    }

    string line;
    vector<task_manager>task_manager_data;
    for(int i = 1; i < data.length(); i++)
    {
        if(data[i] != '\n')
            line = line + data[i];
        else
        {
            image_name_set(line);
            pid_set(line);
            session_name_set(line);
            session_hash_set(line);
            memory_usage_set(line);
            task_manager_data.push_back(task_manager(in, pi, sn, sh, mu));
            in.clear();
            pi.clear();
            sn.clear();
            sh.clear();
            mu.clear();
            line.clear();

        }
    }
    cout << "How do you want the task manager to be sorted before displaying?" << endl;
    cout << "Enter 1 to sort by name in alphabetical order" << endl;
    cout << "Enter 2 to sort by PID" << endl;
    cout << "Enter 3 to sort by  memory usage" << endl;
    cout << "Enter your choice: ";
    cin >> choice;
    if(choice == 1)
    {
        sort(task_manager_data.begin(), task_manager_data.end(),compare_name);
        cout << header << endl;
        for(int i = 0; i < task_manager_data.size(); i++)
        {
            cout << task_manager_data[i].get_image_name();
            cout << task_manager_data[i].get_pid();
            cout << task_manager_data[i].get_session_name();
            cout << task_manager_data[i].get_session_hash();
            cout <<task_manager_data[i].get_mem_usage();
            cout << endl;
        }
    }
    else if(choice == 2)
    {
        sort(task_manager_data.begin(), task_manager_data.end(),compare_pid);
        cout << header << endl;
        for(int i = 0; i < task_manager_data.size(); i++)
        {
            cout << task_manager_data[i].get_image_name();
            cout << task_manager_data[i].get_pid();
            cout << task_manager_data[i].get_session_name();
            cout << task_manager_data[i].get_session_hash();
            cout <<task_manager_data[i].get_mem_usage();
            cout << endl;
        }
    }
    else if(choice == 3)
    {
        sort(task_manager_data.begin(), task_manager_data.end(),compare_mem);
        cout << header << endl;
        for(int i = 0; i < task_manager_data.size(); i++)
        {
            cout << task_manager_data[i].get_image_name();
            cout << task_manager_data[i].get_pid();
            cout << task_manager_data[i].get_session_name();
            cout << task_manager_data[i].get_session_hash();
            cout <<task_manager_data[i].get_mem_usage();
            cout << endl;
        }
    }
    else
    {
        cout << "Invalid choice!";
    }
    return 0;
}
