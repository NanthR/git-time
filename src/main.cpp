#include "CLI11.hpp"
#include "check.h"
#include "commit_create.h"
#include "helpers.h"

int main(int argc, char *argv[]) {
  std::string GIT_STRING = check();
  if (GIT_STRING.empty()) {
    return 1;
  }
  const int size_reduce = 6;
  GIT_STRING.resize(GIT_STRING.size() - size_reduce);
  const char *GIT_DIR = GIT_STRING.c_str();
  std::string commit;
  std::string date;
  CLI::App app{"Change the time of your commits"};
  app.add_option("-c, --commit", commit, "Specify the required hash");
  app.add_option(
      "-d, --date", date,
      "Date to change to. Format 'Day Month Date Hour:Min:Sec Year TZ");
  CLI11_PARSE(app, argc, argv);
  std::vector<std::string> commits = show_commits(GIT_DIR);

  // Checks if no commits have been made
  if (commits.empty()) {
    std::cout << "No commits\n";
    return 1;
  }

  int flag = 0;
  std::vector<std::string> hashes;
  // Checks if both commit and date are set and otherwise prompts the user for
  // input
  if (commit.empty() || date.empty()) {
    hashes = get_commits(commits);
    flag = 1;
  } else {
    hashes.push_back(commit);
  }
  if (hashes.empty()) {
    std::cout << "No hashes were provided or selected\n";
    return 1;
  }
  if (flag == 0) {
    for (auto i : commits) {
      // Checks if commit hash provided belongs is valid
      if (commit == i) {
        flag = 1;
      }
    }
  }
  if (flag == 0) {
    std::cout << "No matching hash\n";
    return 1;
  }
  std::cout << "Set the new date. Format `Day Month Date Hour:Min:Sec Year "
               "TimeZone'\n";
  std::cout << "Example 'Tue Jan 28 23:53:22 2005 +0530'\n";

  std::vector<std::string> dates;
  dates = get_dates(hashes.size());
  std::string command = create_commmand(hashes, dates);
  if (command.empty()) {
    return 1;
  }
  const char *c = command.c_str();
  system(c);
  return 0;
}
