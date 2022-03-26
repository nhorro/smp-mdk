# See https://www.jsonrpcclient.com/en/stable/examples.html#zeromq

from jsonrpcclient import request_json, parse_json, Ok
import logging
import zmq

# Use ZMQ backend
socket = zmq.Context().socket(zmq.REQ)
socket.connect("tcp://localhost:5050")


# Invoke method
socket.send_string(request_json(method="model_request",
                                params={
                                    "operation": "reset",
                                    "model":"counter1"
                                }))

# Check response
response = parse_json(socket.recv().decode())
if isinstance(response, Ok):
    print(response.result)
else:
    logging.error(response.message)