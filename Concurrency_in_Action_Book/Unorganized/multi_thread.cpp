#include <iostream>
#include <string>
#include <thread>

#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

using std::cin;
using std::cout;
using std::endl;


class decoder
{
private:
    /* data */
public:
    int thread_id;
    std::string ip_addr;    
    decoder(int some_id, std::string some_mess);
    ~decoder();
    void decode(std::string some_message);
};

decoder::decoder(int some_id, std::string some_mess)
{
    thread_id=some_id;
    ip_addr = some_mess; 
    cout<<"thread_id: "<<thread_id<<endl;
}

decoder::~decoder()
{
}

void decoder::decode(std::string some_message)
{
    for(int i=0; i<100; i++)
    {
        cout<<"thread_id: "<<thread_id<<" index: "<<i<<" input message to function: "<<some_message<<" ori message init: "<<ip_addr<<endl;
        sleep(2);
    }
}

int main()
{
    decoder *d1 = new decoder(1, "dec_1");
    decoder *d2 = new decoder(2, "dec_2");
    std::thread t1(&decoder::decode, d1, "message_1");
    std::thread t2(&decoder::decode, d2, "message_2");
    t1.join();
    t2.join();
    return 0;
}

