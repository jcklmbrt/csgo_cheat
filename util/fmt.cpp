#include <chrono>
#include <deque>
#include <cstdio>
#include <cstdarg>
#include "util/fmt.hpp"

using std::chrono::duration_cast;
using std::chrono::milliseconds;
using std::chrono::system_clock;
using std::chrono::time_point;

constexpr int LINE_SIZE = 1024;
constexpr int MAX_LINES = 128;

struct FmtLine
{
	char str[LINE_SIZE];
	time_point<system_clock> time;
};

static std::deque<FmtLine> g_lines = {};

void fmt::PrintLn(const char *fmt, ...)
{
	FmtLine line = {};

	line.time = system_clock::now();

	va_list args;
	va_start(args, fmt);
	vsnprintf(line.str, LINE_SIZE, fmt, args);
	va_end(args);

	g_lines.push_front(line);

	while(g_lines.size() > MAX_LINES)
		g_lines.pop_back();
}

void fmt::DrawLog(Draw &gr)
{
	int x = 10;
	int y = 10;

	time_point<system_clock> t = system_clock::now();

	while(!g_lines.empty())
	{
		//delete after 5 seconds. assume the entries are in chronological order.
		if(duration_cast<milliseconds>(t - g_lines.back().time).count() <= 5000.0f)
			break;

		g_lines.pop_back();
	}

	for(auto &line : g_lines)
	{
		float delta = duration_cast<milliseconds>(t - line.time).count();

		int a = 255;

		//fade out after 4 seconds
		if(delta > 4000.0f)
		{
			delta -= 4000.0f;
			a -= static_cast<int>((delta / 1000.0f) * 255.0f);
		}

		gr.PutS(x, y, dxvk::ColorARGB(a, 255, 255, 255), line.str);
		y += Draw::FONT_HEIGHT + 2;
	}

}