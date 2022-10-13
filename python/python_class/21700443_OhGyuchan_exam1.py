books = []
menus = ["list", "delete", "register", "quit"]
print("내 책들")
while True :
    print("="*20)
    for i in range(len(menus)) :
        print("#", menus[i])
    print("="*20)
    while True :
        menu = input("메뉴 입력: ")
        if menu in menus :
            break
        
    if menu == "list" :
        if not books :
            print("아직 등록된 책이 없어요")
        else :
            print("="*20)
            for i in range(len(books)) :
                print("[%d] %s" % (i+1, books[i]))
    if menu == "quit" :
        print("="*20)
        break
    
    if menu == "register" :
        while True :
            book = input("등록할 책 이름을 입력(메뉴로 돌아가려면 그냥 엔터): ")
            if book == " " or book == "": 
                break
            else :
                if book in books :
                    print("이미 등록된 책 입니다.")
                else :
                    books.append(book)
    
    if menu == "delete" :
        dBook = input("삭제할 책 번호나 책 제목을 입력: ")
        if dBook.isnumeric() :
            dBook = int(dBook) - 1
            if dBook >= 0 and dBook < len(books) :
                bookName = books[dBook]
                confirm = input("%s 을 삭제(y): " % (bookName))
                if confirm == "y" :
                    books.remove(bookName)
                    print(bookName, "삭제 완료")
                else :
                    print("취소")
            else :
                print("잘못된 입력")
        else :
            if dBook in books :
                books.remove(dBook)
                print(dBook, "삭제 완료")
            else :
                print("잘못된 입력")