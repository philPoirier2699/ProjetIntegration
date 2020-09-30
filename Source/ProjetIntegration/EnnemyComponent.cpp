// Fill out your copyright notice in the Description page of Project Settings.


#include "EnnemyComponent.h"

// Sets default values
AEnnemyComponent::AEnnemyComponent()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Health = 50;
}

void AEnnemyComponent::TakeDamage(int damage)
{
	Health = Health - damage;
}

// Called when the game starts or when spawned
void AEnnemyComponent::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEnnemyComponent::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (Health <= 0)
		this->Destroy();
}

// Called to bind functionality to input
void AEnnemyComponent::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

