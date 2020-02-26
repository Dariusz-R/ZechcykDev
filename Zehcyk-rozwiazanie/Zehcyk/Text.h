#ifndef TEXT
#define TEXT

#include <string>
#include <vector>


class Text
{
	
	public:
	static std::string language_version;
	static std::vector <std::string> pl_OR_eng;
	static std::vector <std::string> log_frames;
	static std::vector <std::string> log_message;
	static std::vector <std::string> start_menu;
	static std::vector <std::string> A_4;
	static std::vector <std::string> A_8;
	static std::vector <std::string> Warsow_txt;
	static std::vector <std::string> game_log_message;


	static void set_language_version(std::string);
	static void placing_text_in_center_of_the_frame(std::string&, short&, std::string = "");
		static short cin_check(short&, short, bool = false);
		static void cin_check(short&, short, std::vector<short>);
		static void load_language_version();
		static void read_text(std::vector<std::string>, short, short);
		static void load_language_file(std::vector <std::string> &, std::string = "", char = '#');
};
#endif



