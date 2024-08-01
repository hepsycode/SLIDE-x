import math

# !/usr/bin/env python
from GUI import GUI
from InputsGenerator import InputsGenerator
from Parser import Parser
from CommandsManager import CommandsManager
import shutil
import os
from os.path import dirname, realpath, abspath, isdir, isfile, join
from os import makedirs, chdir, listdir, getcwd
from json import load
from csv import reader, DictWriter
from shutil import move, rmtree
from timeit import default_timer as timer
import numpy as np

# Absolute path of the directory containing the configuration files 
configsrc = dirname(realpath(__file__).rsplit("/", 1)[0])
projectPath = dirname(configsrc) + '/'
benchmarkFolder = '/SLIDE-x-BENCH/KERNEL/'  # '/benchmark/POLYBENCH/linear-algebra/kernels/'

optFlagsArr = (['-O1',
            '-O1 -fcse-follow-jumps -fno-tree-ter -ftree-vectorize',
            '-O1 -fno-cprop-registers -fno-dce -fno-move-loop-invariants -frename-registers -fno-tree-copy-prop -fno-tree-copyrename',
            '-O1 -freorder-blocks -fschedule-insns -fno-tree-ccp -fno-tree-dominator-opts',
            '-O2',
            '-O2 -falign-loops -fno-cse-follow-jumps -fno-dce -fno-gcse-lm -fno-inline-functions-called-once -fno-schedule-insns2 -fno-tree-ccp -fno-tree-copyrename -funroll-all-loops',  # Problem with Atmega MatrixMul int32
            '-O2 -finline-functions -fno-omit-frame-pointer -fschedule-insns -fno-split-ivs-in-unroller -fno-tree-sink -funroll-all-loops',
            '-O2 -fno-align-jumps -fno-early-inlining -fno-gcse -fno-inline-functions-called-once -fno-move-loop-invariants -fschedule-insns -fno-tree-copyrename -fno-tree-loop-optimize -fno-tree-ter -fno-tree-vrp',
            '-O2 -fno-caller-saves -fno-guess-branch-probability -fno-ira-share-spill-slots -fno-tree-reassoc -funroll-all-loops -fno-web',
            '-O2 -fno-caller-saves -fno-ivopts -fno-reorder-blocks -fno-strict-overflow -funroll-all-loops',
            '-O2 -fno-cprop-registers -fno-move-loop-invariants -fno-omit-frame-pointer -fpeel-loops',
            '-O2 -fno-dce -fno-guess-branch-probability -fno-strict-overflow -fno-tree-dominator-opts -fno-tree-loop-optimize -fno-tree-reassoc -fno-tree-sink',
            '-O2 -fno-ivopts -fpeel-loops -fschedule-insns',
            '-O2 -fno-tree-loop-im -fno-tree-pre',
            '-O3',
            '-O3 -falign-loops -fno-caller-saves -fno-cprop-registers -fno-if-conversion -fno-ivopts -freorder-blocks-and-partition -fno-tree-pre -funroll-all-loops',
            '-O3 -falign-loops -fno-cprop-registers -fno-if-conversion -fno-peephole2 -funroll-all-loops',
            # NO: '-O3 -falign-loops -fno-delete-null-pointer-checks -fno-gcse-lm -fira-coalesce -floop-interchange -fsched2-use-superblocks -fno-tree-pre -fno-tree-vectorize -funroll-all-loops -funsafe-loop-optimizations -fno-web',
            '-O3 -fno-gcse -floop-strip-mine -fno-move-loop-invariants -fno-predictive-commoning -ftracer',
            '-O3 -fno-inline-functions-called-once -fno-regmove -frename-registers -fno-tree-copyrename',
            '-O3 -fno-inline-functions -fno-move-loop-invariants',
            '-Os', '-Ofast', '-Og'])  # 23 Optimization flags

optNameFolderArr = ['optO1-00', 'optO1-01', 'optO1-02', 'optO1-03',
                    'optO2-00', 'optO2-01', 'optO2-02', 'optO2-03', 'optO3-04', 'optO2-05', 'optO2-06', 'optO2-07', 'optO2-08', 'optO2-09',
                    'optO3-00', 'optO3-01', 'optO3-02', 'optO3-03', 'optO3-04', 'optO3-05', # 'optO3-06',
                    'optO4-Os', 'optO5-Ofast', 'optO6-Og'] # 23 folders

matrixFolderName = '32x32'

