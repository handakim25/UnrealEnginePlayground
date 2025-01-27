// Fill out your copyright notice in the Description page of Project Settings.


#include "UReferenceTest.h"

// Sets default values
AUReferenceTest::AUReferenceTest()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AUReferenceTest::BeginPlay()
{
	Super::BeginPlay();
	Destroy();
}

// Called every frame
void AUReferenceTest::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

