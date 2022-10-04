# 책 제목 리스트
books = ["오만과 편견",
         "위대한 게츠비",
         "프랑켄슈타인",
         "드라큘라",
         "어둠의 마음",
         "로빈슨 크루소",
         "모비딕",
         "황야의 절규",
         "이상한 나라의 앨리스",
         "아메리카의 비극"]

# 책 저자 리스트
authors = ["제인 오스틴",
           "F. 스콧 피츠제럴드",
           "메리 셸리",
           "브램 스토커",
           "조지프 콘래드",
           "다니엘 디포",
           "허먼 멜빌",
           "잭 런던",
           "루이스 캐럴",
           "시어도어 드레이저"]

summaries = ["《오만과 편견》 (Pride and Prejudice)은 제인 오스틴이 쓴 소설이다. 스무 살 때(1796년~1797년) 쓴 소설로 처음 완성되었을 때는 제목이 첫인상 이었지만, 그 제목으로 한번도 출판되지 않았다. 그녀의 두번째 작품으로 1813년 최초로 출간되었으며, 영국의 가장 위대한 명작들 중 하나로 사랑받고 있다.",
             "《위대한 개츠비(The Great Gatsby)》는 미국의 작가 F. 스콧 피츠제럴드의 소설이다. 첫 출판일은 1925년 4월 10일이며, 이야기는 1922년 여름의 뉴욕시와 롱 아일랜드에서 펼쳐진다. 피츠제럴드는 그 자신이 '재즈 시대(Jazz Age)'라 이름 붙인 시대를 이 소설에서 그려냈다.",
             "프랑켄슈타인(Frankenstein)은 메리 셸리가 열아홉의 나이에 놀라운 상상력으로 쓴 과학소설이다. 무생물에 생명을 부여할 수 있는 방법을 알아낸 물리학자 프랑켄슈타인이 시체로 만든 괴물에 생명을 불어넣는다. 하지만 인간 이상의 힘을 발위하는 괴물은 오히려 흉측하고 괴기스러운 모습의 자신을 만든 창조주에 대한 증오심으로 복수를 꾀하는 내용이다. 부제는‘근대의 프로메테우스(The Modern Prometheus)’이며 첫 판은 1818년에 런던에 익명으로 출판되었다가 1823년에 프랑스에 그녀의 이름으로 두 번째 판이 출판되었다.",
             "《드라큘라》(Dracula)는 아일랜드의 작가 브람 스토커가 쓴 1897년작 소설로, 흡혈귀인 드라큘라 백작이 주인공이다. 드라큘라는 사람들의 피를 빨아 먹으며 자신의 삶을 연장시키고 젊음을 유지하려고 한다. 다른 사람의 희생을 전혀 개의치 않는 악의 화신으로 표현된 드라큘라 백작을 반헬싱 무리들이 뒤쫓는 이야기를 편지, 전보, 일기, 신문기사 등에 의한 기술로 다루었다. 극도의 공포를 잘 표현했으며 이를 통해 인간 내면에 내재하고 있는 나약함과 인간이 지니고 있는 다양한 욕망을 표현하고 있다. 소설 드라큘라는 아일랜드의 흡혈귀 전설 그리고 드라큘라 이전에 쓰여진 같은 흡혈귀 작품인 카밀라(1872년)의 영향을 강하게 받았다.",
             "조셉 콘래드 자신의 1890년 아프리카 여행 경험을 토대로 쓴 《어둠의 마음》은 콘래드의 단편 중 단연 최고이자, 모든 작품을 통틀어도 가장 훌륭한 작품이다. 유려하고, 대담하고, 실험적이고, 퇴행적이며, 풍자적이고, 그러면서도 매우 인간적인 이 작품은 1899년 첫 연재부터 끊임없는 논란과 분석의 대상이었다.",
             "《로빈슨 크루소》(Robinson Crusoe)는 영국의 작가 대니얼 디포가 1719년에 발표한 장편 소설이자, 그 소설의 주인공 이름이기도 하다. 이 소설은 로빈슨 크루소가 무인도에 표착하는 사건을 다룬 가상의 자서전이다. 원제는 《요크의 선원 로빈슨 크루소의 생애와 이상하고 놀라운 모험(The Life and Strange Surprising Adventures of Robinson Crusoe of York)》이다. 요크 태생의 크루소가 모험 항해를 나서다가 바다에 난파되어 무인도에 표착된다. 무인도에서 혼자의 힘으로 생활을 설계한 다음 탈출할 배를 만든다. 그때 식인종에게 먹힐뻔한 원주민인 프라이데이를 구출하여 하인으로 만들고 무인도에 기착한 영국의 반란선을 진압해 선장을 구출하여 28년 만에 고국으로 들어오는 이야기이다.",
             "《모비 딕》(Moby Dick, 白鯨)은 허먼 멜빌의 장편 소설이다. 모비딕이라는 흰 고래에게 한쪽 다리를 잃은 선장 에이햅이 복수심에 휩싸여 광기와도 같은 추격을 하고 운명에 도전하는 모습을 상징적으로 그린 내용이다. 《모비 딕》은 포경선 선원들의 생활을 생생하게 나타내었을 뿐 아니라 인간이 지니고 있는 자유의지, 악, 숙명 등을 담고 있다. 1851년 런던에서 리처드 벤틀리에 의해 《고래》(The Whale)라는 이름의 세 권짜리 삭제판으로 처음 출판되었다. 이어서 무삭제판은 1851년 11월 14일 뉴욕에서 Harper and Brothers에 의해 한 권짜리로 나오게 된다.",
             "캘리포니아에 있는 목가적인 목장에서 자란 가정 개였던 버크는 그 집에 드나드는 정원사에 의해 납치되어 큰 금광이 발견된 알래스카로 팔려가 썰매를 끄는 잔인한 삶으로 바뀌게 된다. 버크는 그곳에서 문명 세계와는 완전 다른 약육강식의 세계와 무정한 인간의 혹사를 경험하게 된다. 후에 버크는 다정한 주인 존 소튼을 만나게 되고 충성을 다짐하지만 불행히도 존 소튼은 죽게 된다. 이 사건은 버크 내부의 야성을 불러일으켜 결국 북극의 이리떼에 가담하게 되면서 존경과 두려움의 대상인 리더가 되어가는 과정의 이야기를 담고 있다.",
             "《이상한 나라의 앨리스》(영어 원제 :Alice's Adventures in Wonderland)는 영국의 수학자이자 작가인 찰스 루트위지 도지슨이 루이스 캐럴이라는 필명으로 1865년에 발표한 소설이다. 이 소설은 앨리스라는 이름의 소녀가 토끼굴에 빠져 기묘하고 의인화된 생명체들이 사는 환상 속 세계에서 모험을 겪는 이야기를 담고 있다. 본문에는 동화 형식을 빌려 도지슨과 그의 친구들과 관련된 일화나 영국 아동들의 강제적인 암기 수업을 풍자하는 내용이 많이 포함되어 있다. 이상한 나라의 앨리스 이야기는 아이들뿐만 아니라 어른들까지 전 세계의 많은 사람들 사이에서 계속 사랑받고 있다.",
             "주인공 클라이드 그리피스는 캔자스 시의 순회 목사의 집안에서 태어났다. 그는 따분한 가정 생활에서 벗어나, 돈과 사회적 지위를 동경하게 되었다. 가난 때문에 심한 제약을 받고 불우하게 자란 주인공 클라이드가 자신이 동경해 온 상류사회에로의 진출을 위해 부유한 집 딸 산드라와의 결혼을 꿈꾼다.",]              # 책 줄거리 리스트

