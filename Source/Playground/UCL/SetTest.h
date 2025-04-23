// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SetTest.generated.h"

UCLASS()
class PLAYGROUND_API ASetTest : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ASetTest();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};
