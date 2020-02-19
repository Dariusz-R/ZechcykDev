#ifndef TEXT
#define TEXT

#include <string>
#include <vector>

using namespace std;

class Text
{
	
	public:
	static string language_version;
	static vector <string> pl_OR_eng;
	static vector <string> log_frame;
	static vector <string> log_message;
	static vector <string> start_menu;
	static vector <string> A_4; 
	static vector <string> A_8;

	static void set_language_version(string);
	static void placing_text_in_center_of_the_frame(string&, short&, string = "");
		static short cin_check(short&, short, bool = false);
		static void load_language_version();
		static void read_text(vector<string>, short, short);
		static void load_language_file( vector <string> &, string = "", char = '#');
};
#endif



