#include "Persistence/MemCache.h"
#include "HttpHandler/RequestHandler.h"
#include <boost/asio.hpp>
#include <iostream>
#include <thread>
#include "Util/RequestHandlerThread.h"

int main() {
    try {
        boost::asio::io_context ioc;
        boost::asio::ip::tcp::acceptor acceptor(ioc, {boost::asio::ip::tcp::v4(), 8080});
        MemCache db;
        std::cout<<"test"<<std::endl;

        while (true) {
            std::cout << "Waiting for connection..." << std::endl;
            boost::asio::ip::tcp::socket socket(ioc);
            boost::system::error_code ec;
            acceptor.accept(socket, ec);
            if (ec) {
                std::cerr << "Error accepting connection: " << ec.message() << std::endl;
                continue;
            }
            std::cout << "Connection accepted" << std::endl;
            std::thread{
                [&db, acceptedSocket = std::move(socket)]() mutable {
                    RequestHandlerThread(db, acceptedSocket)();
                }
            }.detach();
        }
    } catch (std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
    return 0;
}