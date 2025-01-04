// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MacroTest.generated.h"

UCLASS()
class PLAYGROUND_API AMacroTest : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMacroTest();
	
	// https://dev.epicgames.com/documentation/ko-kr/unreal-engine/unreal-engine-uproperties

	// https://dev.epicgames.com/documentation/ko-kr/unreal-engine/gameplay-classes-in-unreal-engine
	// 발췌
	// 컴포넌트 서브오브젝트를 만들고 액터의 계층구조에 붙이는 것은 생성자 안에서도 가능합니다.
	// 액터 스폰시, 그 컴포넌트가 CDO 에서 복제됩니다.
	// 컴포넌트가 항상 제대로 생성, 소멸, 가비지 콜렉팅의 과정을 거치도록 하기 위해서는,
	// 생성자에서 생성된 모든 컴포넌트로의 포인터를 소유 클래스의 UPROPERTY 에 저장해야 합니다.

	// 공개 / 접근 권한
	// Edit, Visible은 베타적인 관계라서 둘 중에 하나만 사용 가능

	// Visible : 편집 불가능하고 읽기만 가능
	// 모든 프로퍼티 창에서 확인 가능
	UPROPERTY(VisibleAnywhere)
	int VisibleAnywhere_Variable;
	// 아티 타입에 대한 프로퍼티 창에서 확인 가능(블루프린트 창에서 확인 가능)
	UPROPERTY(VisibleDefaultsOnly)
	int VisibleDefaultOnly_Variable;
	// 인스턴스에서만 확인 가능(월드에 배치된 엑터의 디테일 창에서 확인 가능)
	UPROPERTY(VisibleInstanceOnly)
	int VisibleInstanceOnly_Variable;

	// Edit : 읽고 편집 가능
	// 모든 프로퍼티 창에서 수정 가능
	UPROPERTY(EditAnywhere)
	int EditAnywhere_Variable;
	// 아키 타입에 대한 프로퍼티 창에서 수정 가능(블루프린트 창에서 수정 가능)
	UPROPERTY(EditDefaultsOnly)
	int EditDefaultsOnly_Variable;
	// 인스턴스에서만 수정 가능(월드에 배치된 엑터의 디테일 창에서 수정 가능)
	UPROPERTY(EditInstanceOnly)
	int EditInstanceOnly_Vairable;

	// Blueprint 공개 / 접근 권한
	// Read/Write는 상호베타적임

	// 블루프린트에서 Get만 가능
	UPROPERTY(BlueprintReadOnly)
	int BluePrintReadonly_Variable;
	// 블루프린트에서 Get/Set 가능
	UPROPERTY(BlueprintReadWrite)
	int BlueprintReadWrite_Variable;
	
	UPROPERTY(VisibleAnywhere, BlueprintGetter = GetBlueprintVal, BlueprintSetter = SetBlueprintVal)
	int BlueprintGetterSetter_Variable = 3;

	UFUNCTION(BlueprintGetter)
	int GetBlueprintVal();

	UFUNCTION(BlueprintSetter)
	void SetBlueprintVal(int val);

	UPROPERTY(VisibleAnywhere, AdvancedDisplay)
	// 디테일 패널에서 고급(드롭다운) 섹션에 들어간다.
	int AdvancedDisplay_Variable;

	// Category
	UPROPERTY(VisibleAnywhere, Category = "Top|Sub|Ssub")
	int Category_Variable;

	// 메타 데이터
	// 언리얼 엔진 및 에디터의 다양한 측면에서 행동하는 방식을 지정

	// Clamp Max : 최대, Clamp Min : 최소
	UPROPERTY(EditAnywhere, meta= (ClampMax="3", ClampMin="1"))
	int clamp = 2;

	// 프로퍼티가 표시될 이름을 설정
	// 프로퍼티 창뿐만 아니라 블루 프린트에서도 이름이 변경된다.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(DisplayName="Display Meta"))
	int DisplayTest_Variable;

	UPROPERTY(VisibleAnywhere)
	int CallInEditorVal = 0;

