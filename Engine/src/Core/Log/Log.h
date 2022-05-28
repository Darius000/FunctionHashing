#pragma once


struct  ImGuiTextBuffer;

template<typename T>
struct ImVector;

class Log
{
public:
	static void AddLog(const char* fmt, ...);

	static void Clear();

	static struct ImGuiTextBuffer& GetBuffer();

	static void WriteLog(const char* buffer);

private:

	static struct ImGuiTextBuffer Buf;

public:
	static bool ScrollToBottom;

};

#define LOG(x, ...) Log::AddLog(x, __VA_ARGS__);