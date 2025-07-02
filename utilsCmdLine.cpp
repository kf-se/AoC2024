#include <algorithm>
#include <iostream>
#include <unordered_map>

#include "helpers.h"

enum class State { idle, chdf, quit };

void printVector(const std::vector<std::string> &vec) {
  std::for_each(vec.begin(), vec.end(),
                [](const std::string &s) { std::cout << "'" << s << "',"; });
  std::cout << std::endl;
}

void print(const std::string s) { std::cout << s << std::endl; }

State parseCommand(const std::unordered_map<std::string, State> &cmdsMap,
                   const std::vector<std::string> &args, State state) {
  for (auto argc : args) {
    auto it = cmdsMap.find(argc);
    if (it != cmdsMap.end()) {
      return it->second;
    }
  }

  return state;
}

void executeCmdHelp(const State &state) {
  if (state == State::chdf) {
    print("Change delimiter of file\n");
    print("filename delimiter_in delimiter_out\n");
  }
}

static const std::unordered_map<std::string, State> cmdsMap = {
    {"chdf", State::chdf}, {"quit", State::quit}, {"exit", State::quit}};

static void executeChdf(const std::vector<std::string> &args) {
  if (args.size() < 3) {
    print("Not enough arguments.");
    return;
  }

  auto fp = args.at(0);
  auto fp_out = fp + ".out";
  changeDelimiterOfFile(fp, fp_out, args.at(1), args.at(2));
}

std::vector<std::string> tokenize(const std::string &line) {
  std::istringstream iss(line);
  std::vector<std::string> tokens;
  std::string token;

  while (iss >> std::quoted(token)) {
    tokens.push_back(token);
  }

  return tokens;
}

int main(int argc, char ** /* argv */) {
  print("Utilities for parsing/manipulating raw AoC input data\n");
  print("Type 'exit/quit' to quit.\n");

  std::string line;
  State state = State::idle;

  while (state != State::quit) {
    std::cout << "> ";
    std::getline(std::cin, line);

    auto args = tokenize(line);

    if (args.empty())
      continue;
    printVector(args);
    auto next_state = parseCommand(cmdsMap, args, state);

    switch (state) {
    case State::idle:
      executeCmdHelp(next_state);
      break;
    case State::chdf:
      executeChdf(args);
      break;
    default:
      break;
    }
    if (next_state != state) {
      state = next_state;
    }
  }

  print("Exiting the program");
  return 0;
}