# TODO: automatic switching between signed and unsigned types
# Global Variables
filess = {'8051': 'scnd.c', 'Leon3': 'frst.c', 'Thumb': 'frst.c', 'Atmega328p': 'frst.c', 'Arm': 'frst.c',
          'Bambu': 'frst.c', 'RiscV': 'frst.c', 'ALL': 'frst.c', 'Perf': 'frst.c'}

targets = ["float", "double"]
# targets = ["int8_t", "int16_t", "int32_t", "int64_t", "float", "double"]  # TARGET_TYPE types

indexes = ["uint32_t", "uint64_t"]
# indexes = ["uint8_t", "int16_t", "int32_t", "int64_t"]  # TARGET_INDEX types

simulations = ['Leon3']
# simulations = ['Leon3', 'RiscV', 'Atmega328p', 'Thumb', 'Arm', 'Bambu', 'Perf']

functions = ['kruskal']  # TODO: 'kruskal',

# RECIPE INT:
# 'bs', 'bsort100', 'cnt', 'fac', 'fdct', 'fft', 'fibcall', 'insertionsort', 'lud', 'matrix_mult', 'park_miller', 'prime', 'select', 'shell_sort', 'sqrt'

# RECIPE DECIMAL:
# 'bs', 'bsort100', 'cnt', 'fibcall', 'insertionsort', 'lud', 'matrix_mult', 'select', 'shell_sort'

# KERNEL INT:
# 'astar', 'banker_algorithm', 'bellmanford', 'bfs', 'binary_search', 'floydwarshall', 'gcd', 'kruskal', 'mergesort', 'selectionsort'

# KERNEL DECIMAL:
# 'astar', 'banker_algorithm', 'bellmanford', 'bfs', 'floydwarshall', 'gcd', 'kruskal', 'mergesort', 'selectionsort'

# POLYBENCH (linear-algebra/kernels)
# '2mm', '3mm', 'atax', 'bicg', 'cholesky', 'doitgen', 'gemm', 'gemver', 'gesummv', 'mvt', 'symm', 'syr2k', 'syrk', 'trisolv', 'trmm'

# POLYBENCH (linear-algebra/solvers)
# 'durbin', 'dynprog', 'gramschmidt', 'lu', 'ludcmp'

# POLYBENCH (datamining)
# 'correlation', 'covariance'

# POLYBENCH (medley)
# 'floyd-warshall', 'reg_detect'

# POLYBENCH (stencil)
# 'adi', 'convolution-2d', 'convolution-3d', 'fdtd-2d', 'jacobi-1d-imper', 'jacobi-2d-imper', 'seidel-2d'

# AFFINITY (control group):
# 'bitrev', 'can_can', 'can_dsp', 'conv', 'corr', 'dir', 'dot', 'fir', 'fir_dps', 'ipow', 'maxx', 'mm', 'order', 'bin2dec', 'sos', 'tap', 'vecpermat', 'dwt1d', 'dwt2d', 'idwt1d', 'idwt2d', 'max', 'wave', 'wrap', 'viterbi'

headers = [
    'ID', 'CInstr', 'AssemblyInstr', 'ClockCycles', 'ExecutionTime', 'CC4CS'
]  # headers of the output csv

def loadCommands():
    # Gets the commands from cmds.json
    with open(projectPath + 'SLIDE-x-CORE/src/cmds.json', 'r') as file:
        content = load(file)
    return content


def loadCommandsJSON(filePath):
    # Gets the commands from cmds.json
    with open(filePath + '.json', 'r') as file:
        content = load(file)
    return content


def getFiles(topDir, extension):
    """This function returns the files with a specified extension
    that are contained in topDir.
    """
    return [
        f for f in listdir(topDir)
        if isfile(join(topDir, f)) and f.endswith(extension)
    ]


def num(s):
    try:
        return int(s)
    except ValueError:
        return float(s)

