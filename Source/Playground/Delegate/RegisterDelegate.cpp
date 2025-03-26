// Fill out your copyright notice in the Description page of Project Settings.


#include "RegisterDelegate.h"

#include "DelegateTest.h"
#include "EngineUtils.h"

// Sets default values
ARegisterDelegate::ARegisterDelegate()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void ARegisterDelegate::BeginPlay()
{
	Super::BeginPlay();

	
	// Find DelegateTest
	for (TActorIterator<ADelegateTest> It(GetWorld()); It; ++It)
	{
		if (ADelegateTest* DelegateTest = *It)
	    {
			DelegateTestWeakPtr = DelegateTest;
	    }
	}
}

void ARegisterDelegate::CallSimpleMethod()
{
	UE_LOG(LogTemp, Display, TEXT("Call Simple Method"));
}

void ARegisterDelegate::BindSimpleDelegate()
{
	if (DelegateTestWeakPtr.IsValid())
	{
		DelegateTestWeakPtr->OnSimpleValidDelegate.BindUObject(this, &ARegisterDelegate::CallSimpleMethod);
	}
}

void ARegisterDelegate::DestroyAndGC()
{
	UE_LOG(LogTemp, Display, TEXT("Destroy and GC"));
	Destroy();
	GEngine->ForceGarbageCollection(true);
}

void ARegisterDelegate::OnlyDestroy()
{
	UE_LOG(LogTemp, Display, TEXT("Only Destroy"));
	Destroy();
}

// Called every frame
void ARegisterDelegate::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

