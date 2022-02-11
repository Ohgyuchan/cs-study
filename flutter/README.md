Flutter

Firebase  
Firebase Auth  
SNS Login  
Flutter Tips

`android hash key` 명령어  
```ssh
keytool -exportcert -alias androiddebugkey -keystore ~/.android/debug.keystore -storepass android -keypass android | openssl sha1 -binary | openssl base6
```

`android SHA-1 & SHA-256 key` 명령어
```ssh
keytool -list -v -keystore ~/.android/debug.keystore -alias androiddebugkey -storepass android -keypass android 
```
