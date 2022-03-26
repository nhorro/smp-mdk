#ifndef ZMQRPCSERVER_HPP
#define ZMQRPCSERVER_HPP

#include <atomic>
#include <iostream>
#include <string>
#include <thread>
#include "jsonrpc_request_handler_base.hpp"
#include "transport/rpc_transport_base.hpp"

class jsonrpc_server : public jsonrpc_request_handler_base {
   public:
    jsonrpc_server(std::shared_ptr<rpc_transport_base> transport) : transport(transport), keep_running(false) {}

    ~jsonrpc_server() {
        if (this->keep_running) {
            this->stop();
        }
    }

    void start() {
        this->transport->connect();
        this->receiver_thread = std::thread([this]() { this->run(); });
    }

    void stop() {
        this->keep_running = false;
        this->receiver_thread.join();
    }

    inline std::shared_ptr<rpc_transport_base> get_transport() { return this->transport; }

   private:
    std::shared_ptr<rpc_transport_base> transport;
    std::atomic<bool> keep_running;
    std::thread receiver_thread;

    void run() {
        this->keep_running = true;
        try {
            while (this->keep_running) {
                std::string request_str;
                if (this->transport->receive_str(request_str)) {
                    try {
                        jsonrpcpp::Response response = this->handle_request(request_str);
                        std::string response_str(response.to_json().dump());
                        this->transport->send_str(response_str);
                    } catch (jsonrpcpp::MethodNotFoundException& jsonrpcex) {
                        jsonrpcpp::Response response(jsonrpcex);
                        std::string response_str(response.to_json().dump());
                        this->transport->send_str(response_str);
                    } catch (jsonrpcpp::RequestException& jsonrpcrequestex) {
                        jsonrpcpp::Response response(jsonrpcrequestex);
                        std::string response_str(response.to_json().dump());
                        this->transport->send_str(response_str);
                    } catch (nlohmann::json::exception& ex) {
                        throw;
                    } catch (std::exception& ex) {
                        // FIXME: ZMQ REQ-REP Workaround: Send something to unblock receiver
                        std::string tmp_str("");
                        this->transport->send_str(tmp_str);
                    }
                }
            }
            this->transport->disconnect();
        } catch (const rpc_transport_base::exception& tex) {
            this->keep_running = false;
        }
    }
};

#endif  // ZMQRPCSERVER_HPP
