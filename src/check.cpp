#ifndef CHECK_H
#include "check.h"
#endif

bool format_check(std::string date) {
  std::regex format("^" + std::string(DAYS) + " " + std::string(MONTHS) + " " +
                    "([0-2]?[0-9]|3[0-1]) "
                    "([0-1][0-9]|2[0-4]):([0-5]?[0-9]|60):([0-5]?[0-9]|60) "
                    "[0-9]+ [-/+][0-9]{4}$");
  if (std::regex_match(date.begin(), date.end(), format) == 0) {
    return false;
  }
  return true;
}

bool input_num(std::string n) {
  // Regex string for input
  std::regex format("^([0-9]+ )*[0-9]+$");
  if (std::regex_match(n.begin(), n.end(), format) == 0) {
    return false;
  }
  return true;
}

std::string check() {
  char cwd[50];
  // Finds the present directory that the binary is running in
  getcwd(cwd, sizeof(cwd));
  // Starts ligit2
  git_libgit2_init();
  git_buf root = {NULL, 0, 0};
  // Checks if the provided directory is a git repo
  int a = git_repository_discover(&root, cwd, 1, NULL);
  if (a < 0) {
    const git_error *e = giterr_last();
    std::cout << e->message << "\n";
    return "";
  }
  git_libgit2_shutdown();
  // root => struct; ptr stores the directory  containing the repo
  return root.ptr;
}

std::vector<std::string> show_commits(const char *GIT_DIR) {
  git_libgit2_init();
  git_repository *repo = nullptr;
  git_repository_open(&repo, GIT_DIR);
  // Refers to the revision walker
  git_revwalk *walker = nullptr;
  git_revwalk_new(&walker, repo);
  // Pushes the head, i.e the latest commit to the revison walker
  git_revwalk_push_head(walker);
  // OID refers to the unique name for each commit
  git_oid oid;
  std::vector<std::string> commits;
  while (!git_revwalk_next(&oid, walker)) {
    git_commit *commit = nullptr;
    git_commit_lookup(&commit, repo, &oid);
    commits.push_back(git_oid_tostr_s(&oid));
    git_commit_free(commit);
  }
  git_revwalk_free(walker);
  git_repository_free(repo);
  git_libgit2_shutdown();
  return commits;
}
