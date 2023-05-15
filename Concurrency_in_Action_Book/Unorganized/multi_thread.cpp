
#include <iostream>
#include <string>
#include <thread>
#include <future>
#include <vector>
#include <queue>
#include <mutex>
#include <condition_variable>

#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

using std::cin;
using std::cout;
using std::endl;

template <typename T>
class ThreadSafeQueue {
// Ref: https://www.geeksforgeeks.org/implement-thread-safe-queue-in-c/
public:
    // Underlying queue
    std::queue<T> m_queue;

    // mutex for synchronize
    std::mutex m_mutex;

    // Condition variable for signaling
    std::condition_variable m_cond;
    // Push data to queue
    void push(T item)
    {
        // Acquire lock
        std::unique_lock<std::mutex> lock(m_mutex);

        // Add item
        m_queue.push(item);

        // Notify one thread that is waiting
        m_cond.notify_one();
    } // Lock is automatically release here

    // Pops an element off the queue
    T pop()
    {
        // acquire lock
        std::unique_lock<std::mutex> lock(m_mutex);

        // Wait until queue is not empty
        // m_cond.wait(lock, [this]() {return !m_queue.empty(); });
        while (m_queue.size() == 0)
        {
            m_cond.wait(lock);
        }
        
        // retrieve item
        T item = m_queue.front();
        m_queue.pop();

        // return item
        return item;
    }
};

// ThreadSafeQueue<std::string> dataQueue;
std::queue<std::string> dataQueue;
std::mutex q_mutex;

struct dec_res {
    bool isFrame;
    std::string cvMat; 
};

class Processor
{
public:
    std::string model;
    Processor(std::string model_path);
    ~Processor();

    void process(std::string randomMat);
};


Processor::Processor(std::string model_path)
{
    model = model_path;
    cout<<"Initialize model"<<endl;
}

Processor::~Processor()
{
}

void Processor::process(std::string randomMat)
{

    while (true)
    {
        q_mutex.lock();
        std::string outputMat = dataQueue.front();
        dataQueue.pop();
        cout<<"output: "<<outputMat<<endl;
        q_mutex.unlock();
        sleep(2);
        if (dataQueue.empty())
        {
            break;
        }
    }
}

class Decoder
{
private:
    /* data */
public:
    int thread_id;
    std::string ip_addr;    
    Decoder(int some_id, std::string some_mess);
    ~Decoder();
    void decode(std::string some_message);
};

Decoder::Decoder(int some_id, std::string some_mess)
{
    thread_id=some_id;
    ip_addr = some_mess; 
    cout<<"thread_id: "<<thread_id<<endl;
}

Decoder::~Decoder()
{
}

void Decoder::decode(std::string some_message)
{
    for(int i=0; i<10; i++)
    {
        q_mutex.lock();
        std::string outputMat = some_message;
        outputMat = outputMat + "_thread_id_" + std::to_string(thread_id) + "_id_" + std::to_string(i);
        dataQueue.push(outputMat);
        q_mutex.unlock();
        // cout<<"thread_id: "<<thread_id<<" index: "<<i<<" input message to function: "<<some_message<<" ori message init: "<<ip_addr<<endl;
        sleep(1);
    }
    cout<<"Done"<<endl;
}


int main(int argc, char *argv[])
{
    // if(argc != 2)
    // {
    //     cout<<"Usage: ./multi_thread 2" <<endl;
    //     return -1; 
    // }
    // int num_queue = std::stoi(argv[1]);
    // std::vector<std::queue<std::string>> vQueue;
    // for (size_t i = 0; i < num_queue; i++)
    // {
    //     std::queue<std::string> qString;
    //     vQueue.push_back(qString);
    // }


    Decoder *d1 = new Decoder(1, "dec_1");
    Decoder *d2 = new Decoder(2, "dec_2");

    Processor *ai_processsor = new Processor("model_path");

    std::thread t_decoder_1(&Decoder::decode, d1, "message_1");
    std::thread t_decoder_2(&Decoder::decode, d2, "message_2");

    std::thread t_processor(&Processor::process, ai_processsor, "randomMat");

    t_decoder_1.join();
    t_decoder_2.join();
    t_processor.join();

    return 0;
}

