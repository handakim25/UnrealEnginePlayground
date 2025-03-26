// Fill out your copyright notice in the Description page of Project Settings.


#include "DelegateTest.h"

void FNormalClass::TestMethod()
{
	UE_LOG(LogTemp, Display, TEXT("TestMethod in FNormalClass::TestMethod()"));
}

// Sets default values
ADelegateTest::ADelegateTest()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ADelegateTest::BeginPlay()
{
	Super::BeginPlay();

	// Single Cast Delegate Test
	// CallBindSimpleDelegate();
	// CallSimpleDelegate();

	// Multi Cast Delegate Test
	// CallBindSimpleMulticastDelegate();
	// CallSimpleMulticastDelegate();

	// Single Cast Dynamic Delegate Test
	// CallBindDynamicDelegate();
	// CallDynamicDelegate();

	// Multi Cast Dynamic Delegate Test
	// CallBindDynamicMulticastDelegate();
	// CallDynamicMulticastDelegate();

	// 델리게이트가 무효화 됬을 때의 정상 작동 태스트
	// 시나리오
	// 1. 다른 객체가 델리게이트를 바인딩한다.
	// FSimpleDelegate에 바인딩
	// DelegateTest의 델리게이트에 RegisterDelegate가 바인드
	// 2. 다른 객체가 파괴된다.
	// Register Delegate를 파괴
	// a. GC를 수행
	// b. GC를 수행하지 않음, Reference 관리에 주의
	// 3. 델리게이트가 호출을 테스트한다.
}

void ADelegateTest::CallSimpleDelegate()
{
	if (OnSimpleDelegate.IsBound())
	{
		// Valid하지 않을 경우에 호출하면 크래시가 발생한다.
		// 반드시 유효를 확인해야 한다.
		OnSimpleDelegate.Execute();
	}

	// 반환값이 없을 경우 ExecuteIfBound()를 이용할 수 있다.
	// 반환값이 없어야 하는 이유는 ExecuteIfBound()가 반환값으로 성공 여부를 반환하기 때문이다.
	if (!OnSimpleDelegate.ExecuteIfBound())
	{
		UE_LOG(LogTemp, Display, TEXT("On Simple Delegate is not bound"));
	}
}

void ADelegateTest::CallBindSimpleDelegate()
{
	UE_LOG(LogTemp, Display, TEXT("Bind Test"));
	
	// BindStatic
	// OnSimpleDelegate.BindStatic(&ADelegateTest::TestStaticMethod);
	// OnSimpleDelegate.BindStatic(&TestStaticMethod);

	// BindRaw
	// NormalClass = new FNormalClass();
	// OnSimpleDelegate.BindRaw(NormalClass, &FNormalClass::TestMethod);

	// BindLambda
	// OnSimpleDelegate.BindLambda([]() {UE_LOG(LogTemp, Display, TEXT("Bind Lambda Function"));});

	// BindSP
	// 인자로 SharedPtr 자체를 받는 것이 아니라 SharedRef를 사용하는 것에 유의한다.
	// SharedNormalClass = MakeShared<FNormalClass>();
	// OnSimpleDelegate.BindSP(SharedNormalClass.ToSharedRef(), &FNormalClass::TestMethod);
	// auto SharedRef = SharedNormalClass.ToSharedRef();
	// OnSimpleDelegate.BindSPLambda(SharedNormalClass.ToSharedRef(), [SharedRef]{UE_LOG(LogTemp, Display, TEXT("Call SP Lambda"));});

	// BindUObject
	// 언리얼 오브젝트를 바인딩한다. 위의 C++ 로우 포인터에서 언리얼 오브젝트를 바인딩할 수 없고 언리얼 오브젝트는 이 함수를 이용한다.
	OnSimpleDelegate.BindUObject(this, &ADelegateTest::TestMethod);
	// 없는 함수에 바인드를 시도하면 크래시 발생한다.
	// OnSimpleDelegate.BindUFunction(this, FName("TestMethod"));
	// OnSimpleDelegate.BindUFunction(this, FName("TestUFunctionMethod"));
	
	// OnSimpleDelegate.Unbind();
	
	// if (OnSimpleDelegate.IsBoundToObject(this))
	// {
	// 	UE_LOG(LogTemp, Display, TEXT("Check Bind"));		
	// }
}

