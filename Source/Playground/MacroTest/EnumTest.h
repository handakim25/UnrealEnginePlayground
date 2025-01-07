// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EnumTest.generated.h"

// https://forums.unrealengine.com/t/uenum-enum-class-with-uint8/434902/6
// 기본적으로 Enum에서 데이터 형식은 상관 없지만 BlueprintType이 될려면 uint8로 선언해야 한다.

// https://dev.epicgames.com/documentation/ko-kr/unreal-engine/epic-cplusplus-coding-standard-for-unreal-engine
// 열겨형의 경우 E로 시작해야 한다.
// 강 - 타입 Enum : UEnum을 정의할 때는 enum class로 정의해야 한다.

UENUM()
enum class ETestEnum
{
	// UMETA(DisplayName = "")을 이용해서 편집기에서 표시되는 이름을 설정할 수 있다.
	// Enum의 항목에 주석을 작성하려면 항목 위에다가 작성해야 한다.
	// 옆에 작성하면 밑의 항목의 주석으로 된다.
	VE_None UMETA(DisplayName = "None"), 
	VE_Success UMETA(DisplayName = "Success"),
	VE_Fail UMETA(DisplayName = "Failure"),
};

UENUM(BlueprintType)
// enum class EBlueprintEnum <- 빌드 실패. BlueprintType으로 선언할려면 uint8로 선언해야 한다.
enum class EBlueprintEnum : uint8
{
	BPE_A,
	BPE_B,
	BPE_C,
};

UENUM(BlueprintType, meta=(Bitflags, UseEnumValuesAsMaskValuesInEditor="true"))
// UseEnumValuesAsMaskValuesInEditor : Enum의 값을 에디터에서 사용한다.
// 따라서 비트에 해당 되는 값만 에디터에 노출된다.(i.e 0, 1, 2, 4 : 3은 노출되지 않는다.)
// value 값이 플래그 값이므로 플래그에 값을 저장하기 쉽다.
enum class EFlagEnum : uint8
{
	// BitFlags 옵션 설정시에 값이 0인 열거형은 반드시 존재해야 한다.
	// 하지만 인스펙터 창에서는 설정할 수 없다.
	Test_Flag_0 = 0,
	Test_Flag_1 = 1,
	Test_Flag_2 = 2,
	// 값이 3이므로 에디터에 노출되지 않는다.
	Test_Flag_3 = 3,
	Test_Flag_4 = 4,
	// 값이 5이므로 에디터에서 노출되지 않는다.
	Test_Flag_5 = 5,
};

// Enum의 비트 연산을 정의해 준다.
ENUM_CLASS_FLAGS(EFlagEnum)

UENUM(BlueprintType, meta = (Bitflags))
// 값 자체가 비트 플래그로 결정되는 것이 아니라 값 자체가 i 번째 플래그로 설정된다.
// 즉, 실제 값과 설정되는 값이 다르다. 만약에 실제 값을 구할려면 비트 시프트 연산을 통해서 해당 되는 열거형을 구해야 한다.
// 인스펙터 창에서 Test_Flag_1 설정 -> 100(2)의 값이 설정된다. 어느 플래그가 설정되었는지 확인할려면
// 1 << Test_Flag_3을 수행해서 비교한다.
enum class EFlagEnumWithoutMeta : uint8
{
	// 설정하면 2^0 값이 들어간다.
	Test_Flag_0 = 0,
	// 설정하면 2^3 값이 들어간다.
	Test_Flag_1 = 3, 
	// 2^4 값이 들어간다.
	Test_Flag_2 = 4,
	// 2^5 값이 들어간다.
	Test_Flag_3 = 5,
	// 2^6 값이 들어간다.
	Test_Flag_4 = 6,
	// 2^7 값이 들어간다.
	Test_Flag_5 = 7,
};

UCLASS()
class PLAYGROUND_API AEnumTest : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEnumTest();

	// ENUM을 태스트
	UPROPERTY(EditAnywhere)
	ETestEnum test;

	UPROPERTY(EditAnywhere)
	EBlueprintEnum BlueprintEnum;

	UFUNCTION(BlueprintCallable)
	void BlueprintParamNotSupport(ETestEnum testEnum);

	UFUNCTION(BlueprintCallable)
	void BlueprintParamSupport(EBlueprintEnum paramSupportEnum);

	// BitMask
	// https://dev.epicgames.com/documentation/ko-kr/unreal-engine/unreal-engine-uproperties

	// Flag 1, Flag 2, ... 형식으로 선택 가능
	UPROPERTY(EditAnywhere, Meta=(BitMask))
	int32 BasicBits;

	// 언리얼엔진 5버전에서는 Warning이 뜬다.
	// https://forums.unrealengine.com/t/fixing-short-type-name-warning-messages/696553/4
	// /Script/<ProjectName>.<EnumName> 형식으로 수정하면 된다고 한다.
	// EFlagEnum -> /Script/Playground.ElagEnum
	UPROPERTY(EditAnywhere, Meta=(BitMask, BitmaskEnum = "/Script/Playground.EFlagEnum"))
	int EnumFlags;

	UPROPERTY(EditAnywhere, Meta=(BitMask, BitmaskEnum = "/Script/Playground.EFlagEnumWithoutMeta"))
	int EnumFlagWithoutMeta;

	UFUNCTION(CallInEditor)
	void PrintEnumFlag();
	UFUNCTION(CallInEditor)
	void PrintEnumFlagWithoutMeta();

	void BitflagFunction();

	// https://forums.unrealengine.com/t/how-to-use-a-bitflags-parameter-in-a-blueprintcallable-function/450899

	UPROPERTY(EditAnywhere, Meta=(BitMask, BitmaskEnum = "/Script/Playground.EFlagEnum"))
	uint8 OutputFlag;

	UFUNCTION(BlueprintCallable)
	void SetFlagInBlueprint(UPARAM(meta=(BitMask, BitmaskEnum = "/Script/Playground.EFlagEnum")) int32 flag);

	UFUNCTION(BlueprintCallable)
	void SetFlagInBlueprintWithoutMeta(UPARAM(meta=(BitMask, BitmaskEnum = "/Script/Playground.EFlagEnumWithoutMeta")) uint8 flag);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
