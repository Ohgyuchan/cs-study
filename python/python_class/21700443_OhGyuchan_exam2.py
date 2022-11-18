
import random
opt = True
while True :
    fileName = input("Enter a file name: ")
    try :
        file = open(fileName, "r", encoding="utf-8")
        
    except Exception as e:
        print(e)
    
    else :
        try:
            text = file.read()
            print("The length of text: %d" % len(text)) 

        except Exception as e:
            print(e)
        
        else :
            delimiter = input("Enter a delimiter: ")
            
            textSplit = text.split(delimiter)
            print("*" * 30)
            print("The number of sentences: %d" % (len(textSplit)))
            
            validSentence = []
            for ts in textSplit :
                if ts.strip() != "":
                    validSentence.append(ts.strip())

            print("The number of valid sentences: %d" % len(validSentence))
            
            sentenceDict = dict()
            for i in range(len(validSentence)) :
                sentenceDict.update({i+1: validSentence[i]})
            
            print("**** Sentence Dictionary ****")
            print(sentenceDict)
            
            while True :
                number = input("Enter a sentence number to print: ")
                if number.isdigit() :
                    number = int(number)
                    if len(validSentence) < number or number < 1 :
                        print("Wrong sentence number, it must be between 1 and %d" % len(validSentence))
                    else :
                        print(sentenceDict.get(number))
                        break
                else :
                    print("not a number")

            print("**** A Quote for you ****")
            rn = int(random.randrange(1, len(validSentence)))
            print(rn, sentenceDict.get(rn))
            
            while True :
                ch = input("Enter a character: ")
                starts = []
                for vs in validSentence :
                    if vs.startswith(ch) :
                        starts.append(vs)
                if not starts :
                    print("There is no sentence starting with %s" % ch)
                else :
                    print("The sentences which start with %s are" % ch)
                    for s in starts :
                        print(s)
                    break
            break 
        finally:
            file.close() 
