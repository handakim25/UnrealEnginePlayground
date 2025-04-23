// Fill out your copyright notice in the Description page of Project Settings.


#include "SetTest.h"

// Reference
// https://dev.epicgames.com/documentation/ko-kr/unreal-engine/set-containers-in-unreal-engine

// Sets default values
ASetTest::ASetTest()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

// Called when the game starts or when spawned
void ASetTest::BeginPlay()
{
	Super::BeginPlay();

	// Add : Adds an element to the set. If the element already exists, it does nothing.
	// Emplace : Adds an element to the set, constructing it in place. This is more efficient than Add when the element type is expensive to copy.
	// TMap과 TSet의 차이점은 TMap은 Key-Value 쌍으로 이루어져 있고, TSet은 Key만 존재한다는 것이다.
	UE_LOG(LogTemp, Display, TEXT("Add Test"))
	TSet<int32> AddSet;
	AddSet.Add(1);
	AddSet.Add(2);
	AddSet.Add(3);
	// AddSet == {1, 2, 3}
	for (const auto& Value : AddSet)
	{
		UE_LOG(LogTemp, Display, TEXT("Value: %d"), Value);
	}
	AddSet.Add(1);
	// AddSet == {1, 2, 3}
	for (const auto& Value : AddSet)
	{
		UE_LOG(LogTemp, Display, TEXT("Value: %d"), Value);
	}

	bool bIsAlreadyInSet = false;
	AddSet.Add(4, &bIsAlreadyInSet);
	// AddSet == {1, 2, 3, 4}
	// bIsAlreadyInSet == false
	UE_LOG(LogTemp, Display, TEXT("AddSet.Add(4, &bIsAlreadyInSet)"));
	for (const auto& Value : AddSet)
	{
		UE_LOG(LogTemp, Display, TEXT("Value: %d"), Value);
	}
	UE_LOG(LogTemp, Display, TEXT("bIsAlreadyInSet: %s"), bIsAlreadyInSet ? TEXT("true") : TEXT("false"));
	// AddSet == {1, 2, 3, 4}
	// bIsAlreadyInSet == false
	AddSet.Add(4, &bIsAlreadyInSet);
	// AddSet == {1, 2, 3, 4}
	// bIsAlreadyInSet == true
	UE_LOG(LogTemp, Display, TEXT("AddSet.Add(4, &bIsAlreadyInSet)"));
	for (const auto& Value : AddSet)
	{
		UE_LOG(LogTemp, Display, TEXT("Value: %d"), Value);
	}
	UE_LOG(LogTemp, Display, TEXT("bIsAlreadyInSet: %s"), bIsAlreadyInSet ? TEXT("true") : TEXT("false"));

	// Query
	UE_LOG(LogTemp, Display, TEXT("Query Test"))
	// Contains : Checks if the set contains a specific element.
	UE_LOG(LogTemp, Display, TEXT("Contains 1: %s"), AddSet.Contains(1) ? TEXT("true") : TEXT("false")); // true
	UE_LOG(LogTemp, Display, TEXT("Contains 5: %s"), AddSet.Contains(5) ? TEXT("true") : TEXT("false")); // false
	// Num : Returns the number of elements in the set.
	UE_LOG(LogTemp, Display, TEXT("Num: %d"), AddSet.Num()); // 4
	// IsEmpty : Checks if the set is empty.
	UE_LOG(LogTemp, Display, TEXT("IsEmpty: %s"), AddSet.IsEmpty() ? TEXT("true") : TEXT("false")); // false
	// FindId : Returns the index of a specific element in the set. If the element is not found, it returns INDEX_NONE.
	// FindId : 요소의 위치를 나타내는 FSetElementId를 반환하는 함수 예제
	UE_LOG(LogTemp, Display, TEXT("FindId 테스트"));
	
	// 기존 AddSet에서 FindId 테스트
	FSetElementId ElementId1 = AddSet.FindId(1);
	UE_LOG(LogTemp, Display, TEXT("FindId 1 유효함: %s"), 
	       ElementId1.IsValidId() ? TEXT("true") : TEXT("false")); // true 출력
	
	FSetElementId ElementId4 = AddSet.FindId(4);
	UE_LOG(LogTemp, Display, TEXT("FindId 4 유효함: %s"), 
	       ElementId4.IsValidId() ? TEXT("true") : TEXT("false")); // true 출력
	
	// 존재하지 않는 요소 검색
	FSetElementId ElementId5 = AddSet.FindId(5);
	UE_LOG(LogTemp, Display, TEXT("FindId 5 유효함: %s"), 
	       ElementId5.IsValidId() ? TEXT("true") : TEXT("false")); // false 출력
	
	// 특정 요소 검색 및 처리
	int32 ElementToFind = 2;
	if (FSetElementId FoundId = AddSet.FindId(ElementToFind); FoundId.IsValidId())
	{
	    UE_LOG(LogTemp, Display, TEXT("요소 %d를 찾았습니다. 값: %d"), 
	           ElementToFind, AddSet[FoundId]);
	}
	else
	{
	    UE_LOG(LogTemp, Display, TEXT("요소 %d는 집합에 없습니다"), ElementToFind);
	}
	
	// FSetElementId를 정수로 변환하려면 AsInteger() 사용
	UE_LOG(LogTemp, Display, TEXT("요소 1의 내부 인덱스: %d"), ElementId1.AsInteger());

	// Find : Finds an element in the set and returns a pointer to it. If the element is not found, it returns nullptr.
	// TMap과 동일하지만 굳이 이렇게 할 필요는 없다.
	// 내부의 값을 수정하면 Set의 구조가 유지되지 않는다.
	// FindOrAdd도 마찮가지로 포인터를 반환하지만 포인터를 수정하면 Set의 구조가 유지되지 않는다.
	// FindOrAdd는 TMap과 동일한데 Find를 해서 반환하거나 아니면 Add를 해서 반환한다.
	// 이런 방식을 사용할 경우는 class나 구조체를 이용해서 Hash 값을 변경하지는 않고 내부의 구조를 수정할 때 사용할 수 있다.
	if (int32* FoundElement = AddSet.Find(1))
	{
		UE_LOG(LogTemp, Display, TEXT("Found Element: %d"), *FoundElement);
		// (*FoundElement) = 5;
	}
	else
	{
		UE_LOG(LogTemp, Display, TEXT("Element not found"));
	}

	for (const auto& Value : AddSet)
	{
		UE_LOG(LogTemp, Display, TEXT("Value: %d"), Value);
	}
	if (int32* FoundElement = AddSet.Find(5))
	{
		UE_LOG(LogTemp, Display, TEXT("Found Element: %d"), *FoundElement);
	}
	else
	{
		UE_LOG(LogTemp, Display, TEXT("Element not found"));
	}

	// Remove : Removes an element from the set. If the element is not found, it does nothing.
	AddSet.Remove(4);
	// AddSet == {1, 2, 3}
	for (const auto& Value : AddSet)
	{
		UE_LOG(LogTemp, Display, TEXT("Value: %d"), Value);
	}

	// Iterate
	UE_LOG(LogTemp, Display, TEXT("Iterate Test"))
	// Ranged for
	for (const auto& Value : AddSet)
	{
		UE_LOG(LogTemp, Display, TEXT("Value: %d"), Value);
	}
	// Create Iterator
	for (auto It = AddSet.CreateIterator(); It; ++It)
	{
		UE_LOG(LogTemp, Display, TEXT("Value: %d"), *It);
	}
	// for (TSet<int32>::TIterator It(AddSet); It; ++It)
	// {
	// 	UE_LOG(LogTemp, Display, TEXT("Value: %d"), *It);
	// }
	// Create Const Iterator
	for (auto It = AddSet.CreateConstIterator(); It; ++It)
	{
		UE_LOG(LogTemp, Display, TEXT("Value: %d"), *It);
	}
	// for (TSet<int32>::TConstIterator It(AddSet); It; ++It)
	// {
	// 	UE_LOG(LogTemp, Display, TEXT("Value: %d"), *It);
	// }

	// 초기화
	// Empty : Removes all elements from the set, leaving it empty.
	// Reset : Removes all elements from the set, but keeps the allocated memory for future use.
	// Reserve : Preallocates enough memory to contain Number elements

	// FindByHash : Finds an element in the set using its hash value.
	UE_LOG(LogTemp, Display, TEXT("FindByHash Test with FString"));
	TSet<FString> StringSet;
	StringSet.Add(TEXT("Apple"));
	StringSet.Add(TEXT("Banana"));
	StringSet.Add(TEXT("Cherry"));
	
	FString SearchKey = TEXT("Banana");
	uint32 HashValue = GetTypeHash(SearchKey);
	
	if (FString* FoundElement = StringSet.FindByHash(HashValue, SearchKey))
	{
	    UE_LOG(LogTemp, Display, TEXT("Found Element by Hash: %s"), **FoundElement);
	}
	else
	{
	    UE_LOG(LogTemp, Display, TEXT("Element not found by Hash"));
	}

	// Set 연산
	// Union : Combines two sets into one.
	// Intersect : Finds the common elements between two sets.
	// Difference : Finds the elements that are in one set but not in another.
	// Append : Adds all elements from another set to this set.
	UE_LOG(LogTemp,Display, TEXT("Set Operation Test"))
	TSet<int32> SetA = {1, 2, 3};
	TSet<int32> SetB = {3, 4, 5};
	for (const auto& Value : SetA)
	{
		UE_LOG(LogTemp, Display, TEXT("SetA Value: %d"), Value);
	}
	for (const auto& Value : SetB)
	{
		UE_LOG(LogTemp, Display, TEXT("SetB Value: %d"), Value);
	}
	// Append와 다르게 Union은 새로운 Set을 생성한다.
	TSet<int32> UnionSet = SetA.Union(SetB);
	// UnionSet == {1, 2, 3, 4, 5}
	for (const auto& Value : UnionSet)
	{
		UE_LOG(LogTemp, Display, TEXT("UnionSet Value: %d"), Value);
	}
	TSet<int32> IntersectSet = SetA.Intersect(SetB);
	// IntersectSet == {3}
	for (const auto& Value : IntersectSet)
	{
		UE_LOG(LogTemp, Display, TEXT("IntersectSet Value: %d"), Value);
	}
	TSet<int32> DifferenceSet = SetA.Difference(SetB);
	// DifferenceSet == {1, 2}
	for (const auto& Value : DifferenceSet)
	{
		UE_LOG(LogTemp, Display, TEXT("DifferenceSet Value: %d"), Value);
	}
	if (UnionSet.Includes(SetA))
	{
		UE_LOG(LogTemp,Display, TEXT("UnionSet includes SetA"));
	}

	// Array
	TArray<int32> Array = UnionSet.Array();
	// Array == {1, 2, 3, 4, 5}
	for (const auto& Value : Array)
	{
		UE_LOG(LogTemp, Display, TEXT("Array Value: %d"), Value);
	}
}