void ADelegateTest::CallSimpleMulticastDelegate()
{
	UE_LOG(LogTemp, Display, TEXT("Call Multicast Test"));

	if (!OnSimpleBroadcastDelegate.IsBound())
	{
		UE_LOG(LogTemp, Display, TEXT("On Simple Delegate is not bound"));
	}
	
	// Bind 되어 있지 않은 상태에서 호출해도 안전하다.
	// 호출 순서는 보장이 되지 않으므로 순서에 의존하지 않아야 한다.
	OnSimpleBroadcastDelegate.Broadcast();
}

void ADelegateTest::CallBindSimpleMulticastDelegate()
{
	// Static
	OnSimpleBroadcastDelegate.AddStatic(&ADelegateTest::TestStaticMethod);

	// Raw
	NormalClass = new FNormalClass();
	OnSimpleBroadcastDelegate.AddRaw(NormalClass, &FNormalClass::TestMethod);

	// Lambda
	OnSimpleBroadcastDelegate.AddLambda([](){UE_LOG(LogTemp, Display, TEXT("Call Lambda Test"));});

	// Shared Ptr
	// 인자로 SharedPtr 자체를 받는 것이 아니라 SharedRef를 사용하는 것에 유의한다.
	SharedNormalClass = MakeShared<FNormalClass>();
	OnSimpleBroadcastDelegate.AddSP(SharedNormalClass.ToSharedRef(), &FNormalClass::TestMethod);

	// UObject
	FDelegateHandle DelegateHandle = OnSimpleBroadcastDelegate.AddUObject(this, &ADelegateTest::TestMethod);
	
	// OnSimpleBroadcastDelegate.Remove(DelegateHandle);
	OnSimpleBroadcastDelegate.RemoveAll(this);
	if(!OnSimpleBroadcastDelegate.IsBoundToObject(this))
	{
		UE_LOG(LogTemp, Display, TEXT("This object is not bounded"));
	}

	// OnSimpleBroadcastDelegate.Clear();
}

void ADelegateTest::CallDynamicDelegate()
{
	if (OnDynamicDelegate.IsBound())
	{
		OnDynamicDelegate.Execute();
	}
	if (!OnDynamicDelegate.ExecuteIfBound())
	{
		UE_LOG(LogTemp, Display, TEXT("On Dynamic Delegate is not bound"));
	}
}

void ADelegateTest::CallBindDynamicDelegate()
{
	// UFUNCTION이 함수를 넘기면 에러가 발생한다.
	// OnDynamicDelegate.BindDynamic(this, &ADelegateTest::TestMethod);
	OnDynamicDelegate.BindDynamic(this, &ADelegateTest::TestUFunctionMethod);
	// OnDynamicDelegate.BindUFunction(this, FName(TEXT("TestUFunctionMethod")));
}

void ADelegateTest::CallBindDynamicMulticastDelegate()
{
}

void ADelegateTest::CallDynamicMulticastDelegate()
{
	UE_LOG(LogTemp, Display, TEXT("Call Multicast Test"));
	OnDynamicBroadcastDelegate.Broadcast();
}

void ADelegateTest::CallRetWithTwoParams()
{
	if (OnRetWithTwoParamsDelegate.IsBound())
	{
		const int32 Ret = OnRetWithTwoParamsDelegate.Execute(3.0f, 1);
		UE_LOG(LogTemp, Display, TEXT("OnRetWithTwoParams returned %d"), Ret);
	}
}

void ADelegateTest::CallSimpleDynamicDelegate()
{
}

void ADelegateTest::TestStaticMethod()
{
	UE_LOG(LogTemp, Display, TEXT("Test static method in static method"));
}

void ADelegateTest::TestMethod()
{
	UE_LOG(LogTemp, Display, TEXT("Test method"));
}

void ADelegateTest::TestUFunctionMethod()
{
	UE_LOG(LogTemp, Display, TEXT("UFunction Method"));
}

void ADelegateTest::ValidDelegateTest()
{
	// if (OnSimpleValidDelegate.IsBound())
	// {
	// 	UE_LOG(LogTemp, Display, TEXT("OnSimpleValidDelegate is bound"));
	// 	OnSimpleValidDelegate.Execute();
	// }
	// else
	// {
	// 	UE_LOG(LogTemp, Display, TEXT("OnSimpleValidDelegate is not bound"));
	// }

	OnSimpleValidDelegate.Execute();
}

// Called every frame
void ADelegateTest::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

