// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "InterfaceTest.generated.h"

// 리플렉션 시스템 비저빌리티를 위한 빈 클래스
// UInterface를 상속받기만 하고 실질적인 선언은 I<Interface_Name>에 선언한다.
// - Blueprintable : 블루프린트에서 구현 가능할 수 있도록 인터페이스를 노출한다. 모든 메소드가 BlueprintImplementableEvent, BlueprintNatviteEvent로 이루어져 있어야 한다.
// - BlueprintType : 블루프린트 변수에 사용할 수 있는 타입으로 노출한다.
// - MinimalAPI : 모듈 공개 설정을 위한 키워드이다. 공개 설정을 해서 캐스팅이 가능하지만, 인라인 메소드를 제외하면 호출될 수 없다.
// This class does not need to be modified.

// 참고
// https://dev.epicgames.com/documentation/ko-kr/unreal-engine/interfaces-in-unreal-engine
// https://dev.epicgames.com/documentation/ko-kr/unreal-engine/blueprint-interface-in-unreal-engine
// https://dev.epicgames.com/documentation/ko-kr/unreal-engine/implementing-blueprint-interfaces-in-unreal-engine
// https://benui.ca/unreal/uclass/
// https://benui.ca/unreal/uinterface/
// https://stackoverflow.com/questions/79177844/unreal-engine-i-cant-fix-interfaces-with-blueprintcallable-functions-but-no
// https://algorfati.tistory.com/45
// https://forums.unrealengine.com/t/how-blueprintnativeevent-specifier-works/360534/5

UINTERFACE(MinimalAPI)
class UInterfaceTest : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class PLAYGROUND_API IInterfaceTest
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
};

UINTERFACE(MinimalAPI)
class UCPPInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * Interface를 실질적으로 선언하는 클래스이다. 다른 클래스에서 상속 받을 때는 이 클래스를 상속 받아서 사용한다.
 */
class PLAYGROUND_API ICPPInterface
{
	GENERATED_BODY()
	
	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	// 순수 가상 함수가 아닌 인터페이스의 경우 기본 구현을 구현하는 것은 가능하다.
	// 다만, 인터페이스의 기본 정의에 의하면 구현은 가지지 않는 것이 바랍직하다.
	// 특별한 이유가 없다면 순수 가상 함수로 정의한다.
	virtual void TakeDamage();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void BlueprintNativeEventTest();
};

// NotBlueprintable - C++에서만 사용 가능한 Interface
// NotBlueprintable은 블루프린트에서 함수들을 구현할 수 없는 것을 의미한다.
// 따라서 이 경우는 BlueprintNativeEvent, BlueprintImplementableEvent를 사용할 수 없다.
UINTERFACE(MinimalAPI, NotBlueprintable)
class UBlueprintCallableTest : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class PLAYGROUND_API IBlueprintCallableTest
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	// BlueprintCallable을 이용할 경우 NotBlueprintable을 해야 한다.
	// 그렇지 않을 경우 빌드 되지 않는다.
	UFUNCTION(BlueprintCallable)
	virtual int TestBlueprintCallabe();

	// Compile Error : BlueprintImplementableEvent는 NotBlueprintable에서 사용 불가능하다.
	// UFUNCTION(BlueprintImplementableEvent)
	// void BlueprintImpleFunction();
};

// Blueprintable이 아니지만 Blueprint 메소드 정의
// Blueprint 메소드들은 가상 함수가 아니어야 한다.
// BlueprintImplementableEvent : 블루프린트에서만 오버라이드해서 사용하는 함수
// BlueprintNativeEvent : C++ 혹은 블루프린트에서 구현 가능
UINTERFACE(MinimalAPI)
class UBlueprintFuncTest : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class PLAYGROUND_API IBlueprintFuncTest
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	// 블루프린트에서 상속 받아서 사용 가능하다.
	// 반환값이 없으면 이벤트로 취급한다.
	// C++ 클래스가 상속 받을 경우 따로 override로 지정하지 않아도 BP에서 Interface로 구현할 수 있다.
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void BlueprintImplementableFunc();

	// 반환값이 있으면 함수로 취급된다.
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	int BlueprintImplementableFuncWithReturn();
};

// BlueprintType : 변수로 사용할 수 있는 타입으로 노출 여부
// Blueprintable이 아니어도 BlueprintType으로 지정하면 변수로 받아와서 사용할 수 있다.
UINTERFACE(MinimalAPI, NotBlueprintable, BlueprintType)
class UBlueprinttype : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class PLAYGROUND_API IBlueprinttype
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
};



// Blueprint, C++ 모두에서 대응하는 인터페이스 : BlueprintNativeEvent
UINTERFACE(MinimalAPI)
class UBlueprintNativeInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * BlueprintNatvieEvent 태스트. 공식 문서의 예시가 컴파일이 안 된다.
 * 다른 곳에서의 구현은 Interface에 _Implementation을 두고 다른 C++에서 오버라이딩하는 방식이기에 해당 방법을 이용한다.
 */
class PLAYGROUND_API IBlueprintNativeInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintNativeEvent)
	void BlueprintNativeEventFunc();

	UFUNCTION(BlueprintNativeEvent)
	int BlueprintNativeEventWithReturn();

	UFUNCTION(BlueprintNativeEvent)
	void BlueprintNativeEventWithParam(int a, int b);

	UFUNCTION(BlueprintNativeEvent)
	void BLueprintNativeEventNotImple();
};

UINTERFACE(MinimalAPI, Blueprintable)
class UBlueprintableInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class PLAYGROUND_API IBlueprintableInterface
{
	GENERATED_BODY()
	
	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	// 문서 상으로는 Blueprintable은 모든 인터페이스가 Blueprint 함수이어야 한다고 하지만 현재로서는 빌드가 가능하다.
	virtual void NotBlueprintableFunc() = 0;

	UFUNCTION(BlueprintNativeEvent)
	void BlueprintNativeEvent();
};
