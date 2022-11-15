
isUnicodeDecodeError = False
opt = True
while True : # 3번 조건을 위한 while 문
    fileName = input("Enter the file name to read: ") # 1번 조건 충족
    try : # 3-a 조건 충족
        if isUnicodeDecodeError :
            file = open(fileName, "r", encoding="utf-8") # 3-d 조건 충족
        else :
            file = open(fileName, "r")

    except Exception as e: # 3-b번 조건 충족 system error 출력
        print(e)
        continue
    
    else :
        try: # 3-a 조건 충족
            text = file.read()
            print("Successfully read %d characters" % len(text)) # 2번 조건 충족

        except Exception as e: # 3-b번 조건 충족 system error 출력
            print(e)
            if e == UnicodeDecodeError : # 3-d 조건 충족
                isUnicodeDecodeError = True
        
        else :
            uChar = set(list(text)) 
            print("%d unique characters are found" % (len(uChar))) # 4-a 조건 충족
            print(uChar) #4-b 조건 충족
            
            uChar = list(uChar)
            # 5번 조건 충족
            uChar.sort()
            print("sorted alphabetically in ascending order")
            print(uChar)
            
            # 6번 조건 충족
            uCharDict = dict()
            for u in uChar :
                uCharDict.update({u: text.count(u)})
            print(uCharDict)
            
            # 7번 조건 충족
            textSplit = text.split()
            print("%d words in total" % (len(textSplit)))
            
            # 8번 조건 충족
            uTextSplit = list(set(textSplit))
            print("%d unique words are found" % (len(uTextSplit)))
            
            # 9번 조건 충족
            uTextSplitDict = dict()
            for u in uChar :
                count = 0
                for ut in uTextSplit :
                    if ut.startswith(u):
                        count += 1
                uTextSplitDict.update({u: count})
            print("The count of words starting with each character:")
            print(uTextSplitDict)
            while True:
                while True : # 마지막 입력이 "y"가 아니면 10번으로 돌아와 반복하게 하는 while 문
                    inputChars = input("Enter at least characters to find words which start with the characters: ") # 10번 조건 충족
                    if len(inputChars) >= 2 : # 11번 조건 충족
                        break
                
                # 12번 조건 충족
                resultWords = []
                for ut in uTextSplit :
                    if ut.startswith(inputChars) :
                        resultWords.append(ut)
                
                print("%d words are found, which starts with %s" % (len(resultWords), inputChars)) # 12-a 조건 충족
                resultWords.sort() # 12-b 조건 충족
                print(resultWords) # 12-b 조건 충족
                
                for rw in resultWords : # 13번 조건 충족
                    print("%s appears %d times in %s" % (rw, text.split().count(rw), fileName))
                
                quitOption = input("Do you wnat to quit? (y): ") # 14번 조건 충족
                
                if quitOption == "y" : # 15번 조건 충족
                    break
                else :
                    continue
            break # 15번 조건 충족 시 바로 3번 조건을 위한 while 문을 벗어나기 위한 break
        finally:
            file.close() # 3-c 조건 충족
