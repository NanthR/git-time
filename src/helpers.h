#include<iostream>
#include<vector>

using namespace std;

const vector<string> explode(const string& s, const char& c) {
	string buff;
	vector<string> v;
	
	for(auto n:s)
	{
		if(n != c) {
			buff+=n;
		}
		if(n == c && !buff.empty()) { v.push_back(buff); buff = ""; }
	}
	if(!buff.empty()) {
		v.push_back(buff);
	}
	return v;
}

string rtrim(string str) {
	int count = 0;
	for(auto c = str.rbegin(); c!= str.rend(); ++c) {
		if(*c == ' ') {
			count++;
		}
		else {
			break;
		}
	}
	str.resize(str.size() - count);
	return str;
}

string create_commmand(vector<string>hashes, vector<string>dates) {
	if(hashes.empty() || dates.empty()) {
		return "";
	}
	string command = "git filter-branch -f --env-filter \\ ";
	command += "'case $GIT_COMMIT in";
	for(int i = 0; i < hashes.size(); i++) {
		command += " " + hashes[i] + ")";
		command += " export GIT_AUTHOR_DATE=\"" + dates[i] + "\";";
		command += " export GIT_COMMITTER_DATE=\"" + dates[i] + "\"";
		command += ";;";
	}
	command += "esac'";
	return command;
}

