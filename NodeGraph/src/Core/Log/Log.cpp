#include "PCH.h"
#include "Log.h"
#include "imgui.h"
#include <ctime>
#include <iostream>
#include <fstream>
#include <filesystem>

void Log::AddLog(const char* fmt, ...)
{
	time_t rawtime;
	struct tm* timeinfo;
	char datebuffer[80];

	time(&rawtime);
	timeinfo = localtime(&rawtime);

	strftime(datebuffer, sizeof(datebuffer), "%d-%m-%Y %H:%M:%S ", timeinfo);

	auto old_size = Buf.size();

	va_list args;
	va_start(args, fmt);
	Buf.append(datebuffer);
	Buf.appendfv(fmt, args);
	Buf.append("\n");
	va_end(args);
	ScrollToBottom = true;

	auto new_size = Buf.size();

	if (Buf.size() > 0)
	{
		std::string buf(Buf.c_str());
		WriteLog(buf.substr(old_size, new_size).c_str());
	}
	
}

void Log::Clear()
{
	Buf.clear();
}

struct ImGuiTextBuffer& Log::GetBuffer()
{
	return Buf;
}

void Log::WriteLog(const char* buffer)
{
	std::ofstream ofs;
	ofs.open("Log.txt", std::ios::out | std::ios::app);
	ofs << buffer;
}

struct ImGuiTextBuffer Log::Buf;

bool Log::ScrollToBottom = false;
