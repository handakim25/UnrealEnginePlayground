// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RegisterDelegate.generated.h"

class ADelegateTest;
UCLASS()
class PLAYGROUND_API ARegisterDelegate : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARegisterDelegate();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	TWeakObjectPtr<ADelegateTest> DelegateTestWeakPtr;

	void CallSimpleMethod();
	UFUNCTION(CallInEditor)
	void BindSimpleDelegate();

	UFUNCTION(CallInEditor)
	void DestroyAndGC();

	UFUNCTION(CallInEditor)
	void OnlyDestroy();
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
