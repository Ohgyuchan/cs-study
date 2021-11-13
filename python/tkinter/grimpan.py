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
    canvas.create_line(x1, y1, x1+1, y1+1, width = myWidth, fill = color[1])
    x1 = event.x
    y1 = event.y

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
    canvas.bind("<Double-Button-2>", draw_circle)

def triangle():
    global color
    color = askcolor()
    canvas.bind("<Double-Button-3>", draw_triangle)

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
    global im, tk_img
    fname = fd.askopenfilename()
    im = Image.open(fname)
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

def image_rotateL():
    global im, tk_img
    out = im.rotate(-90)
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
# canvas.create_text(193, 350, text="< 조작키 >", fill="red")
# canvas.create_text(350, 430, text="마우스를 이용하여 여러 기능을 활용해 보세요!\n 초기 설정된 색은 흰 색 입니다.", fill="white")
# canvas.create_text(350, 500, text="== ALL CELAN 을 눌러 시작하세요", fill="white")

canvas.create_text(350, 80, text="우클릭 = 기본색상선택\n\n휠 클릭 = 다른 색상 선택\n\n좌클릭 = 지우개\n\n 우더블클릭 = 도형 삽입", fill="white")

canvas.create_rectangle(130, 160, 250, 330, outline="white")
canvas.create_line(130, 220, 250, 220, fill="white")
canvas.create_rectangle(130, 160, 190, 220, fill="gray22", outline='white')
canvas.grid()

frame=Frame(window)
frame.grid()

menubar = tk.Menu(window)
filemenu = tk.Menu(menubar)
rotatemenu = tk.Menu(menubar)
ipmenu = tk.Menu(menubar)

menubar.add_cascade(label="File", menu=filemenu)
filemenu.add_command(label='Open', command=open)
filemenu.add_command(label='save', command=save)
filemenu.add_command(label='Save As', command=save)
filemenu.add_command(label='Exit', command=quit)

menubar.add_cascade(label='그림 회전', menu=rotatemenu)
rotatemenu.add_command(label='오른쪽으로 90도 회전', command=image_rotateR)
rotatemenu.add_command(label='왼쪽으로 90도 회전', command=image_rotateL)


menubar.add_cascade(label='특수효과', menu=ipmenu)
ipmenu.add_command(label='흐리게', command=image_blur)

canvas.bind('<B1-Motion>', draw)
canvas.bind('<B2-Motion>', eraser)
canvas.bind('<B3-Motion>', draw2)

clear=Button(frame, text="=====ALL CLEAR=====", fg='darkblue', bg='skyblue', command=clearCanvas)
clear.grid(row=1, column=2)
l2=Label(window, text='색상 선택: ')
l2.place(x=750, y=70)

button1=Button(window, text='    ', bg='red', command=change_colorRed)
button1.place(x=705, y=90)
button2=Button(window, text='    ', bg='orange', command=change_colorOrange)
button2.place(x=730, y=90)
button3=Button(window, text='    ', bg='yellow', command=change_colorYellow)
button3.place(x=755, y=90)
user=Button(window, text='다른 색 선택', fg='black', command=colorASK)
user.place(x=705, y=190)

l2=Label(window, text="도형 찍기: ")
l2.place(x=705, y=270)
button1=Button(window, text='사각형', fg='black', command=rectangle)
button1.grid(row=0, column=1)
button1=Button(window, text='사각형', fg='black', command=circle)
button1.grid(row=0, column=2)
button1=Button(window, text='삼각형', fg='black', command=triangle)
button1.place(x=750, y=320)

l1 = Label(window, text='선 굵기: ')
l1.place(x=705, y=380)
button1 = Button(window, text=' 굵기 1 ', fg='black', command=penWidth1)
button1.place(x=705, y=400)
button1 = Button(window, text=' 굵기 5 ', fg='black', command=penWidth5)
button1.place(x=760, y=400)
button1 = Button(window, text=' 굵기 10 ', fg='black', command=penWidth10)
button1.place(x=705, y=430)
button1 = Button(window, text=' 굵기 20 ', fg='black', command=penWidth20)
button1.place(x=760, y=430)
button1 = Button(window, text=' 굵기 30 ', fg='black', command=penWidth30)
button1.place(x=705, y=460)
button1 = Button(window, text=' 굵기 50 ', fg='black', command=penWidth50)
button1.place(x=760, y=460)

window.config(menu=menubar)
window.mainloop()