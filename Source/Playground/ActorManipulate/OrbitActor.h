// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "OrbitActor.generated.h"

UCLASS()
class PLAYGROUND_API AOrbitActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AOrbitActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	void UpdatePositionAndRotation();

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* StaticMeshComponent;
	
	UPROPERTY(EditAnywhere)
	AActor* TargetActor;
	UPROPERTY(EditAnywhere)
	float RotationSpeed;
	UPROPERTY(EditAnywhere)
	float OrbitRadius;
	UPROPERTY(EditAnywhere)
	float CurrentAngle;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void OnConstruction(const FTransform& Transform) override;
};
