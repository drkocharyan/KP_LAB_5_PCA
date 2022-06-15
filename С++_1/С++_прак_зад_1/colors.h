#pragma once
#include <iostream>
#include <string>


namespace clr {
	using namespace std;

	enum colorcode {
		black = 0,
		dark_blue,
		dark_green,
		light_blue,
		dark_red,
		magenta,
		orange,
		light_gray,
		gray,
		blue,
		green,
		cyan,
		red,
		pink,
		yellow,
		white
	};

	class Color {
	protected:
		colorcode background = black;
		colorcode foreground = white;
		string txt;

	public:
		Color(const char txt[]); 
		~Color();

		friend std::ostream& operator<<(std::ostream& out, const Color& color);

	};

	class Green : public Color {

	public:
		Green(const char txt[]) : Color(txt) {
			foreground = dark_green;
		}
	};

	class Red : public Color {

	public:
		Red(const char txt[]) : Color(txt) {
			foreground = dark_red;
		}
	};
}

