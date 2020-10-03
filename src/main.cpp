#include<stdlib.h>
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
	CLI11_PARSE(app, argc, argv);
	vector<string> commits = show_commits(GIT_DIR);
	
	// Checks if no commits have been made
	if(commits.size() < 1) {
		cout << "No commits\n";
		exit(1);
	}

	//Checks if both commit and date are set and otherwise prompts the user for input
	if(commit == "" || date == "") {
		cout << "Choose the required commit\n";
		string n;
		getline(cin, n);
		int t = stoi(n);
		if(t > commits.size()) {
			cout << "Enter a valid number\n";
			exit(1);
		}
		commit = commits[t-1];
		cout << "Set the new date. Format `Day Month Date Hour:Min:Sec Year TimeZone'\n";
		cout << "Example 'Tue Jan 28 23:53:22 2005 +0530'\n";
		getline(cin, date);
		if(!format_check(date))
			exit(0);
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

