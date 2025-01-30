// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RotatingFVector.generated.h"

UCLASS()
class PLAYGROUND_API ARotatingFVector : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARotatingFVector();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category="Components")
	class UStaticMeshComponent* StaticMeshComponent;
	
	UPROPERTY(EditAnywhere)
	FRotator Rotation;
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
