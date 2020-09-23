// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Components/InputComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "ThirdPersonCharacter.generated.h"


UCLASS()
class PROJETINTEGRATION_API AThirdPersonCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AThirdPersonCharacter();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
		USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
		UCameraComponent* FollowCamera;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Combat)
		UAnimMontage* sheatheMontage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Combat)
		UAnimMontage* withdrawMontage;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Combat)
		FName playerWeaponHandSocket = TEXT("RightHandSocket");

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Combat)
		FName playerWeaponSheatheSocket = TEXT("SheatheSocket");

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Combat)
		bool weaponInUse;

	bool sprinting;

	// Getter empeche la creation de blueprint runtime error
	UFUNCTION(BlueprintCallable)
		bool getWeaponInUse() const { return weaponInUse; }

	void MoveForward(float Axis);
	void MoveRight(float Axis);
	void Sprint();
	void UseWeapon();



protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
