# SLIDE-x
**S**ystem-**L**evel **I**nfrastructure for HW/SW **D**ataset **E**-**x**traction

<p align="center">
<img src="img/logo_NEW.png" width="250" height="250">
</p>

[![License: GPL v3](https://img.shields.io/badge/License-GPLv3-blue.svg)](https://www.gnu.org/licenses/gpl-3.0)

## Installation instructions

### OVERVIEW
SLIDE-x
A framework has been developed to calculate the CC4CS metrics. You can execute a custom C function using with several ISSs (Instruction Set Simulators) of different processors. The framework has been developed in Python and includes a simple benchmark composed by 10 well-know algorithms. The source code of the algorithms is contained in /framework/benchmark directory.  

The framework is structured in three modules: the InputsGenerator, Parser, and the CommandsManager. The InputsGenerator (semi)automatically generates inputs for a function. The parameters of a function are specified in a json file (`cmds.json`) contained in the same directory of the function. The InputsGenerator reads a range `[x; y]` that is used to generate the values of the parameters and the number of inputs to be created. Finally, for each function, different data types have been considered (i.e., int8, int16, int32, and float) to analyze the results with respect to the internal  architecture of the considered processor.

The number of executed C statements is obtained by profiling the benchmark functions using the `gcov` profiler for each generated input. It is worth noting that such a profiling is performed one-shot on the  host platform since it is independent of the target processor technologies. Instead, the clock cycles needed by the target processor technology to execute each function in the benchmark. Depending on the processor technology there is the need for an Instruction Set Simulator (ISS) or an HDL Simulator.

### SLIDE-x Main Components:
1. **SLIDE-x-Bench**: Extensible C-based Benchmark
2. **SLIDE-x-CORE**:
   - **SLIDE-x-Data**: Extensible Python Data-driven Module
   - **SLIDE-x-Code**: Extensible Python Code-driven Module
   - **SLIDE-x-Sim**: Extensible Python HW/SW Simulation-driven Module
     - **SLIDE-x-HLS** (e.g., Bambu, Vitis-HLS, LegUP)
     - **SLIDE-x-ISS** (e.g., TSIM, Armulator, Thumbulator, Dalton, SimulAVR, Spike 64-bit RISC-V, x86-64 with Perf)
3. **SLIDE-x-AGGR**: Extensible Python dataset Aggragator, with Unified HW/SW metric (e.g., CC4CS, CC4IR, CC4SSA, CC4OPT), statistical models and analysis, and platform comparison
4. **SLIDE-x-ML**: HW/SW ML-based Models with Matlab Statistics and Machine Learning Toolbox and Python TensorFlow/Keras/PyTorch/Scikit-Learn Frameworks
5. Support for FPGA (i.e., **SLIDE-x-FPGA**) and SoC (i.e., **SLIDE-x-SoC**) Target Form Factor, ASIC WIP.
6. **HEPSYCODE-x**: HEPSYCODE enhanced with SLIDE-x extensions 
7. **PAM-x**: PAM1 & PAM2 Design Space Exploration enhanced with SLIDE-x extensions (GIMPLE-SSA-OPTIMIZED Intermediate Representations)
