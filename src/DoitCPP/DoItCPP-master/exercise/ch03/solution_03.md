#### 문제 3 동적 메모리 할당 이해
동적으로 할당한 메모리는 반드시 해제해야 합니다. 그 이유는 무엇일까요?<br>
그리고 일반 변수는 왜 메모리 해제를 관리하지 않아도 될까요?<br>
최대한 자세하게 서술해 보세요.
<br/><br/>

---

#### 모범 답안 과 설명
##### 답안
[동적으로 할당한 메모리는 반드시 해제해야 하는 이유］
</br>

1. 메모리 누수 방지:
동적 메모리 할당은 프로그램 실행 중 필요에 따라 메모리를 할당하는 방식입니다. 반면, 일반 변수는 프로그램 시작 시 컴파일러에 의해 메모리가 할당됩니다.
문제는 사용하지 않는 동적 메모리가 프로그램 종료 후에도 해제되지 않으면 메모리 누수가 발생한다는 것입니다. 이는 메모리 사용량이 점점 증가하여 시스템 성능 저하, 심지어 시스템 충돌까지 초래할 수 있습니다.
</br>

2. 메모리 낭비 방지:
프로그램이 종료되더라도 동적 메모리가 해제되지 않으면 메모리가 낭비됩니다. 특히, 큰 크기의 데이터를 다루는 프로그램에서 메모리 낭비는 심각한 문제가 될 수 있습니다.
메모리 해제는 사용하지 않는 메모리를 다시 시스템에 반환하여 다른 프로그램에서 사용할 수 있도록 합니다. 이는 시스템 전체의 메모리 사용 효율성을 높이는 데 중요한 역할을 합니다.
</br>

3. 안정적인 프로그램 운영:
메모리 누수는 예측 불가능한 시스템 동작을 초래하여 프로그램 오류, 충돌, 심지어 시스템 전체의 불안정성을 야기할 수 있습니다.
메모리 해제는 프로그램이 사용하는 메모리를 명확하게 관리하여 안정적인 운영 환경을 유지하는 데 필수적입니다.
</br>

4. 효율적인 메모리 관리:
동적 메모리 할당 및 해제는 프로그래머에게 메모리 사용에 대한 직접적인 제어 권한을 제공합니다.
이를 통해 프로그래머는 필요에 따라 메모리를 효율적으로 할당하고 해제하여 메모리 사용량을 최소화하고 프로그램 성능을 향상시킬 수 있습니다.
</br></br>

[일반 변수는 메모리 해제 관리가 필요 없는 이유]

1. 자동 메모리 해제:
일반 변수는 프로그램 종료 시 컴파일러에 의해 자동으로 메모리가 해제됩니다.
따라서 프로그래머가 직접 메모리 해제를 관리할 필요가 없습니다.
</br>

2. 명확한 범위:
일반 변수는 함수 범위 내에서만 유효하며, 함수 종료 시 자동으로 메모리가 해제됩니다. 따라서 메모리 누수가 발생할 가능성이 낮습니다.
반면 동적 메모리는 프로그램 종료 전까지 유지될 수 있으며, 명확하게 해제하지 않으면 메모리 누수가 발생할 수 있습니다.
</br>


##### 설명
동적 메모리 할당 해제는 메모리 누수, 낭비, 프로그램 오류를 방지하고 메모리 사용 효율성을 높이는 데 중요한 역할을 합니다.
일반 변수는 자동 메모리 해제 기능 덕분에 메모리 관리가 간편하지만, 동적 메모리에 비해 유연성이 떨어집니다.
상황에 따라 적절한 메모리 관리 방식을 선택하는 것이 중요합니다.

[문제로 돌아 가기](README.md "문제로 돌아 가기")