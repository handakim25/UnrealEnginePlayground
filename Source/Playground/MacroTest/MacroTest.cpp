// Fill out your copyright notice in the Description page of Project Settings.


#include "MacroTest.h"

// Sets default values
AMacroTest::AMacroTest()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMacroTest::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMacroTest::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

int AMacroTest::GetBlueprintVal()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Orange, TEXT("Set"));
    return BlueprintGetterSetter_Variable + 10;
}

void AMacroTest::SetBlueprintVal(int val)
{
	// Set을 호출할 때 Getter도 같이 호출된다.
	BlueprintGetterSetter_Variable += val + 100;
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Orange, TEXT("Get"));
}

void AMacroTest::Callable()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Orange, TEXT("Blueprint Callable"));
}

void AMacroTest::CallableConst(int& a) const
{
	return;
}

int AMacroTest::Pure()
{
	Priavet_Variable += 10;
    return 10;
}

void AMacroTest::BlueprintNativeEventFunction_Implementation(int a)
{
	
}

void AMacroTest::OutputParamTest(int &out, int a)
{
	out += 30;
}

void AMacroTest::InputRefParamTest(UPARAM(ref) int &refIn, int b)
{

}

int AMacroTest::ReturnIntFunction()
{
    return 0;
}

void AMacroTest::ConstRefParamFunction(const int &refConstIn, int b)
{
}

void AMacroTest::CallInEditorFunction()
{
	UE_LOG(LogTemp, Warning, TEXT("This function was called in the editor!"));

	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Orange, TEXT("Editor Function"));

	FMessageLog("PIE").Info(FText::FromString(TEXT("This is an editor debug message.")));

	Modify();
	CallInEditorVal = 100;
	MarkPackageDirty();
}

void AMacroTest::ChangeParamFunction(int a)
{

}
