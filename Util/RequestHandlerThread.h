#ifndef REQUESTHANDLERTHREAD_H
#define REQUESTHANDLERTHREAD_H

#include "../Persistence/MemCache.h"
#include <boost/asio.hpp>

class RequestHandlerThread {
public:
    RequestHandlerThread(MemCache& db, std::reference_wrapper<boost::asio::ip::tcp::socket> socket);
    void operator()() const;

private:
    MemCache& db;
    std::reference_wrapper<boost::asio::ip::tcp::socket> socket;
};

#endif // REQUESTHANDLERTHREAD_H
