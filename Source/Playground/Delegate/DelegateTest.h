// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Windows/AllowWindowsPlatformTypes.h"
#include "DelegateTest.generated.h"

// https://darkcatgame.tistory.com/66

// 참고
// 1. https://dev.epicgames.com/documentation/ko-kr/unreal-engine/delegates-and-lamba-functions-in-unreal-engine
// 2. https://benui.ca/unreal/delegates-intro/
// 3. https://forums.unrealengine.com/t/how-to-setup-dynamic-single-delegate-with-retval-to-make-it-bindable-from-blueprints/764150/1
// 4. https://dev.epicgames.com/community/learning/tutorials/6xrK/unreal-engine-brief-overview-of-delegates-and-their-uses-in-c-and-blueprints
// 5. Delegate.h

// TO-Do
// 1. Blueprint Assignable Test(Dynamic Delegate)
// 2. Delegate 등록 객체 소멸 시에 Delegate 유효값 확인

// no return value, no parameter
DECLARE_DELEGATE(FSimpleSignature);
DECLARE_MULTICAST_DELEGATE(FSimpleBroadcastDelegate);
DECLARE_DYNAMIC_DELEGATE(FDynamicSignature);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDynamicBroadcastDelegate);

DECLARE_DELEGATE_RetVal_TwoParams(int32, FRetWithTwoParamsSignature, float, int32);

DECLARE_DYNAMIC_DELEGATE(FSimpleDynamicSignature);

class FNormalClass
{
public:
	void TestMethod();
};

UCLASS()
class PLAYGROUND_API ADelegateTest : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADelegateTest();

	FNormalClass* NormalClass;
	TSharedPtr<FNormalClass> SharedNormalClass;
	
	FSimpleSignature OnSimpleDelegate;
	FSimpleBroadcastDelegate OnSimpleBroadcastDelegate;
	FRetWithTwoParamsSignature OnRetWithTwoParamsDelegate;
	FSimpleDynamicSignature OnSimpleDynamicDelegate;

	FDynamicSignature OnDynamicDelegate;
	FDynamicBroadcastDelegate OnDynamicBroadcastDelegate;

	FSimpleSignature OnSimpleValidDelegate;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION(CallInEditor)
	void CallSimpleDelegate();

	UFUNCTION(CallInEditor)
	void CallBindSimpleDelegate();

	UFUNCTION(CallInEditor)
	void CallSimpleMulticastDelegate();

	UFUNCTION(CallInEditor)
	void CallBindSimpleMulticastDelegate();

	UFUNCTION(CallInEditor)
	void CallDynamicDelegate();

	UFUNCTION(CallInEditor)
	void CallBindDynamicDelegate();

	UFUNCTION(CallInEditor)
	void CallBindDynamicMulticastDelegate();

	UFUNCTION(CallInEditor)
	void CallDynamicMulticastDelegate();
	
	UFUNCTION(CallInEditor)
	void CallRetWithTwoParams();

	UFUNCTION(CallInEditor)
	void CallSimpleDynamicDelegate();

	static void TestStaticMethod();
	void TestMethod();
	UFUNCTION()
	void TestUFunctionMethod();

	UFUNCTION(CallInEditor)
	void ValidDelegateTest();
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
