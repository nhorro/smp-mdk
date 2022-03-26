Counters with IDynamicInovation (RPC)
=====================================

Adaptation of Counter example from the handbook with added Dynamic Invocation interface to reset method, accesable through the RPC simulator interface.

Instructions
------------

Make sure python 3 and required packages are available.

~~~bash
python3 --version
pip install -r requirements.txt
~~~

Run example:

~~~bash
./run-sim.sh
~~~

Reset counter1.

~~~bash
python3 reset_counter1.py
~~~

The accompanying python example invokes the `reset()` method on `counter1`. Note that thread-safety is not granted, and resource syncrhonization mechanisms might be required in more complex scenarios.