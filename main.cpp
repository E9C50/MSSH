#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <sstream>
#include <array>

using namespace std;

vector<vector<string>> readServerListFile() {
    string file_name = "/Users/e9c50/.server.csv";

    vector<vector<string>> content;
    vector<string> row;
    string line, word;

    fstream file(file_name, ios::in);
    if (file.is_open()) {
        while (getline(file, line)) {
            row.clear();

            stringstream str(line);

            while (getline(str, word, ','))
                row.push_back(word);
            content.push_back(row);
        }
    } else
        cout << "Could not open the file\n";
    return content;
}

template<typename T>
void printElement(T t, const int &width) {
    cout << left << setw(width) << setfill(' ') << t;
}

void ls_server() {
    vector<vector<string>> serverList = readServerListFile();
    const int nameWidth = 25;

    for (auto &i: serverList) {
        for (size_t j = 0; j < i.size() - 1; j++) {
            printElement("| " + i[j], nameWidth);
        }
        cout << endl;
    }
}

void print_help() {
    const int nameWidth = 30;

    cout << "Example usage:" << endl;
    printElement("    mssh ls", nameWidth);
    printElement("list all servers", nameWidth);
    cout << endl;

    printElement("    mssh conn [ServerName]", nameWidth);
    printElement("connect to server [ServerName]", nameWidth);
    cout << endl << endl;

    printElement("    mssh connip [ServerIpAddress]", nameWidth);
    printElement("connect to server [ServerIpAddress]", nameWidth);
    cout << endl << endl;

    cout << "Further help::" << endl;
    printElement("    mssh help", nameWidth);
    printElement("command helps", nameWidth);
    cout << endl << endl;
}

void conn_server(auto server) {
    string ssh_command = "sshpass -p " + server[4] + " ssh " + server[2] + "@" + server[1];
    system(ssh_command.c_str());

    cout << endl << endl << "server disconnect!" << endl;
}

void conn_server_name(const char *server_name) {
    vector<vector<string>> serverList = readServerListFile();
    for (auto &server: serverList) {
        if (strcmp(server_name, server[0].c_str()) == 0) {
            conn_server(server);
            return;
        }
    }
    cout << ("no server found!") << endl << endl;
}

void conn_server_ip(char *server_ip) {
    vector<vector<string>> serverList = readServerListFile();
    for (auto &server: serverList) {
        if (strcmp(server_ip, server[1].c_str()) == 0) {
            conn_server(server);
            return;
        }
    }
    cout << ("no server found!") << endl << endl;
}


int main(int argc, char *argv[]) {
    if ((argc == 1) || (strcmp(argv[1], "ls") == 0)) ls_server();
    else if (strcmp(argv[1], "conn") == 0) conn_server_name(argv[2]);
    else if (strcmp(argv[1], "connip") == 0) conn_server_ip(argv[2]);
    else print_help();
}