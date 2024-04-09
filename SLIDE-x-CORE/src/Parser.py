import subprocess
from os.path import isdir, join, splitext
from os import listdir
from re import search, findall
from csv import DictWriter, reader
from os.path import isfile
import re


def parseline(reg_exp, line):
    for key, rx in reg_exp.items():
        match = rx.search(line)
        if match:
            return key, match.group(key)
    return None, None

reg_exp_halsted = {
    'Total_operators': re.compile(r'\s*Total\s*operators\s*:\s*(?P<Total_operators>.+)'),
    'Distinct_operators': re.compile(r'\s*Distinct\s*operators\s*:\s*(?P<Distinct_operators>.+)'),
    'Total_operands': re.compile(r'\s*Total_operands\s*:\s*(?P<Total_operands>.+)'),
    'Distinct_operands': re.compile(r'\s*Distinct\s*operands\s*:\s*(?P<Distinct_operands>.+)'),
    'Program_length': re.compile(r'\s*Program\s*length\s*:\s*(?P<Program_length>.+)'),
    'Vocabulary_size': re.compile(r'\s*Vocabulary\s*size\s*:\s*(?P<Vocabulary_size>.+)'),
    'Program_volume': re.compile(r'\s*Program\s*volume\s*:\s*(?P<Program_volume>.+)'),
    'Effort': re.compile(r'\s*Effort\s*:\s*(?P<Effort>.+)'),
    'Program_level': re.compile(r'\s*Program\s*level\s*:\s*(?P<Program_level>.+)'),
    'Difficulty_level': re.compile(r'\s*Difficulty\s*level\s*:\s*(?P<Difficulty_level>.+)'),
    'Time_to_implement': re.compile(r'\s*Time\s*to\s*implement\s*:\s*(?P<Time_to_implement>.+)'),
    'Bugs_delivered': re.compile(r'\s*Bugs\s*delivered\s*:\s*(?P<Bugs_delivered>.+)'),
}

reg_exp_McCabe = {
    'Sloc': re.compile(r'\s*Sloc\s*=\s*(?P<Sloc>.+)'),
    'Decision_point': re.compile(r'\s*Decision\s*point\s*=\s*(?P<Decision_point>.+)'),
    'Global_variables': re.compile(r'\s*Global\s*variables\s*=\s*(?P<Global_variables>.+)'),
    'If': re.compile(r'\s*If\s*=\s*(?P<If>.+)'),
    'Loop': re.compile(r'\s*Loop\s*=\s*(?P<Loop>.+)'),
    'Goto': re.compile(r'\s*Goto\s*=\s*(?P<Goto>.+)'),
    'Assignment': re.compile(r'\s*Assignment\s*=\s*(?P<Assignment>.+)'),
    'Exit_point': re.compile(r'\s*Exit\s*point\s*=\s*(?P<Exit_point>.+)'),
    'Function': re.compile(r'\s*Function\s*=\s*(?P<Function>.+)'),
    'Function_call': re.compile(r'\s*Function\s*call\s*=\s*(?P<Function_call>.+)'),
    'Pointer_dereferencing': re.compile(r'\s*Pointer\s*dereferencing\s*=\s*(?P<Pointer_dereferencing>.+)'),
    'Cyclomatic_complexity': re.compile(r'\s*Cyclomatic\s*complexity\s*=\s*(?P<Cyclomatic_complexity>.+)'),
    'Syntactically_reachable_functions': re.compile(r'\s*Syntactically\s*reachable\s*functions\s*=\s*(?P<Syntactically_reachable_functions>\s*.[0-9]*)'),
    'Semantically_reached_functions': re.compile(r'\s*Semantically.reached.functions.=.(?P<Semantically_reached_functions>.+)'),
    'Coverage_estimation': re.compile(r'\s*Coverage.estimation.=.(?P<Coverage_estimation>.+)'),
    'Main_statements': re.compile(r'\s*main:\s*(?P<Main_statements>\s*.[0-9]*)'),
}

