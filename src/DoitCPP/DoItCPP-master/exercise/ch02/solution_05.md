#### 문제 5 표현식과 연산자
다음 코드에서 컴파일 오류가 발생하는 부분이 있습니다. 위치와 원인을 설명해 보세요.
<br/><br/>

---

#### 모범 답안 과 설명
##### 답안
a / b 연산의 결과는 int 타입입니다.
float 타입 변수 result_1에 저장할 때 정보 손실이 발생할 수 있습니다.
</br>

해결방법
```cpp
int a = 10, b = 3;
float result_2 = (float)a / b;
```

##### 설명
(float)a 형태로 캐스팅하여 a를 float 타입으로 변환합니다.

[문제로 돌아 가기](README.md "문제로 돌아 가기")