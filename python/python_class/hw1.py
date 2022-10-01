books = ["Alice's Adventures in Wonderland", "Little Women", "Pride and Prejudice", "The Scarlet Letter", "The Adventures of Sherlock Homes", " A Tale of Two Cities", "The Great Gatsby", "Don Quixote", "Adventures of Huckleberry Finn", "Anne of Green Gables", "Uncle Tom's Cabin", "Frankenstein; or, The Modern Prometheus"]
authors = []
summaries = []

def operation() :
    startProgram()
    while True:
        print("Test")
        

def printMenu() :
    for i in range(len(books)) :
        print(i, books[i])

def divider() :
    for i in range(40) :
        print("#", end="")

def startProgram() :
    print("도서관 서비스 프로그람")
    divider()
    printMenu()
    divider()

