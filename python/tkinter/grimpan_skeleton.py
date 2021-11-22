"""
TODO:
1. ALL CLEAR 완성
2. 펜 굵기 메뉴 완성
3. 펜 색깔 메뉴 완성
4. 도형 그리기 완성
5. 마우스 인터렉션 완성
6. 화면 회전
7. 화면 흐리게
"""
from tkinter import *
from PIL import Image, ImageTk, ImageFilter  
import tkinter as tk
from tkinter import filedialog
from tkinter import filedialog as fd
from tkinter.colorchooser import *

im = None
tk_img = None
window=None
canvas=None
x1,y1=None,None

#사용자에게 색상을 입력받는 함수 
def colorASK():
    global color
    color=askcolor()

#굵기 지정 함수
def penWidth1():
    global mywidth
    mywidth=1

mycolor = "white"
mywidth = 5

def dot(event):
    global x1, y1
    x1, y1 = event.x, event.y

#그리기 함수
def paint(event):
    global x1,y1
    canvas.create_line(x1, y1, event.x, event.y, width=mywidth, fill=mycolor)
    x1=event.x
    y1=event.y

# 휠 클릭
def paint2(event):
    global x1,y1
    x1=event.x
    y1=event.y
    canvas.create_line(x1,y1,x1+1,y1+1,width=mywidth, fill=color[1])

#사각형 그리기 함수
def paint3(event):
    global x1,y1
    x1=event.x
    y1=event.y
    canvas.create_rectangle(x1-10,y1-10,x1+100,y1+100, fill=color[1])

#원 그리기 함수
def paint4(event):
    global x1,y1
    x1=event.x
    y1=event.y
    canvas.create_oval(x1-10,y1-10,x1+100,y1+100, fill=color[1])

#삼각형 그리기 함수
def paint5(event):
    global x1,y1
    x1=event.x
    y1=event.y
    # (x1,y1), (x2,y2), (x3,y3)을 꼭짓점으로 하는 삼각형 그리기 
    canvas.create_polygon(x1,y1,x1,y1+140,x1+140,y1+60, fill=color[1])

# TODO: Add CLICK EVENT(좌클릭 더블클릭)
def rectangle():
    global color
    color=askcolor()
    canvas.bind("<Double-Button-1>",paint3)

def oval():
    global color
    color=askcolor()
    canvas.bind("<Double-Button-1>",paint4)

def triangle():
    global color
    color=askcolor()
    canvas.bind("<Double-Button-1>",paint5)

# 지우개 함수
def eraser(event):
    global x1,y1
    x1=event.x
    y1=event.y
    canvas.create_line(x1,y1,x1+1,y1+1,width=mywidth,fill="black")

#색 변형 함수 
def change_colorRed():
    global mycolor
    mycolor="red"

def change_colorYellow():
    global mycolor
    mycolor="yellow"

def change_colorBlue():
    global mycolor
    mycolor="blue"
    
def change_colorGray80():
    global mycolor
    mycolor="Gray80"
    
def change_colorGray60():
    global mycolor
    mycolor="Gray60"
    
def change_colorGray30():
    global mycolor
    mycolor="Gray30"
    
def change_colorGray10():
    global mycolor
    mycolor="Gray10"

def change_colorGreen():
    global mycolor
    mycolor="green"

def change_colorBrown():
    global mycolor
    mycolor="Brown"

def change_colorPink():
    global mycolor
    mycolor="pink"

def change_colorOrange():
    global mycolor
    mycolor="orange"
    
def change_colorPurple():
    global mycolor
    mycolor="purple"

def change_colorLawngreen():
    global mycolor
    mycolor="lawngreen"

def change_colorWhite():
    global mycolor
    mycolor="white"

def change_colorSkyblue():
    global mycolor
    mycolor="skyblue"

def change_colorDarkblue():
    global mycolor
    mycolor="darkblue"

# 윈도우를 생성한다.
window=Tk()
window.title("그려 그려 그림판")
canvas=Canvas(window,width=700,height=600,bg="black")
canvas.create_text(350,80,text="그려 그려 그림판", fill = "white",font=("둥근모꼴",35))
canvas.create_text(193,350,text="< 조작키 >", fill = "red",font=("둥근모꼴",12))
canvas.create_text(350,430, text="마우스를 이용하여 여러 기능을 활용해 보세요!\n          초기 설정된 색은 흰 색 입니다.",fill="gold", font=("둥근모꼴",13))
canvas.create_text(350,500, text="== ALL CLEAR를 눌러 시작하세요! ==",fill="white", font=("둥근모꼴",14))

