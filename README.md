SMP2 Simulator for Hardware in the Loop
=======================================

This project is forked from [Juan R. García Blanco's implementation of SMP (*Simulation Model Portability*) Model Development Kit](https://github.com/juanrgar/smp-mdk) for open-source development of SMP2 models, mainly geared for 
academic research projects related to HIL (Hardware in the Loop) and OBC (On board computer) device and peripheral models.

SMP2 standard header files have been removed from the original codebase and instead inherited from [SmpStandard project by Nicolás Iriarte](https://github.com/NicolasIriarte/SmpStandard).

**Implementation details**

The scheduler is attached to the computer clock instead of using a discrete event queue so Scheduler and TimeKeeper services behaviour is not fully compliant to the SMP2 standard. Save/restore and hold/resume are not available, but the partial implementation should be enough to run SMP2 models connected to HW interfaces. This is useful for many testing scenarios in which an SMP2 model needs to comunicate through SpW, 1553, CAN, I/O signals or any other protocolol with real hardware.

Differences from original author's code:

- Changed to CMake build system (WIP).
- Modified original code for compatibility with C++17 (removed throws).
- Added some examples from the official handbook (WIP).
- Added a minimal implementation of a simulation infrastructure: Scheduler, Logger, Time Keeper, etc. (WIP).

Maturity
--------

Still WIP. A more detailed status for each item of SMP2 standard to be provided in next tag.

- [Simulator service](./simulator/):
    - Simulator service. :heavy_check_mark:
    - Dynamic model loading and configuration using YAML. :heavy_check_mark:
    - RPC: JSON RPC 2.0/ZMQ. :heavy_check_mark:
    - SMP2 variables publication. :white_check_mark:
- [SMP2 Standard implementation](./libsmp2):
    - Hardware in the Loop Scheduler + TimeKeeper. :heavy_check_mark:
    - Discrete event Scheduler + TimeKeeper. :white_check_mark:
    - Managed models. :white_check_mark:
    - Logger. :heavy_check_mark:
    - Event Manager. :white_check_mark:
    - Publication. :white_check_mark:
    - Dynamic invocation. :white_check_mark:
    - Save/restore. :white_check_mark:
- [SMP2 handbook examples](./examples):
    - SMP2 Handbook Counter example (non managed). :heavy_check_mark:
- [Example models](./models)
- Code and process quality:
    - CMake. :heavy_check_mark:
    - Tests. :white_check_mark:
    - Documentation. :white_check_mark:
    - CI. :white_check_mark:

Instructions
------------

Requirements:

- C++ compiler
- CMake
- Boost

Follow specific instructions for [general third-party libraries installation](./thirdparty) and [simulator-specific third party libraries](./simulator/thirdparty).

Build and install everything: SMP2 library and examples, simulator, models and tests:

~~~bash
mkdir build
cd build
cmake ..
make && sudo make install
~~~

Tested on Ubuntu 18.04.

Specific instructions for each component are in its directory README file.

- [Building and using the SMP2 library](./libsmp2/README.md)
- [Building and running the SMP2 library examples](./examples/README.md).
- [Building and running the simulation service](./simulator/README.md).
- [Building and running the SMP2 example models for the simulator](./models/README.md).


Related resources and references
--------------------------------

- [SMP 2.0 Handbook - EGOS-SIM-GEN-TN-0099 - Issue 1 Revision 2 - 28 October 2005](https://taste.tuxfamily.org/wiki/images/9/9a/SMP_2.0_Handbook_-_1.2.pdf). Accessed 2021-09-30.
