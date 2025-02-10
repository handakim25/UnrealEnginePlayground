// Fill out your copyright notice in the Description page of Project Settings.


#include "RotationTest.h"

// Sets default values
ARotationTest::ARotationTest()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	auto RootScene = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(RootScene);

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(RootScene);
	
	static ConstructorHelpers::FObjectFinder<UStaticMesh> DefaultMesh(TEXT("/Engine/BasicShapes/Cube.Cube"));
	if (DefaultMesh.Succeeded())
	{
		Mesh->SetStaticMesh(DefaultMesh.Object);
	}

	static ConstructorHelpers::FObjectFinder<UMaterial> DefaultMaterial(TEXT("/Engine/BasicShapes/BasicShapeMaterial.BasicShapeMaterial"));
	if (DefaultMaterial.Succeeded())
	{
		Mesh->SetMaterial(0, DefaultMaterial.Object);
	}

	HeadMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("HeadMesh"));
	FTransform HeadTransform;
	HeadTransform.SetLocation(FVector::ForwardVector * 50.0f);
	HeadTransform.SetScale3D(FVector::One() * 0.5f);
	HeadMesh->SetRelativeTransform(HeadTransform);
	HeadMesh->SetupAttachment(Mesh);

	if (DefaultMesh.Succeeded())
	{
		HeadMesh->SetStaticMesh(DefaultMesh.Object);
	}

	if (DefaultMaterial.Succeeded())
	{
		HeadMesh->SetMaterial(0, DefaultMaterial.Object);
	}

	RotateDuration = 2.0f;
	TargetRotator = FRotator(0.0f, 180.0f, 0.0f);
	LerpSpeed = 5.0f;
}

// Called when the game starts or when spawned
void ARotationTest::BeginPlay()
{
	Super::BeginPlay();

	StartRotator = GetActorRotation();
	bIsRotating = true;
	CurrentTime = 0.0f;
}

// Called every frame
void ARotationTest::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!bIsRotating)
	{
		return;
	}

	CurrentTime += DeltaTime;
	
	if (RotateType == ERotateType::RotateType_Const)
	{
		FRotator ConstRotator = FMath::RInterpConstantTo(GetActorRotation(), TargetRotator, DeltaTime, LerpSpeed);
		SetActorRotation(ConstRotator);
	}
	else if (RotateType == ERotateType::RotateType_RLerp)
	{
		FRotator RInterpRotator = FMath::RInterpTo(GetActorRotation(), TargetRotator, DeltaTime, LerpSpeed);
		SetActorRotation(RInterpRotator);
	}
	else if (RotateType == ERotateType::RotateType_Slerp)
	{
		FQuat CurrentQuat = GetActorQuat();
		FQuat TargetQuat = FQuat(TargetRotator);
		FQuat SlerpQuat = FQuat::Slerp(CurrentQuat, TargetQuat, DeltaTime * LerpSpeed);
		SetActorRotation(SlerpQuat);
	}

	if (IsRotateFinished())
	{
		UE_LOG(LogTemp, Display, TEXT("%s Rotate Finished : %f Time"), *GetName(), CurrentTime);
		bIsRotating = false;
	}
}

void ARotationTest::ResetRotation()
{
	SetActorRotation(StartRotator);
	bIsRotating = true;
	CurrentTime = 0.0f;
}

bool ARotationTest::IsRotateFinished() const
{
	FQuat CurrentQuat = FQuat(GetActorRotation());
	FQuat TargetQuat = FQuat(TargetRotator);
	return CurrentQuat.AngularDistance(TargetQuat) < FMath::DegreesToRadians(1.0f);
}
