// Fill out your copyright notice in the Description page of Project Settings.


#include "TObjectPtrTest.h"
#include "Components/ArrowComponent.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
ATObjectPtrTest::ATObjectPtrTest()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootScene = CreateDefaultSubobject<USceneComponent>(TEXT("RootScene"));
	RootComponent = RootScene;

	RawPointer = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RawPointer"));
	RawPointer->SetupAttachment(RootScene);

	ObjectPtr = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TObjectPtr"));
	ObjectPtr->SetupAttachment(RootScene);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> BoxAsset(TEXT("StaticMesh'/Engine/BasicShapes/Cube.Cube'"));
	if(BoxAsset.Succeeded())
	{
		RawPointer->SetStaticMesh(BoxAsset.Object);
		ObjectPtr->SetStaticMesh(BoxAsset.Object);
	}
}

// Called when the game starts or when spawned
void ATObjectPtrTest::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATObjectPtrTest::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATObjectPtrTest::AccessRawPointer()
{
	RawPointer->GetName();
}

void ATObjectPtrTest::AccessTObjectPtr()
{
	ObjectPtr->GetName();
}

void ATObjectPtrTest::DeleteRawPointer()
{
	RawPointer->DestroyComponent();
	// CollectGarbage(GARBAGE_COLLECTION_KEEPFLAGS);
}

void ATObjectPtrTest::DeleteTObjectPtr()
{
	ObjectPtr->DestroyComponent();
	// CollectGarbage(GARBAGE_COLLECTION_KEEPFLAGS);
}

void ATObjectPtrTest::LogRawPointer()
{
	if(RawPointer)
	{
		UE_LOG(LogTemp, Warning, TEXT("Raw Pointer is valid"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Raw Pointer is not valid"));
	}
}

void ATObjectPtrTest::LogTObjectPointer()
{
	if(ObjectPtr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Object Pointer is valid"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Object Pointer is not valid"));
	}
}

void ATObjectPtrTest::SpawnLoadedActors(TObjectPtr<UStaticMeshComponent> Mesh)
{

}