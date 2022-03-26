#ifndef RPC_TRANSPORT_BASE_H
#define RPC_TRANSPORT_BASE_H

#include <stdexcept>
#include <string>

class rpc_transport_base {
   public:
    using exception = std::logic_error;
    rpc_transport_base(int port) : port(port) {}
    virtual ~rpc_transport_base() = default;
    virtual void connect() = 0;
    virtual void disconnect() = 0;
    virtual bool receive_str(std::string& request_str) = 0;
    virtual void send_str(std::string& response_str) = 0;
    inline int get_port() const { return this->port; }

   protected:
    int port;
};

#endif  // RPC_TRANSPORT_BASE_H
