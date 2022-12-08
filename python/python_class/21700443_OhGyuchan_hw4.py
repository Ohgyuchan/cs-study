from tkinter import *
from tkinter.scrolledtext import *
from tkinter.filedialog import *
from tkinter import messagebox

from PIL import Image
from PIL import ImageTk

def toNightMode():
    contents.configure(background="black", foreground="white")

def toDayMode():
    contents.configure(background="white", foreground="black")

def updateBookCover():
    # bookCoverImageName이 업데이트가 되어야하기 때문에 global 선언, global 선언하지 않으면 동명의 local 변수가 생성됨.
    global bookCoverImageName
    try:
        bookCoverImageName = askopenfilename(title='책표지 변경', filetypes=((".png","*.png"),(".jpg","*.jpg"),)) 
        newBookCoverImage = ImageTk.PhotoImage(Image.open(bookCoverImageName).resize((200,200)))
        bookCoverLabel.configure(image=newBookCoverImage)
        bookCoverLabel.image = newBookCoverImage
    except Exception as e:
        messagebox.showerror("이미지 파일 선택 에러", e)
        
def setBookCoverLabelImage(imgUrl:str):
    newBookCoverImage = ImageTk.PhotoImage(Image.open(imgUrl).resize((200,200)))
    bookCoverLabel.configure(image=newBookCoverImage)
    bookCoverLabel.image = newBookCoverImage

def newFile():
    title.set('')
    author.set('')
    year.set('')
    language.set('')
    contents.delete(1.0, END)
    setBookCoverLabelImage(defaultBookCoverImageName)
    
def openFile():
    try:
        textFileName = askopenfilename(title='파일 열기', filetypes=((".txt","*.txt"),)) 
        textFile = open(textFileName, 'r')
        contents.insert(1.0, textFile.read())
        textFile.close()
        try:
            infoFileName = textFileName.split('.')[0]+'.info'
            infoFile = open(infoFileName, 'r')
            infoDictionary = eval(infoFile.read())

            title.set(infoDictionary['title'])
            author.set(infoDictionary['author'])
            year.set(infoDictionary['year'])
            language.set(infoDictionary['language'])
            setBookCoverLabelImage(infoDictionary['image'])
        except Exception as e:
            messagebox.showwarning("파일 열기 에러", ".info 파일이 없습니다.")
    except Exception as e:
        messagebox.showerror("파일 열기 에러", e)
    
def saveFile():
    text = contents.get(1.0, END)
    if text.replace(" ", "").replace("\n", "") == "":
        messagebox.showwarning("파일 저장 에러", "저장할 내용이 없습니다.")
    else:
        try:
            fileName= asksaveasfilename(defaultextension=".txt", filetypes=((".txt", "*.txt"),)) 
            saveTextFile = open(fileName, 'w')
            saveTextFile.write(text)
            saveTextFile.close()

            infoDictionary = dict()
            infoDictionary['title'] = title.get()
            infoDictionary['author'] = author.get()
            infoDictionary['year'] = year.get()
            infoDictionary['language'] = language.get()
            infoDictionary['image'] = bookCoverImageName

            infoFileName = fileName.split('.')[0]+'.info'
            infoFile = open(infoFileName,'w')
            infoFile.write(str(infoDictionary))
            infoFile.close()
        except Exception as e:
            messagebox.showerror("파일 저장 에러", e)
        
def about():
    messagebox.showinfo("정보", "HW4 입니다.")

def quit():
    master.destroy()
    master.quit()
    

master = Tk()
master.title("HW4")

defaultBookCoverImageName = "bookcover.png"
bookCoverImageName = defaultBookCoverImageName

# 메뉴 추가
menu = Menu(master)

# 파일 메뉴
fileMenu = Menu(menu)
menu.add_cascade(label="파일", menu=fileMenu)
fileMenu.add_command(label="새 파일", command=newFile)
fileMenu.add_command(label="열기", command=openFile)
fileMenu.add_command(label="저장", command=saveFile)
fileMenu.add_separator()
fileMenu.add_command(label="종료", command=quit)

# 도움말 메뉴
helpMenu = Menu(menu)
menu.add_cascade(label="도움말", menu=helpMenu)
helpMenu.add_command(label="정보", command=about)

# master에 menu 설정
master.config(menu=menu)

# masterFrame 설정  
masterFrame = Frame(master)
masterFrame.grid(column=0, row=0)

# masterFrame에 북커버 이미지 라벨 배치
bookCoverLabel = Label(masterFrame)
setBookCoverLabelImage(defaultBookCoverImageName)
bookCoverLabel.grid(column=0, row=0)

# masterFrame에 북커버 변경 버튼 배치
changBookCoverButton = Button(masterFrame, text="커버 사진 변경", command=updateBookCover).grid(column=0, row=1)

# masterFrame에 bookInfoFrame 배치
bookInfoFrame = Frame(masterFrame)
bookInfoFrame.grid(column=0, row=2)

# bookInfoFrame에 제목 라벨 배치
titleLabel = Label(bookInfoFrame, text="제목").grid(column=0, row=1)
title = StringVar()
titleEntry = Entry(bookInfoFrame, width=10, textvariable=title).grid(column=1, row=1)

# bookInfoFrame에 저자 라벨 배치
authorLabel = Label(bookInfoFrame, text="저자").grid(column=0, row=2)
author = StringVar()
authorEntry = Entry(bookInfoFrame, width=10, textvariable=author).grid(column=1, row=2)

# bookInfoFrame에 출판년도 라벨 배치
yearLabel = Label(bookInfoFrame, text="출판년도").grid(column=0, row=3)
year = StringVar()
yearEntry = Entry(bookInfoFrame, width=10, textvariable=year).grid(column=1, row=3)

# bookInfoFrame에 언어 라벨 배치
languageLabel = Label(bookInfoFrame, text="언어").grid(column=0, row=4)
language = StringVar()
languageEntry = Entry(bookInfoFrame, width=10, textvariable=language).grid(column=1, row=4)

# masterFrame에 책 내용 ScrolledText 배치
contents = ScrolledText(masterFrame)
contents.grid(column=1, row=0, rowspan=4)
contents.configure(background="white", foreground="black", height=27, width=80)

# masterFrame에 읽기 모드 프레임 배치
readModeFrame = Frame(masterFrame)
readModeFrame.grid(column=1, row=4)

# readModeFrame에 밤 버튼, 읽기 모드 라벨, 낮 버튼 일렬로 배치
toNightModeButton = Button(readModeFrame, text="밤", command=toNightMode).grid(column=1, row=0)
readLabel = Label(readModeFrame, text="읽기 모드").grid(column=2, row=0)
toDayModeButton = Button(readModeFrame, text="낮", command=toDayMode).grid(column=3, row=0)

master.mainloop()

