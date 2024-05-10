#ifndef REQUESTHANDLER_H
#define REQUESTHANDLER_H

#include "../Persistence/MemCache.h"
#include <boost/beast.hpp>
#include <boost/asio.hpp>

namespace beast = boost::beast;
using tcp = boost::asio::ip::tcp;

class RequestHandler {
public:
    MemCache& db;
    RequestHandler(MemCache& db);
    void operator()(tcp::socket& socket);
    beast::http::response<beast::http::string_body> handleRequest(const beast::http::request<beast::http::string_body>& req);
    std::string petToJson(const Pet& pet);
    std::string petsToJson(const std::vector<Pet*>& pets);
};

#endif // REQUESTHANDLER_H
