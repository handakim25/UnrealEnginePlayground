// Fill out your copyright notice in the Description page of Project Settings.


#include "MapTest.h"

// References
// https://dev.epicgames.com/documentation/ko-kr/unreal-engine/map-containers-in-unreal-engine

// Sets default values
AMapTest::AMapTest()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

// Called when the game starts or when spawned
void AMapTest::BeginPlay()
{
	Super::BeginPlay();

	// Add : Adds a key-value pair to the map. If the key already exists, it updates the value.
	// Emplace : Adds a key-value pair to the map, constructing the value in place. This is more efficient than Add when the value type is expensive to copy.
	TMap<FString, int32> AddMap;
	AddMap.Add(TEXT("A"), 1);
	AddMap.Add(TEXT("B"), 2);
	AddMap.Add(TEXT("C"), 3);
	// AddMap == {A: 1, B: 2, C: 3}
	for (const auto& Pair : AddMap)
	{
		UE_LOG(LogTemp, Display, TEXT("Key: %s, Value: %d"), *Pair.Key, Pair.Value);
	}
	AddMap.Add(TEXT("A"), 4);
	// AddMap == {A: 4, B: 2, C: 3}
	UE_LOG(LogTemp,Display, TEXT("AddMap.Add(A, 4)"));
	for (const auto& Pair : AddMap)
	{
		UE_LOG(LogTemp, Display, TEXT("Key: %s, Value: %d"), *Pair.Key, Pair.Value);
	}
	AddMap.Add(TEXT("D"));
	// AddMap == {A: 4, B: 2, C: 3, D: 0}
	UE_LOG(LogTemp, Display, TEXT("AddMap.Add(D)"));
	for (const auto& Pair : AddMap)
	{
		UE_LOG(LogTemp, Display, TEXT("Key: %s, Value: %d"), *Pair.Key, Pair.Value);
	}

	// Append : Adds all key-value pairs from another map to the current map.
	// If a key already exists, it updates the value.
	// 문서에서는 Append 호출 시에 Append 후의 내용이 비워진다고 했지만, 우측값일 경우에만 비워진다.
	TMap<FString, int32> AppendMap;
	AppendMap.Add(TEXT("D"), 4);
	AppendMap.Add(TEXT("E"), 5);
	AppendMap.Add(TEXT("F"), 6);
	// AppendMap == {D: 4, E: 5, F: 6}
	UE_LOG(LogTemp, Display, TEXT("AppendMap == {D: 4, E: 5, F: 6}"));
	// AddMap.Append(AppendMap);
	AddMap.Append(MoveTemp(AppendMap));
	// AddMap == {D: 4, E: 5, F: 6, A: 4, B: 2, C: 3}
	// AppendMap == {}
	for (const auto& Pair : AddMap)
	{
		UE_LOG(LogTemp, Display, TEXT("Key: %s, Value: %d"), *Pair.Key, Pair.Value);
	}
	UE_LOG(LogTemp,Display, TEXT("Append Map Size: %d"), AppendMap.Num());

	// Value의 참조는 다음 Map 변화 전까지 유효하다.
	int& AddedValue = AddMap.Add(TEXT("G"), 7);
	AddedValue = 8;
	// AddMap == {D: 4, E: 5, F: 6, A: 4, B: 2, C: 3, G: 8}
	for (const auto& Pair : AddMap)
	{
		UE_LOG(LogTemp, Display, TEXT("Key: %s, Value: %d"), *Pair.Key, Pair.Value);
	}
	
	// Iterate
	// ranged-for
	UE_LOG(LogTemp,Display,TEXT("Iterate"));
	UE_LOG(LogTemp,Display,TEXT("Ranged for"))
	for (const auto& Pair : AddMap)
	{
		UE_LOG(LogTemp, Display, TEXT("Key: %s, Value: %d"), *Pair.Key, Pair.Value);
	}
	// Iterator
	UE_LOG(LogTemp, Display, TEXT("Iterator"));
	for (TMap<FString, int32>::TIterator It(AddMap); It; ++It)
	{
		UE_LOG(LogTemp, Display, TEXT("Key: %s, Value: %d"), *It.Key(), It.Value());
	}
	// for (auto It = AddMap.CreateIterator(); It; ++It)
	// {
	// 	UE_LOG(LogTemp, Display, TEXT("Key: %s, Value: %d"), *It.Key(), It.Value());
	// }
	// Const Iterator
	UE_LOG(LogTemp, Display, TEXT("Const Iterator"));
	for (TMap<FString, int32>::TConstIterator It(AddMap); It; ++It)
	{
		UE_LOG(LogTemp, Display, TEXT("Key: %s, Value: %d"), *It.Key(), It.Value());
	}
	// for (auto It = AddMap.CreateConstIterator(); It; ++It)
	// {
	// 	UE_LOG(LogTemp, Display, TEXT("Key: %s, Value: %d"), *It.Key(), It.Value());
	// }

	UE_LOG(LogTemp,Display, TEXT("Keys"))
	TArray<FString> Keys;
	// GetKeys를 호출할 때 Set를 이용해서 중복된 값을 제거한다.
	// 일반적으로는 중복된 값이 없지만 TWeakObjectPtr의 경우 둘 다 invalid일 경우 중복된 값으로 처리하므로 Set을 이용해서 중복된 값을 제거한다.
	// Map.h Line343
	// WeakObjectPtrTemplates.h Line267
	// WeakObjectPtr.h Line123
	AddMap.GetKeys(Keys);
	// Keys == {D, E, F, A, B, C, G}
	for (const auto& Key : Keys)
	{
		UE_LOG(LogTemp, Display, TEXT("Key: %s"), *Key);
	}

	UE_LOG(LogTemp,Display, TEXT("KeyArray"))
	TArray<FString> KeyArray;
	AddMap.GenerateKeyArray(KeyArray);
	// KeyArray == {D, E, F, A, B, C, G}
	for (const auto& Key : KeyArray)
	{
		UE_LOG(LogTemp, Display, TEXT("Key: %s"), *Key);
	}
	
	UE_LOG(LogTemp,Display,TEXT("Values"))
	TArray<int32> Values;
	AddMap.GenerateValueArray(Values);
	// Values == {4, 5, 6, 4, 2, 3, 8}
	for (const auto& Value : Values)
	{
		UE_LOG(LogTemp, Display, TEXT("Value: %d"), Value);
	}

	UE_LOG(LogTemp,Display,TEXT("Query"))
	// Num : Returns the number of key-value pairs in the map.
	UE_LOG(LogTemp,Display, TEXT("Num: %d"), AddMap.Num()); // 7
	// IsEmpty : Returns true if the map is empty.
	UE_LOG(LogTemp,Display, TEXT("IsEmpty: %s"), AddMap.IsEmpty() ? TEXT("true") : TEXT("false")); // false
	// Contains : Returns true if the map contains the specified key.
	UE_LOG(LogTemp,Display, TEXT("Contains A: %s"), AddMap.Contains(TEXT("A")) ? TEXT("true") : TEXT("false")); // true
	UE_LOG(LogTemp,Display, TEXT("Contains Z: %s"), AddMap.Contains(TEXT("Z")) ? TEXT("true") : TEXT("false")); // false
	// Find : Returns a pointer to the value associated with the specified key. Contain을 하고 접근을 하면 두 번을 접근해야 하지만, Find는 한 번에 접근이 가능하다.
	if (int* Value = AddMap.Find(TEXT("A")))
	{
		UE_LOG(LogTemp, Display, TEXT("Find A: %d"), *Value); // 4
		// 여기서 찾은 값을 변경할 수 있다.
	}
	else
	{
		UE_LOG(LogTemp, Display, TEXT("Find A: Not Found"));
	}
	// FindOrAdd : Returns a reference to the value associated with the specified key. If the key does not exist, it adds the key with a default value.
	// Find는 값이 없을 수 있지만 FindOrAdd는 없으면 기본값을 추가하기 때문에 항상 값이 존재하는 것을 보장한다.
	// 항상 값이 있는 것을 보장할 수 있기 때문에 포인터가 아니라 참조로 반환한다.
	// 맵을 수정할 수 있기 때문에 non-const맵만 사용 가능하다.
	int32& FindValue = AddMap.FindOrAdd(TEXT("B"));
	UE_LOG(LogTemp, Display, TEXT("FindOrAdd B: %d"), FindValue); // 2
	int32& FindValue2 = AddMap.FindOrAdd(TEXT("Z"));
	FindValue2 = 26;
	UE_LOG(LogTemp, Display, TEXT("FindOrAdd Z: %d"), FindValue2); // 26
	AddMap.FindOrAdd(TEXT("Y"), 25); // Y가 존재하지 않기 때문에 Value를 추가한다.
	UE_LOG(LogTemp,Display, TEXT("FindOrAdd Y: %d"), AddMap["Y"]); // 25
	AddMap.FindOrAdd(TEXT("Z"), 24); // Z는 이미 존재하기 때문에 값이 변경되지 않는다.
	UE_LOG(LogTemp,Display, TEXT("FindOrAdd Z: %d"), AddMap["Z"]); // 26
	// FindRef : 지정된 값에 대한 값을 반환한다. 값이 존재하지 않으면 기본값을 반환한다.
	// 값을 반환하므로 기존의 map이 변경되지 않는다. 따라서 const map에서도 사용 가능하다.
	int32 FindRefValue = AddMap.FindRef(TEXT("A"));
	UE_LOG(LogTemp, Display, TEXT("FindRef A: %d"), FindRefValue); // 4
	int32 FindRefValue2 = AddMap.FindRef(TEXT("W"));
	UE_LOG(LogTemp,Display, TEXT("FindRef W: %d"), FindRefValue2); // 0
	int32 FindRefValue3 = AddMap.FindRef(TEXT("Y"), 100);
	UE_LOG(LogTemp,Display, TEXT("FindRef Y: %d"), FindRefValue3); // 25
	int32 FindRefValue4 = AddMap.FindRef(TEXT("X"), 100);
	UE_LOG(LogTemp,Display, TEXT("FindRef X: %d"), FindRefValue4); // 100
	// FindKey : Returns a pointer to the key associated with the specified value. If the value does not exist, it returns nullptr.
	// Map은 sort되지 않기 때문에, Key를 찾는 것은 O(N)이다.
	// 또한, Key는 중복될 수 있기 때문에, Key를 찾는 것이 아니라 Key의 첫 번째 값을 찾는다.
	if (const FString* Key = AddMap.FindKey(4))
	{
		UE_LOG(LogTemp, Display, TEXT("FindKey 4: %s"), **Key); // A
	}
	else
	{
		UE_LOG(LogTemp, Display, TEXT("FindKey 4: Not Found"));
	}

	UE_LOG(LogTemp,Display,TEXT("Find Arbitrary"))
	// Find FindArbitraryElement : Returns a pointer to an arbitrary key-value pair in the map. The pointer is only valid until the next change to any key in the map.
	// 실질적으로 단순히 임의의 키 값을 선택하는 것이기 때문에 가장 뒤의 값을 선택하고 있는 것 같다. 랜덤을 보장한다고 생각하고 사용해서는 안 된다.
	if (const TPair<FString, int32>* ArbitraryPair = AddMap.FindArbitraryElement())
	{
		UE_LOG(LogTemp, Display, TEXT("FindArbitrary - Key: %s, Value: %d"), *ArbitraryPair->Key, ArbitraryPair->Value);
	}
	else
	{
		UE_LOG(LogTemp, Display, TEXT("FindArbitrary: Map is empty"));
	}

	// Remove
	UE_LOG(LogTemp,Display, TEXT("Remove"))
	// Remove : 특정한 Key를 가진 Key-Value 쌍을 삭제한다. 만약 Key가 존재하지 않으면 아무것도 하지 않는다. 반환값은 삭제된 원소의 개수이다.
	AddMap.Remove("Z");
	// AddMap == {D: 4, E: 5, F: 6, A: 4, B: 2, C: 3, G: 8, Y: 25}
	UE_LOG(LogTemp,Display, TEXT("Remove Z"));
	for (const auto& Pair : AddMap)
	{
		UE_LOG(LogTemp, Display, TEXT("Key: %s, Value: %d"), *Pair.Key, Pair.Value);
	}
	
	// FindAndRemoveChecked : 특정한 Key를 가진 Key-Value 쌍을 삭제하고 값을 반환한다. 만약에 Key가 존재하지 않으면 assert를 발생시킨다.
	int32 FindAndRemoveCheckedValue = AddMap.FindAndRemoveChecked("Y");
	// AddMap == {D: 4, E: 5, F: 6, A: 4, B: 2, C: 3, G: 8}
	UE_LOG(LogTemp,Display, TEXT("FindAndRemoveChecked Y: %d"), FindAndRemoveCheckedValue);
	for (const auto& Pair : AddMap)
	{
		UE_LOG(LogTemp, Display, TEXT("Key: %s, Value: %d"), *Pair.Key, Pair.Value);
	}

	// RemoveAndCopyValue : Removes the specified key from the map and copies its value to the provided variable. Returns true if the key was found and removed, false otherwise.
	if (int RemoveAndCopy = 0; AddMap.RemoveAndCopyValue(TEXT("G"), RemoveAndCopy))
	{
		UE_LOG(LogTemp, Display, TEXT("RemoveAndCopy G: %d"), RemoveAndCopy); // 8
	}
	else
	{
		UE_LOG(LogTemp, Display, TEXT("RemoveAndCopy G: Not Found"));
	}
	// AddMap == {D: 4, E: 5, F: 6, A: 4, B: 2, C: 3}
	for (const auto& Pair : AddMap)
	{
		UE_LOG(LogTemp, Display, TEXT("Key: %s, Value: %d"), *Pair.Key, Pair.Value);
	}

	// Sort
	// KeySort : 키를 기준으로 정렬합니다.
	UE_LOG(LogTemp, Display, TEXT("KeySort"));
	AddMap.KeySort([](const FString& A, const FString& B) {
		return A < B; // 오름차순 정렬
	});
	// AddMap == {A: 4, B: 2, C: 3, D: 4, E: 5, F: 6}
	for (const auto& Pair : AddMap)
	{
		UE_LOG(LogTemp, Display, TEXT("Key: %s, Value: %d"), *Pair.Key, Pair.Value);
	}

	// ValueSort : Value를 기준으로 정렬합니다.
	UE_LOG(LogTemp,Display,TEXT("ValueSort"))
	AddMap.ValueSort([](const int32& A, const int32& B) {
		return A < B; // 오름차순 정렬
	});
	// AddMap == {B: 2, C: 3, A: 4, D: 4, E: 5, F: 6}
	for (const auto& Pair : AddMap)
	{
		UE_LOG(LogTemp, Display, TEXT("Key: %s, Value: %d"), *Pair.Key, Pair.Value);
	}

	// Empty, Reset : 둘 다 모든 원소를 삭제한다. Empty의 경우 Slack 만큼 설정하고, Reset의 경우는 Slack이 더 작을 경우 유지된다.
	// Empty : Removes all elements from the map, leaving it empty.
	// Reset : Removes all elements from the map, but keeps the allocated memory for future use.

	// Shrink : 컨테이너 끝의 모든 slack을 제거하지만 중간이나 시작 부분의 slack은 제거하지 않는다.
	UE_LOG(LogTemp,Display, TEXT("Shrink"))
	TMap<int32, FString> ShrinkMap;
	for (int32 i = 0; i < 10; i++)
	{
		ShrinkMap.Add(i, FString::Printf(TEXT("Value %d"), i));
	}
	// ShrinkMap == {0: Value 0, 1: Value 1, 2: Value 2, 3: Value 3, 4: Value 4, 5: Value 5, 6: Value 6, 7: Value 7, 8: Value 8, 9: Value 9}
	for (const auto& Pair : ShrinkMap)
	{
		UE_LOG(LogTemp, Display, TEXT("Key: %d, Value: %s"), Pair.Key, *Pair.Value);
	}
	for (int32 i = 0; i < 10; i += 2)
	{
		ShrinkMap.Remove(i);
	}
	// ShrinkMap == {1: Value 1, 3: Value 3, 5: Value 5, 7: Value 7, 9: Value 9}
	FStringOutputDevice OutputDevice;
	ShrinkMap.Dump(OutputDevice);
	// TSet: 5 elements, 16 hash slots   Hash[0] = 0   Hash[1] = 1   Hash[2] = 0   Hash[3] = 1   Hash[4] = 0   Hash[5] = 1   Hash[6] = 0   Hash[7] = 1   Hash[8] = 0   Hash[9] = 1   Hash[10] = 0   Hash[11] = 0   Hash[12] = 0   Hash[13] = 0   Hash[14] = 0   Hash[15] = 0
	UE_LOG(LogTemp, Display, TEXT("%s"), *OutputDevice);
	ShrinkMap.Shrink();
	OutputDevice.Empty();
	ShrinkMap.Dump(OutputDevice);
	// TSet: 5 elements, 16 hash slots   Hash[0] = 0   Hash[1] = 1   Hash[2] = 0   Hash[3] = 1   Hash[4] = 0   Hash[5] = 1   Hash[6] = 0   Hash[7] = 1   Hash[8] = 0   Hash[9] = 1   Hash[10] = 0   Hash[11] = 0   Hash[12] = 0   Hash[13] = 0   Hash[14] = 0   Hash[15] = 0
	UE_LOG(LogTemp,Display, TEXT("%s"), *OutputDevice);
	ShrinkMap.Compact();
	ShrinkMap.Shrink();
	OutputDevice.Empty();
	ShrinkMap.Dump(OutputDevice);
	// TSet: 5 elements, 16 hash slots   Hash[0] = 0   Hash[1] = 1   Hash[2] = 0   Hash[3] = 1   Hash[4] = 0   Hash[5] = 1   Hash[6] = 0   Hash[7] = 1   Hash[8] = 0   Hash[9] = 1   Hash[10] = 0   Hash[11] = 0   Hash[12] = 0   Hash[13] = 0   Hash[14] = 0   Hash[15] = 0
	UE_LOG(LogTemp,Display, TEXT("%s"), *OutputDevice);

	// Filter
	UE_LOG(LogTemp,Display, TEXT("Filter"));
	// FilterByPredicate : Returns a new map containing only the elements that satisfy the given predicate.
	TMap<FString, int32> FilteredMap = AddMap.FilterByPredicate([](const TPair<FString, int32>& Pair) {
	    return Pair.Value > 3; // Value가 3보다 큰 요소만 필터링
	}); // {D: 4, E: 5, F: 6, A: 4, G: 8}
	
	UE_LOG(LogTemp, Display, TEXT("FilteredMap : Value > 3"));
	for (const auto& Pair : FilteredMap)
	{
	    UE_LOG(LogTemp, Display, TEXT("Key: %s, Value: %d"), *Pair.Key, Pair.Value);
	}

	TMap<UObject*, int32> ObjectMap;
	// Object 삽입
	UE_LOG(LogTemp, Display, TEXT("Inserting Objects into ObjectMap"));
	UObject* NewObject1 = NewObject<UObject>(this);
	UObject* NewObject2 = NewObject<UObject>(this);
	ObjectMap.Add(NewObject1, 1);
	ObjectMap.Add(NewObject2, 2);
	
	// ObjectMap 출력
	for (const auto& Pair : ObjectMap)
	{
	    UE_LOG(LogTemp, Display, TEXT("Key: %s, Value: %d"), Pair.Key ? *Pair.Key->GetName() : TEXT("nullptr"), Pair.Value);
	}
	
	// Object 파괴
	UE_LOG(LogTemp, Display, TEXT("Destroying Objects"));
	NewObject1->ConditionalBeginDestroy();
	NewObject2->ConditionalBeginDestroy();
	CollectGarbage(RF_NoFlags);
	TArray<UObject*> ObjectKeys;
	ObjectMap.GetKeys(ObjectKeys);
	for (const auto& Object : ObjectKeys)
	{
		UE_LOG(LogTemp, Display, TEXT("Object: %s"), Object ? *Object->GetName() : TEXT("nullptr"));
	}

	// TWeakObjectPtr 예제
	UE_LOG(LogTemp, Display, TEXT("TWeakObjectPtr Example"));
	
	// UObject 생성 및 추가
	UObject* WeakObject1 = NewObject<UObject>(this);
	UObject* WeakObject2 = NewObject<UObject>(this);
	UObject* WeakObject3 = NewObject<UObject>(this);

	WeakObjectMap.Add(WeakObject1, TEXT("Object1"));
	WeakObjectMap.Add(WeakObject2, TEXT("Object2"));
	WeakObjectMap.Add(WeakObject3, TEXT("Object3"));
	
	// 맵 출력
	for (const auto& Pair : WeakObjectMap)
	{
		UE_LOG(LogTemp, Display, TEXT("Key: %s, Value: %s"), Pair.Key.IsValid() ? *Pair.Key->GetName() : TEXT("Invalid"), *Pair.Value);
	}
	
	// UObject 파괴
	UE_LOG(LogTemp, Display, TEXT("Destroying Objects"));
	WeakObject1->ConditionalBeginDestroy();
	WeakObject2->ConditionalBeginDestroy();
	WeakObject3->ConditionalBeginDestroy();
	CollectGarbage(RF_NoFlags);

	// 가비지 컬렉션 후 맵 출력
	GetWorld()->GetTimerManager().SetTimerForNextTick([this]()
	{
		UE_LOG(LogTemp,Display,TEXT("Num : %d"), WeakObjectMap.Num());
		TArray<TWeakObjectPtr<UObject>> WeakKeys;
		WeakObjectMap.GetKeys(WeakKeys);
		UE_LOG(LogTemp, Display, TEXT("Keys : %d"), WeakKeys.Num());
		for (const auto& WeakKey : WeakKeys)
		{
			UE_LOG(LogTemp, Display, TEXT("WeakKey: %s"), WeakKey.IsValid() ? *WeakKey->GetName() : TEXT("Invalid"));
		}

		TArray<TWeakObjectPtr<UObject>> WeakKeys2;
		WeakObjectMap.GenerateKeyArray(WeakKeys2);
		UE_LOG(LogTemp, Display, TEXT("Keys2 : %d"), WeakKeys2.Num());
		for (const auto& WeakKey : WeakKeys2)
		{
			UE_LOG(LogTemp, Display, TEXT("WeakKey2: %s"), WeakKey.IsValid() ? *WeakKey->GetName() : TEXT("Invalid"));
		}
	});
}
