#ifndef TEXT
#define TEXT

#include <string>
#include <vector>
#include "Player.h"


class Text
{
	
	public:
	static std::string language_version;
	static std::string one_line_frame;
	static std::vector <std::string> pl_OR_eng;
	static std::vector <std::string> log_frames;
	static std::vector <std::string> log_message;
	static std::vector <std::string> start_menu;
	static std::vector <std::string> A_4;
	static std::vector <std::string> A_8;
	static std::vector <std::string> Warsow_txt;
	static std::vector <std::string> game_log_message;
	static std::vector <std::string> frames;
	static std::vector <std::string> auction_text;


	static void set_language_version(std::string);
		static short cinCheck(short&, short, bool = false);
		static void cinCheck(short&, short, std::vector<short>);
		static void load_language_version();
		static void readText(std::vector<std::string>, short, short);
		static void load_language_file(std::vector <std::string> &, std::string = "", char = '#');
		static void show_first_auction_menu(Player*, short);
		static void showGame(Player*, std::vector<short>);
};
#endif