class Parser:
    def __init__(self, outputPath, parsingFunction, headers = []):
        self.outputPath = outputPath
        self.parsingFunction = parsingFunction
        self.headers = headers

    def writeFile(self, row, outputPath=None):
        if outputPath is None:
            outputPath = self.outputPath

        # output file access mode
        flag = 'w'
        if isfile(outputPath):
            flag = 'a'

        # Creates the output file 
        with open(outputPath, flag) as outFile:
            wrt = DictWriter(outFile, fieldnames = self.headers)

            # If headers is a field of the object, then they are written on the output file
            if flag == 'w':
                wrt.writeheader()

            wrt.writerow(row)

    def run(self, parserInput, values = []):
        # Executes the parsing function 
        results = self.parsingFunction(parserInput)
        values.extend(results)
        # Writes the values
        self.writeFile({key:value for key, value in zip(self.headers, values)})

    """ This functions extracts the needed information from InputResume output file
    """

    def inputParser(self, outputPath, inputsPath):
        dirs = [f for f in listdir(inputsPath) if isdir(join(inputsPath, f))]

        # Gets the headers from the output file
        self.headers = ["inputName"]
        filesPath = inputsPath + "/values_0/values.h"
        params = [filesPath, 2, None, r'[a-z\[\]]+\s=']

        tempHeaders = map(str.strip, self.getHeaders(params))
        self.headers.extend(tempHeaders)

        for dirName in dirs:
            filesPath = inputsPath + '/' + dirName + '/values.h'
            params = [filesPath, 2, None]
            self.getInputsRow(outputPath, params, values = dirName)

    def getHeaders(self, args, pascalCase=False):
        """ This functions extracts the needed information from a FramaC output file
        """
        filePath, idxStart, idxEnd, regex = args
        headers = []

        with open(filePath, 'r') as fp:
            lines = fp.readlines()[idxStart:idxEnd]
            for ln in lines:
                key = search(regex, ln)

                if key:
                    # Removes the last char (e.g. :)
                    key = key.group()[:-1]
                    # Puts the string in pascal case
                    if pascalCase: key = ''.join(x for x in key.title() if not x.isspace())

                    headers.append(key)

        return headers

    def getInputsRow(self, outputPath, args, values ):
        filePath, idxStart, idxEnd = args
        with open(filePath, 'r') as fp:
            lines = fp.readlines()[idxStart:idxEnd]
            # Removes the last element from the array that is a useless line
            lines = lines[:-1]
            content = [values]

            for ln in lines:
                value = ln.split('=')[1]
                value = value.replace('=', '').strip()
                value = value.replace(';', '')
                occurrences = value.count('}')
                if occurrences <= 1:
                    value = value.replace('}', '')
                else:
                    value = value.replace('{', '[')
                    value = value.replace('}', ']')

                content.append(value)

        self.writeFile({key:value for key, value in zip(self.headers, content)}, outputPath)

    """ This functions extracts the needed information from GCOV output file
    """

    def gcovParser(filePath):
        """This function analyzes the output of GCov profiler

        Args:
            txtfilePath (string): the name of the .c.gcov file.

        Returns:
            int: the number of executed C statements
        """
        result = 0
        stringB = 'block'

        with open(filePath + ".c.gcov", "r") as file:
            for line in file:
                if not (stringB in line):
                    number = line.split(':')[0]
                    number = number.strip()

                    if number.isdigit():
                        result += int(number)

        return [result]

    def gcovGimpleParser(filePath):
        """This function analyzes the output of GCov profiler

        Args:
            txtfilePath (string): the name of the .c.gcov file.

        Returns:
            int: the number of executed C statements
        """
        results = []
        stringB = 'block'

        tmp = 0
        gimpleIRCount = 0
        ssaReleaseIRCount = 0
        optimizedIRCount = 0

        with open(filePath + '.c.gcov', 'r') as file:
            for line in file:
                if not (stringB in line):
                    # number = line.split('*:' if '*:' in line else ':')[0]
                    number = line.split(':')[0] # if re.match(r'^(\s*)?(\d+):(.*)', line) else line.split("*:")[0]
                    number = number.strip()

                    if number.isdigit():
                        tmp += int(number)
                        # print('C Statement:' + number)
                        # print('Total C Statement:' + str(tmp))
                        match = re.search(r'^\s*\d+:\s+(\d+)', line)

                        if match:
                            # numberLine = int(match.group(1))
                            # print('Line Number:' + str(numberLine))
                            occLines = filePath.rsplit('/', 1)[1] + '.c:' + str(match.group(1))
                            #print('String:' + occLines)

                            with open(filePath + '.c.006t.gimple', 'r') as execFile:
                                gimpleIRCounttmp = sum(line.count(occLines) for line in execFile)
                            if gimpleIRCounttmp == 0:
                                gimpleIRCount += int(number)
                            else:
                                gimpleIRCount += int(number) * gimpleIRCounttmp
                            # print('gimpleIRCount:' + str(gimpleIRCount) + '\n')

                            with open(filePath + '.c.051t.release_ssa', 'r') as execFile:
                                ssaReleaseIRCounttmp = sum(line.count(occLines) for line in execFile)
                            if ssaReleaseIRCounttmp == 0:
                                ssaReleaseIRCount += int(number)
                            else:
                                ssaReleaseIRCount += int(number) * ssaReleaseIRCounttmp
                            # print('ssaReleaseIRCount:' + str(ssaReleaseIRCount) + '\n')

                            with open(filePath + '.c.244t.optimized', 'r') as execFile:
                                optimizedIRCounttmp = sum(line.count(occLines) for line in execFile)
                            if optimizedIRCounttmp == 0:
                                optimizedIRCount += int(number)
                            else:
                                optimizedIRCount += int(number) * optimizedIRCounttmp
                            # print('optimizedIRCount:' + str(optimizedIRCount) + '\n')

        if tmp: results.append(tmp)
        if gimpleIRCount: results.append(gimpleIRCount)
        if ssaReleaseIRCount: results.append(ssaReleaseIRCount)
        if optimizedIRCount: results.append(optimizedIRCount)

        with open(filePath.rsplit('/', 1)[0] + "/gcovOutput.txt", "r") as execFile2:
            content2 = execFile2.read()
            lineExe = re.findall(r'Lines executed\s*:\s*([\d.]+)% of', content2)
            if lineExe: results.append(lineExe[0])
            else: results.append('0')
            #print('lineExe' + lineExe[0])
            branchesExe = re.findall(r'Branches executed\s*:\s*([\d.]+)% of', content2)
            if branchesExe: results.append(branchesExe[0])
            else: results.append('0')
            #print('branchesExe' + branchesExe[0])
            onceExe = re.findall(r'Taken at least once\s*:\s*([\d.]+)% of', content2)
            if onceExe: results.append(onceExe[0])
            else: results.append('0')
            #print('onceExe' + onceExe[0])
            callExe = re.findall(r'Calls executed\s*:\s*([\d.]+)% of', content2)
            if callExe: results.append(callExe[0])
            else: results.append('0')
            #print('callExe' + callExe[0])

        return results

    """ This functions extracts the needed information from a FramaC output file
    """

    def getFramaRowBackup(args):
        filePath, idxStart, idxEnd = args
        content = []

        with open(filePath, 'r') as fp:
            lines = fp.readlines()[idxStart:idxEnd]
            for ln in lines:
                if ln.find(':') != -1:
                    value = ln.split(':')[1]
                elif ln.find('=') != -1:
                    value = ln.split('=')[1]
                if value:
                    content.append(value)

        return content

    def getFramaRow(args):
        filePath, idxStart, idxEnd, reg_exp = args
        content = []

        with open(filePath, 'r') as fp:
            lines = fp.readlines()[idxStart:idxEnd]
            for ln in lines:
                key, match = parseline(reg_exp, ln)

                if key:
                    if "%" in match:
                        match = match.replace("%", "")
                    content.append(match)

        return content

    def framaParserOLD(self, inputsPath, analysisFlag):
        dirs = [f for f in listdir(inputsPath) if isdir(join(inputsPath, f))]
        # Gets the headers from the output file
        self.headers = ["inputName"]

        # Halsted output parsing
        if analysisFlag:
            idxStart = 3
            fileName = "Halsted.txt"
            idxEnd = 17
            # Parameters for the Halsted file
            filesPath = inputsPath + "/values_0/" + fileName
            params = [filesPath, idxStart, idxEnd, r'([a-zA-Z_]+\s?)*:']
        else:
            # McCabe output parameters
            idxStart = 25 # 25
            idxEnd = 37 # 37
            fileName = "McCabe.txt"
            filesPath = inputsPath + "/values_0/" + fileName
            params = [filesPath, idxStart, idxEnd, r'([a-zA-Z_]+\s)+=']  # (\w+\s)+=

        self.headers.extend(self.getHeaders(params, pascalCase=True))

        for dirName in dirs:
            filesPath = inputsPath + '/' + dirName + '/' + fileName
            params = [filesPath, idxStart, idxEnd]

            self.run(params, values=[dirName])

    def framaParser(self, inputsPath, analysisFlag):
        dirs = [f for f in listdir(inputsPath) if isdir(join(inputsPath, f))]
        # Gets the headers from the output file
        self.headers = ["inputName"]

        if analysisFlag:
            # Halsted output parsing

            idxStart = 2
            fileName = "Halsted.txt"
            idxEnd = None
            # Parameters for the Halsted file
            filesPath = inputsPath + "/values_0/" + fileName
            params = [filesPath, idxStart, idxEnd, reg_exp_halsted]
        else:
            # McCabe output parameters

            idxStart = 2  # 25
            idxEnd = None  # 37
            fileName = "McCabe.txt"
            filesPath = inputsPath + "/values_0/" + fileName
            params = [filesPath, idxStart, idxEnd, reg_exp_McCabe]  # (\w+\s)+=

        self.headers.extend(self.getHeadersFrama(params, pascalCase=True))

        for dirName in dirs:
            filesPath = inputsPath + '/' + dirName + '/' + fileName
            if analysisFlag:
                params = [filesPath, idxStart, idxEnd, reg_exp_halsted]
            else:
                params = [filesPath, idxStart, idxEnd, reg_exp_McCabe]
            self.run(params, values=[dirName])

    def framaParserCEF(self, inputsPath):
        dirs = [f for f in listdir(inputsPath) if isdir(join(inputsPath, f))]
        # Gets the headers from the output file
        self.headers = ['inputName', 'For', 'While', 'Switch', 'Case', 'Break', 'Continue', 'Do']
        fileName = "Halsted.txt"
        for dirName in dirs:
            filesPath = inputsPath + '/' + dirName + '/' + fileName
            with open(filesPath, "r") as execFile:
                content = execFile.read()

                forRes = findall(r'\s*for\s*:\s*(?P<forRes>.+)', content)
                whileRes = findall(r'\s*while\s*:\s*(?P<whileRes>.+)', content)
                switchRes = findall(r'\s*switch\s*:\s*(?P<switchRes>.+)', content)
                caseRes = findall(r'\s*case\s*:\s*(?P<caseRes>.+)', content)
                breakRes = findall(r'\s*break\s*:\s*(?P<breakRes>.+)', content)
                continueRes = findall(r'\s*continue\s*:\s*(?P<continueRes>.+)', content)
                doRes = findall(r'\s*do\s*:\s*(?P<doRes>.+)', content)

                forResVal = int(forRes[0]) if forRes else 0
                whileResVal = int(whileRes[0]) if whileRes else 0
                switchResVal = int(switchRes[0]) if switchRes else 0
                caseResVal = int(caseRes[0]) if caseRes else 0
                breakResVal = int(breakRes[0]) if breakRes else 0
                continueResVal = int(continueRes[0]) if continueRes else 0
                doResVal = int(doRes[0]) if doRes else 0

            params = [str(forResVal), str(whileResVal), str(switchResVal), str(caseResVal), str(breakResVal), str(continueResVal), str(doResVal)]
            values=[dirName]
            values.extend(params)
            self.writeFile({key: value for key, value in zip(self.headers, values)})

    def framaParserOp(self, inputsPath):
        dirs = [f for f in listdir(inputsPath) if isdir(join(inputsPath, f))]
        # Gets the headers from the output file
        self.headers = ['inputName', '==', '!=', '>', '<', '>=', '<=', '||', '&&']
        fileName = "Halsted.txt"
        for dirName in dirs:
            filesPath = inputsPath + '/' + dirName + '/' + fileName
            with open(filesPath, "r") as execFile:
                content = execFile.read()

                equalRes = findall(r'\s*\={2}:\s*(?P<equalRes>.+)', content)
                diffRes = findall(r'\s*\!\=:\s*(?P<diffRes>.+)', content)
                greaterRes = findall(r'\s*\>:\s*(?P<greaterRes>.+)', content)
                lowerRes = findall(r'\s*\<:\s*(?P<lowerRes>.+)', content)
                greaterEqualRes = findall(r'\s*\>=:\s*(?P<greaterEqualRes>.+)', content)
                lowerEqualRes = findall(r'\s*\<=:\s*(?P<lowerEqualRes>.+)', content)
                orRes = findall(r'\s*\|{2}:\s*(?P<orRes>.+)', content)
                andRes = findall(r'\s*\&{2}:\s*(?P<andRes>.+)', content)

                equalResVal = int(equalRes[0]) if equalRes else 0
                diffResVal = int(diffRes[0]) if diffRes else 0
                greaterResVal = int(greaterRes[0]) if greaterRes else 0
                lowerResVal = int(lowerRes[0]) if lowerRes else 0
                greaterEqualResVal = int(greaterEqualRes[0]) if greaterEqualRes else 0
                lowerEqualResVal = int(lowerEqualRes[0]) if lowerEqualRes else 0
                orResVal = int(orRes[0]) if orRes else 0
                andResVal = int(andRes[0]) if andRes else 0

            params = [str(equalResVal), str(diffResVal), str(greaterResVal), str(lowerResVal), str(greaterEqualResVal),
                      str(lowerEqualResVal), str(orResVal), str(andResVal)]
            values=[dirName]
            values.extend(params)
            self.writeFile({key: value for key, value in zip(self.headers, values)})

    def framaParserRegOp(self, inputsPath, inputsCPath):
        dirs = [f for f in listdir(inputsPath) if isdir(join(inputsPath, f))]
        # Gets the headers from the output file
        self.headers = ['inputName', '++', '--', '=', '-', '*', '/', '%', '+=', '-=', '*=', '/=', '%=', '&',
                        '|', '&=', '^=', '|=', '<<', '<<=', '>>', '>>=', '+', '^', '~', '+( )', '-( )', '!( )', '~( )']
        fileName = "Halsted.txt"
        for dirName in dirs:
            filesPath = inputsPath + '/' + dirName + '/' + fileName
            with open(filesPath, "r") as execFile:
                content = execFile.read()

                sig0 = findall(r'\s*\+{2}:\s*(?P<sig0>.+)', content)
                sig1 = findall(r'\s*\-{2}:\s*(?P<sig1>.+)', content)
                sig2 = findall(r'\s*[^\<\>\*\+\-\=\/\%\&\^]\=:\s*(?P<sig2>.+)', content)
                sig3 = findall(r'\s*-:\s*(?P<sig3>.+)', content)
                sig4 = findall(r'\s*\*:\s*(?P<sig4>.+)', content)
                sig5 = findall(r'\s*\/:\s*(?P<sig5>.+)', content)
                sig6 = findall(r'\s*\\%:\s*(?P<sig6>.+)', content)
                sig7 = findall(r'\s*\+\=:\s*(?P<sig7>.+)', content)
                sig8 = findall(r'\s*-=:\s*(?P<sig8>.+)', content)
                sig9 = findall(r'\s*\*\=:\s*(?P<sig9>.+)', content)
                sig10 = findall(r'\s*\/\=:\s*(?P<sig10>.+)', content)
                sig11 = findall(r'\s*\%\=:\s*(?P<sig11>.+)', content)
                sig12 = findall(r'\s*\&:\s*(?P<sig12>.+)', content)
                sig13 = findall(r'\s*\|:\s*(?P<sig13>.+)', content)
                sig14 = findall(r'\s*\&\=:\s*(?P<sig14>.+)', content)
                sig15 = findall(r'\s*\^\=:\s*(?P<sig15>.+)', content)
                sig16 = findall(r'\s*\|\=:\s*(?P<sig16>.+)', content)
                sig17 = findall(r'\s*\<{2}:\s*(?P<sig17>.+)', content)
                sig18 = findall(r'\s*\<{2}=:\s*(?P<sig18>.+)', content)
                sig19 = findall(r'\s*\&\>{2}:\s*(?P<sig19>.+)', content)
                sig20 = findall(r'\s*\>{2}=:\s*(?P<sig20>.+)', content)
                sig21 = findall(r'[^+]\+:\s(?P<sig21>.+)', content)
                sig22 = findall(r'\s*\^:\s*(?P<sig22>.+)', content)
                sig27 = findall(r'\s*\~:\s*(?P<sig27>.+)', content)

                sig0Val = int(sig0[0]) if sig0 else 0
                sig1Val = int(sig1[0]) if sig1 else 0
                sig2Val = int(sig2[0]) if sig2 else 0
                sig3Val = int(sig3[0]) if sig3 else 0
                sig4Val = int(sig4[0]) if sig4 else 0
                sig5Val = int(sig5[0]) if sig5 else 0
                sig6Val = int(sig6[0]) if sig6 else 0
                sig7Val = int(sig7[0]) if sig7 else 0
                sig8Val = int(sig8[0]) if sig8 else 0
                sig9Val = int(sig9[0]) if sig9 else 0
                sig10Val = int(sig10[0]) if sig10 else 0
                sig11Val = int(sig11[0]) if sig11 else 0
                sig12Val = int(sig12[0]) if sig12 else 0
                sig13Val = int(sig13[0]) if sig13 else 0
                sig14Val = int(sig14[0]) if sig14 else 0
                sig15Val = int(sig15[0]) if sig15 else 0
                sig16Val = int(sig16[0]) if sig16 else 0
                sig17Val = int(sig17[0]) if sig17 else 0
                sig18Val = int(sig18[0]) if sig18 else 0
                sig19Val = int(sig19[0]) if sig19 else 0
                sig20Val = int(sig20[0]) if sig20 else 0
                sig21Val = int(sig21[0]) if sig21 else 0
                sig22Val = int(sig22[0]) if sig22 else 0
                sig27Val = int(sig27[0]) if sig27 else 0

            # print("InputCPath:"+inputsCPath)

            filename = inputsCPath + 'frst.c'
            # print('filename' + filename)

            cmd1 = "sed 's/) \?/)\\n/g' " + filename + " | grep -c '.*+(.*).*'"
            cmd2 = "sed 's/) \?/)\\n/g' " + filename + " | grep -c '.*-(.*).*'"
            cmd3 = "sed 's/) \?/)\\n/g' " + filename + " | grep -c '.*!(.*).*'"
            cmd4 = "sed 's/) \?/)\\n/g' " + filename + " | grep -c '.*~(.*).*'"

            ps1 = subprocess.Popen(cmd1, shell=True, stdout=subprocess.PIPE, universal_newlines=True, stderr=subprocess.STDOUT)
            ps2 = subprocess.Popen(cmd2, shell=True, stdout=subprocess.PIPE, universal_newlines=True, stderr=subprocess.STDOUT)
            ps3 = subprocess.Popen(cmd3, shell=True, stdout=subprocess.PIPE, universal_newlines=True, stderr=subprocess.STDOUT)
            ps4 = subprocess.Popen(cmd4, shell=True, stdout=subprocess.PIPE, universal_newlines=True, stderr=subprocess.STDOUT)
            sig23Val = ps1.communicate()[0].strip('\n')
            sig24Val = ps2.communicate()[0].strip('\n')
            sig25Val = ps3.communicate()[0].strip('\n')
            sig26Val = ps4.communicate()[0].strip('\n')

            params = [str(sig0Val), str(sig1Val), str(sig2Val), str(sig3Val), str(sig4Val),
                      str(sig5Val), str(sig6Val), str(sig7Val), str(sig8Val), str(sig9Val),
                      str(sig10Val), str(sig11Val), str(sig12Val), str(sig13Val), str(sig14Val),
                      str(sig15Val), str(sig16Val), str(sig17Val), str(sig18Val), str(sig19Val),
                      str(sig20Val), str(sig21Val), str(sig22Val), str(sig27Val), str(sig23Val), str(sig24Val),
                      str(sig25Val), str(sig26Val)]
            values = [dirName]
            values.extend(params)
            self.writeFile({key: value for key, value in zip(self.headers, values)})

    def framaParserDataTypes(self, inputsPath):
        dirs = [f for f in listdir(inputsPath) if isdir(join(inputsPath, f))]
        # Gets the headers from the output file
        self.headers = ['inputName', 'Char', 'short', 'int', 'double', 'float', 'long', 'signed', 'unsigned', '[]', 'array',
                        'struct', 'int8_t', 'uint8_t', 'int16_t', 'uint16_t', 'int32_t', 'uint32_t', 'int64_t', 'uint64_t', 'TARGET_TYPE', 'TARGET_INDEX']
        fileName = "Halsted.txt"
        for dirName in dirs:
            filesPath = inputsPath + '/' + dirName + '/' + fileName
            with open(filesPath, "r") as execFile:
                content = execFile.read()

                sig0 = findall(r'\s*[^a-z][^A-Z]char:\s*(?P<sig0>.+)', content)
                sig1_1 = findall(r'\s*[^a-z][^A-Z]short:\s*(?P<sig1>.+)', content)
                sig1 = findall(r'\s*[^a-z][^A-Z]int:\s*(?P<sig1>.+)', content)
                sig2 = findall(r'\s*[^a-z][^A-Z]double\s*:\s*(?P<sig2>.+)', content)
                sig3 = findall(r'\s*[^a-z][^A-Z]float:\s*(?P<sig3>.+)', content)
                sig4 = findall(r'\s*[^a-z][^A-Z]long:\s*(?P<sig4>.+)', content)
                sig5 = findall(r'\s*[^a-z][^A-Z]signed:\s*(?P<sig5>.+)', content)
                sig6 = findall(r'\s*[^a-z][^A-Z]unsigned:\s*(?P<sig6>.+)', content)
                sig7 = findall(r'\s*[^a-z][^A-Z]\[\]:\s*(?P<sig7>.+)', content)
                sig8 = findall(r'\s*[^a-z][^A-Z][aA]rray:\s*(?P<sig8>.+)', content)
                sig9 = findall(r'\s*[^a-z][^A-Z][sS]truct[^A-Z]*:\s*(?P<sig9>.+)', content)
                sig10 = findall(r'\s*int8[_]*:\s*(?P<sig10>.+)', content)
                sig11 = findall(r'\s*uint8[_]*t:\s*(?P<sig11>.+)', content)
                sig12 = findall(r'\s*int16[_]*t:\s*(?P<sig12>.+)', content)
                sig13 = findall(r'\s*uint16[_]*t:\s*(?P<sig13>.+)', content)
                sig14 = findall(r'\s*int32[_]*t:\s*(?P<sig14>.+)', content)
                sig15 = findall(r'\s*uint32[_]*t:\s*(?P<sig15>.+)', content)
                sig16 = findall(r'\s*int64[_]*t:\s*(?P<sig14>.+)', content)
                sig17 = findall(r'\s*uint64[_]*t:\s*(?P<sig15>.+)', content)
                sig18 = findall(r'\s*TARGET[_]*TYPE:\s*(?P<sig16>.+)', content)
                sig19 = findall(r'\s*TARGET[_]*INDEX:\s*(?P<sig17>.+)', content)

                sig0Val = int(sig0[0]) if sig0 else 0
                sig1_1Val = int(sig1_1[0]) if sig1_1 else 0
                sig1Val = int(sig1[0]) if sig1 else 0
                sig2Val = int(sig2[0]) if sig2 else 0
                sig3Val = int(sig3[0]) if sig3 else 0
                sig4Val = int(sig4[0]) if sig4 else 0
                sig5Val = int(sig5[0]) if sig5 else 0
                sig6Val = int(sig6[0]) if sig6 else 0
                sig7Val = int(sig7[0]) if sig7 else 0
                sig8Val = int(sig8[0]) if sig8 else 0
                sig9Val = int(sig9[0]) if sig9 else 0
                sig10Val = int(sig10[0]) if sig10 else 0
                sig11Val = int(sig11[0]) if sig11 else 0
                sig12Val = int(sig12[0]) if sig12 else 0
                sig13Val = int(sig13[0]) if sig13 else 0
                sig14Val = int(sig14[0]) if sig14 else 0
                sig15Val = int(sig15[0]) if sig15 else 0
                sig16Val = int(sig16[0]) if sig16 else 0
                sig17Val = int(sig17[0]) if sig17 else 0
                sig18Val = int(sig18[0]) if sig18 else 0
                sig19Val = int(sig19[0]) if sig19 else 0

            params = [str(sig0Val), str(sig1_1Val), str(sig1Val), str(sig2Val), str(sig3Val), str(sig4Val),
                      str(sig5Val), str(sig6Val), str(sig7Val), str(sig8Val), str(sig9Val),
                      str(sig10Val), str(sig11Val), str(sig12Val), str(sig13Val), str(sig14Val),
                      str(sig15Val), str(sig16Val), str(sig17Val), str(sig18Val), str(sig19Val)]
            values = [dirName]
            values.extend(params)
            self.writeFile({key: value for key, value in zip(self.headers, values)})

    def getHeadersFrama(self, args, pascalCase=False):
        """ This functions extracts the needed information from a FramaC output file
        """
        filePath, idxStart, idxEnd, regex = args
        headers = []

        with open(filePath, 'r') as fp:
            lines = fp.readlines()[idxStart:idxEnd]
            for ln in lines:
                key, match = parseline(regex, ln)

                if key:
                    # Removes the last char (e.g. :)
                    # key = key.group()[:-1]
                    # Puts the string in pascal case
                    if pascalCase: key = ''.join(x for x in key.title() if not x.isspace())

                    headers.append(key)

        return headers

    """ This functions extracts the needed information from ISS/HLS output file
    """

    def simParser(filePath):
        """Generic parsing for the output file of an ISS

        Args:
            simFilename (string):  the name of the file that contains simulation information

        Returns:
            string: number of clock cycles

        Todo:
            * Not Generic, it works only with the micros already tested
        """
        results = []
        with open(filePath + ".txt", "r") as execFile:
            content = execFile.read()

            cycleStr = search(r'([cC]ycles.*?:\s*)(\d+)', content)
            assemblyInst = search(r'([iI]nstructions.*?:\s*)(\d+(.\d+)?)', content)
            cacheHit = findall(r'Cache hit rate\s*:\s*([\d.]+)\s*%\s*\(inst:', content)
            cacheHitInstr = search(r'inst:\s*([\d.]+)', content)
            cacheHitData = search(r'data:\s*([\d.]+)', content)
            mops_numbers = findall(r'([\d.]+)\s*MOPS', content)
            mips_numbers = findall(r'([\d.]+)\s*MIPS', content)
            mflops_numbers = findall(r'([\d.]+)\s*MFLOPS', content)

            if cycleStr: results.append(cycleStr.group(2))
            if assemblyInst: results.append(assemblyInst.group(2))
            if cacheHit: results.append(cacheHit[0])
            if cacheHitInstr: results.append(cacheHitInstr[1])
            if cacheHitData: results.append(cacheHitData[1])
            if mops_numbers: results.append(mops_numbers[0])
            if mips_numbers: results.append(mips_numbers[0])
            if mflops_numbers: results.append(mflops_numbers[0])

        return results

    def thumbParser(filePath):
        """Parsing for the output file of the Thumbulator ISS

        Args:
            simFilename (string):  the name of the file that contains simulation information

        Returns:
            string: number of clock cycles and assembly instruction
        """
        results = []
        with open(filePath + ".txt", "r") as execFile:
            content = execFile.read()

            cycleStr = search(r'(\d+)\s+ticks', content)
            assemblyInst = search(r'(\d+)\s+instructions', content)

            if cycleStr: results.append(cycleStr.group(1))
            if assemblyInst: results.append(assemblyInst.group(1))

        return results

    def riscVParser(filePath):
        """Parsing for the output file of the Thumbulator ISS

        Args:
            simFilename (string):  the name of the file that contains simulation information

        Returns:
            string: number of clock cycles and assembly instruction
        """
        results = []
        with open(filePath + ".txt", "r") as execFile:
            content = execFile.read()

            cycleStr = search(r'(\d+)\s+cycles', content)
            assemblyInst = search(r'(\d+)\s+instructions', content)

            cacheInfo = findall(r'(?<=:)\s+(\d+(?:\.\d+)?)', content)

            # print(cacheInfo)

            if cycleStr: results.append(cycleStr.group(1))
            if assemblyInst: results.append(assemblyInst.group(1))
            if cacheInfo: results.append(cacheInfo)

        return results

    def simParserBambu(filePath):
        """Generic parsing for the output file of an ISS

        Args:
            simFilename (string):  the name of the file that contains simulation information

        Returns:
            string: number of clock cycles

        Todo:
            * Not Generic, it works only with the micros already tested
        """
        results = []

        with open(filePath + ".txt", "r") as execFile:
            content = execFile.read()
            cycleStr = search(r'(Total.*?[cC]ycles.*?:\s*)(\d+)', content)
            assemblyInst = search(r'([iI]nstructions.*?:\s*)(\d+(.\d+)?)', content)

            if cycleStr: results.append(cycleStr.group(2))
            if assemblyInst: results.append(assemblyInst.group(2))

        return results

    """ This functions extracts the needed information from size output file
    """

    def getSizeRow(args):
        filePath, idxStart, idxEnd = args
        content = []

        with open(filePath, 'r') as fp:
            lines = fp.readlines()[idxStart:idxEnd]
            for ln in lines:
                if(ln.find(':')!=-1):
                    value=ln.split(':')[1]
                elif(ln.find('=')!=-1):
                    value=ln.split('=')[1]
                if value: content.append(value)

        print("Content: " + filePath + "; Value: " + content)

        return content

    def sizeParser(self, inputsPath):
        """Generic parsing for the size output file of a compiler

        Args:
            inputsPath (string):  the name of the path that contains size information

        Returns:
            file: csv file containing compiled code size information

        Todo:
            * Not Generic, it works only with the micros already tested
        """
        dirs = [f for f in listdir(inputsPath) if isdir(join(inputsPath, f))]
        # Gets the headers from the output file
        self.headers = ['inputName','text','data','bss']
        fileName = "size.txt"
        for dirName in dirs:
            filesPath = inputsPath + '/' + dirName + '/' + fileName
            with open(filesPath, 'r') as fp:
                lines = fp.readlines()
                try:
                    params = [int(temp)for temp in lines[1].split() if temp.isdigit()]
                    values=[dirName]
                    values.extend(params)
                    self.writeFile({key:value for key, value in zip(self.headers, values)})
                except:
                    values = '0'
                    self.writeFile({key: value for key, value in zip(self.headers, values)})

    def size8051Parser(self, inputsPath):
        """Generic parsing for the size output file of a compiler

        Args:
            inputsPath (string):  the name of the path that contains size information

        Returns:
            file: csv file containing compiled code size information

        Todo:
            * Not Generic, it works only with the micros already tested
        """
        dirs = [f for f in listdir(inputsPath) if isdir(join(inputsPath, f))]
        # Gets the headers from the output file
        self.headers = ['inputName','text','data','bss']
        fileName = "size.txt"
        subString = 'ROM/EPROM/FLASH'
        subString2 = 'EXTERNAL RAM'
        substring3 = 'PAGED EXT. RAM'
        for dirName in dirs:
            filesPath = inputsPath + '/' + dirName + '/' + fileName
            fp = open(filesPath, 'r')
            lines = fp.readlines()
            for line in lines:
                if subString in line:
                    numbers = re.findall(r"\d+", line)
                    sizeFLASH = int(numbers[-2])
                    #print('RAM/EPROM/FRALSH:'+str(sizeFLASH))
                elif subString2 in line:
                    numbers2 = re.findall(r"\d+", line)
                    exRAM = int(numbers2[-2])
                    # print('EXTERNAL RAM:'+str(sizeFLASH))
                elif substring3 in line:
                    numbers2 = re.findall(r"\d+", line)
                    pagedRAM = int(numbers2[-2])
                    # print('PAGED EXT. RAM:'+str(sizeFLASH))

            params = [str(sizeFLASH), str(exRAM), str(pagedRAM)]
            values=[dirName]
            values.extend(params)
            self.writeFile({key:value for key, value in zip(self.headers, values)})

    PARSERS = {
        'Thumb': thumbParser,
        'Leon3': simParser,
        '8051': simParser,
        'Atmega328p': simParser,
        'Arm': simParser,
        'Bambu': simParserBambu,
        'RiscV': riscVParser
    }