# 대여한 책 리스트
borrowed = [False, False, False, False, False, False, False, False, False, False]

def borrowMenu(index) : # 책 대여 함수
    if borrowed[index] : # 과제 11번 조건 충족
            cmd = input("이미 빌린 책입니다. 반납하시려면 'c'를 누르세요: ")
            if cmd == 'c' : # 과제 12번 충족
                borrowed[index] = False # 대여 취소를 했다면 해당 index 값 False
                print("반납되었습니다.") 
            else : # 과제 13번 충족
                print("반납되지 않았습니다.")
    else:            
        opt = input("이 책을 빌리려면 'b'를 누르세요: ") # 과제 8번 조건 충족
        
        if opt == 'b' :
            borrowed[index] = True # 빌린 책의 index 값 True로 변경
            print("성공적으로 대여하였습니다.")
        else : # 입력받음 opt의 값이 b가 아니면 Not borrowed 출력, 과제 10번 조건 충족
            print("대여하지 않았습니다.")
    divider()
    
    while True : # 과제 17번 조건 충족
        ch = input("도서 목록으로 이동하시려면 'y', 프로그램을 종료하시려면 'q'을 누르세요: ") # 과제  14번 조건 충족
        if ch == 'y' :
            return back2list() # 과제 15번 A 조건 충족
        elif ch == 'q' :
            return -1

