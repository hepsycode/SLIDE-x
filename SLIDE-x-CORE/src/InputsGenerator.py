from re import search, findall, match, compile
from random import uniform, randint
import os
from os import makedirs, chdir, rename
from os.path import abspath, isdir, dirname
from itertools import product
from json import load
from shutil import rmtree

class InputsGenerator:
    def __init__(self, filePath, functionName, micro):
        self.filePath = filePath
        self.functionName = functionName
        # List of function variable definitions
        self.ranges, self.args = self.getParameters(functionName, micro)
        # List containing the typedef of a scalar
        # ("TARGET_INDEX" or "TARGET_TYPE") and its name 
        self.scalars = self.getScalars()
        self.arrays = self.getArrays()


    def getParameters(self, function, micro):
        benchmark = dirname(self.filePath)
        with open(benchmark + '/parameters.json', 'r') as file:
            content = load(file)
        return content[micro], content['args']

    def isIndex(self, var):
         if "TARGET_INDEX" in var:
            return True
         return False

    def isArray(self, var):
        r = compile(r'\[\w+\](\[\w+\])?')
        matching = r.search(var)

        if matching:
            return True

        return False

    def getScalars(self):
        """ Keeps in a list all the definition of scalar variables
        """
        return [x for x in self.args if not self.isArray(x)]

    def getArrays(self):
        """ Keeps in a list all the definition of the arrays
        """
        return [x for x in self.args if self.isArray(x)]

    def expandRanges(self, varRange, scalarType):
        # Retrieves the values included in the range and coverts them from int to string
        rangeValues = list(map(int, findall(r'-?\d+', varRange)))

        # Unpacks the values of the list
        minValue, maxValue, numValues = rangeValues

        # Creates a random values list of size numValues in the range of [minValue, maxValue]
        return [round(uniform(minValue, maxValue), 3) for _ in range(numValues)] if scalarType == "float" else \
            [round(randint(minValue, maxValue), 3) for _ in range(numValues)]

    def generateValues(self, currentype, indextype):
        # Multidimensional array contaning all the generated values for scalar variables
        values = []

        for var in self.scalars:
            varType, varName = var.split(" ")
            # Checks if the current scalar is an index or not
            scalarType = indextype if self.isIndex(var) else currentype
            varRange = self.ranges[scalarType][varName]

            scalarList = self.expandRanges(varRange, scalarType)
            values.append(scalarList)

        return values

    def cartesianProduct(self, lst):
        if len(lst) == 1:
            return lst[0]
        return list(product(*lst))

    def createHeaders(self, currentype, indextype):
        # Multidimensinal array containing a list for each scalar
        expandedScalars = self.generateValues(currentype, indextype)
        idxFile = 0

        for i, combination in enumerate(self.cartesianProduct(expandedScalars)):
            # If the current combination is represented just by an int, then it means that the execution
            # involves just a scalar. However, the second loop requires an iterable object to take place.
            # So, the int is converted in an single dimensioned array of one element
            if isinstance(combination, int): combination = [combination]
            # Arrays to be generated for the current combination
            currentArrays = self.arrays
            # For each combination will be generated 10 random array
            # for index in range(10):
            dirName = "values_" + str(idxFile)

            # Creates the directory containing the header       
            makedirs(dirName)

            # Creates the header file for the current combination
            with open("values.h", "w+") as fdHeader:
                # Variable containing the code to define a macron in C
                macroDef = "#ifndef VALUES\n#define VALUES\n"
                fdHeader.write(macroDef)

                # Writes all the scalars and their corresponding value in the header file
                for idxScalar, (currentScalar, scalarValue) in enumerate(zip(self.scalars, combination)):
                    # Gets the name of the variable and removes the type
                    _, scalarName = currentScalar.split(" ")

                    # Writes a different variable definition according to the variable function
                    if self.isIndex(currentScalar):
                        fdHeader.write("\tenum{" + scalarName + " = " + str(scalarValue) + "};\n")
                        # Assigns the current value of the size to the corresponding array
                        currentArrays = [x.replace(scalarName, str(scalarValue)) for x in currentArrays]
                    else:
                        fdHeader.write("\t" + currentype + " " + scalarName + " = " + str(scalarValue) + ";\n")

                # Writes all the arrays in the header file of the current combination
                for idxArray, array in enumerate(currentArrays):
                    # Gets the array definition from the arrays vector
                    arrayDef = self.arrays[idxArray]
                    # Gets the name of the array
                    _, arrayName = arrayDef.split(" ")
                    # Retrieves the specified range from the parameters.json
                    varRange = self.ranges[currentype][arrayName]

                    # Extracts the integers from the range
                    sizes = findall(r'\d+', array)
                    sizes = list(map(int, sizes))

                    flag = True
                    if len(sizes) == 1:
                        flag = False
                        sizes.insert(0, 1)

                    # Unpacks values contained in the list
                    frstSize, scndSize = sizes

                    result = ""
                    for fidx in range(frstSize):
                        lst = self.expandRanges(varRange + ';' + str(scndSize), currentype)
                        # Stringifies the just generated array
                        strArray = ", ".join(map(str, lst))
                        strArray = '{' + strArray + '}'
                        # Concatenates it to the resulting array
                        result += strArray

                    # Inserts commas between single dimensioned array
                    result = result.replace('}{', '},{')

                    # Inserts the curly brackets at the sides of the array if the latter has size 
                    # greater than 2 
                    if flag: result = '{' + result + '};\n'
                    else: result = result + ';\n'

                    # Writes the resulting array in the header file
                    fdHeader.write("\t" + currentype + " " + arrayName + " = " + result)

                fdHeader.write("#endif")
            # Moves the file in the created directory  
            rename("values.h", dirName + "/values.h")
            
            idxFile += 1

        # Returns to the previous directory
        chdir('..')

    def replace(self, filename, regexStr, replacementStr):
        """This function replaces a line in a file that matches
        the specified regular expression
            Args:
                filename (string): the name of the file to be opened
                regexStr (string): a regular expression
                replacementStr (string): the string to write in the file
        """
        with open(os.path.join(self.filePath, filename), 'r') as file:
            lines = file.readlines()

        for i, line in enumerate(lines):
            # TODO: rise an exception if this is never accessed
            if match(regexStr, line):
                lines[i] = replacementStr

        with open(filename, "w") as file:
            file.writelines(lines)

    def generate(self, outputPath, target, index):
        self.replace(
            self.filePath, r'typedef\s[a-z0-9_\s]+TARGET_TYPE',
            "typedef " + target + " TARGET_TYPE;\n"
        )

        self.replace(
            self.filePath, r'typedef\s[a-z0-9_\s]+TARGET_INDEX',
                "typedef " + index + " TARGET_INDEX;\n"
        )

        # Creates the directory containing the headers 
        if isdir(outputPath):
            rmtree(outputPath)

        makedirs(outputPath)
        chdir(outputPath)
        self.createHeaders(target, index)
        chdir("..")
