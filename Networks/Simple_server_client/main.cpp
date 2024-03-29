#include <iostream>
#include <chrono>
#include <vector>
#define ASIO_STANALONE
#include <asio.hpp>
#include <asio/ts/buffer.hpp>
#include <asio/ts/internet.hpp>


std::vector<char> vBuffer(20*1024);
void GrabSomeData(asio::ip::tcp::socket& socket)
{
    socket.async_read_some(asio::buffer(vBuffer.data(), vBuffer.size()),
        [&](std::error_code ec, std::size_t length)
        {
            if(!ec)
            {
                std::cout<<"\n\n Read "<<length <<" bytes \n\n";
                for(int i=0; i < length; i++)
                {
                    std::cout<<vBuffer[i];
                }
                GrabSomeData(socket);
            }
        }
    );
}

int main()
{
    asio::error_code ec;

    // Create a context
    asio::io_context context;

    std::thread thrContext = std::thread([&]() {context.run(); });
    
    // Get the address we wish to connect to
    asio::ip::tcp::endpoint endpoint(asio::ip::make_address("51.38.81.49", ec), 80);

    // Create a socket, the context will delivery the implementation
    asio::ip::tcp::socket socket(context);

    socket.connect(endpoint, ec);
    // Tell the socket to try and connect
    if(!ec)
    {
        std::cout<<"Connect!" << std::endl;
    }
    else
    {
        std::cout<<"Failed to connect to address:\n" << ec.message()<<std::endl; 
    }

    if(socket.is_open())
    {
        std::string sRequest = 
            "GET /index.html HTTP/1.1\r\n"
            "Host: example.com\r\n"
            "Connection: close\r\n\r\n";
        socket.write_some(asio::buffer(sRequest.data(), sRequest.size()), ec);

        using namespace std::chrono_literals;
        std::this_thread::sleep_for(2000ms);
    }
    else
    {
        std::cout<<"Socket is not open"<<std::endl;
    }

    return 0;
}