#include<iostream>
#include<git2.h>
#include<unistd.h>
#include<time.h>
#include<vector>
#include<regex>

using namespace std;

int format_check(string date) {
	//Regex string for days
	string days = "(Mon|Tue|Wed|Thu|Fri|Sat|Sun)";
	
	//Regex string for months
	string months = "(Jan|Feb|Mar|Apr|May|Jun|Jul|Aug|Sep|Oct|Nov|Dec)";

	regex format ("^"+days+" "+months+" "+"([0-2]?[0-9]|3[0-1]) ([0-1][0-9]|2[0-4]):([0-5]?[0-9]|60):([0-5]?[0-9]|60) [0-9]+ [-/+][0-9]{4}$");
	if(regex_match(date.begin(), date.end(), format) == 0) {
			return 0;
		}
	return 1;
}

string check() {
	char cwd[50];
	// Finds the present directory that the binary is running in
	getcwd(cwd, sizeof(cwd));
	//Starts ligit2
	git_libgit2_init();
	git_buf root = {NULL};
	//Checks if the provided directory is a git repo
	int a = git_repository_discover(&root, cwd, 1, NULL);
	if(a < 0) {
		const git_error *e = giterr_last();
		cout << e->message << "\n";
		exit(a);
	}
	git_libgit2_shutdown();
	//root => struct; ptr stores the directory  containing the repo
	return root.ptr;
}

vector<string> show_commits(const char* GIT_DIR) {
	git_libgit2_init();
	git_repository * repo = nullptr;
	git_repository_open(&repo, GIT_DIR);
	//Refers to the revision walker
	git_revwalk * walker = nullptr;
	git_revwalk_new(&walker, repo);
	//Pushes the head, i.e the latest commit to the revison walker
	git_revwalk_push_head(walker);
	//OID refers to the unique name for each commit
	git_oid oid;
	int count = 1;
	vector<string> commits;
	while(!git_revwalk_next(&oid, walker)){
		git_commit * commit = nullptr;
		git_commit_lookup(&commit, repo, &oid);
		commits.push_back(git_oid_tostr_s(&oid));
		std::cout << count << " " << git_oid_tostr_s(&oid) << "\n";
		git_commit_free(commit);
		count++;
	}
	git_revwalk_free(walker);
	git_repository_free(repo);
	git_libgit2_shutdown();
	return commits;
}

