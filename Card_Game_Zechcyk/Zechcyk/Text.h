#ifndef TEXT
#define TEXT

#include <string>
#include <vector>
#include "Player.h"


class Text
{
	
	public:
	static std::vector <std::string> m_languageMenuText;
	static std::vector <std::string> m_start_menu;
	static std::string m_language_version;
	static std::string m_one_line_frame;
	static std::vector <std::string> m_auctionText;
	static std::vector <std::string> m_auctionLogFrame;
	static std::vector <std::string> m_auctionLog;
	static std::vector <std::string> m_gameLogFrame;
	static std::vector <std::string> m_gameLogText;
	static std::vector <std::string> m_gameFrame;
	
	

	static void set_language_version(std::string);
		static short cinCheck(short&, short, bool = false);
		static void cinCheck(short&, short, std::vector<short>);
		
		static void readText(std::vector<std::string>, short, short);
		
		static void show_first_auction_menu(Player*, short);
		static void showGame(Player*, std::vector<short>);
};
#endif



