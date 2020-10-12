#include "catch.hpp"

using namespace std;

string rtrim(string str) {
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

TEST_CASE("Trim check", "[trim]") {
  REQUIRE(rtrim("1 2 ") == "1 2");
  REQUIRE(rtrim("    ") == "");
  REQUIRE(rtrim("1         ") == "1");
  REQUIRE(rtrim("asdf fghjk    j") == "asdf fghjk    j");
}
