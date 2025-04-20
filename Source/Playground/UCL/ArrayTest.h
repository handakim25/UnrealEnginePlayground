// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ArrayTest.generated.h"

// - 같은 유형의 데이터를 저장하는 오브젝트이다.
// - value type으로 사용된다. new, delete를 사용하지 않는다.
// - TArray를 파괴하면 내부의 원소도 파괴한다.

UCLASS()
class PLAYGROUND_API AArrayTest : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AArrayTest();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
