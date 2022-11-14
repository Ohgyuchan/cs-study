
isUnicodeDecodeError = False
opt = True
while True :
    fileName = input("Enter the file name to read: ")
    try : 
        if isUnicodeDecodeError :
            file = open(fileName, "r", encoding="utf-8")
        else :
            file = open(fileName, "r")

    except Exception as e:
        print("예러 발생", e)
        continue
    
    else :
        try: 
            text = file.read()
            print(len(text))

        except Exception as e:
            print("에러 발생", e)
            if e == UnicodeDecodeError :
                isUnicodeDecodeError = True
        
        else :
            uChar = set(list(text))
            print("%d unique characters are found" % (len(uChar)))
            print(uChar)
            
            uChar = list(uChar)
            uChar.sort()
            print("sorted alphabetically in ascending order")
            print(uChar)
            
            uCharDict = dict()
            for u in uChar :
                uCharDict.update({u: text.count(u)})
            print(uCharDict)
            
            textSplit = text.split()
            print("%d words in total" % (len(textSplit)))
            
            uTextSplit = list(set(textSplit))
            print("%d unique words are found" % (len(uTextSplit)))
            
            uTextSplitDict = dict()
            for u in uChar :
                count = 0
                for ut in uTextSplit :
                    if ut.startswith(u):
                        count += 1
                uTextSplitDict.update({u: count})
            print(uTextSplitDict)
            
            while True :
                while True :
                    inputChars = input("Enter at least characters to find words which start with the characters: ")
                    if len(inputChars) >= 2 :
                        break
                resultWords = []
                for ut in uTextSplit :
                    if ut.startswith(inputChars) :
                        resultWords.append(ut)
                
                print("%d words are found, which starts with %s" % (len(resultWords), inputChars))
                print(resultWords)
                
                for rw in resultWords :
                    print("%s appears %d times in %d" % (rw, text.count(rw), fileName))
                
                quitOption = input("Do you wnat to quit? (y): ")
                
                if quitOption == "y" :
                    break
            break
        finally:
            file.close()
