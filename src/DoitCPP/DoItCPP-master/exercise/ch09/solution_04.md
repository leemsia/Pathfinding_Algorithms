#### 문제 4 인터페이스 분리 원칙(ISP)
우리가 사용하는 라이브러리 또는 프레임워크에서 인터페이스 분리 원칙이 주요 설계 원칙인 예를 찾아서 설명해 보세요.
<br/><br/>

---


#### 모범 답안
##### 답안
이번 문제는 꽤 난이도가 있는 문제 입니다. ISP는 인터페이스는 세밀해야 하고 클래스는 꼭 필요한 인터페이스에만 최소한으로 의존해야 한다는 원칙입니다. STL중 ISP를 가장 명확하게 확인할 수 있는 것이 반복자 카테고리 입니다.

STL중 자료를 저장하는 컨테이너는 저장된 데이터(엘리먼트)를 순회 하기 위해서 반복자(iterator)를 사용합니다. 반복자 카테고리는 반복자의 다양한 종류입니다. 순회를 하나씩 모두 순회하거나 순차적으로 데이터를 업데이트 하는 등 다양한 반복자가 존재 합니다. STL의 컨테이너는 데이터의 특성에 맞게 특정 반복자 카테고리만을 사용할 수 있습니다.

바로 ISP의 최소한의 필요한 인터페이스에만 의존해야 한다는 원칙이 적용된 것입니다. 예를 들면  input_iterators는 데이터를 한 번만 읽을 수 있고 순차 접근만 가능합니다. std::find나 std::copy에서 사용합니다. bidirectional_iterators는 데이터를 여러 번 읽거나 쓸 수 있으며, 양방향으로 가능합니다. std::list, std::set, std::map 등에서 사용됩니다.

std::find에서는 bidirectional_iterator을 사용할 수 없습니다. 즉, 해당 컨테이너에 적합한 반복자만을 사용하는 것입니다.

[문제로 돌아 가기](README.md "문제로 돌아 가기")