from tkinter import *
from tkinter.scrolledtext import *
from tkinter.filedialog import *
from tkinter import messagebox

def funcNew() :
    st1.delete(1.0, END)
    st2.delete(1.0, END)
    passwordEntry.delete(0, END)

def funcOpen() :
    openFileName = askopenfilename(title='파일 열기', filetypes=((".txt","*.txt"),))
    openFile = open(openFileName, "r")
    st1.insert(1.0, openFile.read())
    openFile.close()

def funcSave() :
    print("SAVE")

def funcDecode() :
    print()

master = Tk()
master.title("Final")

newButton = Button(master, text="New", command=funcNew)
openButton = Button(master, text="Open", command=funcOpen)
saveButton = Button(master, text="Save", command=funcSave)

newButton.grid(row=0, column=0)
openButton.grid(row=0, column=1)
saveButton.grid(row=0, column=2)

fileNameLabel = Label(master, text="File name:")
fileNameLabel.grid(row=1, column=0, columnspan=3)

st1 = ScrolledText(master)
st1.grid(row=2, column=0, columnspan=3)

passwordLabel = Label(master, text="Password")
passwordEntry = Entry(master)
decodeButton = Button(master, text="Decode", command=funcDecode)

passwordLabel.grid(row=3, column=0)
passwordEntry.grid(row=3, column=1)
decodeButton.grid(row=3, column=2)

st2 = ScrolledText(master)
st2.grid(row=4, column=0, columnspan=3)

master.mainloop()