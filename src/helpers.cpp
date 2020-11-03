#include "helpers.h"

const std::vector<std::string> explode(const std::string &s, const char &c) {
  std::string buff;
  std::vector<std::string> v;

  for (auto n : s) {
    if (n != c) {
      buff += n;
    }
    if (n == c && !buff.empty()) {
      v.push_back(buff);
      buff = "";
    }
  }
  if (!buff.empty()) {
    v.push_back(buff);
  }
  return v;
}

std::string rtrim(std::string str) {
  int count = 0;
  for (auto c = str.rbegin(); c != str.rend(); ++c) {
    if (*c == ' ') {
      count++;
    } else {
      break;
    }
  }
  str.resize(str.size() - count);
  return str;
}

std::string create_commmand(std::vector<std::string> hashes,
                            std::vector<std::string> dates) {
  if (hashes.empty() || dates.empty()) {
    return "";
  }
  std::string command = "git filter-branch -f --env-filter \\ ";
  command += "'case $GIT_COMMIT in";
  for (int i = 0; i < (int)hashes.size(); i++) {
    command += " " + hashes[i] + ")";
    command += " export GIT_AUTHOR_DATE=\"" + dates[i] + "\";";
    command += " export GIT_COMMITTER_DATE=\"" + dates[i] + "\"";
    command += ";;";
  }
  command += "esac'";
  return command;
}
