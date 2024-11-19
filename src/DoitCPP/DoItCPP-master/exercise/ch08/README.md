![](../../images/exercise_title.png "되새김문제")

이번 장에서는 다중 상속으로 여러 부모 클래스에서 속성과 기능을 상속받는 법을 배웠습니다. 그리고 다중 상속의 단점을 극복할 수 있는 컴포지션과 어그리게이션도 알아보았습니다. 가상 함수는 상속받아서 오버라이딩한 함수가 다형성을 지원할 수 있게 하며, 추상 클래스는 객체의 흐름만 순수 가상 함수로 설계한 후, 구현은 자식 클래스에 위임해 설계 의도에 따를 수 있게 합니다. 정적 멤버는 사용 범위를 통제하면서 객체를 생성하지 않고도 특정 속성이나 기능을 공통으로 사용할 수 있는 방법입니다.

### 문제 1 클래스 객체 곱하기 연산자 오버로딩
몬스터 A, B, C를 진화하기 위해서 A, B, C를 곱하는 연산을 오버로딩해 보세요. A×B, A×C, B×A, B×C, C×A, C×B 각각 다른 형태로 진화하도록 만들어 보겠습니다. A×B와 B×A는 다른 형태의 진화입니다. 몬스터 사이에는 상생이 있어서 상생이 좋은 경우는 능력치가 더욱 향상되고, 상생이 좋지 않은 경우에는 진화에 실패합니다. 상생 관계는 다음 표와 같습니다.

||A|B|C|
|:---:|:---:|:---:|:---:|
|A|X2|X3|실패|
|B|X5|X2|실패|
|C|실패|X4|X2|

소스 코드로 구현할 때 한 가지 요구 사항이 있습니다. 흡수한 제물의 능력치를 빼앗는 것뿐만 아니라, 제물의 특수 능력을 사용할 수 있어야 합니다. 그런데 몬스터의 특수 능력은 몬스터 A, B, C가 상속받은 부모의 함수를 오버라이딩한 함수입니다. 제물을 흡수한 몬스터는 자신의 특수 능력과 제물의 특수 능력을 모두 사용 가능합니다. 제물은 컴포지션이나 어그리게이션으로 표현합니다.

[모범 답안](https://github.com/mystous/DoItCPP/tree/main/exercise/ch08/solution_01.md "문제 1번 정답")
<br /><br />

### 문제 2 다중 상속 개념
다중 상속의 단점을 설명해 보세요. 그리고 몬스터 소스에서 다중 상속을 받는 클래스 한 가지를 선택하여 어그리게이션으로 변경해 보세요.

[모범 답안](https://github.com/mystous/DoItCPP/tree/main/exercise/ch08/solution_02.md "문제 2번 정답")
<br /><br />

### 문제 3 가상 함수 활용
커피를 제공하는 클래스를 만들어 보세요. 커피를 제공하는 기본 흐름은 order_coffee 멤버 함수로 구현합니다. order_coffee 함수는 커피 주문받기, 커피 만들기, 커피 서빙하기를 수행합니다. 그리고 이 클래스를 상속받는 다양한 커피 판매소가 있습니다. 커피 판매소1은 무인 매장이고 판매소2는 프랜차이즈, 판매소3은 주문만 키오스크를 사용합니다. 커피 판매소1~3은 모두 커피를 만드는 클래스를 상속받습니다. 이 조건에 만족하는 클래스를 설계하고 의사코드를 작성해 보세요.

[모범 답안](https://github.com/mystous/DoItCPP/tree/main/exercise/ch08/solution_03.md "문제 3번 정답")
<br /><br />

### 문제 4 추상 클래스 활용
추상 클래스를 활용해 비행기 클래스를 설계해 보세요. 비행기는 전투기, 대형 항공기, 헬리콥터, 행글라이더 4종류입니다. 필수 기능으로는 이륙, 착륙, 고도 상승, 고도 하강, 불시착입니다. 추상 클래스를 여러 개 활용해도 됩니다. 공통 기능은 상속이 아닌 컴포지션이나 어그리게이션으로 작성해 보세요.

[모범 답안](https://github.com/mystous/DoItCPP/tree/main/exercise/ch08/solution_04.md "문제 4번 정답")
<br /><br />

### 문제 5 정적 멤버 활용
정적 멤버의 특징을 활용해 자유로운 주제로 클래스를 설계하고 구현해 보세요. 설계는 클래스 다이어그램을 활용합니다.

[모범 답안](https://github.com/mystous/DoItCPP/tree/main/exercise/ch08/solution_05.md "문제 5번 정답")