#include "RequestHandlerThread.h"
#include "../HttpHandler/RequestHandler.h"

RequestHandlerThread::RequestHandlerThread(MemCache& db, std::reference_wrapper<boost::asio::ip::tcp::socket> socket)
    : db(db), socket(socket) {}

void RequestHandlerThread::operator()() const {
    RequestHandler requestHandler(db);
    requestHandler(socket.get());
}