private:
	// Private 변수도 UPROPERTY를 사용하면 노출된다.
	UPROPERTY(VisibleAnywhere)
	int Priavet_Variable;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// https://dev.epicgames.com/documentation/ko-kr/unreal-engine/ufunctions-in-unreal-engine
	// https://dev.epicgames.com/documentation/ko-kr/unreal-engine/exposing-gameplay-elements-to-blueprints-visual-scripting-in-unreal-engine
	// https://dev.epicgames.com/documentation/ko-kr/unreal-engine/exposing-cplusplus-to-blueprints-visual-scripting-in-unreal-engine

	// UFUNCTION
	// 1. 블루프린트에 노출시킬 수 있게 된다.
	// 2. 네트워크 콜백을 가능하게 한다.
	// 3. 콘솔 명령어 대응

	UFUNCTION(BlueprintCallable)
	// 블루프린트에서 호출 가능하다.
	void Callable();

	UFUNCTION(BlueprintCallable)
	// BlueprintPure가 아니더라도 출력이 있는 const는 pure 노드가 된다.
	void CallableConst(int& a) const;

	UFUNCTION(BlueprintPure)
	// 블루프린트에서 순수 함수로 나타나게 되며 실행 흐름 노드가 아니라 값 노드로 나타내어져서 출력만이 존재하고 실행 핀이 존재하지 않는다.
	// 상태를 변경하지 않고 단순하게 값을 반환하는 함수에 사용된다. 따라서 데이터를 조회하거나 계산 결과를 반환할 때 사용한다.
	int Pure();

	UFUNCTION(BlueprintImplementableEvent)
	// C++에서 구현하지 않고 블루프린트에서 구현할 수 있는 함수. C++ 내부에서는 블루프린트로 구현된 것을 사용한다.
	void BlueprintImpleFunction();

	UFUNCTION(BlueprintImplementableEvent)
	// Blueprint에서 구현하기 때문에 블루프린트에서는 인자를 받아서 사용한다.
	void BlueprintImpleFunctionWithParam(float f, int a);

	UFUNCTION(BlueprintImplementableEvent)
	int BlueprintImpleFunctionWithRet(int a);

	UFUNCTION(BlueprintNativeEvent)
	// C++, Blueprint 모두에서 구현 가능한 함수이다.
	// C++은 함수이름_Implementation 함수를 정의하면 된다.
	// Blueprint로 구현하게 되면 블루프린트로 오버라이드하게 된다.
	// 오버라이드하기 때문에 블루프린트 내부에서 상속된 C++ 함수를 호출할 수 있다.
	void BlueprintNativeEventFunction(int a);
	void BlueprintNativeEventFunction_Implementation(int a);

	// Param
	// 블루프린트 노드에서 노출되는 핀을 제어할 수 있다.
	
	// Display Name
	// 핀의 이름을 지정할 수 있다.
	UFUNCTION(BlueprintCallable)
	void ChangeParamFunction(UPARAM(DisplayName = "Display") int a);

	// 참조를 받는 것은 출력으로 사용된다.
	// https://stackoverflow.com/questions/70478765/why-is-c-functions-inputs-become-outputs-in-the-blueprint
	// 출력 값을 여러개 받는 것은 기본적으로 여러 출력 값을 가지고 싶을 때 사용하는 것이기 때문이다.
	// 왜냐하면 어떠한 값이 오든 이것은 이 함수에서 결정이 되기 때문이다.
	// 만약 참조 입력이 필요한 경우 UPARAM(ref)를 이용해야 한다.
	UFUNCTION(BlueprintCallable)
	void OutputParamTest(int& out, int a);

	UFUNCTION(BlueprintCallable)
	void InputRefParamTest(UPARAM(ref) int & refIn, int b);

	UFUNCTION(BlueprintCallable)
	int ReturnIntFunction();

	UFUNCTION(BlueprintCallable)
	void ConstRefParamFunction(const int& refConstIn, int b);

	// 에디터와의 통합 기능

	UFUNCTION(CallInEditor)
	// 에디터에서 호출이 가능하다. 하지만 블루프린트 에디터에서는 호출이 불가능하다.
	void CallInEditorFunction();
};