def back2list() : # 책 제목 리스트로 돌아가는 옵션 선택 함수
    cmd = input("1. 전체, 2. 빌리지 않은 책만: ")
    if cmd.isdigit() :
        cmd = int(cmd)
        if cmd == 1 or cmd == 2 :
            return cmd
        else :
            return back2list() # 과제 15번 B 조건 충족
    else :
        return back2list()

def printBookInfo(index) : # 책 상세정보 출력 함수
    divider()
    print("제목:", books[index])
    print("저자:", authors[index])
    print("줄거리 요약:", summaries[index])
    divider()

def bookChoice(cmd) : # 책 고르는 함수
    while True : 
        if cmd == 2 : # 과제 15번 D 조건 충족
            notBorrowedBookNums = [i + 1 for i in range(len(borrowed)) if not borrowed[i]]
        else :
            notBorrowedBookNums = [i + 1 for i in range(len(books))]
        bookNum = input("책 번호 입력: ") # 책 번호 입력 과제 5번 조건 충족
        if bookNum.isdigit() : # 입력 받은 책 번호가 숫자인지 확인
            bookNum = int(bookNum) # 숫자라면 숫자로 재대입
            if bookNum in notBorrowedBookNums : # 입력이 Wrong Number가 아닐 때만 반복문을 탈출, 과제 7번 조건 충족
                break 
            else : # 책 번호가 리스트 범위를 넘는 수라면 틀린 번호 출력
                print("잘못된 번호입니다.")
        else :
            print("잘못된 번호입니다.")
            
    printBookInfo(bookNum - 1) # 과제 6번 조건 충족
    return borrowMenu(bookNum - 1)

def printGoodByeMenu() :
    divider()
    print("프로그램 종료")
    # 과제 16번 조건 충족
    print(borrowed.count(True), "권의 책을 빌렸습니다.")
    printBorrowedBooks()
    print("잘 가요~")

def printBorrowedBooks() :
    for i in range(len(books)) :
        if borrowed[i] :
            print("\t", books[i])

def operation() : # 프로그램을 구동하는(Operate) 함수
    startProgram() # 프로그램 시작
    cmd = 0
    while True:
        if cmd == -1 : # 과제 16번 조건 충족
            printGoodByeMenu()
            break
        elif cmd == 1 : # 과제 15번 C 조건 충족
            printBooks()
        elif cmd == 2 : # 과제 15번 D 조건 충족
            printNotBorrowed()
        cmd = bookChoice(cmd)

def printNotBorrowed() : # 빌리지 않은 책 제목만 출력하는 함수
    divider()
    for i in range(len(books)) :
        if borrowed[i] : # borrowed 인덱스 값이 True면 continue
            continue
        else :
            print(i + 1, books[i]) # 빌리지 않은 책 제목은 번호와 함께 출력
    divider()

def printBooks() : # 책 제목들을 출력해주는 함수
    divider() # 과제 2번 조건 충족
    for i in range(len(books)) :
        print(i + 1, books[i])
    divider() # 과제 4번 조건 충족

def divider() : # 반복문을 이용해서 문자를 40개를 출력해서 구분선을 생성하는 함수
    for i in range(40) :
        print("#", end="")
    print()

def startProgram() : # 프로그램 시작 시 처음 메뉴 출력
    print("==도서 대출 관리 프로그램에 접속해주셔서 감사합니다==") # 과제 1번 조건 충족
    printBooks() # 과제 3번 조건 충족

operation() # 프로그램을 작동시키는 함수 호출

