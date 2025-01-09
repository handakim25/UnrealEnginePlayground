// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "StructTest.generated.h"

// https://dev.epicgames.com/documentation/ko-kr/unreal-engine/structs-in-unreal-engine
// strut의 정의 자체는 class와 유사하다. class와 마찮가지로 GENERATED_BODY()가 첫번째 줄에 와야 한다.
// 매크로로 지정하지만 UObject가 아니고 class의 내부에서만 사용한다.
// UPROPERTY를 지원하지만 UFUNCTION은 지원하지 않는다.

// 활용
// 1. 에디터와의 통합
// 2. 네트워크 레플리케이션
// 3. 블루프린트 통합
// 리플리케이션은 현재 범위에 넣기에는 광대하기에 블루프린트 통합과 에디터 통합만 다룬다.

// USRUCT : BlueprintType : 블루프린트에서 사용 가능하게 한다., NoExport : 자동 생성 코드가 생성되지 않고 메타 데이터만 파싱된다.

// BlueprintType, Atomic, NoExport
USTRUCT()
struct PLAYGROUND_API FTestStruct
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	int Anywhere = 3;

	UPROPERTY(EditDefaultsOnly)
	int DefaultsOnly = 2;

	UPROPERTY(EditInstanceOnly)
	int InstanceOnly = 1;
};

// Blueprint에서 사용하기 위해서는 BlueprintType을 지정해야 한다. 블루프린트 타입이 되면 다음과 같은 것이 가능하다.
// Blueprint에서 Class의 프로퍼티를 노출 가능하다.
// Make / Break 노드가 생성됨. Make 노드의 경우는 ReadWrite, Write 변수가 노출되고 Break 노드의 경우는 Read 변수가 노출된다.
// 또한, 블루프린트에서 변수를 선언할 수도 있다.

USTRUCT(BlueprintType)
struct FBlueprintReadWriteStruct
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite)
	int BlueprintReadWrite = 1;

	UPROPERTY(BlueprintReadOnly)
	int BlueprintReadOnly = 2;
};

USTRUCT(BlueprintType)
struct FBlueprintStruct
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	int Anywhere = 3;

	UPROPERTY(EditDefaultsOnly)
	int DefaultsOnly = 2;

	UPROPERTY(EditInstanceOnly)
	int InstanceOnly = 1;

	UPROPERTY(BlueprintReadWrite)
	int BlueprintReadWrite = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int AnywhereReadWrite = 2;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	int DefaultsOnlyReadWrite = 3;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite)
	int InstanceOnlyReadWrite = 4;

	UPROPERTY(BlueprintReadOnly)
	int BluepirntReadonly = 2;
};

// noexport
// noexport로 설정되면 메타 데이터만 정의되므로 GENERATED_BODY가 없어야 한다.
// 대표적인 예시로는 FVector가 있다.
// MathFwd : 전방선언, using FVector = UE::Math::TVector<double>
// Vector.h : TVector 선언 및 정의
// NoExportTypes.h : Blueprint에서의 FVector 정의
// KismetMathLibray.inl : Bluepirnt에서의 Make, Break Vector를 정의
// Tempalte struct이니까 리플렉션을 사용할 수가 없다. 하지만 블루프린트에서 사용되어야 하므로 리플렉션이 안 되지만 헤더에는 노출되게 한다.

UCLASS()
class PLAYGROUND_API AStructTest : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AStructTest();

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite)
	FBlueprintStruct BlueprintWriteStruct;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FBlueprintStruct EditAnywhereBlueprintWriteStruct;

	UPROPERTY(BlueprintReadWrite)
	int OnlyBlueprintReadWrite;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};

// 참고
// https://vorixo.github.io/devtricks/atomicity/
// https://www.reddit.com/r/unrealengine/comments/kd0h4i/ustruct_specifiers_explained_with_more_on_the_way/?rdt=44347
// https://benui.ca/unreal/ustruct/