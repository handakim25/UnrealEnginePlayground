// Fill out your copyright notice in the Description page of Project Settings.


#include "InterfaceImpleTest.h"

// Sets default values
AInterfaceImpleTest::AInterfaceImpleTest()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void AInterfaceImpleTest::TakeDamage()
{
}

void AInterfaceImpleTest::BlueprintNativeEventFunc_Implementation()
{
}

int AInterfaceImpleTest::BlueprintNativeEventWithReturn_Implementation()
{
	return 0;
}

void AInterfaceImpleTest::BlueprintNativeEventWithParam_Implementation(int a, int b)
{

}

// 인터페이스 관련 함수 예제
void AInterfaceImpleTest::CodeExample()
{
	// https://dev.epicgames.com/documentation/ko-kr/unreal-engine/interfaces-in-unreal-engine

	// 블루프린트 이벤트 호출하기
	// 인자가 있으면 같이 넘겨주고, 반환값도 같은 형식으로 받아올 수 있다.
	IBlueprintNativeInterface::Execute_BlueprintNativeEventFunc(this);
	int ret = IBlueprintNativeInterface::Execute_BlueprintNativeEventWithReturn(this);
	IBlueprintNativeInterface::Execute_BlueprintNativeEventWithParam(this, 2, 3);
	IBlueprintNativeInterface::Execute_BlueprintNativeEventFunc(Cast<AInterfaceImpleTest>(this));

	// 인터페이스 구현 여부 확인
	// 리플렉션 정보에 접근할 때는 U<Interface Name>으로 접근한다.
	bool bImplementInterface = this->GetClass()->ImplementsInterface(UBlueprintNativeInterface::StaticClass());
	// 리플렉션 정보에 접근할 때는 U<Interface Name>으로 접근한다.
	bool bImplements = this->Implements<UBlueprintNativeInterface>();
	// C++ 버전이 구현되어 있을 경우에만 NULL을 반환하지 않는다.
	IBlueprintNativeInterface* NativeInterface = Cast<IBlueprintNativeInterface>(this);

	UE_LOG(LogTemp, Warning, TEXT("bImplementInterface : %s"), (bImplementInterface ? TEXT("True") : TEXT("False")));	

	// 오브젝트와 인터페이스 포인터 안전하게 저장하기
	TScriptInterface<ICPPInterface> ScriptInterface = TScriptInterface<ICPPInterface>(this);
	// 원본 오브젝트 포인터 얻기
	UObject* RetrievedObjectPtr = ScriptInterface.GetObject();
	// 원본 인터페이스 얻기
	ICPPInterface* RetrievedInterface = ScriptInterface.GetInterface();
}

// Called when the game starts or when spawned
void AInterfaceImpleTest::BeginPlay()
{
	Super::BeginPlay();

	CodeExample();	
}

// Called every frame
void AInterfaceImpleTest::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

