// Fill out your copyright notice in the Description page of Project Settings.


#include "RotatingActor.h"

#include "Components/StaticMeshComponent.h"

// Sets default values
ARotatingActor::ARotatingActor()
	: RotationSpeed(10.0f)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	const auto SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(SceneRoot);

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	StaticMeshComponent->SetupAttachment(SceneRoot);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> DefaultMeshAsset(TEXT("/Engine/BasicShapes/Cube.Cube"));
	if(DefaultMeshAsset.Succeeded())
	{
		StaticMeshComponent->SetStaticMesh(DefaultMeshAsset.Object);
	}

	static ConstructorHelpers::FObjectFinder<UMaterial> DefaultMaterialAsset(TEXT("/Engine/BasicShapes/BasicShapeMaterial.BasicShapeMaterial"));
	if(DefaultMaterialAsset.Succeeded())
	{
		StaticMeshComponent->SetMaterial(0, DefaultMaterialAsset.Object);
	}
}

// Called when the game starts or when spawned
void ARotatingActor::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ARotatingActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AddActorLocalRotation(FRotator(0, RotationSpeed * DeltaTime, 0));
	FRotator NewRotation = FRotator(0, RotationSpeed * DeltaTime, 0);
}