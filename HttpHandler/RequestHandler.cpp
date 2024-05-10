#include "RequestHandler.h"
#include <iostream>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

RequestHandler::RequestHandler(MemCache& db) : db(db) {}

void RequestHandler::operator()(tcp::socket& socket) {
    try {
        beast::flat_buffer buffer;
        beast::http::request<beast::http::string_body> req;
        beast::http::read(socket, buffer, req);
        auto response = handleRequest(req);
        beast::http::write(socket, response);
        socket.shutdown(tcp::socket::shutdown_send);
    } catch (std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}

beast::http::response<beast::http::string_body> RequestHandler::handleRequest(const beast::http::request<beast::http::string_body>& req) {
    beast::http::response<beast::http::string_body> res;

    if (req.method() == beast::http::verb::post && req.target() == "/pets") {
        auto pet = db.createPet(req.body());
        res.result(beast::http::status::created);
        res.body() = petToJson(*pet);
    } else if (req.method() == beast::http::verb::get && req.target().starts_with("/pets/")) {
        auto id = boost::lexical_cast<unsigned long>(req.target().substr(6));
        auto petOpt = db.getPet(id);
        if (petOpt) {
            res.result(beast::http::status::ok);
            res.body() = petToJson(*petOpt.value());
        } else {
            res.result(beast::http::status::not_found);
        }
    } else if (req.method() == beast::http::verb::get && req.target() == "/pets") {
        auto pets = db.listPets();
        res.result(beast::http::status::ok);
        res.body() = petsToJson(pets);
    } else if (req.method() == beast::http::verb::delete_ && req.target().starts_with("/pets/")) {
        //auto id = std::stoul(req.target().substr(6));
        auto id = boost::lexical_cast<unsigned long>(req.target().substr(6));
        if (db.deletePet(id)) {
            res.result(beast::http::status::no_content);
        } else {
            res.result(beast::http::status::not_found);
        }
    } else {
        res.result(beast::http::status::bad_request);
    }
    res.set(beast::http::field::content_type, "application/json");
    res.keep_alive(req.keep_alive());
    return res;
}

std::string RequestHandler::petToJson(const Pet& pet) {
    boost::property_tree::ptree pt;
    pt.put("id", pet.id);
    pt.put("name", pet.name);
    pt.put("createdAt", boost::posix_time::to_iso_extended_string(pet.createdAt));
    std::ostringstream oss;
    boost::property_tree::json_parser::write_json(oss, pt);
    return oss.str();
}

std::string RequestHandler::petsToJson(const std::vector<Pet*>& pets) {
    boost::property_tree::ptree pt;
    for (const auto& pet : pets) {
        boost::property_tree::ptree petNode;
        petNode.put("id", pet->id);
        petNode.put("name", pet->name);
        petNode.put("createdAt", boost::posix_time::to_iso_extended_string(pet->createdAt));
        pt.push_back(std::make_pair("", petNode));
    }
    std::ostringstream oss;
    boost::property_tree::json_parser::write_json(oss, pt);
    return oss.str();
}
