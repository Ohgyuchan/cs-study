from tkinter import *
from PIL import Image, ImageTk, ImageFilter
import tkinter as tk
from tkinter import filedialog
from tkinter import filedialog as fd
from tkinter.colorchooser import *

im = None
tk_img = None
window = None
canvas = None
x1, y1 = None, None

def colorASK():
    global color
    color = askcolor()

def penWidth1():
    global myWidth
    myWidth = 1

def penWidth5():
    global myWidth
    myWidth = 5

def penWidth10():
    global myWidth
    myWidth = 10

def penWidth20():
    global myWidth
    myWidth = 20

def penWidth30():
    global myWidth
    myWidth = 30

def penWidth50():
    global myWidth
    myWidth = 50

myColor = "white"
myWidth = 5

def draw(event):
    global x1, y1
    x1 = event.x
    y1 = event.y
    canvas.create_line(x1, y1, x1+1, y1+1, width = myWidth, fill = myColor)

def draw_rectangle(event):
    global x1, y1
    x1 = event.x
    y1 = event.y
    canvas.create_rectangle(x1-10, y1-10, x1+100, y1+100, width = myWidth, fill = color[1])

def draw_circle(event):
    global x1, y1
    x1 = event.x
    y1 = event.y
    canvas.create_oval(x1-10, y1-10, x1+100, y1+100, width = myWidth, fill = color[1])

def draw_triangle(event):
    global x1, y1
    x1 = event.x
    y1 = event.y
    canvas.create_oval(x1, y1, x1, y1+140, x1+140, y1+140, width = myWidth, fill = color[1])

def rectangle():
    global color = askcolor()
    canvas.bind("<Double-Button-1>", draw_rectangle)

