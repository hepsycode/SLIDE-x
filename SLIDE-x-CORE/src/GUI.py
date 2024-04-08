import tkinter as tk
from tkinter.filedialog import askdirectory
from functools import partial
from os import listdir
from os.path import isdir, join, expanduser

def returnDirNames(topDir):
    return [f for f in listdir(topDir) if isdir(join(topDir, f))]

class GUI:
    def __init__(self, title, dimension):
        # Main Window
        self.root = tk.Tk()
        self.root.title(title)
        self.root.geometry(dimension)
        self.root.eval('tk::PlaceWindow . center')

        self.lbox = ""
        self.rbtn = ""
        # microprocessors
        self.micros = ['Leon3', 'Thumb', 'Atmega328p', 'Arm', '8051', 'Bambu', 'RiscV', 'ALL']

    def getmicros(self):
        return ['Thumb', 'Leon3', 'Arm', 'Atmega328p', '8051', 'Bambu', 'RiscV']

    # def fixSize(self):
        # self.root.resizable(0, 0)  # Don't allow resizing in the x or y direction

    def start(self):
        self.root.grid()
        self.root.mainloop()

    def createLabel(self, referenceFrame, text):
        labelText = tk.StringVar()
        labelText.set(text)
        return tk.Label(referenceFrame, textvariable=labelText, relief=tk.RIDGE)

    def setSelection(self, lbox, rbtn):
        self.lbox = lbox.get(tk.ACTIVE)
        self.rbtn = rbtn.get()

    def getSelection(self):
        return (self.lbox, self.rbtn)

    def quit(self):
        self.root.destroy()

    def fillMainWindow(self, benchmarkPath, customCallback):
        ## Frame used for the listbox 
        fstFrame = tk.Frame(self.root, relief=tk.GROOVE, width=500, height=300, padx=10, pady=5)
        fstFrame.pack(fill=tk.X)

        lboxLabel = self.createLabel(fstFrame, "Benchmark Functions")
        lboxLabel.pack(pady=5, fill=tk.X)

        ## Creates the listbox
        lbox = tk.Listbox(fstFrame, height=16)
        lbox.pack(fill=tk.X)

        ## Insert list names 
        for item in returnDirNames(benchmarkPath):
            lbox.insert(tk.END, item)

        ## Make the first element as the default selection
        lbox.select_set(0)
        lbox.event_generate("<<ListboxSelect>>")

        # Second Frame Section - Checkbar code
        scndFrame = tk.Frame(self.root, relief=tk.GROOVE, height=45, padx=10)
        scndFrame.pack(fill=tk.X)

        chkbarLabel = self.createLabel(scndFrame, "Microprocessors")
        chkbarLabel.pack(fill=tk.X)

        var = tk.IntVar()
        for idx, item in enumerate(self.micros):
            chk = tk.Radiobutton(scndFrame, text=item, variable=var, value=idx)
            chk.pack(side=tk.LEFT,  fill=tk.X, expand=True)

        # Third Frame Section - Button code
        trdFrame = tk.Frame(self.root, relief=tk.GROOVE, height=10, padx=10, pady=15)
        trdFrame.pack(fill=tk.X)

        button = tk.Button(trdFrame, text="Calculate Metrics",
            command=partial(customCallback, lbox, var, tk.ACTIVE))

        button.pack(fill=tk.X)

    def callback(self, functions, micro, listbox):
        """
        Retrieves data from the GUI:
            * function
            * micro
            * results directory path
        """
        function = functions.get(listbox) # chosen function

        results = askdirectory(
            initialdir = expanduser("~/Desktop"),
            title = 'Select folder to save results'
        )
        # TODO: creation of the results directory from the GUI

        # Retrieves ranges and function's parameters from 'parameters.json'
        # ranges, args = getParameters(function, micros[micro.get()])

        self.function = function
        self.results = results
        self.micro = self.micros[micro.get()]

        self.quit()
