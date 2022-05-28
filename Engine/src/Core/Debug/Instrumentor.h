#pragma once
#include <chrono>
#include <ostream>
#include <fstream>
#include <thread>


struct ProfilerResult
{
	std::string m_Name;
	long long m_Start, m_End;
	unsigned int m_ThreadID;
};

struct InstrumentionSession
{
	std::string m_Name;
};

class Instrumentor
{
public:
	Instrumentor()
		:m_CurrentSession(nullptr), m_ProfileCount(0)
	{

	}

	void BeginSession(const std::string& name, const std::string& filepath = "results.json")
	{
		m_OutputStream.open(filepath.c_str());
		WriteHeader();
		m_CurrentSession = new InstrumentionSession{ name };
	}

	void EndSession()
	{
		WriteFooter();
		m_OutputStream.close();
		delete m_CurrentSession;
		m_CurrentSession = nullptr;
		m_ProfileCount = 0;
	}

	void WriteProfile(const ProfilerResult& result)
	{
		if (m_ProfileCount++ > 0)
			m_OutputStream << ",";

		std::string name = result.m_Name;
		name.replace(name.begin(), name.end(), '"', '\'');

		m_OutputStream << "{";
		m_OutputStream << "\"cat\":\"function\",";
		m_OutputStream << "\"dur\":" << (result.m_End - result.m_Start) << ",";
		m_OutputStream << "\"name\":\"" << name << "\",";
		m_OutputStream << "\"ph\":\"X\",";
		m_OutputStream << "\"pid\":0,";
		m_OutputStream << "\"tid\":" << result.m_ThreadID << ",";
		m_OutputStream << "\"ts\":" << result.m_Start;
		m_OutputStream << "}";

		m_OutputStream.flush();
	}

	void WriteHeader()
	{
		m_OutputStream << "{\"otherData\":{},\"traceEvents\":[";
		m_OutputStream.flush();
	}

	void WriteFooter()
	{
		m_OutputStream << "]}";
		m_OutputStream.flush();
	}

	static Instrumentor& Get()
	{
		static Instrumentor* instance = new Instrumentor();
		return *instance;
	}

private:
	InstrumentionSession* m_CurrentSession;
	std::ofstream m_OutputStream;
	int m_ProfileCount;
};

//template<typename Fn>
struct InstrumentionTimer
{
	InstrumentionTimer(const char* name)
		:m_Name(name), m_Stopped(false)
	{
		m_StartPoint = std::chrono::high_resolution_clock::now();
	}

	~InstrumentionTimer()
	{
		if(!m_Stopped)
			Stop();
	}

	void Stop()
	{
		auto endTimePoint = std::chrono::high_resolution_clock::now();
			
		long long start = std::chrono::time_point_cast<std::chrono::microseconds>(m_StartPoint).time_since_epoch().count();
		long long end = std::chrono::time_point_cast<std::chrono::microseconds>(endTimePoint).time_since_epoch().count();
		float duration = (end - start) * .001f;

		m_Stopped = true;

		unsigned int threadID = (unsigned int)std::hash<std::thread::id>{}(std::this_thread::get_id());

		Instrumentor::Get().WriteProfile({ m_Name, start, end, threadID});
	}

private:
	std::chrono::time_point<std::chrono::steady_clock> m_StartPoint;
	const char* m_Name;
	bool m_Stopped;
	//Fn m_Func;
		
};

#define PROFILING 1
#if PROFILING 
#define PROFILE_BEGIN_SESSION(name, filepath)Instrumentor::Get().BeginSession(name, filepath)
#define PROFILE_END_SESSION() Instrumentor::Get().EndSession()
#define PROFILE_SCOPE(name)InstrumentionTimer timer##__LINE__(name)
#define PROFILE_FUNCTION() PROFILE_SCOPE(__FUNCSIG__)
#else
#define PROFILE_BEGIN_SESSION(name, filepath) 
#define PROFILE_END_SESSION()
#define PROFILE_SCOPE(name) 
#define PROFILE_FUNCTION() 
#endif // PROFILING
