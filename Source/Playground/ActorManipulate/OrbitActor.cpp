// Fill out your copyright notice in the Description page of Project Settings.


#include "OrbitActor.h"

// https://gist.github.com/josimard/c69b87dc88882e6f5286d9d69a5b6e85
// Vector.h
// Quat.h
// Rotator.h
// KismetMathLibrary.h
// RotatoinMatrix.h

// Sets default values
AOrbitActor::AOrbitActor()
	:RotationSpeed(30.0f), OrbitRadius(100.0f)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	const auto SceneRoot = CreateDefaultSubobject<USceneComponent>("Root");
	SetRootComponent(SceneRoot);

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("StaticMesh");
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
void AOrbitActor::BeginPlay()
{
	Super::BeginPlay();
	
}

void AOrbitActor::UpdatePositionAndRotation()
{
	const FVector RotationVector = FVector::ForwardVector * OrbitRadius;
	
	// Orbit Vector = Center Vector + Rotated Vector
	const FVector NewLocation = TargetActor->GetActorLocation() + RotationVector.RotateAngleAxis(CurrentAngle, FVector::UpVector);
	SetActorLocationAndRotation(NewLocation, FRotator(0.0f, CurrentAngle, 0.0f));
}

// Called every frame
void AOrbitActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (TargetActor)
	{
		CurrentAngle += DeltaTime * RotationSpeed;
		if (CurrentAngle > 360.0f)
		{
			CurrentAngle -= 360.0f;
		}

		UpdatePositionAndRotation();
	}
}

void AOrbitActor::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	if (TargetActor)
	{
		UpdatePositionAndRotation();
	}
}

