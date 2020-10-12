#include "CLI11.hpp"
#include "check.h"
#include "helpers.h"

int main(int argc, char *argv[]) {
  string GIT_STRING = check();
  if (GIT_STRING.empty()) {
    return 1;
  }
  const int size_reduce = 6;
  GIT_STRING.resize(GIT_STRING.size() - size_reduce);
  const char *GIT_DIR = GIT_STRING.c_str();
  string commit;
  string date;
  CLI::App app{"Change the time of your commits"};
  app.add_option("-c, --commit", commit, "Specify the required hash");
  app.add_option(
      "-d, --date", date,
      "Date to change to. Format 'Day Month Date Hour:Min:Sec Year TZ");
  CLI11_PARSE(app, argc, argv);
  vector<string> commits = show_commits(GIT_DIR);

  // Checks if no commits have been made
  if (commits.empty()) {
    cout << "No commits\n";
    return 1;
  }

  int flag = 0;
  vector<string> hashes;
  // Checks if both commit and date are set and otherwise prompts the user for
  // input
  if (commit.empty() || date.empty()) {
    cout << "Choose the required commit\n";
    int count = 1;
    for (auto i : commits) {
      cout << count << " " << i << "\n";
      count++;
    }
    string n;
    getline(cin, n);
    n = rtrim(n);
    if (!input_num(n)) {
      cout << "Invalid options\n";
      return 1;
    }
    vector<string> options{explode(n, ' ')};
    for (auto i : options) {
      int j = stoi(i);
      if (j > commits.size()) {
        cout << "Invalid arguements\n";
        return 1;
      }
      hashes.push_back(commits[j - 1]);
    }
    flag = 1;
  } else {
    hashes.push_back(commit);
  }
  if (hashes.empty()) {
    cout << "No hashes were provided or selected\n";
    return 1;
  }
  if (flag == 0) {
    for (auto i : commits) {
      if (commit == i) {
        flag = 1;
      }
    }
  }
  if (flag == 0) {
    cout << "No matching hash\n";
    return 1;
  }
  cout << "Set the new date. Format `Day Month Date Hour:Min:Sec Year "
          "TimeZone'\n";
  cout << "Example 'Tue Jan 28 23:53:22 2005 +0530'\n";
  vector<string> dates;
  for (auto i : hashes) {
    cout << "Date for " << i << "\n";
    getline(cin, date);
    date = rtrim(date);
    while (!format_check(date)) {
      cout << "Invalid date format\nTry again\n";
    }
    dates.push_back(date);
  }
  string command = create_commmand(hashes, dates);
  if (command.empty()) {
    return 1;
  }
  const char *c = command.c_str();
  system(c);
  return 0;
}
