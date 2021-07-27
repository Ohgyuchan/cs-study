# Flutter Firebase 연동하기
## 1. [Firebase 프로젝트 만들기](https://firebase.google.com/)
![프로젝트 추가](/assets/images/flutter_firebase/flutter_firebase_1.png)

## 2. Firebase에 앱 등록
> **중요**: Flutter 앱을 iOS와 Android에 모두 출시하는 경우 앱의 iOS와 Android 버전을 모두 **동일한 Firebase 프로젝트**에 등록해야 한다.

### 2.1. Android앱 등록
#### 2.1.1. [Firebase Consle](https://console.firebase.google.com/)의 프로젝트 개요 페이지 중앙에 있는 운영체제(Android)아이콘을 클릭.
![운영체제 아이콘](/assets/images/flutter_firebase/flutter_firebase_2.png)

#### 2.1.2. 앱 패키지명 입력
아래 화면처럼 Firebase에 등록할 Flutter 프로젝트의 패키지명을 입력하면 됩니다.
![안드로이드 앱등록](/assets/images/flutter_firebase/flutter_firebase_3.png)

#### 2.1.2.1. 안드로이드 패키지명 확인
&lt;project>/app/build.gradle 에서
```
...
defaultConfig {
        // TODO: Specify your own unique Application ID (https://developer.android.com/studio/build/application-id.html).
        applicationId "your.pakage.name" // Check here!
        minSdkVersion 16
        targetSdkVersion 30
        versionCode flutterVersionCode.toInteger()
        versionName flutterVersionName
    }
...
```
또는 &lt;project>/app/src/main/AndroidManifest.xml 에서
```
<manifest xmlns:android="http://schemas.android.com/apk/res/android"
    package="your.pakage.name"> // Check here!
...
```
#### 2.1.2.2. 패키지명 변경
> 혹시나 패키지명을 잘못 입력하였거나, 패키지명을 변경하고 싶을 시에는 아래 링크 참고   
[How to Change the Package Name of your Flutter app](https://medium.com/@skyblazar.cc/how-to-change-the-package-name-of-your-flutter-app-4529e6e6e6fc)

#### 2.1.3. 구성파일 다운로드
다운로드한 `google-services.json` 파일을 `<project>/android/app/`에 저장
![안드로이드 구성파일 다운로드](/assets/images/flutter_firebase/flutter_firebase_4.png)

#### 2.1.4. FirebaseSDK등록
방금 다운로드한 `google-service.json` 파일을 로드하기 위한 플러그인을 사용하기 위해서 build.gradle파일을 수정.
![안드로이드 FirebaseSDK 등록](/assets/images/flutter_firebase/flutter_firebase_5.png)

프로젝트 수준의 `build.gradle` (&lt;project&gt;/android/build.gradle)에 자리에 맞춰서 아래 코드 복사, 붙여넣기
> `// Add this line` 주석이 달린 부분 복사, 붙여넣기

    buildscript {
        repositories {
            // Check that you have the following line (if not, add it):
            google()  // Google's Maven repository
        }
        dependencies {
            ...
            // Add this line
            classpath 'com.google.gms:google-services:4.3.8'
        }
    }

    allprojects {
    ...
        repositories {
            // Check that you have the following line (if not, add it):
            google()  // Google's Maven repository
            ...
        }
    }

앱 수준의 `build.gradle` (&lt;project&gt;/android/app/build.gradle)
> `// Add this line` 주석이 달린 부분 복사, 붙여넣기

    apply plugin: 'com.android.application'
    // Add this line
    apply plugin: 'com.google.gms.google-services'

    dependencies {
        // Import the Firebase BoM
        implementation platform('com.google.firebase:firebase-bom:28.2.0')

        // Add the dependencies for the desired Firebase products
        // https://firebase.google.com/docs/android/setup#available-libraries
    }


### 2.2. iOS앱 등록
#### 2.2.1. [Firebase Consle](https://console.firebase.google.com/)의 프로젝트 개요 페이지 좌측에 있는 운영체제(iOS)아이콘을 클릭.
![운영체제아이콘](/assets/images/flutter_firebase/flutter_firebase_2.png)

### 2.2.2. 앱 패키지명 입력
아래 명령어로 패키지명 확인 후 입력
```
$ open ios/Runner.xcworkspace
```
### 2.2.3. 구성파일 다운로드
* `GoogleService-Info.plist` 다운로드 후 Runner/Runner 에 넣기
> 주의사항:   
> 반드시 `Xcode`를 통해서 넣어야 됩니다.  
> ![Xcode](/assets/images/flutter_firebase/flutter_firebase_6.png)
> `Create folder references` 가 아닌 `Create groups` 을 선택
> ![Create gruops](/assets/images/flutter_firebase/flutter_firebase_7.png)
## 3. Firebase에 데이터 추가
```
CollectionReference postdb = FirebaseFirestore.instance.collection('posts');

...

Future<void> addPost(
    String position,
    String level,
    String division,
    String dutystation,
    String description,
    String uid,
  ) {
    return postdb
        .add({
          'title': position,
          'position': position,
          'level': level,
          'dutystation': dutystation,
          'division': division,
          'approval': false,
          'description': description,
          'uid': uid,
        })
        .then((value) => print("Post Added"))
        .catchError((error) => print("Failed to add Post: $error"));
  }
```

## 4. Firebase에서 데이터 로드
```
Widget _buildStream(BuildContext context) {
    return StreamBuilder<QuerySnapshot>(
      stream: FirebaseFirestore.instance
          .collection("Collection Name")
          .snapshots(),
      builder: (context, snapshot) {
        return !snapshot.hasData
            ? Center(child: CircularProgressIndicator())
            : GridView.builder(
                padding: EdgeInsets.all(16.0),
                itemCount: snapshot.data!.docs.length,
                gridDelegate: SliverGridDelegateWithFixedCrossAxisCount(
                  mainAxisSpacing: 15,
                    childAspectRatio: 3.0 / 3.0, crossAxisCount: 1),
                itemBuilder: (context, index) {
                  DocumentSnapshot data = snapshot.data!.docs[index];
                  return PostItem(
                    uid: data['uid'],
                    id: data.id,
                    title: data['title'],
                    position: data['position'],
                    description: data['description'],
                    level: data['level'],
                    division: data['division'],
                    approval: data['approval'],
                    dutystation: data['dutystation'],
                    documentSnapshot: data,
                  );
                },
              );
      },
    );
  }
```

## 5. 보안 규칙 (Security Rules)
보안 규칙이란 
```
// 테스트모드로 프로젝트 생성 시 기본 보안 규칙
rules_version = '2';
service cloud.firestore {
  match /databases/{database}/documents {
    match /{document=**} {
      allow read, write: if
          request.time < timestamp.date(2021, 7, 22);
    }
  }
}

// 로그인 시에만 접근 가능
rules_version = '2';
service cloud.firestore {
  match /databases/{database}/documents {
    match /{document=**} {
      allow read, write: if request.auth.uid != null;
    }
  }
}

// document 별로 규칙 설정
rules_version = '2';
service cloud.firestore {
  match /databases/{database}/documents {
    match /guestbook/{entry} {
      allow read: if request.auth.uid != null;
      allow create: if request.auth.uid == request.resource.data.userId;
      allow update, delete: if request.auth.uid == resource.data.userId;
      }
      match /attendees/{userId} {
      allow read: if true;
      allow write: if request.auth.uid == userId
      		&& "attending" in request.resource.data;
    }
  }
}
```

## 6. [당근마켓UI 클론에 Firebase CRUD 적용하기 (Security Rules)](https://github.com/Ohgyuchan/flutter_dev/tree/firebase/carrot_clone)

* 참고 자료   
[Firebase Security-rules (한글)](https://gist.github.com/Dohyunwoo/b8370f208619c7f44a2a13fb390e1514)   
[Firebase 보안 규칙 (공식문서)](https://firebase.google.com/docs/rules)   
[Firebase 기본 보안 규칙 (공식문서)](https://firebase.google.com/docs/rules/basics)   
