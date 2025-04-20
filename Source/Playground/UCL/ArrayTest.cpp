// Fill out your copyright notice in the Description page of Project Settings.


#include "ArrayTest.h"


// Sets default values
AArrayTest::AArrayTest()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

// Called when the game starts or when spawned
void AArrayTest::BeginPlay()
{
	Super::BeginPlay();

	// TArray 생성
	// 비어 있는 TArray 생성
	TArray<int32> IntArray;
	
	// 초기값을 가진 TArray 생성
	TArray <int32> IntArrayWithInitializeList = { 1, 2, 3, 4, 5 };
	UE_LOG(LogTemp, Display, TEXT("IntArrayWithInitializeList contains:"));
	for (int32 Element : IntArrayWithInitializeList)
	{
		// 1, 2, 3, 4, 5
		UE_LOG(LogTemp, Display, TEXT("%d"), Element);
	}
	
	// 초기값 n개를 가지도록 초기화
	TArray<int32> IntArrayWithInit;
	IntArrayWithInit.Init(5, 10);
	UE_LOG(LogTemp, Display, TEXT("IntArrayWithInit contains:"));
	for (int32 Element : IntArrayWithInit)
	{
		// 5, 5, 5, 5, 5, 5, 5, 5, 5, 5
		UE_LOG(LogTemp, Display, TEXT("%d"), Element);
	}
	
	// TArray 삽입
	TArray<int32> InsertArray;
	// return : 삽입된 원소의 인덱스
	InsertArray.Add(1);
	InsertArray.Add(2);
	InsertArray.Add(3);
	InsertArray.Add(4);
	InsertArray.Add(5);
	UE_LOG(LogTemp, Display, TEXT("InsertArray contains:"));
	for (int32 Element : InsertArray)
	{
		// 1, 2, 3, 4, 5
		UE_LOG(LogTemp, Display, TEXT("%d"), Element);
	}

	TArray<int32> EmplaceArray;
	// return : 삽입된 원소의 인덱스
	EmplaceArray.Emplace(1);
	EmplaceArray.Emplace(2);
	EmplaceArray.Emplace(3);
	EmplaceArray.Emplace(4);
	EmplaceArray.Emplace(5);
	UE_LOG(LogTemp, Display, TEXT("EmplaceArray contains:"));
	for (int32 Element : EmplaceArray)
	{
		// 1, 2, 3, 4, 5
		UE_LOG(LogTemp, Display, TEXT("%d"), Element);
	}
	// Add는 삽입할 원소를 복사해서 넣는다.
	// Emplace는 삽입할 원소를 직접 생성해서 넣는다.

	// 생성자가 필요하다면 AddDefaulted를 이용한다.
	TArray<int32> InsertZeroArray;
	// return : 추가된 원소의 첫번째 인덱스
	InsertZeroArray.AddZeroed();
	// 5개를 추가한다.
	InsertZeroArray.AddZeroed(5);
	UE_LOG(LogTemp, Display, TEXT("InsertZeroArray contains:"));
	for (int32 Element : InsertZeroArray)
	{
		// 0, 0, 0, 0, 0
		UE_LOG(LogTemp, Display, TEXT("%d"), Element);
	}

	TArray<int32> AddUniqueArray;
	AddUniqueArray.AddUnique(1);
	AddUniqueArray.AddUnique(2);
	AddUniqueArray.AddUnique(3);
	AddUniqueArray.AddUnique(4);
	AddUniqueArray.AddUnique(5);
	AddUniqueArray.AddUnique(1);
	// AddUnique는 중복된 원소를 추가하지 않는다.
	UE_LOG(LogTemp, Display, TEXT("AddUniqueArray contains:"));
	for (int32 Element : AddUniqueArray)
	{
		// 1, 2, 3, 4, 5
		UE_LOG(LogTemp, Display, TEXT("%d"), Element);
	}

	TArray<int32> InsertAtArray;
	// Item : 삽입할 원소
	// Index : 삽입할 인덱스, 0-based
	// 끝에 삽입하는 것은 가능하지만 Index를 벗어나면 오류가 발생한다.
	InsertAtArray.Init(0, 5);
	// 0번째 인덱스에 1을 삽입한다.
	InsertAtArray.Insert(1, 0);
	// 1, 0, 0, 0, 0, 0
	InsertAtArray.Insert(2, 3);
	// 1, 0, 0, 2, 0, 0, 0
	UE_LOG(LogTemp, Display, TEXT("InsertAtArray contains:"));
	for (int32 Element : InsertAtArray)
	{
		// 1, 0, 0, 2, 0, 0, 0
		UE_LOG(LogTemp, Display, TEXT("%d"), Element);
	}
	const int ToInsert = 5;
	if (InsertAtArray.IsValidIndex(ToInsert))
	{
		// 1, 0, 0, 2, 0, 3, 0, 0
		InsertAtArray.Insert(3, ToInsert);
	}
	UE_LOG(LogTemp, Display, TEXT("InsertAtArray After Valid Check contains:"));
	for (int32 Element : InsertAtArray)
	{
		// 1, 0, 0, 2, 0, 3, 0, 0
		UE_LOG(LogTemp, Display, TEXT("%d"), Element);
	}
	const int OutOfIndex = 10;
	if (InsertAtArray.IsValidIndex(OutOfIndex))
	{
		InsertAtArray.Insert(4, OutOfIndex);
	}
	UE_LOG(LogTemp, Display, TEXT("InsertAtArray After Valid Check contains:"));
	for (int32 Element : InsertAtArray)
	{
		// 1, 0, 0, 2, 0, 3, 0, 0
		UE_LOG(LogTemp, Display, TEXT("%d"), Element);
	}
	
	TArray<int32> AppendArray;
	// 다른 TArray를 추가한다.
	AppendArray.Append(InsertArray);
	AppendArray.Append(InsertAtArray);
	UE_LOG(LogTemp, Display, TEXT("AppendArray contains:"));
	for (int32 Element : AppendArray)
	{
		// 1, 2, 3, 4, 5, 1, 0, 0, 2, 0, 0
		UE_LOG(LogTemp, Display, TEXT("%d"), Element);
	}
	AppendArray.Append({ 6, 7, 8, 9, 10 });
	UE_LOG(LogTemp, Display, TEXT("AppendArray After Initialize List contains:"));
	for (int32 Element : AppendArray)
    {
        // 1, 2, 3, 4, 5, 1, 0, 0, 2, 0, 0, 6, 7, 8, 9, 10
        UE_LOG(LogTemp, Display, TEXT("%d"), Element);
    }

	// SetNum
	// SetNum은 TArray의 크기를 설정한다. resize와 같은 역할을 한다.
	TArray<int32> SetNumArray;
	SetNumArray.Init(5, 5);
	// 원래 개수보다 큰 수를 넣으면 뒤에는 기본값으로 초기화된다.
	SetNumArray.SetNum(8);
	UE_LOG(LogTemp, Display, TEXT("SetNumArray contains:"));
	for (int32 Element : SetNumArray)
	{
		// 5, 5, 5, 5, 5, 0, 0, 0
		UE_LOG(LogTemp, Display, TEXT("%d"), Element);
	}
	// 원래 개수보다 작은 수를 넣으면 뒤의 원소는 삭제된다.
	SetNumArray.SetNum(3);
	UE_LOG(LogTemp, Display, TEXT("SetNumArray contains:"));
	for (int32 Element : SetNumArray)
	{
		// 5, 5, 5
		UE_LOG(LogTemp, Display, TEXT("%d"), Element);
	}

	// Iterate TArray
	TArray<int32> IterateArray = { 1, 2, 3, 4, 5 };
	//  range-based for loop
	UE_LOG(LogTemp, Display, TEXT("IterateArray contains:"));
	for (int32 Element : IterateArray)
	{
		// 1, 2, 3, 4, 5
		UE_LOG(LogTemp, Display, TEXT("%d"), Element);
	}

	// index-based for loop
	UE_LOG(LogTemp, Display, TEXT("IterateArray contains:"));
	for (int32 Index = 0; Index < IterateArray.Num(); ++Index)
	{
		// 1, 2, 3, 4, 5
		UE_LOG(LogTemp, Display, TEXT("%d"), IterateArray[Index]);
	}

	// iterator for loop
	UE_LOG(LogTemp, Display, TEXT("IterateArray contains:"));
	// CreateConstIterator : 읽기 전용 Iterator
	// CreateIterator : 읽기, 쓰기 가능한 Iterator
	for (auto Iterator = IterateArray.CreateConstIterator(); Iterator; ++Iterator)
	{
		// 1, 2, 3, 4, 5
		UE_LOG(LogTemp, Display, TEXT("%d"), *Iterator);
	}

	// Remove
	TArray<int32> RemoveArray = { 1, 2, 3, 4, 5 };
	// RemoveAt
	// Index : 삭제할 인덱스, 0-based
	RemoveArray.RemoveAt(2);
	// 1, 2, 4, 5
	UE_LOG(LogTemp, Display, TEXT("RemoveArray contains:"));
	for (int32 Element : RemoveArray)
	{
		// 1, 2, 4, 5
		UE_LOG(LogTemp, Display, TEXT("%d"), Element);
	}

	// Remove
	TArray<int32> RemoveValueArray = { 1, 1, 1, 2, 3 };
	// Value : 삭제할 원소
	RemoveValueArray.Remove(1);
	// 2, 3
	UE_LOG(LogTemp, Display, TEXT("RemoveValueArray contains:"));
	for (int32 Element : RemoveValueArray)
	{
		// 2, 3
		UE_LOG(LogTemp, Display, TEXT("%d"), Element);
	}

	// RemoveSingle
	// RemoveSingle은 처음 발견된 원소만 삭제한다.
	TArray<int32> RemoveSingleArray = { 1, 1, 1, 2, 3 };
	RemoveSingleArray.RemoveSingle(1);
	// 1, 1, 2, 3
	UE_LOG(LogTemp, Display, TEXT("RemoveSingleArray contains:"));
	for (int32 Element : RemoveSingleArray)
	{
		// 1, 1, 2, 3
		UE_LOG(LogTemp, Display, TEXT("%d"), Element);
	}
	
	// RemoveAll
	TArray<int32> RemoveAllArray = {1, 2, 3, 4, 5, 6, 7, 8};
	// Predicate : 삭제할 조건
	RemoveAllArray.RemoveAll([](int32 Value) { return Value % 2 == 0; });
	// 1, 3, 5, 7
	UE_LOG(LogTemp, Display, TEXT("RemoveAllArray contains:"));
	for (int32 Element : RemoveAllArray)
	{
		// 1, 3, 5, 7
		UE_LOG(LogTemp, Display, TEXT("%d"), Element);
	}

	// RemoveAtSwap
	TArray<int32> RemoveAtSwapArray = { 1, 2, 3, 4, 5 };
	// Index : 삭제할 인덱스, 0-based
	// RemoveAtSwap은 삭제할 원소를 뒤에 있는 원소와 교환한다.
	// 따라서 순서가 중요하지 않은 경우에 사용한다.
	// 뒤에 있는 원소와 교환하므로 시간 복잡도가 상수 시간이다.
	RemoveAtSwapArray.RemoveAtSwap(2);
	// 1, 2, 5, 4
	UE_LOG(LogTemp, Display, TEXT("RemoveAtSwapArray contains:"));
	for (int32 Element : RemoveAtSwapArray)
	{
		// 1, 2, 5, 4
		UE_LOG(LogTemp, Display, TEXT("%d"), Element);
	}

	// RemoveSingleSwap
	TArray<int32> RemoveSwapSingleArray = { 1, 1, 1, 2, 3 };
	// Value : 삭제할 원소
	// RemoveSingleSwap은 RemoveSingle처럼 동작하지만 Swap을 이용한다.
	// 순서가 보장되지 않지만 효율이 좋다.
	RemoveSwapSingleArray.RemoveSingleSwap(1);
	// 3, 1, 1, 2
	UE_LOG(LogTemp, Display, TEXT("RemoveSwapSingleArray contains:"));
	for (int32 Element : RemoveSwapSingleArray)
	{
		// 3, 1, 1, 2
		UE_LOG(LogTemp, Display, TEXT("%d"), Element);
	}

	// RemoveSwap
	TArray<int32> RemoveSwapArray = { 1, 1, 1, 2, 3 };
	// Value : 삭제할 원소
	// RemoveSwap은 내부적으로 RemoveAtSwap을 호출한다.
	// 순서가 보장되지 않지만 효율이 좋다.
	RemoveSwapArray.RemoveSwap(1);
	// 3, 2
	UE_LOG(LogTemp, Display, TEXT("RemoveSwapArray contains:"));
	for (int32 Element : RemoveSwapArray)
	{
		// 3, 2
		UE_LOG(LogTemp, Display, TEXT("%d"), Element);
	}

	// RemoveSwapAll
	TArray<int32> RemoveSwapAllArray = { 1, 2, 3, 4, 5, 6, 7, 8 };
	// Predicate : 삭제할 조건
	// RemoveSwapAll은 내부적으로 RemoveSwap을 호출한다.
	// 순서가 보장되지 않지만 효율이 좋다.
	RemoveSwapAllArray.RemoveAllSwap([](int32 Value) { return Value % 2 == 0; });
	// 1, 7, 3, 5
	UE_LOG(LogTemp, Display, TEXT("RemoveSwapAllArray contains:"));
	for (int32 Element : RemoveSwapAllArray)
	{
		// 1, 7, 3, 5
		UE_LOG(LogTemp, Display, TEXT("%d"), Element);
	}

	// Slack
	// Num : 원소의 개수
	// Max : 할당된 메모리의 개수
	// AllocatedSize : 할당된 메모리의 크기
	// Slack : 할당된 메모리 중 사용되지 않는 메모리의 개수
	// Num + Slack = Max
	// Allocated Size는 바이트로 할당된 메모리의 크기이다.
	// AllocateSize = Max * sizeof(ElementType)
	TArray<int32> SlackArray;
	// Num = 0, Max = 0, AllocatedSize = 0, Slack = 0
	UE_LOG(LogTemp, Display, TEXT("Initial : Num  = %d, Max = %d, AllocatedSize = %d, Slack = %d"),
		SlackArray.Num(), SlackArray.Max(), SlackArray.GetAllocatedSize(), SlackArray.GetSlack());
	SlackArray.Add(1);
	// Num = 1, Max = 4, AllocatedSize = 16, Slack = 3
	UE_LOG(LogTemp, Display, TEXT("After Add 1 : Num  = %d, Max = %d, AllocatedSize = %d, Slack = %d"),
			SlackArray.Num(), SlackArray.Max(), SlackArray.GetAllocatedSize(), SlackArray.GetSlack());
	SlackArray.Reserve(100);
	// Num = 1, Max = 100, AllocatedSize = 400, Slack = 99
	UE_LOG(LogTemp, Display, TEXT("After Reserve 100 : Num  = %d, Max = %d, AllocatedSize = %d, Slack = %d"),
			SlackArray.Num(), SlackArray.Max(), SlackArray.GetAllocatedSize(), SlackArray.GetSlack());
	SlackArray.Empty();
	// Num = 0, Max = 0, AllocatedSize = 0, Slack = 0
	UE_LOG(LogTemp, Display, TEXT("After Empty : Num  = %d, Max = %d, AllocatedSize = %d, Slack = %d"),
			SlackArray.Num(), SlackArray.Max(), SlackArray.GetAllocatedSize(), SlackArray.GetSlack());
	// Empty : 배열을 초기화하고 인자로 받은 크기 만큼 메모리를 할당한다.
	// Reset : 배열을 초기화하고 인자로 받은 크기 만큼 메모리를 할당한다. 하지만, 현재 할당된 메모리보다 작은 크기를 받으면 할당된 메모리를 유지한다.
	SlackArray.Init(1, 100);
	SlackArray.Empty(100);
	// Num = 0, Max = 100, AllocatedSize = 400, Slack = 100
	UE_LOG(LogTemp, Display, TEXT("After Empty 100 : Num  = %d, Max = %d, AllocatedSize = %d, Slack = %d"),
			SlackArray.Num(), SlackArray.Max(), SlackArray.GetAllocatedSize(), SlackArray.GetSlack());
	SlackArray.Init(1, 100);
	SlackArray.Reset(50);
	// Num = 0, Max = 100, AllocatedSize = 400, Slack = 100
	UE_LOG(LogTemp, Display, TEXT("After Reset 50 : Num  = %d, Max = %d, AllocatedSize = %d, Slack = %d"),
			SlackArray.Num(), SlackArray.Max(), SlackArray.GetAllocatedSize(), SlackArray.GetSlack());
	SlackArray.Init(1, 100);
	SlackArray.Reset(200);
	UE_LOG(LogTemp, Display, TEXT("After Reset 200 : Num  = %d, Max = %d, AllocatedSize = %d, Slack = %d"),
			SlackArray.Num(), SlackArray.Max(), SlackArray.GetAllocatedSize(), SlackArray.GetSlack());
	// Shrink
	// Num : 원소의 개수
	SlackArray.Empty();
	SlackArray.Add(1);
	SlackArray.Add(2);
	// Num = 2, Max = 4, AllocatedSize = 16, Slack = 2
	UE_LOG(LogTemp, Display, TEXT("Before Shrink : Num  = %d, Max = %d, AllocatedSize = %d, Slack = %d"),
			SlackArray.Num(), SlackArray.Max(), SlackArray.GetAllocatedSize(), SlackArray.GetSlack());
	SlackArray.Shrink();
	// Num = 2, Max = 2, AllocatedSize = 8, Slack = 0
	UE_LOG(LogTemp, Display, TEXT("After Shrink : Num  = %d, Max = %d, AllocatedSize = %d, Slack = %d"),
			SlackArray.Num(), SlackArray.Max(), SlackArray.GetAllocatedSize(), SlackArray.GetSlack());

	// Sort
	TArray<int32> SortArray = { 3, 1, 4, 1, 5, 9, 2, 6, 5, 3, 5 };
	// Predicate : 정렬 기준
	SortArray.Sort([](const int32& A, const int32& B) { return A < B; });
	// 1, 1, 2, 3, 3, 4, 5, 5, 5, 6, 9
	UE_LOG(LogTemp, Display, TEXT("SortArray contains:"));
	for (int32 Element : SortArray)
	{
		// 1, 1, 2, 3, 3, 4, 5, 5, 5, 6, 9
		UE_LOG(LogTemp, Display, TEXT("%d"), Element);
	}
}

// Called every frame
void AArrayTest::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

