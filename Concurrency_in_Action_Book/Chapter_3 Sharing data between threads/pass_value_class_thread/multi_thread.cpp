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
    for(int i=0; i<100; i++)
    {
        cout<<"thread_id: "<<thread_id<<" "<<some_message<<" "<<ip_addr<<endl;
        sleep(2);
    }
}

int main()
{
    Decoder *d1 = new Decoder(1, "dec_1");
    Decoder *d2 = new Decoder(2, "dec_2");
    std::thread t1(&Decoder::decode, d1, "message_1");
    std::thread t2(&Decoder::decode, d2, "message_2");
    t1.join();
    t2.join();
    return 0;
}

