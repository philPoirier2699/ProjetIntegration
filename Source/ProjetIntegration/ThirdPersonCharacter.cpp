// Fill out your copyright notice in the Description page of Project Settings.


#include "ThirdPersonCharacter.h"
#include "UObject/ConstructorHelpers.h"

// Sets default values
AThirdPersonCharacter::AThirdPersonCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Rotate the character to the directtion in which he is moving
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.f, 0.0f);
	GetCharacterMovement()->JumpZVelocity = 600.0f;
	GetCharacterMovement()->AirControl = 0.2f;

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraCoom"));
	// Attach camera Boom to capsule component of the character
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 300.0f;
	//Rotate the camera boom based on controller
	CameraBoom->bUsePawnControlRotation = true;
	CameraBoom->SocketOffset = FVector(0.0f, 0.0f, 30.0f);

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;
	
	GetCharacterMovement()->MaxWalkSpeed = 300.0f;
	AThirdPersonCharacter::GetMesh()->OnComponentBeginOverlap.AddDynamic(this, &AThirdPersonCharacter::OnOverlapBegin);
	sprinting = false;
	weaponInUse = false;
	
}


// Called when the game starts or when spawned
void AThirdPersonCharacter::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AThirdPersonCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Draw and sheath sword
	if(CanDrawSword)
		AThirdPersonCharacter::GetMesh()->GetChildComponent(0)->AttachTo(AThirdPersonCharacter::GetMesh(), playerWeaponHandSocket);
	else if (CanSheathSword)
		AThirdPersonCharacter::GetMesh()->GetChildComponent(0)->AttachTo(AThirdPersonCharacter::GetMesh(), playerWeaponSheathSocket);

	//Attack montage
	if (attackWaiting == 0 && !GetCharacterMovement()->IsFalling())
	{
		ACharacter::StopAnimMontage(attackMontage);
		GetCharacterMovement()->SetMovementMode(MOVE_Walking);
	}
}

// Called to bind functionality to input
void AThirdPersonCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Gere la rotation de la camera avec la souris
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	// Appel MoveForward quand Laction defini dans l'engine est fait
	PlayerInputComponent->BindAxis("MoveForward", this, &AThirdPersonCharacter::MoveForward);
	// Appel MoveRight quand Laction defini dans l'engine est fait
	PlayerInputComponent->BindAxis("MoveRight", this, &AThirdPersonCharacter::MoveRight);

	PlayerInputComponent->BindAction("Jump",IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	PlayerInputComponent->BindAction("Sprint",IE_Pressed, this, &AThirdPersonCharacter::Sprint);

	PlayerInputComponent->BindAction("UseWeapon", IE_Pressed, this, &AThirdPersonCharacter::UseWeapon);

	PlayerInputComponent->BindAction("Attack", IE_Pressed, this, &AThirdPersonCharacter::attackAnim);


}

void AThirdPersonCharacter::AttackWaitingMinus()
{
	attackWaiting--;
}

void AThirdPersonCharacter::ResetAttackWaiting()
{
	attackWaiting = 0;
}

void AThirdPersonCharacter::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("ATTACK!"));
}

void AThirdPersonCharacter::MoveForward(float Axis)
{
	FRotator rotation = Controller->GetControlRotation();
	FRotator yawRotation(0.0f, rotation.Yaw, 0.0f);
	FVector direction = FRotationMatrix(yawRotation).GetUnitAxis(EAxis::X);
	
	AddMovementInput(direction, Axis);
}

void AThirdPersonCharacter::MoveRight(float Axis)
{
	FRotator rotation = Controller->GetControlRotation();
	FRotator yawRotation(0.0f, rotation.Yaw, 0.0f);
	FVector direction = FRotationMatrix(yawRotation).GetUnitAxis(EAxis::Y);
	
	AddMovementInput(direction, Axis);
}

void AThirdPersonCharacter::Sprint()
{
	sprinting = !sprinting;
	if (sprinting)
		GetCharacterMovement()->MaxWalkSpeed = 600.0f;
	else
		GetCharacterMovement()->MaxWalkSpeed = 300.0f;
}

void AThirdPersonCharacter::UseWeapon()
{
	weaponInUse = !weaponInUse;

	if(weaponInUse)
	{
		ACharacter::PlayAnimMontage(withdrawMontage);
	}
	else
	{
		ACharacter::PlayAnimMontage(sheatheMontage);
	}
}

void AThirdPersonCharacter::attackAnim()
{
	if (weaponInUse) 
	{
		if (attackWaiting == 0)
		{
			ACharacter::PlayAnimMontage(attackMontage);
			GetCharacterMovement()->StopMovementImmediately();
			GetCharacterMovement()->SetMovementMode(MOVE_None);
		}
			
		attackWaiting++;
	}
}


