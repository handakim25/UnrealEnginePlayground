// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RegisterDelegate.generated.h"

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

	UPROPERTY(EditAnywhere)
	class ADelegateTest* DelegateTest;

	void BindSimpleDelegate();
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
