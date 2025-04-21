# TMap

- 키-값 쌍을 저장하는 컨테이너
- TPair<KeyType, ElementType>으로 구성
- Key는 GetHash, operator==를 지원해야 한다.
- TMap은 SparseArray를 기반으로 구현되어 있다.

## Reference

- [TMap](https://dev.epicgames.com/documentation/ko-kr/unreal-engine/map-containers-in-unreal-engine)

```text
UObject와 TWeakObj의 동등 비교 문제 해결
UObject나 TWeakObj가 무효화되었을 때 실제로 포인터가 자동으로 nullptr로 설정되지 않지만, 다음과 같은 이유로 == 비교에서 동일하게 취급될 수 있습니다:


UObject 포인터 비교 동작
커스텀 비교 연산자:


언리얼 엔진은 UObject 포인터에 대한 == 연산자를 오버로드하고 있습니다
이 오버로드된 연산자는 단순 메모리 주소 비교가 아닌 특별한 비교 로직을 사용합니다
내부 식별자 비교:


UObject는 내부적으로 고유 식별자(ObjectID)를 가지고 있습니다
무효화된 UObject는 이 식별자가 특수한 값으로 설정될 수 있습니다
TWeakObj의 경우
FWeakObjectPtr 기반 구현:


TWeakObj는 내부적으로 FWeakObjectPtr을 사용합니다
무효화된 경우 내부 정보가 특정 패턴으로 리셋됩니다
비교 연산자 오버로딩:


무효화된 TWeakObj들은 내부적으로 동일한 상태 정보를 가질 수 있습니다
이로 인해 서로 다른 객체를 참조했던 포인터들이 무효화 후에 동일하게 비교될 수 있습니다
이러한 이유로 코드에서는 VisitedKeys 세트를 사용하여 중복된 무효화 키를 필터링하여, 무효화된 키들이 모두 동일하게 취급되어 결과에 중복 추가되는 문제를 방지하고 있습니다.
```