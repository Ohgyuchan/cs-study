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

def draw2(event):
    global x1, y1
    x1 = event.x
    y1 = event.y
    canvas.create_line(x1, y1, x1+1, y1+1, width = myWidth, fill = color[1])

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
    canvas.create_polygon(x1, y1, x1, y1+140, x1+140, y1+140, width = myWidth, fill = color[1])

def rectangle():
    global color
    color = askcolor()
    canvas.bind("<Double-Button-1>", draw_rectangle)

def circle():
    global color
    color = askcolor()
    canvas.bind("<Double-Button-1>", draw_circle)

def triangle():
    global color
    color = askcolor()
    canvas.bind("<Double-Button-1>", draw_triangle)

def eraser(event):
    global x1, y1
    x1 = event.x
    y1 = event.y
    canvas.create_line(x1, y1, x1+1, y1+1, width = myWidth, fill = "black")

def change_colorRed():
    global myColor
    myColor = "red"

def change_colorYellow():
    global myColor
    myColor = "yellow"

def change_colorBlue():
    global myColor
    myColor = "blue"

def change_colorGray80():
    global myColor
    myColor = "Gray80"

def change_colorGray60():
    global myColor
    myColor = "Gray60"

def change_colorGray30():
    global myColor
    myColor = "Gray30"

def change_colorGray10():
    global myColor
    myColor = "Gray10"

def change_colorGreen():
    global myColor
    myColor = "green"

def change_colorBrown():
    global myColor
    myColor = "Brown"

def change_colorPink():
    global myColor
    myColor = "pink"

def change_colorOrange():
    global myColor
    myColor = "orange"

def change_colorPurple():
    global myColor
    myColor = "purple"

def change_colorLawngreen():
    global myColor
    myColor = "lawngreen"

def change_colorWhite():
    global myColor
    myColor = "white"

def change_colorSkyblue():
    global myColor
    myColor = "skyblue"

def change_colorDarkblue():
    global myColor
    myColor = "darkblue"

def clearCanvas():
    canvas.delete("all")

def save():
    filename = filedialog.asksaveasfilename(initialdir = "/",
                                            title = "Select file",
                                            filetypes = (("PPTX files", "*.pptx"), ("akk files", "*.*")))

def open():
    global im, tk_imgfname = fd.askopenfilename()
    im = Image.open(fanme)
    tk_img = ImageTk.PhotoImage(im)
    canvas.create_image(250, 250, image = tk_img)
    window.update()

def quit():
    window.quit()
    window.destroy()

def image_rotateR():
    global im, tk_img
    out = im.rotate(90)
    tk_img = ImageTk.PhotoImage(out)
    canvas.create_image(250, 250, image = tk_img)
    window.update()

def image_blur():
    global im, tk_img
    out = im.filter(ImageFilter.BLUR)
    tk_img = ImageTk.PhotoImage(out)
    canvas.create_image(250, 250, image = tk_img)
    window.update()


window = Tk()
window.title("그려 그려 그림판")
canvas = Canvas(window, width=700, height=600, bg="black")
canvas.create_text(350, 80, text="그려 그려 그림판", fill="white")
# canvas.create_text(350, 80, text="그려 그려 그림판", fill="white")
# canvas.create_text(350, 80, text="그려 그려 그림판", fill="white")
# canvas.create_text(350, 80, text="그려 그려 그림판", fill="white")
# canvas.create_text(350, 80, text="그려 그려 그림판", fill="white")



