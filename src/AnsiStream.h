/* -*- C++ -*- */
/*
Ansi structures to use with Streaming (https://github.com/scottdky/Streaming)

author: ruihfazevedo@gmail.com (Aug2016)

ansi codes based on: https://github.com/rklancer/ansiterm
Ansiterm.cpp -- an Arduino library that simplifies using the ANSI terminal
control escape sequences. This allows your code to  position text exactly in the
terminal, to add colour and other effects. To use Ansiterm, an ANSI terminal must
be connected to the Arduino's serial port. The terminal built into the Arduino
IDE does not respond to the ANSI codes, but most MacOs and Linux terminals do.
In Windows, I read that Hyperterm responds to ANSI codes. Realterm responds to most
codes, but will not change the color of the foreground.

Copyright (c) 2009 Bruce Robertson, VE9QRP. All rights reserved.

This library is free software; you can redistribute it and/or modify it under
the terms of the GNU Lesser General Public License as published by the Free
Software Foundation; either version 2.1 of the License, or (at your option)
any later version.

This library is distributed in the hope that it will be useful, but WITHOUT
ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more
details.

You should have received a copy of the GNU Lesser General Public License along
with this library; if not, write to the Free Software Foundation, Inc., 51
Franklin St, Fifth Floor, Boston, MA 02110-1301 USA

*/

#ifndef AnsiStream_h
	#define AnsiStream_h

	#include <Arduino.h>
	// #include <streamFlow.h>
	#include <Streaming.h>

	#define ESCAPE 0x1B
	#define BRACE '['
	#define BLACK 0
	#define RED 1
	#define	GREEN 2
	#define YELLOW 3
	#define BLUE 4
	#define MAGENTA 5
	#define CYAN 6
	#define WHITE 7
	#define BOLD_ON 1
	#define BOLD_OFF 22
	#define UNDERLINE_ON 4
	#define UNDERLINE_OFF 24
	#define ITALICS_ON 3
	#define ITALICS_OFF 23
	#define STRIKETHROUGH_ON 9
	#define STRIKETHROUGH_OFF 29
	#define INVERSE_ON 7
	#define INVERSE_OFF 27
	#define RESET 1
	#define DEFAULT_FOREGROUND 39
	#define DEFAULT_BACKGROUND 49

	//ANSI --------------------------------------------
	namespace ANSI {

	///////////////////////////////////////////////////////////
	// ANSI Streaming

	//cant use this generic form as original Streaming lib uses it in other way
	/*template<typename T>
	inline Print& operator<<(Print &o, const T cmd) { return cmd(o); }*/

	struct preamble {
		Print& operator()(Print& out) {
			out.write(ESCAPE);
			out.write(BRACE);
			return out;
		}
	};
	inline Print& operator<<(Print &o, preamble cmd) { return cmd(o); }

	struct preambleAndNumberAndValue {
		int x;char v;
		preambleAndNumberAndValue(int x, char v):x(x),v(v) {}
		inline Print& operator()(Print& out) {
			out<<preamble();
			out.print(x,DEC);
			out.write(v);
			return out;
		}
	};
	inline Print& operator<<(Print &o, preambleAndNumberAndValue cmd) { return cmd(o); }

	struct setAttribute {
		int a;
		setAttribute(int a):a(a) {}
		inline Print& operator()(Print& out) const {return out<<preambleAndNumberAndValue(a, 'm');}
	};
	inline Print& operator<<(Print &o, const setAttribute cmd) { return cmd(o); }

	struct home {inline Print& operator()(Print& out) const {return out<<preamble()<<'H';}};
	inline Print& operator<<(Print &o, const home cmd) { return cmd(o); }

	struct xy {
		int x,y;
		inline xy(int x, int y):x(x),y(y) {}
		inline Print& operator()(Print& out) const {
			out<<preamble();
			out.print(y,DEC);
			out.write(';');
			out.print(x, DEC);
			return out<<'H';
		}
	};
	inline Print& operator<<(Print &o, const xy cmd) { return cmd(o); }

	struct up {
		int x;
		inline up(int x=1):x(x){}
		inline Print& operator()(Print& out) const {return out<<preambleAndNumberAndValue(x,'A');}
	};
	inline Print& operator<<(Print &o, const up cmd) { return cmd(o); }

	struct down {
		int x;
		inline down(int x=1):x(x) {}
		inline Print& operator()(Print& out) const {return out<<preambleAndNumberAndValue(x,'B');}
	};
	inline Print& operator<<(Print &o, const down cmd) { return cmd(o); }

	struct forward {
		int x;
		inline forward(int x=1):x(x) {}
		inline Print& operator()(Print& out) const {return out<<preambleAndNumberAndValue(x,'C');}
	};
	inline Print& operator<<(Print &o, const forward cmd) { return cmd(o); }

	struct backward {
		int x;
		inline backward(int x=1):x(x) {}
		inline Print& operator()(Print& out) const {return out<<preambleAndNumberAndValue(x,'D');}
	};
	inline Print& operator<<(Print &o, const backward cmd) { return cmd(o); }

	struct eraseLine {inline Print& operator()(Print& out) const {return out<<preamble()<<'2'<<'K';}};
	inline Print& operator<<(Print &o, const eraseLine cmd) { return cmd(o); }

	struct eraseScreen {inline Print& operator()(Print& out) const {return out<<preamble()<<'1'<<'J';}};
	inline Print& operator<<(Print &o, const eraseScreen cmd) { return cmd(o); }

	struct setBackgroundColor {
		int color;
		inline setBackgroundColor(int color):color(color) {}
		inline Print& operator()(Print& out) const {return out<<setAttribute(color + 40);}
	};
	inline Print& operator<<(Print &o, const setBackgroundColor cmd) { return cmd(o); }

	struct setForegroundColor {
		int color;
		inline setForegroundColor(int color):color(color) {}
		inline Print& operator()(Print& out) const {return out<<setAttribute(color + 30);}
	};
	inline Print& operator<<(Print &o, const setForegroundColor cmd) { return cmd(o); }

	struct fill {
		int x1, y1, x2, y2;
		char ch;
		inline fill(int x1, int y1, int x2, int y2,char ch=' '):x1(x1),y1(y1),x2(x2),y2(y2),ch(ch) {}
		inline Print& operator()(Print& out) const {
			for (int y = y1; y <= y2; y++) {
				out<<xy(x1,y);
				for (int x = x1; x <= x2; x++) out<<ch;
			}
			return out;
		}
	};
	inline Print& operator<<(Print &o, const fill cmd) { return cmd(o); }

	template<char c>
	struct attr {inline Print& operator()(Print& out) const {return out<<setAttribute(c);}};
	template<char c>
	inline Print& operator<<(Print &o, const attr<c> cmd) { return cmd(o); }

	typedef attr<BOLD_ON> boldOn;
	typedef attr<BOLD_OFF> boldOff;
	typedef attr<ITALICS_ON> italicsOn;
	typedef attr<ITALICS_OFF> italicsOff;
	typedef attr<UNDERLINE_ON> underlineOn;
	typedef attr<UNDERLINE_OFF> underlineOff;
	typedef attr<STRIKETHROUGH_ON> strikethroughOn;
	typedef attr<STRIKETHROUGH_OFF> strikethroughOff;
	typedef attr<INVERSE_ON> inverseOn;
	typedef attr<INVERSE_OFF> inverseOff;
	typedef attr<RESET> reset;
	typedef attr<DEFAULT_BACKGROUND> defaultBackground;
	typedef attr<DEFAULT_FOREGROUND> defaultForeground;

}

#endif