def calculateAffinity(inputPath, outputPath):
    """The function merges the content of the files obtained from the
    Frama-c phases. Then, it writes their content
    and the metric values in the "affinity.csv" file

    Args:
        Halsted.csv (string): path of the file obtained from
            the Halsted phase

        McCabe.csv (string): path of the file obtained from the
        McCabe phase

        Operands.csv (string): path of the file obtained from the
        Operands phase

        Reg_operands.csv (string): path of the file obtained from the
        Register Operands phase

        Control_exec_flow.csv (string): path of the file obtained from the
        Control Execution Flow phase

        Dtypes.csv (string): path of the file obtained from the
        Data Types phase
    """
    Halsted = inputPath + 'Halsted.csv'
    McCabe = inputPath + 'McCabe.csv'
    Operands = inputPath + 'Operands.csv'
    Reg_operands = inputPath + 'Reg_operands.csv'
    Control_exec_flow = inputPath + 'Control_exec_flow.csv'
    Dtypes = inputPath + 'Dtypes.csv'

    with open(Halsted) as HalstedFile, open(McCabe) as McCabeFile, open(Operands) as OperandsFile, open(
            Reg_operands) as Reg_operandsFile, open(Control_exec_flow) as Control_exec_flowFile, open(
            Dtypes) as DtypesFile, open(outputPath, "w") as outputFile:

        # Reads the content of the output files
        HalstedContent = reader(HalstedFile)
        McCabeContent = reader(McCabeFile)
        OperandsContent = reader(OperandsFile)
        Reg_operandsContent = reader(Reg_operandsFile)
        Control_exec_flowContent = reader(Control_exec_flowFile)
        DtypesContent = reader(DtypesFile)

        # Retrieves the headers of the output files
        HalstedHeaders = next(HalstedContent)
        McCabeHeaders = next(McCabeContent)
        OperandsHeaders = next(OperandsContent)
        Reg_operandsHeaders = next(Reg_operandsContent)
        Control_exec_flowHeaders = next(Control_exec_flowContent)
        DtypesHeaders = next(DtypesContent)

        # Headers of the output file
        headers = list(dict.fromkeys(
            HalstedHeaders + McCabeHeaders + OperandsHeaders + Reg_operandsHeaders + Reg_operandsHeaders + Control_exec_flowHeaders + DtypesHeaders))
        # print('headers:'+str(headers))

        """ Control Flow Complexity (CFC): Number of source lines that contain 
        loop structures (for, while) and condictional case ( if, case etc)  
        divided total source lines """
        headers.append('CFC')

        """I/O Ratio (IOR): Defined by the number of line containing I/O operations divided by the number of source 
        lines"""
        headers.append('IOR')

        """ Conditional Ratio (CR) : Difference between Control flow complexity (CFC) and Loop Ratio (LR) """
        headers.append('CR')

        """ Data ratio (DR): The number of declared variables of GPP compatible 
        type (e.g. integer, float, character, string, etc.) """
        headers.append('DR_char_string')
        headers.append('DR_int_real')
        headers.append('DR_gpp')

        """ Structure Ratio (STR): The sum of all class method and class member divided the number of source lines """
        headers.append('STR')

        """ LR: Number of source line that contain loop structures divided total source line """
        headers.append('LR')

        """The Bit Manipulation Ratio (BMR): Number of source lines that contain bit manipulation operations (e.g. 
        and, or, xor, etc) divided the total lines number
        
        &	bitwise AND
        |	bitwise inclusive OR
        ^	bitwise XOR (exclusive OR)
        <<	left shift
        >>	right shift
        ~	bitwise NOT (ones' complement) (unary)
        
        &=	bitwise AND assignment
        |=	bitwise inclusive OR assignment
        ^=	bitwise exclusive OR assignment
        <<=	left shift assignment
        >>=	right shift assignment
        """
        headers.append('BMR')

        """ Data Ratio bit (DR_bit): The number of declared variables of bit (e.g. integer, fixed point, float, 
        etc.) divided the total source lines number"""
        headers.append('DR_bit')

        """ The goal is to identify functionalities that significantly rely on operations that involve conditional 
        dependent control flows, complex data structures and complex I/O management."""
        headers.append('Agpp')

        """ The goal is to identify regular functionalities that significantly rely on operations that involve bit 
        manipulation. Therefore, in addition to some of the previous defined concepts (i.e. LR ) the following is 
        defined."""
        headers.append('Aasp')

        """The goal is to identify functionalities suitable to be executed by a DSP by considering those issues that 
        exploit the most relevant architectural features of such executor class: circular buffering, MAC operations, 
        and Harvard architecture."""
        # headers.append('Adsp')

        # Write Headers in the file
        resWriter = DictWriter(outputFile, headers)
        resWriter.writeheader()

        # Iterates thorugh the content of the files
        for c1, c2, c3, c4, c5, c6 in zip(HalstedContent, McCabeContent, OperandsContent, Reg_operandsContent,
                                          Control_exec_flowContent, DtypesContent):

            try:
                total_operators = num(float(c1[1]))  # Total Operators
                total_operands = num(float(c1[3]))  # total Operators

                sloc = num(float(c2[1]))  # SLOC

                dpStm = num(float(c2[2]))  # Decision Point
                ifStm = num(float(c2[4]))  # if
                loopStm = num(float(c2[5]))  # loop
                gotoStm = num(float(c2[6]))  # goto

                bitwise_AND = num(float(c4[13]))  # & bitwise AND
                bitwise_inclusive_OR = num(float(c4[14]))  # | bitwise inclusive OR
                bitwise_XOR = num(float(c4[23]))  # ^ bitwise XOR (exclusive OR)
                left_shift = num(float(c4[18]))   # << bitwise AND
                right_shift = num(float(c4[20]))  # >> bitwise AND
                bitwise_NOT = num(float(c4[24]))  # ~ bitwise NOT (ones' complement) (unary)
                bitwise_AND_assignment = num(float(c4[15]))  # &= bitwise AND assignment
                bitwise_inclusive_OR_assignment = num(float(c4[16]))  # |=	bitwise inclusive OR assignment
                bitwise_exclusive_OR_assignment = num(float(c4[17]))  # ^=	bitwise exclusive OR assignment
                left_shift_assignment = num(float(c4[19]))   # <<= left shift assignment
                right_shift_assignment = num(float(c4[21]))  # >>= right shift assignment

                structStm = num(float(c6[11]))  # struct
                charStm = num(float(c6[1]))  # char

                intRealStmShort = num(float(c6[2]))  # short
                intRealStmInt = num(float(c6[3]))  # int
                intRealStmDouble = num(float(c6[4]))  # double
                intRealStmFloat = num(float(c6[5]))  # float
                intRealStmLong = num(float(c6[6]))  # long

                intKStm8 = num(float(c6[12])) + num(float(c6[13]))  # (u)int8_t
                intKStm16 = num(float(c6[14])) + num(float(c6[15]))  # (u)int16_t
                intKStm32 = num(float(c6[16])) + num(float(c6[17]))  # (u)int32_t
                intKStm64 = num(float(c6[18])) + num(float(c6[19]))  # (u)int64_t
                intTargetStm = num(float(c6[20])) + num(float(c6[21]))  # TARGET_TYPE and TARGET_INDEX

                intKStm = intKStm8 + intKStm16 + intKStm32 + intKStm64 + intTargetStm  # stdint data types
                intRealStmGPP = intRealStmShort + intRealStmInt + intRealStmDouble + intRealStmFloat + intRealStmLong  # short, int, double, float, long
                intRealStmASP = intRealStmShort + intRealStmInt + intRealStmLong  # short, int, long

            except:
                sloc = 0
                total_operators = 0
                total_operands = 0

            # Calculates the values of the Affinity metric
            CFC = ((dpStm + ifStm + loopStm + gotoStm) / sloc) if sloc != 0 else 0
            LR = ((loopStm) / sloc) if sloc != 0 else 0
            IOR = 0  # TODO
            CR = CFC - LR
            DR_char_string = (charStm / total_operands) if total_operands != 0 else 0
            DR_int_real = ((intRealStmGPP + intKStm) / total_operands ) if total_operands != 0 else 0
            DR_gpp = DR_char_string + DR_int_real
            STR = (structStm / total_operands) if total_operands != 0 else 0  # TO CHECK
            BMR = ((bitwise_AND + bitwise_inclusive_OR + bitwise_XOR + left_shift + right_shift +
                    bitwise_NOT + bitwise_AND_assignment + bitwise_inclusive_OR_assignment +
                    bitwise_exclusive_OR_assignment + left_shift_assignment + right_shift_assignment) / total_operators) if total_operators != 0 else 0
            DR_bit = ((intRealStmASP + intKStm) / total_operands) if total_operands != 0 else 0

            # DSP
            # SCD, WCD, SHD, WHD, SMC, WMC, DR_dsp
            # Adsp = math.atan((2*math.pi*(SCD+WCD+SHD+WHD+SMC+WMC+LR+DR_dsp)))/(2*math.pi)

            A_gpp = math.atan(2 * math.pi * pow((IOR + CR + STR + DR_gpp), 2)) / 1.57  # Numerator: , Denominator: 2 * math.pi
            A_asp = math.atan(2 * math.pi * pow((LR + BMR + DR_bit), 2)) / 1.57   # Numerator: , Denominator: 2 * math.pi

            # Merges the data of the files
            # c1.extend(x for x in c2 if x not in c1)
            c1.extend(c2[1:])
            c1.extend(c3[1:])
            c1.extend(c4[1:])
            c1.extend(c5[1:])
            c1.extend(c6[1:])
            c1.append(str(CFC))
            c1.append(str(IOR))
            c1.append(str(CR))
            c1.append(str(DR_char_string))
            c1.append(str(DR_int_real))
            c1.append(str(DR_gpp))
            c1.append(str(STR))
            c1.append(str(LR))
            c1.append(str(BMR))
            c1.append(str(DR_bit))
            c1.append(str(A_gpp))
            c1.append(str(A_asp))
            # c1.append(str(A_dsp))

            # Writes it on a file
            resWriter.writerow(dict(zip(headers, c1)))

