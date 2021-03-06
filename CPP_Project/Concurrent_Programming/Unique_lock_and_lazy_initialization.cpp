#include <iostream>
#include <mutex>
#include <vector>
#include <fstream>
#include <string>

using namespace std;

class LogFile
{
public:
	LogFile();
	~LogFile();
	void shared_print(string& msg, int id);
private:
	std::mutex m_mutex;
	ofstream m_ofstream;
};


LogFile::LogFile()
{
	m_ofstream.open("log_file.txt");
}

LogFile::~LogFile()
{
	m_ofstream.close();
}

void LogFile::shared_print(string& msg, int id)
{
	std::unique_lock<mutex> locker(m_mutex, std::defer_lock);
	m_ofstream << "from : " << msg << " with Id : " << id << endl;
}
void m_function_1(LogFile& log)
{
	for (size_t i = 0; i < 100; i++)
	{
		log.shared_print(string("thread_1"), i);
	}
}

int main()
{
	LogFile log;
	std::thread t1(m_function_1, std::ref(log));
	for (size_t i = 0; i < 100; i++)
	{
		log.shared_print(string("From_main: "), i);
	}
	t1.join();
	std::cin.get();
	return 0;
}

