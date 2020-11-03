#include<iostream>
#include<git2.h>
#include<unistd.h>
#include<vector>
#include<regex>

#define DAYS "(Mon|Tue|Wed|Thu|Fri|Sat|Sun)"
#define MONTHS "(Jan|Feb|Mar|Apr|May|Jun|Jul|Aug|Sep|Oct|Nov|Dec)"

bool format_check(std::string data);
bool input_num(std::string n);
std::string check();
std::vector<std::string>show_commits(const char* GIT_DIR);