def calculateMetric(profPath, simPath, outputPath):
    """The function merges the content of the files obtained from the
    simulation and the profiling phases. Then, it writes their content
    and the metric values in the "cc4csValues.csv" file

    Args:
        cyclesFilename (string): path of the file obtained from
            the simulation phase
        statementsFilename (string): path of the file obtained from the
        profiling phase
    """
    with open(simPath) as cyclesFile, open(profPath) as statementsFile, open(outputPath, "w") as outputFile:

        # Reads the content of the output files
        simulationContent = reader(cyclesFile)
        profilingContent = reader(statementsFile)

        # Retrieves the headers of the output files
        profilingHeaders = next(simulationContent)
        simulationHeaders = next(profilingContent)

        # Headers of the output file
        headers = list(dict.fromkeys(profilingHeaders + simulationHeaders))
        # print('headers:'+str(headers))
        headers.append('cc4cs')
        headers.append('cc4ir')
        headers.append('cc4ssa')
        headers.append('cc4opt')

        # Write Headers in the file 
        resWriter = DictWriter(outputFile, headers)
        resWriter.writeheader()

        # Iterates thorugh the content of the files 
        for c1, c2 in zip(simulationContent, profilingContent):

            try:
                op1 = num(float(c1[1]))
                op2 = num(float(c2[1]))
                opGimple = num(float(c2[2]))
                opRelSSA = num(float(c2[3]))
                opOpt = num(float(c2[4]))
            except:
                op1 = 0
                op2 = 0
                opGimple = 0
                opRelSSA = 0
                opOpt = 0

            # Calculates the values of the metric
            if op2 != 0:
                cc4csValue = '%.3f' % (op1 / op2)
            else:
                cc4csValue = 0

            if opGimple != 0:
                cc4irValue = '%.3f' % (op1 / opGimple)
            else:
                cc4irValue = 0

            if opRelSSA != 0:
                cc4ssaValue = '%.3f' % (op1 / opRelSSA)
            else:
                cc4ssaValue = 0

            if opOpt != 0:
                cc4optValue = '%.3f' % (op1 / opOpt)
            else:
                cc4optValue = 0

            # Merges the data of the files
            # c1.extend(x for x in c2 if x not in c1)
            c1.extend(c2[1:])
            c1.append(str(cc4csValue))
            c1.append(str(cc4irValue))
            c1.append(str(cc4ssaValue))
            c1.append(str(cc4optValue))

            # Writes it on a file
            resWriter.writerow(dict(zip(headers, c1)))


