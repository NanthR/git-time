#ifndef COMMIT_CREATE_H
#include "commit_create.h"
#endif
#include <cstring>
#include <string>
#ifndef HELPERS_H
#include "helpers.h"
#endif
#ifndef CHECK_H
#include "check.h"
#endif

std::vector<std::string> get_commits(std::vector<std::string> commits) {
  std::cout << "Choose the required commit\n";
  int count = 1;
  for (auto i : commits) {
    std::cout << count << " " << i << "\n";
    count++;
  }
  std::string n;
  getline(std::cin, n);
  n = rtrim(n);
  if (!input_num(n)) {
    std::cout << "Invalid options\n";
    return std::vector<std::string>();
  }
  std::vector<std::string> options{explode(n, ' ')};
  std::vector<std::string> hashes;
  for (auto i : options) {
    int j = stoi(i);
    if (j > (int)commits.size()) {
      return std::vector<std::string>();
    }
    hashes.push_back(commits[j - 1]);
  }
  return hashes;
}

std::vector<std::string> get_dates(int size) {
  std::vector<std::string> dates;
  for (int i = 0; i < size; i++) {
    std::string date;
    std::cout << "Date for " << i + 1 << "\n";
    getline(std::cin, date);
    date = rtrim(date);
    while (!format_check(date)) {
      std::cout << "Invalid date format\nTry again\n";
      getline(std::cin, date);
    }
    dates.push_back(date);
  }
  return dates;
}
