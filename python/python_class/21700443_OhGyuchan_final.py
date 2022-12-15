from tkinter import *
from tkinter.scrolledtext import *
from tkinter.filedialog import *
from tkinter import messagebox

from PIL import Image
from PIL import ImageTk
class Book():
    histDict = dict()
    def __init__(self, directory: str) :
        self.directory = directory
        
def newFile():
    searchEntry.delete(0, END)
    st1.delete(1.0, END)
    st2.delete(1.0, END)
    
    bookTitleLabel.configure(text=bookTitleText)
    bookInfoLabel.configure(text=bookInfoText)
    searchHistoryLabel.configure(text=searchHistoryText)
    searchResultsLabel.configure(text=searchResultsText)
    
def openFile():
    try:
        bookFileName = askopenfilename(title='Open', filetypes=((".txt","*.txt"),)) 
        bookFile = open(bookFileName, 'r')
        bookText = bookFile.read()
        book = Book(bookFileName)
        booTitle = book.directory.split("/")[-1].split(".")[0]
        bookTitleLabel.configure(text=booTitle)
        
        bookInfo = "Length of the text: %d\nCount of words: %d" % (len(bookText), len(bookText.split()))
        bookInfoLabel.configure(text=bookInfo)
        st1.insert(1.0, bookText)
        bookFile.close()
        
        try:
            histFileName = bookFileName.split('.')[0]+'.hist'
            histFile = open(histFileName, 'r')
            book.histDict = eval(histFile.read())
            searchHistory = "%s" % (book.histDict)
            searchHistoryLabel.configure(text=searchHistory)
            
        except Exception as e:
            messagebox.showwarning("파일 열기 warning", ".hist 파일이 없습니다.")
        
    except Exception as e:
        messagebox.showerror("파일 열기 에러", e)
        
def search():
    if(len(searchEntry.get()) == 0 or len(searchEntry.get().replace(" ", "")) == 0) :
        messagebox.showerror("검색 에러", "No search keyword or text to search")
    else :
        se = searchEntry.get()
        text = "%s" % st1.get(1.0, END)
        sentences = text.split("\n")
        print(sentences)
        sa = ""
        ca = 0
        for s in sentences :
            if s.count(se) > 0 :
                sa = sa + "\n" + s 
                ca += 1
        st2.insert(1.0, sa)
    searchResultsLabel.configure(text="%d sentences were found." % ca)

def saveFile():
    text = st2.get(1.0, END)
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

def exit():
    master.destroy()
    master.quit()
    
master = Tk()
master.title("Final")

menu = Menu(master)

fileMenu = Menu(menu)
menu.add_cascade(label="File", menu=fileMenu)
fileMenu.add_command(label="New", command=newFile)
fileMenu.add_command(label="Open", command=openFile)
fileMenu.add_separator()
fileMenu.add_command(label="Exit", command=exit)

historyMenu = Menu(menu)
menu.add_cascade(label="History", menu=historyMenu)
historyMenu.add_command(label="Save", command=saveFile)

masterFrame = Frame(master)
masterFrame.grid(column=0, row=0)

bookTitleText = "Book Title"
bookInfoText = "Book Info"
searchHistoryText = "Search History"
searchResultsText = "Search Results"

bookTitleLabel = Label(masterFrame, text=bookTitleText)
bookTitleLabel.grid(column=0, row=0)

bookInfoLabel = Label(masterFrame, text=bookInfoText)
bookInfoLabel.grid(column=0, row=1)

searchHistoryLabel = Label(masterFrame, text=searchHistoryText)
searchHistoryLabel.grid(column=0, row=2)

searchFrame = Frame(masterFrame)
searchFrame.grid(column=0, row=4)

searchEntry = Entry(searchFrame)
searchEntry.grid(column=0, row=0)

searchButton = Button(searchFrame, text="Search", command=search)
searchButton.grid(column=1, row=0)

searchResultsLabel = Label(masterFrame, text=searchResultsText)
searchResultsLabel.grid(column=0, row=5)

st1 = ScrolledText(masterFrame)
st1.grid(column=1, row=0, rowspan=4)

st2 = ScrolledText(masterFrame)
st2.grid(column=1, row=4, rowspan=4)

master.config(menu=menu)

master.mainloop()