#include<stdlib.h>
#include<regex>
#include "check.h"
#include "CLI11.hpp"

int main(int argc, char *argv[]) {
	string GIT_STRING = check();
	GIT_STRING.resize(GIT_STRING.size()-6);
	const char * GIT_DIR = GIT_STRING.c_str();
	CLI::App app{"Change the time of your commits"};
	string commit, date;
	app.add_option("-c, --commit", commit, "Specify the required hash");
	app.add_option("-d, --date", date, "Date to change to. Format 'Day Month Date Hour:Min:Sec Year TZ");
	//Regex string for days
	string days = "(Mon|Tue|Wed|Thu|Fri|Sat|Sun)";
	//Regex string for months
	string months = "(Jan|Feb|Mar|Apr|May|Jun|Jul|Aug|Sep|Oct|Nov|Dec)";
	CLI11_PARSE(app, argc, argv);
	vector<string> commits = show_commits(GIT_DIR);
	if(commits.size() < 1) {
		cout << "No commits\n";
		exit(1);
	}
	//Checks if both commit and date are set and otherwise prompts the user for input
	if(commit == "" || date == "") {
		cout << "Choose the required commit\n";
		string n;
		getline(std::cin, n);
		int t = std::stoi(n);
		if(t > commits.size()) {
			cout << "Enter a valid number\n";
			exit(1);
		}
		commit = commits[t-1];
		cout << "Set the new date. Format `Day Month Date Hour:Min:Sec Year TimeZone'\n";
		cout << "Example 'Tue Jan 28 23:53:22 2005 +0530'\n";
		getline(cin, date);
	}
	regex format ("^"+days+" "+months+" "+"([0-2]?[0-9]|3[0-1]) ([0-1][0-9]|2[0-4]):([0-5]?[0-9]|60):([0-5]?[0-9]|60) [0-9]+ [-/+][0-9]{4}$");
		if(std::regex_match(date.begin(), date.end(), format) == 0) {
			std::cout << "Invalid format\n";
			exit(1);
		}
		int flag = 0;
		for(int i = 0; i < commits.size(); i++)	{
			if(commit == commits[i])
				flag = 1;
		}
		if(flag == 0) {
			std::cout << "No matching hash\n";
			exit(1);
		}
		string command =  "git filter-branch -f --env-filter 'if [ $GIT_COMMIT = "+commit+" ];then export GIT_AUTHOR_DATE=\""+date+"\" && export GIT_COMMITTER_DATE=\""+date+"\";fi'";
		const char *c = command.c_str();
		system(c);
}

