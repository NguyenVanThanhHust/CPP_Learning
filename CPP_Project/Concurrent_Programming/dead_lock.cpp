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
	void shared_print2(string& msg, int id);
private:
	std::mutex m_mutex;
	std::mutex d_mutex;

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
	std::lock(m_mutex, d_mutex);
	std::lock_guard<std::mutex> guard(m_mutex, std::adopt_lock);
	std::lock_guard<std::mutex> guard2(d_mutex, std::adopt_lock);
	m_ofstream << "from : " << msg << " with Id : " << id << endl;

}

void LogFile::shared_print2(string& msg, int id)
{
	std::lock(m_mutex, d_mutex);
	std::lock_guard<std::mutex> guard(m_mutex, std::adopt_lock);
	std::lock_guard<std::mutex> guard2(d_mutex, std::adopt_lock);
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
		log.shared_print2(string("From_main: "), i);
	}
	t1.join();
	std::cin.get();
	return 0;
}

/*
To avoid a deadlock 
1. Prefer locking single mutex
2. Avoid locking a mutex and then clalling a user provided function
3. Use std::lock() to lock many mutex
4. Lock in the same order in every function as above
*/