// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InterfaceTest.h"
#include "InterfaceImpleTest.generated.h"

// 인터페이스로 BlueprintImplementable을 상속 받은 경우에도 생성한 BP에서 인터페이스를 정의할 수 있다.
UCLASS(Blueprintable)
class PLAYGROUND_API AInterfaceImpleTest : public AActor, public ICPPInterface, public IBlueprintFuncTest, public IBlueprintNativeInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AInterfaceImpleTest();

	// ICPPInterface
	virtual void TakeDamage() override;

	virtual void BlueprintNativeEventFunc_Implementation() override;
	virtual int BlueprintNativeEventWithReturn_Implementation();
	virtual void BlueprintNativeEventWithParam_Implementation(int a, int b);
	// Code 예제
	void CodeExample();
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
	TScriptInterface<ICPPInterface> TestInterface;
};
