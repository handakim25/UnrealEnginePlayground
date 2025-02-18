// Fill out your copyright notice in the Description page of Project Settings.


#include "RegisterDelegate.h"

#include "DelegateTest.h"

// Sets default values
ARegisterDelegate::ARegisterDelegate()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ARegisterDelegate::BeginPlay()
{
	Super::BeginPlay();
	
}

void ARegisterDelegate::BindSimpleDelegate()
{
	if (DelegateTest == nullptr) return;;
}

// Called every frame
void ARegisterDelegate::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

