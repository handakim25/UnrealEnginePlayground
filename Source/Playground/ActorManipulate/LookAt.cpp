// Fill out your copyright notice in the Description page of Project Settings.


#include "LookAt.h"
#include "Kismet/KismetArrayLibrary.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
ALookAt::ALookAt()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	const auto SceneRoot = CreateDefaultSubobject<USceneComponent>("Root");
	SetRootComponent(SceneRoot);

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("StaticMesh");
	StaticMeshComponent->SetupAttachment(SceneRoot);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> DefaultMeshAsset(TEXT("/Engine/BasicShapes/Cube.Cube"));
	if (DefaultMeshAsset.Succeeded())
	{
		StaticMeshComponent->SetStaticMesh(DefaultMeshAsset.Object);
	}

	static ConstructorHelpers::FObjectFinder<UMaterial> DefaultMaterial(TEXT("/Engine/BasicShapes/BasicShapeMaterial.BasicShapeMaterial"));
	if (DefaultMaterial.Succeeded())
	{
		StaticMeshComponent->SetMaterial(0, DefaultMaterial.Object);
	}

	FrontStaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("FrontStaticMesh");
	FrontStaticMeshComponent->SetupAttachment(StaticMeshComponent);
	FrontStaticMeshComponent->SetRelativeLocation(FVector::ForwardVector * 50);
	FrontStaticMeshComponent->SetRelativeScale3D(FVector::OneVector * 0.5f);

	if (DefaultMeshAsset.Succeeded())
	{
		FrontStaticMeshComponent->SetStaticMesh(DefaultMeshAsset.Object);
	}

	if (DefaultMaterial.Succeeded())
	{
		FrontStaticMeshComponent->SetMaterial(0, DefaultMaterial.Object);
	}

	TraceTarget = false;
}

// Called when the game starts or when spawned
void ALookAt::BeginPlay()
{
	Super::BeginPlay();
	
}

void ALookAt::LookTargetKismet()
{
	if (LookAtTarget)
	{
		FRotator LookAtRotation = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), LookAtTarget->GetActorLocation());
		SetActorRotation(LookAtRotation);
	}
}

void ALookAt::LookTargetMatrix()
{
	if (LookAtTarget)
	{
		// KismetMathLibrary의 FindLookAtRotation과 동일
		// X로 행렬을 만들므로 Front가 Direction이 되는 Matrix를 만들게 된다.
		// 따라서 Direction 방향으로 보는 회전 횡렬을 생성하게 되고 이를 이용하면 Look At을 구현할 수 있다.
		FVector Direction = (LookAtTarget->GetActorLocation() - GetActorLocation());
		FRotator LookAtRotation = FRotationMatrix::MakeFromX(Direction).Rotator();
		SetActorRotation(LookAtRotation);
	}
}

// Called every frame
void ALookAt::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (TraceTarget && LookAtTarget != nullptr)
	{
        if(IsRInterp)
        {
            FVector Direction = (LookAtTarget->GetActorLocation() - GetActorLocation());
            FRotator TargetRotation = FRotationMatrix::MakeFromX(Direction).Rotator();
    
            FRotator SmoothRotation = FMath::RInterpTo(GetActorRotation(), TargetRotation, DeltaTime, 5.0f);
        	SetActorRotation(SmoothRotation);
        }
        if(IsSlerp)
        {
            FVector Direction = (LookAtTarget->GetActorLocation() - GetActorLocation());
            FQuat TargetQuat = FRotationMatrix::MakeFromX(Direction).ToQuat();
            
            FQuat CurrentQuat = GetActorQuat();

        	FQuat SmoothQuat = FQuat::Slerp(CurrentQuat, TargetQuat, DeltaTime * 5.0f);
        	SetActorRotation(SmoothQuat);
        }
	}
}

