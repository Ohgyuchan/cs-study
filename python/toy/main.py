import os, subprocess;

print(os.system('tasklist')) #프로세스 목록 출력
#os.system('taskkill /f /pid 11172') #pid를 사용한 프로세스 종료
# os.system('taskkill /f /im python.exe') #프로세스명을 사용한 프로세스 종료