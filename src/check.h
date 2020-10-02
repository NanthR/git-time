#include<iostream>
#include<git2.h>
#include<unistd.h>
#include<time.h>
#include<vector>

using namespace std;

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
		const git_error *e = git_error_last();
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
