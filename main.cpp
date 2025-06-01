#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <string>
#include <vector>
#include <sstream>
#include <cstring>

void printPrompt() {
    char cwd[1024];
    getcwd(cwd, sizeof(cwd));
    std::cout << cwd << " > ";
}

std::vector<std::string> splitInput(const std::string& input) {
    std::stringstream ss(input);
    std::string token;
    std::vector<std::string> tokens;
    while (ss >> token) {
        tokens.push_back(token);
    }
    return tokens;
}

void executeCommand(std::vector<std::string>& args) {
    if (args.empty()) return;

    if (args[0] == "exit") {
        std::exit(0);
    }

    if (args[0] == "cd") {
        if (args.size() < 2) {
            std::cerr << "cd: missing argument\n";
        } else {
            if (chdir(args[1].c_str()) != 0) {
                perror("cd");
            }
        }
        return;
    }

    std::vector<char*> c_args;
    for (auto& arg : args) {
        c_args.push_back(&arg[0]);
    }
    c_args.push_back(nullptr);

    pid_t pid = fork();
    if (pid == 0) {
        if (execvp(c_args[0], c_args.data()) == -1) {
            perror("execvp");
        }
        exit(EXIT_FAILURE);
    } else if (pid < 0) {
        perror("fork");
    } else {
        int status;
        waitpid(pid, &status, 0);
    }
}

int main() {
    std::string input;

    while (true) {
        printPrompt();
        std::getline(std::cin, input);

        if (std::cin.eof()) {
            std::cout << "\n";
            break;
        }

        std::vector<std::string> args = splitInput(input);
        executeCommand(args);
    }

    return 0;
}
