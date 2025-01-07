// Fill out your copyright notice in the Description page of Project Settings.


#include "EnumTest.h"

// Sets default values
AEnumTest::AEnumTest()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void AEnumTest::BlueprintParamNotSupport(ETestEnum testEnum)
{
}

void AEnumTest::BlueprintParamSupport(EBlueprintEnum paramSupportEnum)
{
}

void AEnumTest::PrintEnumFlag()
{

	UE_LOG(LogTemp, Log, TEXT("EnumFlags : %d"), EnumFlags);
}

void AEnumTest::PrintEnumFlagWithoutMeta()
{
	UE_LOG(LogTemp, Log, TEXT("EnumFlagWithoutMeta : %d"), EnumFlagWithoutMeta);

	const UEnum* Enum = StaticEnum<EFlagEnumWithoutMeta>();
	if(Enum)
	{
		for(int i = 0; i < Enum->NumEnums(); i++)
		{
			FString Name = Enum->GetNameStringByIndex(i);
			int value = Enum->GetValueByIndex(i);

			bool bIsTriggered = (EnumFlagWithoutMeta & (1 << value));
			if(bIsTriggered)
			{
				UE_LOG(LogTemp, Log, TEXT("name : %s, value : %d"), *Name, value);
			}
		}
	}
}

void AEnumTest::BitflagFunction()
{
	// 비트 플래그 연산을 오버로딩을 통해서 마치 정수형 매크로로 정의된 값처럼 사용이 가능하다.
	EFlagEnum curEnum = EFlagEnum::Test_Flag_0;

	// 플래그 추가
	curEnum |= EFlagEnum::Test_Flag_1;

	// 플래그 해제
	// & 연산은 Mask 연산이다. 해당 플래그 이외의 모든 값에 mask를 하게 되면
	// 해당 값을 제외한 모든 값이 결과가 된다.
	curEnum &= ~EFlagEnum::Test_Flag_2;

	// 플래그 토글
	// xor 연산을 하게 되면 비트를 반전시킬 수 있다.
	// 0 ^ 1 = 1 (cur flag ^ Flag_1)
	// 1 ^ 1 = 0 (cur flag ^ Flag_1)
	curEnum ^= EFlagEnum::Test_Flag_3;

	// 플래그 확인
	// of if( (curEnum & EFlagEnum::Test_Flag_1) != EFlag::Test_Flag_0)
	if( (curEnum & EFlagEnum::Test_Flag_1) == EFlagEnum::Test_Flag_1) {
		// Flag1 설정됨
	}
}

void AEnumTest::SetFlagInBlueprint(int32 flag)
{
	UE_LOG(LogTemp, Log, TEXT("Flag : %d"), flag);
	OutputFlag |= flag;
}

void AEnumTest::SetFlagInBlueprintWithoutMeta(uint8 flag)
{

}

// Called when the game starts or when spawned
void AEnumTest::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEnumTest::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
