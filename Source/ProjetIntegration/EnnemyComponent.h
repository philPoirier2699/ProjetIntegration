// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "EnnemyComponent.generated.h"

UCLASS()
class PROJETINTEGRATION_API AEnnemyComponent : public APawn
{
	GENERATED_BODY()

	
public:
	// Sets default values for this pawn's properties
	AEnnemyComponent();

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		int Health;

	UFUNCTION(BlueprintCallable)
		void TakeDamage(int damage);

	UFUNCTION()
		void Die();

	UFUNCTION(BlueprintCallable)
		int GetHealth() const { return Health; }
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
