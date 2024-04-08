from re import search
from subprocess import call, DEVNULL
from os.path import isdir, join, dirname, basename, splitext
from os import chdir, makedirs, listdir
from csv import DictWriter
from shutil import rmtree, move
import subprocess as subproc

class CommandsManager:
    def __init__(self, functionPath, scriptPath, workingDir, OptimizationFlag):
        self.functionPath = functionPath
        self.functionName = basename(splitext(functionPath)[0])
        self.scriptPath = scriptPath
        self.workingDir = workingDir
        self.OptimizationFlag = OptimizationFlag

    def expandCommand(
            self, compactCmd, directory, prjPath
    ):
        # The expandCommand function replaces the placeholders
        # contained in .json file with their actual values

        if '[functionDir]' in compactCmd:
            compactCmd = compactCmd.replace(
                '[functionDir]', dirname(self.functionPath)
            )

        if '[functionPath]' in compactCmd:
            compactCmd = compactCmd.replace(
                '[functionPath]', self.functionPath
            )

        if '[functionName]' in compactCmd:
            compactCmd = compactCmd.replace(
                '[functionName]', self.functionName
            )

        if '[prjPath]' in compactCmd:
            compactCmd = compactCmd.replace(
                '[prjPath]', prjPath + '/'
            )

        if '[scriptPath]' in compactCmd:
            compactCmd = compactCmd.replace('[scriptPath]', self.scriptPath)

        if '[directoryName]' in compactCmd:
            compactCmd = compactCmd.replace('[directoryName]', directory)

        if '[OptimizationFlag]' in compactCmd:
            compactCmd = compactCmd.replace(
                '[OptimizationFlag]', self.OptimizationFlag
            )

        return compactCmd

    def executeCommand(self, cmd):
        outputFile = search(r'[^:\/;]\{(.*?)\}', cmd)
        flags = cmd.split(" ")

        if outputFile:    
            outputFile = outputFile.group(1)
            flags.remove('{' + outputFile + '}')
            with open(outputFile, 'w') as obj:
                subproc.call(flags, stdout = obj, stderr = obj) #, stderr = DEVNULL)
        else:
            subproc.call(flags) #, stderr = DEVNULL, stdout = DEVNULL)


    def executeCommandSet(self, cmdSet, inputsPath, filesDirName, parsingFunction = None):
        # Creates the directory containing 
        # the files produced during the execution
        filesDir = filesDirName # "files"
        # Moves to the directory containing the results
        chdir(self.workingDir)
        # Gets the list of commands
        # if "dependencies" in cmdSet:
        jsonEntry = cmdSet["dependencies"].split(" ")
        dirs = [f for f in listdir(inputsPath) if isdir(join(inputsPath, f))]

        if isdir(filesDir): rmtree(filesDir)
        makedirs(filesDir)
        
        for dirName in dirs:
            filesPath = self.workingDir + '/' + filesDir + '/' + dirName
            # Creates the subdirectory containing 
            # the files produced for each input
            makedirs(filesPath)
            chdir(filesPath)

            for entry in jsonEntry:
                cmd = cmdSet[entry]
                # Changes the values of the eventual placeholders in real ones
                completedCmd = self.expandCommand(cmd, dirName, self.workingDir)
                print(completedCmd)
                self.executeCommand(completedCmd)

            # Calls the function to parse the output    
            if parsingFunction:
                parsingFunction(filesPath + '/' + self.functionName, values = [dirName])

            # Restores the previous working directory
            chdir(self.workingDir)

    def executeCommandSetBambu(self, cmdSet, inputsPath, parsingFunction=None):
        # Changes working directory
        chdir(self.workingDir)

        # Gets the list of commands
        jsonEntry = cmdSet["dependencies"].split(" ")
        dirs = [f for f in listdir(inputsPath) if isdir(join(inputsPath, f))]

        # Creates the directory containing the files produced during the execution
        filesDir = "files"  # files

        if isdir(filesDir): rmtree(filesDir)
        makedirs(filesDir)

        for dirName in dirs:
            filesPath = self.workingDir + '/' + filesDir + '/' + dirName
            # Creates the subdirectory containing the files produced for each input
            makedirs(filesPath)
            chdir(filesPath)

            for entry in jsonEntry:
                cmd = cmdSet[entry]
                # Changes the values of the eventual placeholders in real ones
                completedCmd = self.expandCommand(cmd, dirName, self.workingDir)
                print(completedCmd)
                self.executeCommand(completedCmd)

            # Calls the function to parse the output
            if parsingFunction:
                parsingFunction(filesPath + '/' + dirName, values=[dirName])  # self.functionName, values = [dirName])

            # Restores the previous working directory
            chdir(self.workingDir)

    def movefilesBambuNoGUI(self, functionName, currentType, resultsPath, parsingFunction=None, debugFlag=False):
        # Changes working directory
        chdir(self.workingDir)
        resultsPathBambu = self.workingDir + '/files'  # files
        print(resultsPathBambu)

        dirs = [f for f in listdir(resultsPathBambu) if isdir(join(resultsPathBambu, f))]

        for dirName in dirs:
            # filesDirBambu = self.workingDir + "/results/" + currentType + '/' + 'Area_' + dirName + '.txt' # + "/filesBambu" + '/' + dirName + '.txt'
            filesDirBambu = resultsPath + '/' + 'Area_' + dirName + '.txt'  # + "/filesBambu" + '/' + dirName + '.txt'
            filesPathBambu = resultsPathBambu + '/' + dirName + '/' + dirName + '.txt'
            try:
                move(filesPathBambu, filesDirBambu)
                print('Move ' + filesDirBambu + ' to ' + filesPathBambu)
            # For other errors
            except:
                print("Error occurred while copying file.")
    
