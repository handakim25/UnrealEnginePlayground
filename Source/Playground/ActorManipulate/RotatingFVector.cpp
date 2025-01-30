// Fill out your copyright notice in the Description page of Project Settings.


#include "RotatingFVector.h"

// Sets default values
ARotatingFVector::ARotatingFVector()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	const auto SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(SceneRoot);
	
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("StaticMeshComponent");
	StaticMeshComponent->SetupAttachment(RootComponent);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> DefaultMeshAsset(TEXT("/Engine/BasicShapes/Cube.Cube"));
	if (DefaultMeshAsset.Succeeded())
	{
		StaticMeshComponent->SetStaticMesh(DefaultMeshAsset.Object);
	}

	static ConstructorHelpers::FObjectFinder<UMaterial> DefaultMaterialAsset(TEXT("/Engine/BasicShapes/BasicShapeMaterial.BasicShapeMaterial"));
	if (DefaultMaterialAsset.Succeeded())
	{
		StaticMeshComponent->SetMaterial(0, DefaultMaterialAsset.Object);
	}
}

// Called when the game starts or when spawned
void ARotatingFVector::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ARotatingFVector::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// FRotator CurrentRotator = GetActorRotation();
	// CurrentRotator += Rotation * DeltaTime;
	// SetActorRotation(CurrentRotator);

	// FQuat CurrentQuat = FQuat(GetActorRotation());
	// FQuat DeltaRotation = FQuat(Rotation * DeltaTime);
	// FQuat NewRotation = DeltaRotation * CurrentQuat;
	// SetActorRotation(NewRotation);
	
	AddActorLocalRotation(Rotation * DeltaTime);
}
