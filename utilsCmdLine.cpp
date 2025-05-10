#include <algorithm>
#include <iostream>

#include "helpers.h"

enum class State { idle, command };
enum class Command { unknown, chdf, quit, filepath };

void printVector(std::vector<std::string>& vec) {
  std::for_each(vec.begin(), vec.end(),
                [](std::string& s) { std::cout << s << " "; });
  std::cout << std::endl;
}

void print(std::string s) {
  std::cout << s << std::endl;
}

Command parseCommand(const std::unordered_map<std::string, Command>& cmdsMap,
                     const std::vector<std::string>& args) {
  for (auto argc : args) {
    auto it = cmdsMap.find(argc);
    if (it != cmdsMap.end()) {
      return it->second;
    }
  }

  return Command::unknown;
}

void executeCmdHelp(const Command& cmd) {
  if (cmd == Command::chdf) {
    print("Change delimiter of file\n");
    print("f filename delimiter_in delimiter_out\n");
  } else if (cmd == Command::quit) {
    print("Quitting...\n");
  }
}

static const std::unordered_map<std::string, Command> idleCmdsMap = {
    {"chdf", Command::chdf}, {"quit", Command::quit}, {"exit", Command::quit}};

static const std::unordered_map<std::string, Command> chdfCmdsMap = {
    {"f", Command::filepath}};

static void executeChdf(const std::vector<std::string>& args) {
  auto cmd = parseCommand(chdfCmdsMap, args);
  if (cmd == Command::unknown) {
    print("Unknown command!\n");
    return;
  }
  auto fp = args.at(1);
  auto fp_out = fp + ".out";
  changeDelimiterOfFile(fp, fp_out, args.at(2), args.at(3));
}

// utilities in a command line interface for parsing/manipulating raw AoC input
// data
int main(int argc, char** /* argv */) {
  std::string line;
  State state = State::idle;
  Command current_cmd = Command::unknown;
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
        current_cmd = parseCommand(idleCmdsMap, args);
        if (current_cmd == Command::unknown) {
          print("Please enter a valid command");
          break;
        } else if (current_cmd == Command::quit)
          running = false;
        executeCmdHelp(current_cmd);
        state = State::command;
      case State::command:
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
