from tkinter import *
from tkinter.colorchooser import *

def callback():
    global result
    result = askcolor(title="Color Chooser")
    result = result[1]

root = Tk()

canvas = Canvas(root, width=500, height=500)
color = 'red'
result = '#476042'

B1 = Button(root, text='Choose Color', fg="darkgreen", command=callback)
B1.pack(side=LEFT, padx=10)

lastx, lasty = 0, 0

def xy(event):
    global lastx, lasty
    lastx, lasty = event.x, event.y

def addLine(event):
    global lastx, lasty
    canvas.create_line((lastx, lasty, event.x, event.y), fill=result)
    lastx, lasty = event.x, event.y

root.columnconfigure(0, weight=1)
root.rowconfigure(0, weight=1)

canvas.pack()
canvas.bind("<Button-1>", xy)
canvas.bind("<B1-Motion>", addLine)

root.mainloop()