canvas.create_text(410,150, text="==<실행설명>==",fill="red", font=("둥근모꼴",15))
canvas.create_text(420,250, text="좌클릭 = 기본색상으로 선 그리기\n\n휠 클릭 = 그 외 색상으로 선그리고\n\n우클릭 = 지우개\n\n우더블클릭 = 도형 삽입",fill="white", font=("둥근모꼴",16))

canvas.create_rectangle(130,160,250,330,outline="white")
canvas.create_line(130,220,250,220,fill="white")
canvas.create_rectangle(130,160,190,220,fill="gray22",outline="white")
canvas.grid()

frame=Frame(window)
frame.grid()

# 메뉴를 생성한다. 
menubar = tk.Menu(window)
filemenu = tk.Menu(menubar)
rotatemenu = tk.Menu(menubar)
ipmenu = tk.Menu(menubar)

menubar.add_cascade(label="파일", menu=filemenu)
# TODO: Add command
filemenu.add_command(label="열기(O)")
filemenu.add_command(label="저장(S)")
filemenu.add_command(label="다른 이름으로 저장(A)")
filemenu.add_command(label="끝내기(X)")

menubar.add_cascade(label="그림 회전", menu=rotatemenu)
# TODO: Add command
rotatemenu.add_command(label="오른쪽으로 90도 회전(R)")
rotatemenu.add_command(label="왼쪽으로 90도 회전(L)")

menubar.add_cascade(label="특수효과", menu=ipmenu)
# TODO: Add command
ipmenu.add_command(label="흐리게")


# TODO: Add MOUSE CLICK EVENT

# TODO: Add ALL CLEAR EVENT

clear=Button(frame,text="====ALL CLEAR====",fg="darkblue",bg="skyblue", font=("둥근모꼴",20))
clear.grid(row=1,column=2)
l2=Label(window,text="색상 선택: ")
l2.place(x=705,y=70)

# 화면에 위젯을 위치하게하는 코드
# TODO: Add command & Background  Color
button1=Button(window,text="    ")
button1.place(x=705,y=90)
button2=Button(window,text="    ")
button2.place(x=730,y=90)
button3=Button(window,text="    ")
button3.place(x=755,y=90)
button3=Button(window,text="    ")
button3.place(x=780,y=90)
button4=Button(window,text="    ")
button4.place(x=705,y=115)
button5=Button(window,text="    ")
button5.place(x=730,y=115)
button6=Button(window,text="    ")
button6.place(x=755,y=115)
button3=Button(window,text="    ")
button3.place(x=780,y=115)
button7=Button(window,text="    ")
button7.place(x=705,y=140)
button8=Button(window,text="    ")
button8.place(x=730,y=140)
button9=Button(window,text="    ")
button9.place(x=755,y=140)
button3=Button(window,text="    ")
button3.place(x=780,y=140)
button10=Button(window,text="    ")
button10.place(x=705,y=165)
button11=Button(window,text="    ")
button11.place(x=730,y=165)
button12=Button(window,text="    ")
button12.place(x=755,y=165)
button3=Button(window,text="    ")
button3.place(x=780,y=165)
user=Button(window,text=" 그 외 색상선택 ",fg="black")
user.place(x=705,y=190)

l2=Label(window,text="도형 찍기: ")
l2.place(x=705,y=270)
# TODO: Add command
button=Button(window,text=" 사각형 ",fg="black")
button.grid(row=0,column=1)
button=Button(window,text="  원 형  ",fg="black")
button.grid(row=0,column=2)
button=Button(window,text=" 삼각형 ",fg="black")
button.place(x=705,y=320)

l1=Label(window,text="선 굵기: ")
l1.place(x=705,y=380)
# TODO: Add command
button1=Button(window,text=" 굵기 1 ",fg="black",command=penWidth1)
button1.place(x=705,y=400)
button1=Button(window,text=" 굵기 5 ",fg="black")
button1.place(x=760,y=400)
button2=Button(window,text="굵기 10",fg="black")
button2.place(x=705,y=430)
button2=Button(window,text=" 굵기 20",fg="black")
button2.place(x=760,y=430)
button2=Button(window,text="굵기 30",fg="black")
button2.place(x=705,y=460)
button2=Button(window,text=" 굵기 50",fg="black")
button2.place(x=760,y=460)

window.config(menu=menubar)
window.mainloop()