#include <algorithm>
#include <iostream>

#include "helpers.h"

enum class State { idle, cmd };
enum class Command { chdf };

void printVector(std::vector<std::string>& vec) {
  std::for_each(vec.begin(), vec.end(),
                [](std::string& s) { std::cout << s << " "; });
  std::cout << std::endl;
}

void print(std::string s) {
  std::cout << s << std::endl;
}

bool argIsACommand(std::vector<std::string>& args) {
  bool isCommand = std::any_of(args.begin(), args.end(), [](std::string& s) {
    if (s == "chdf")
      return true;
    else if (s == "quit" || s == "exit")
      return true;
    else
      return false;
  });
  return isCommand;
}

// utilities in a command line interface for parsing/manipulating raw AoC input
// data
int main(int argc, char** /* argv */) {
  std::string line;
  State state = State::idle;
  bool running = true;

  print("Manage aoc input. Type 'exit/quit' to quit.\n");

  while (running) {
    std::cout << "> ";
    std::getline(std::cin, line);

    auto args = tokenizer(line, ',');

    if (args.empty()) continue;
    printVector(args);

    switch (state) {
      case State::idle:
        if (!argIsACommand(args)) {
          print("Please enter a valid command");
          continue;
        }
      case State::cmd:
        if (line == "exit" || line == "quit") running = false;
        break;
      default:
        break;
    }

    if (std::find(args.begin(), args.end(), "chd") != args.end()) {
      print("Enter filename: ");
    }
  }

  print("Exiting the program");
  return 0;
}
