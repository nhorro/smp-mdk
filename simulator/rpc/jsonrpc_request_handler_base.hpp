#ifndef JSONRPCREQUESTHANDLER_HPP
#define JSONRPCREQUESTHANDLER_HPP

#include <functional>
#include <iostream>
#include <jsonrpcpp/jsonrpcpp.hpp>
#include <map>
#include <memory>
#include <string>

class jsonrpc_request_handler_base {
   public:
    using jsonrpc_request_method = std::function<jsonrpcpp::Response(jsonrpcpp::request_ptr)>;

    jsonrpc_request_handler_base() = default;

    virtual ~jsonrpc_request_handler_base() = default;

    void register_handler(const std::string& method, jsonrpc_request_method handler) {
        this->methods[method] = handler;
    }

    jsonrpcpp::Response handle_request(const std::string& str) {
        jsonrpcpp::entity_ptr entity = parser.parse(str);
        jsonrpcpp::request_ptr request = std::dynamic_pointer_cast<jsonrpcpp::Request>(entity);
        if (entity && entity->is_request()) {
            try {
                return this->methods.at(request->method())(request);
            } catch (std::out_of_range& ex) {
                throw jsonrpcpp::MethodNotFoundException(*request);
            }
        }
        return static_cast<jsonrpcpp::Response>(nullptr);  //
    }

   private:
    jsonrpcpp::Parser parser;
    std::map<std::string, jsonrpc_request_method> methods;
};

#endif
