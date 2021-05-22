# 3.1. git commit 수정

날짜 변경
1. 마지막 Commit 날짜를 현재 날짜로 설정
```
git commit --amend --no-edit --date "$(date)"
```

2. 마지막 Commit 날짜를 임의의 날짜로 설정
```
git commit --amend --no-edit --date "Mon 20 Aug 2018 20:19:19 KST"
```