# See https://www.jsonrpcclient.com/en/stable/examples.html#zeromq

from jsonrpcclient import request_json, parse_json, Ok
import logging
import zmq

class SMP2Client():
    def __init__(self,host="localhost",port=5050):
        self.socket = zmq.Context().socket(zmq.REQ)
        self.socket.connect("tcp://{}:{}".format(host,port))

    def run(self):
        """ Run the simulator.        
        """
        self.__rpc_call(self,"run",params={})
        pass

    def resume(self):
        """ Resume the simulator.        
        """
        self.__rpc_call(self,"run",params={})
        pass

    def hold(self):
        """ Hold the simulator.        
        """
        self.__rpc_call(self,"hold",params={})
        pass

    def exit(self):
        """ Exit the simulator.        
        """
        self.__rpc_call(self,"exit",params={})
        pass

    def model_request(self,operation,model,params):
        return self.__rpc_call(method="model_request",
                              params={
                                    "operation": operation,
                                    "model": model,
                                    **params
                              })   

    def __rpc_call(self,method,params):
        self.socket.send_string(request_json(method=method, params=params))
        
        # Check response
        response = parse_json(self.socket.recv().decode())
        if isinstance(response, Ok):
            return response.result
        else:
            logging.error(response.message)
