#include "colors.h"
namespace clr {
	using namespace std;

	string get_textcolor_code(colorcode textcolor) {
		switch (textcolor) {
		case  black: return "30"; 
		case  dark_blue: return "34"; 
		case  dark_green: return "32"; 
		case  light_blue: return "36"; 
		case  dark_red: return "31"; 
		case  magenta: return "35"; 
		case  orange: return "33"; 
		case  light_gray: return "37"; 
		case  gray: return "90"; 
		case  blue: return "94"; 
		case green: return "92"; 
		case cyan: return "96"; 
		case red: return "91"; 
		case pink: return "95"; 
		case yellow: return "93"; 
		case white: return "97"; 
		default: return "37";
		}
	}
	string get_backgroundcolor_code(const int backgroundcolor) {
		switch (backgroundcolor) {
		case  black: return "40";
		case  dark_blue: return "44";
		case  dark_green: return "42";
		case  light_blue: return "46";
		case  dark_red: return "41";
		case  magenta: return "45";
		case  orange: return "43";
		case  light_gray: return "47";
		case  gray: return "100";
		case  blue: return "104";
		case green: return "102";
		case cyan: return "106";
		case red: return "101";
		case pink: return "105";
		case yellow: return "103";
		case white: return "107";
		default: return "40";
		}

	}
	string print_color(colorcode textcolor) { 
		return "\033[" + get_textcolor_code(textcolor) + "m";
	}
	string print_color(colorcode textcolor, colorcode backgroundcolor) { 
		return "\033[" + get_textcolor_code(textcolor) + ";" + get_backgroundcolor_code(backgroundcolor) + "m";
	}

	string reset_color() {
		return "\033[0m"; 
	}

	Color::Color(const char txt[]) {
		this->txt = txt;
		cout << "created " << txt << endl;
	}
	Color::~Color() {
		
		cout << "destroyed " << txt << endl;
	}

	

	std::ostream& operator<<(std::ostream& out, const Color& color) {
		string s = print_color(color.foreground, color.background) + color.txt + reset_color();
		out << s;//[32;40mhello[0m
		return out;
	}
}



