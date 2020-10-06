#include<regex>
#include "catch.hpp"

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


TEST_CASE("Checking if datetime matches the required format", "[datetime]") {
	REQUIRE(format_check("Tue Jan 28 23:53:22 2005 +0530") == true);
	REQUIRE(format_check("Hello") == false);
	REQUIRE(format_check("Tue Jan 45 23:53:22 2007 -0800") == false);
	REQUIRE(format_check("") == false);
	REQUIRE(format_check("Thu Nov 21 23:59:59 2122 +0700") == true);
}
