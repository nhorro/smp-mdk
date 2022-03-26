#ifndef ZMQ_REQREP_TRANSPORT_HPP
#define ZMQ_REQREP_TRANSPORT_HPP

#include <zmq.hpp>

#include "../rpc_transport_base.hpp"

class zmq_reqrep_transport : public rpc_transport_base {
   public:
    zmq_reqrep_transport(int port, int timeout = 500) : rpc_transport_base(port), context(1), socket(context, ZMQ_REP) {
        //this->socket.set(zmq::sockopt::rcvtimeo, timeout);
        this->socket.setsockopt(ZMQ_RCVTIMEO, timeout); // set timeout to value of timeout_ms 
    }

    virtual ~zmq_reqrep_transport() {}

    void connect() override {
        std::string hostname = "tcp://*:";
        hostname += std::to_string(this->rpc_transport_base::get_port());
        try {
            this->socket.bind(hostname);
        } catch (const zmq::error_t& error) {
            throw std::runtime_error("Cannot bind socket to address '" + hostname + "': " + error.what());
        }
    }

    void disconnect() override { this->socket.close(); }

    bool receive_str(std::string& request_str) override {
        try {
            zmq::message_t request;
            if (this->socket.recv(request, zmq::recv_flags::none)) {
                request_str = std::string(reinterpret_cast<const char*>(request.data()), request.size());
                return true;
            }
        } catch (zmq::error_t& ex) {
            throw(rpc_transport_base::exception(ex.what()));
        }

        // timeout
        return false;
    }

    void send_str(std::string& response_str) override {
        try {
            this->socket.send(static_cast<zmq::message_t>(response_str), zmq::send_flags::none);
        } catch (zmq::error_t& ex) {
            throw(rpc_transport_base::exception(ex.what()));
        }
    }

   private:
    zmq::context_t context;
    zmq::socket_t socket;
};

#endif  // ZMQ_REQREP_TRANSPORT_HPP