# Print
# print(__file__)
# print("JOIN:"+join(dirname(__file__), '..'))
# print("Dirname:"+dirname(realpath(__file__)))
# print("ABSPATH:"+abspath(dirname(__file__)))
# print("ProjectPath:"+projectPath)

# Start the GUI
gui = GUI("SLIDE-x GUI", "600x450", True)  # Start GUI
#gui.fillMainWindow(projectPath + benchmarkFolder, gui.callback)
#gui.start()

for idxF, itemF in enumerate(functions):
    for idxM, itemM in enumerate(simulations):
        gui.function = itemF
        
        gui.results = projectPath + 'SLIDE-x-AGGR/KERNEL_DECIMAL_LEON3'
        # gui.results = projectPath + 'SLIDE-x-AGGR-RESULTS/KERNEL_INT'
        gui.micro = itemM

        cmds = loadCommands()

        # directory containing the source file of the functions
        source = projectPath + benchmarkFolder + gui.function + '/'
        funSrc = source + filess[gui.micro]

        # Creates the directory in which store the results for specific function
        if not isdir(gui.results + '/' + gui.function):
            makedirs(gui.results + '/' + gui.function)

        gui.results = gui.results + '/' + gui.function

        inputsGen = InputsGenerator(funSrc, gui.function, gui.micro)

        cmdMan = CommandsManager(funSrc, configsrc, gui.results, '')

        InputGen = 1
        GCovExe = 1
        FramaCExe = 1
        SimExe = 1

        # Start whole execution time
        start = timer()

        for target, index in zip(targets, indexes):

            print(" #### processor: ", gui.micro)
            print(" #### function: ", gui.function)
            print(" #### type: ", target)

            inputsPath = gui.results + "/includes"

            if isdir(inputsPath):
                rmtree(inputsPath)

            # Start Input Gen Execution time
            startInputGen = timer()

            if InputGen:
                """
                Input
                """

                print("\n Input Generation...", end="")

                # Generates the header files, i.e. the inputs of the function
                inputsGen.generate(inputsPath, target, index)
                print("Done!")

                print("\n Collecting INPUTS...\n", end=" ")

                if os.path.exists(gui.results + "/inputResume.csv"):
                    os.remove(gui.results + "/inputResume.csv")

                # Builds a parser to collect Inputs
                parser = Parser(gui.results + "/inputResume.csv", Parser.inputParser)

                # Creates a compact representation of the inputs
                parser.inputParser(gui.results + "/inputResume.csv", gui.results + "/includes")

                shutil.copyfile(projectPath + benchmarkFolder + gui.function + '/parameters.json',
                                join(gui.results, 'parameters.json'))

                # Executes commands needed to include configuration files of the microprocessors
                configcmd = cmds['Configuration'].get(gui.micro)
                if configcmd:
                    cmdMan.executeCommand(cmdMan.expandCommand(configcmd, configsrc, gui.results))

                print("\n #### OPT: ", configcmd)

                print("Done!")

            # Stop Input Generation Execution time
            endInputGen = timer()
            InputGenTime = endInputGen - startInputGen

            # Start FramaC Execution time
            startFramaC = timer()

            if FramaCExe:
                """
                Frama-C
                """

                print("\n Collecting execution statistics using frama-c... \n\n", end="")

                # Retrieves code metrics using FramaC
                cmdMan.executeCommandSet(cmds['FramaC'], inputsPath, 'files_framac')

                # Builds a parser to collect Halsted statistics
                if os.path.exists(gui.results + "/Halsted.csv"):
                    os.remove(gui.results + "/Halsted.csv")

                parser = Parser(gui.results + "/Halsted.csv", Parser.getFramaRow)
                parser.framaParser(gui.results + "/files_framac", 1)
                print("Halsted Done!")

                # Builds a parser to collect McCabe statistics
                if os.path.exists(gui.results + "/McCabe.csv"):
                    os.remove(gui.results + "/McCabe.csv")

                parser.outputPath = gui.results + "/McCabe.csv"
                parser.framaParser(gui.results + "/files_framac", 0)
                print("McCabe Done!")

                # Builds a parser to collect Affinity (Control Exec Flow) statistics
                if os.path.exists(gui.results + "/Control_exec_flow.csv"):
                    os.remove(gui.results + "/Control_exec_flow.csv")

                parser.outputPath = gui.results + "/Control_exec_flow.csv"
                parser.framaParserCEF(gui.results + "/files_framac")
                print("Control Exec Flow Done!")

                # Builds a parser to collect Affinity (Operands) statistics
                if os.path.exists(gui.results + "/Operands.csv"):
                    os.remove(gui.results + "/Operands.csv")

                parser.outputPath = gui.results + "/Operands.csv"
                parser.framaParserOp(gui.results + "/files_framac")
                print("Operands Done!")

                # Builds a parser to collect Affinity (Register Operands) statistics
                if os.path.exists(gui.results + "/Reg_operands.csv"):
                    os.remove(gui.results + "/Reg_operands.csv")

                parser.outputPath = gui.results + "/Reg_operands.csv"
                parser.framaParserRegOp(gui.results + "/files_framac",
                                        projectPath + benchmarkFolder + gui.function + '/')
                print("Register Operands Done!")

                # Builds a parser to collect Affinity (Data Types) statistics
                if os.path.exists(gui.results + "/Dtypes.csv"):
                    os.remove(gui.results + "/Dtypes.csv")

                parser.outputPath = gui.results + "/Dtypes.csv"
                parser.framaParserDataTypes(gui.results + "/files_framac")
                print("Data Types Done!")

                print("\n Calculating Affinity...", end=" ")

                if os.path.exists(gui.results + "/Affinity.csv"):
                    os.remove(gui.results + "/Affinity.csv")

                # Generates Affinity file
                calculateAffinity(gui.results + '/', "Affinity.csv")

                print("Done!")

            # End FramaC Execution time
            endFramaCCommand = timer()
            framaCExeTime = endFramaCCommand - startFramaC

            for idxOpt, itemOpt in enumerate(optFlagsArr):
                optFlags = itemOpt
                print("Optimization Flags:" + optFlags)
                optNameFolder = optNameFolderArr[idxOpt]

                cmdMan.OptimizationFlag = optFlags

                # Start Gcov Execution time
                startProfiling = timer()

                if GCovExe:
                    """
                    Profiling: Gets the number of executed C statements:
                    1. retrieves the commands for profiling the function from cmds.json
                    2. for each couple (input, function) is executed on the host
                    3. the number of executed c statements is collected for each execution
            
                    print("\n Retrieving executed C statements on the host platform... \n\n", end = " ")
            
                    if os.path.exists(gui.results + "/cStatements.csv"):
                        os.remove(gui.results + "/cStatements.csv")
            
                    parser = Parser(gui.results + "/cStatements.csv", Parser.gcovParser, ['id', 'cInstr']) # creates the output file and binds the parser
            
                    cmdMan.executeCommandSet(cmds['Profiling'], inputsPath, 'files_gcov', parsingFunction = parser.run)
            
                    parser
                    print("GCOV Statement Done!")
                    """

                    print("\n Retrieving executed C Gimple on the host platform... \n\n", end=" ")

                    if os.path.exists(gui.results + "/cStatements.csv"):
                        os.remove(gui.results + "/cStatements.csv")

                    parser = Parser(gui.results + "/cStatements.csv", Parser.gcovGimpleParser,
                                    ['id', 'cInstr', 'cGimple', 'cReleaseSSA', 'cOptimized', 'LineExe', 'BranchesExe', 'OnceEe',
                                     'CallExe'])  # creates the output file and binds the parser

                    cmdMan.executeCommandSet(cmds['Profiling'], inputsPath, 'files_gcov', parsingFunction=parser.run)

                    print("GCOV Gimple Done!")

                # End Gcov Execution time
                endProfiling = timer()
                profilingTime = endProfiling - startProfiling

                # Start Sim Execution time
                startCommands = timer()

                if SimExe:
                    """
                    Simulation
                    """

                    if gui.micro == 'Leon3':

                        print("\n Simulation on the LEON3 target platform...", end="\n\n")

                        if os.path.exists(gui.results + "/clockCycles.csv"):
                            os.remove(gui.results + "/clockCycles.csv")

                        parser = Parser(gui.results + "/clockCycles.csv", Parser.PARSERS.get(gui.micro),
                                        ['id', 'clockCycles', 'assemblyInstr', 'cacheHit', 'cacheHitInstr', 'cacheHitData', 'MOPS',
                                         'MIPS', 'MFLOPS'])

                        cmdMan.executeCommandSet(cmds[gui.micro], inputsPath, 'files', parsingFunction=parser.run)
                        print("ISS Performance Simulation Done!")

                    elif gui.micro == 'RiscV':

                        print("\n Simulation on the RiscV target platform...", end="\n\n")

                        if os.path.exists(gui.results + "/clockCycles.csv"):
                            os.remove(gui.results + "/clockCycles.csv")

                        parser = Parser(gui.results + "/clockCycles.csv", Parser.PARSERS.get(gui.micro),
                                        ['id', 'clockCycles', 'assemblyInstr', 'Cache'])

                        cmdMan.executeCommandSet(cmds[gui.micro], inputsPath, 'files', parsingFunction=parser.run)
                        print("ISS Performance Simulation Done!")

                    elif gui.micro == 'Bambu':

                        print("\n Simulation on the HW target platform...", end="\n\n")

                        if os.path.exists(gui.results + "/clockCycles.csv"):
                            os.remove(gui.results + "/clockCycles.csv")

                        parser = Parser(gui.results + "/clockCycles.csv", Parser.PARSERS.get(gui.micro),
                                        ['id', 'clockCycles'])

                        cmdMan.executeCommandSetBambu(cmds[gui.micro], inputsPath, parsingFunction=parser.run)
                        print("Done!")

                        cmdMan.movefilesBambuNoGUI(gui.function, target, gui.results)
                        print("Done!")

                    else:

                        print("\n Simulation on the SW target platform...", end="\n\n")

                        if os.path.exists(gui.results + "/clockCycles.csv"):
                            os.remove(gui.results + "/clockCycles.csv")

                        parser = Parser(gui.results + "/clockCycles.csv", Parser.PARSERS.get(gui.micro),
                                        ['id', 'clockCycles', 'assemblyInstr'])

                        cmdMan.executeCommandSet(cmds[gui.micro], inputsPath, 'files', parsingFunction=parser.run)
                        print("ISS Performance Simulation Done!")

                    if gui.micro != '8051' and gui.micro != 'Bambu':

                        if os.path.exists(gui.results + "/Size.csv"):
                            os.remove(gui.results + "/Size.csv")

                        parser = Parser(gui.results + "/Size.csv", Parser.getSizeRow)
                        parser.sizeParser(gui.results + "/files")
                        print("Size Done!")

                    elif gui.micro == 'Bambu':

                        print("Size Done!")

                    else:

                        if os.path.exists(gui.results + "/Size.csv"):
                            os.remove(gui.results + "/Size.csv")

                        parser = Parser(gui.results + "/Size.csv", Parser.getSizeRow)
                        parser.size8051Parser(gui.results + "/files")
                        print("Size Done!")

                endCommands = timer()
                simTime = endCommands - startCommands

                if (SimExe):
                    """
                    CC4CS
                    """

                    print("\n Calculating cc4s...", end=" ")

                    if os.path.exists(gui.results + "/cc4csValues.csv"):
                        os.remove(gui.results + "/cc4csValues.csv")

                    # Generates CC4CS file
                    calculateMetric(gui.results + "/cStatements.csv", gui.results + "/clockCycles.csv", "cc4csValues.csv")
                    print("Done!")

                # Creates the directory in which store the results
                index = 0
                subfolder_names = [gui.micro, target, optNameFolder, matrixFolderName]
                for x in subfolder_names:
                    if index == 0:
                        if not isdir(x):
                            makedirs(x)
                        dirs = x + '/'
                        # print(dirs)
                        index = 1
                    else:
                        dirs = dirs + x
                        # print(dirs)
                        if not isdir(dirs):
                            makedirs(dirs)
                        dirs = dirs + '/'
                        # print(dirs)

                print("\n #### Ended! #### \n\n Results stored in ", gui.results + '/' + dirs)

                # End whole execution time
                end = timer()
                totTime = end - start

                # Execution Time Report
                names = ['InputGenerationTime', 'ProfilingTime', 'SimulationTime', 'FramaCExecutionTime', 'TotalExecutionTime']
                scores = [InputGenTime, profilingTime, simTime, framaCExeTime, totTime]
                # np.savetxt(gui.results + '/' + dirs + '/CC4CSFrameworkExecutionTime.csv', [p for p in zip(names, scores)], delimiter=',', fmt='%s')
                np.savetxt(gui.results + '/CC4CSFrameworkExecutionTime.csv', [p for p in zip(names, scores)], delimiter=',',
                           fmt='%s')

                print("\n Input Generation Time: ", InputGenTime)  # Time in seconds, e.g. 5.38091952400282
                print(" Profiling Time: ", profilingTime)
                print(" Simulation Time: ", simTime)
                print(" FramaC Execution Time: ", framaCExeTime)
                print(" Total Execution Time: ", totTime, "\n")

                files = getFiles('.', '.csv') + getFiles('.', '.txt')
                for file in files:
                    if (file == "cc4csValues.csv" or file == "Size.csv" or file == "inputResume.csv" or file == "Affinity.csv" or
                            file == "CC4CSFrameworkExecutionTime.csv" or file == '*.txt'):
                        # move(file, join(target, file))
                        shutil.copyfile(file, join(dirs, file))
                    elif file.endswith('.txt'):
                        shutil.move(file, join(dirs, file))

                if os.path.exists("cc4csValues.csv"):
                    os.remove("cc4csValues.csv")

                if os.path.exists("cStatements.csv"):
                    os.remove("cStatements.csv")

                if os.path.exists("clockCycles.csv"):
                    os.remove("clockCycles.csv")

                if os.path.exists("Size.csv"):
                    os.remove("Size.csv")

                # if os.path.exists("inputResume.csv"):
                #     os.remove("inputResume.csv")

                # if os.path.exists(gui.results + "/Affinity.csv"):
                #     os.remove(gui.results + "/Affinity.csv")

                if os.path.exists("Halsted.csv"):
                    os.remove("Halsted.csv")

                if os.path.exists("McCabe.csv"):
                    os.remove("McCabe.csv")

                if os.path.exists(gui.results + "/Control_exec_flow.csv"):
                    os.remove(gui.results + "/Control_exec_flow.csv")

                if os.path.exists(gui.results + "/Operands.csv"):
                    os.remove(gui.results + "/Operands.csv")

                if os.path.exists(gui.results + "/Reg_operands.csv"):
                    os.remove(gui.results + "/Reg_operands.csv")

                if os.path.exists(gui.results + "/Dtypes.csv"):
                    os.remove(gui.results + "/Dtypes.csv")

                if os.path.exists("CC4CSFrameworkExecutionTime.csv"):
                    os.remove("CC4CSFrameworkExecutionTime.csv")

                # if os.path.exists("parameters.json"):
                #    os.remove("parameters.json")

                # rmtree("includes/")
                # rmtree("files/")
                # rmtree("files_gcov/")

            # rmtree("files_framac/")
            # rmtree("filesISS/")
