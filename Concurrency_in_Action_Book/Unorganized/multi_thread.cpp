#include <iostream>
#include <string>
#include <thread>
#include <future>

#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

using std::cin;
using std::cout;
using std::endl;

struct dec_res {
    bool isFrame;
    std::string cvMat; 
}

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
    dec_res decoder::decoder_v2(std::string& some_message);
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

void decoder::decode(std::string& some_message)
{
    for(int i=0; i<10; i++)
    {
        cout<<"thread_id: "<<thread_id<<" index: "<<i<<" input message to function: "<<some_message<<" ori message init: "<<ip_addr<<endl;
        sleep(2);
    }
    cout<<"Done"<<endl;
}

dec_res decoder::decoder_v2(std::string& some_message)
{
    for(int i=0; i<10; i++)
    {
        cout<<"thread_id: "<<thread_id<<" index: "<<i<<" input message to function: "<<some_message<<" ori message init: "<<ip_addr<<endl;
        sleep(1);
    }
    dec_res res{true, ip_addr};
    return res;
}


int main()
{
    decoder *d1 = new decoder(1, "dec_1");
    decoder *d2 = new decoder(2, "dec_2");
    
    auto ret1 = std::async(&decoder::decoder_v2, d1, "message_1");
    auto ret2 = std::async(&decoder::decoder_v2, d2, "message_2");
    
    dec_res v1 = ret1.get();
    dec_res v2 = ret2.get();
    cout<<"get result";
    cout<<v1.cvMat<<endl;
    cout<<v2.cvMat<<endl;
    return 0;
}

