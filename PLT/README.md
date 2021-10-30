## PLT
**프로그래밍언어론** 수강신청하기 전으로 돌아가고 싶다...

### How to compile(Using by Terminal)
#### AE or WAE or FAE or LFAE

#### Interpreter
```
$> java -cp ./bin edu.handong.csee.plt.Main "{+ 2 3}"
(numV 5)
```

OR

```
$> java -cp [class_path_settings] edu.handong.csee.plt.Main "{+ 2 3}"
(numV 5)
```

#### With '-p' option (execute only parser)
```
$> java -cp [class_path_settings] edu.handong.csee.plt.Main -p "{+ 2 3}"
(add (num 2) (num 3))
```
