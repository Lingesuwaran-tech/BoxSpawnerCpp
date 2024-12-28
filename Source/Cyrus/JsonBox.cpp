// Fill out your copyright notice in the Description page of Project Settings.

#include "JsonBox.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "UObject/ConstructorHelpers.h"

#include "CyrusGameMode.h"

// Sets default values
AJsonBox::AJsonBox()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BoxComp = CreateDefaultSubobject <UBoxComponent>(TEXT("Box Collision"));
	BoxComp->SetNotifyRigidBodyCollision(true);
	BoxComp->BodyInstance.SetCollisionProfileName("BlockAll");
	BoxComp->OnComponentHit.AddDynamic(this, &AJsonBox::OnCompHit);
	RootComponent = BoxComp;

	BoxMesh = CreateDefaultSubobject <UStaticMeshComponent>(TEXT("Box Mesh"));
	BoxMesh->SetupAttachment(RootComponent);

	Material = CreateDefaultSubobject<UMaterialInstance>(TEXT("Material Instance"));

	/*
	Default value code for mesh

	static ConstructorHelpers::FObjectFinder<UStaticMesh> BoxAsset(TEXT("/Script/Engine.StaticMesh'/Game/FirstPerson/Blueprints/StaticMesh/Cube.Cube'"));
	if (BoxAsset.Succeeded())
	{
		BoxMesh->SetStaticMesh(BoxAsset.Object);
		BoxMesh->SetRelativeScale3D(FVector(0.5f));
		BoxMesh->SetMaterial(0,Material);

		UE_LOG(LogTemp, Display, TEXT("Done"));
	}
	else UE_LOG(LogTemp, Warning, TEXT("NoDone"));
	*/
	
	

}

// Called when the game starts or when spawned
void AJsonBox::BeginPlay()
{
	Super::BeginPlay();
	
}

//Called when Box is hit
void AJsonBox::OnCompHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if((OtherActor != NULL)&&(OtherActor != this)&&(OtherComp != NULL))
	{
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("-1 HP")));
		}
		HitCounter -= 1;
		if (HitCounter == 0) 
		{
			AJsonBox::Destroy();
			ACyrusGameMode* const GameMode = GetWorld()->GetAuthGameMode<ACyrusGameMode>();

			GameMode->AddScore(Score);
		}

	}
}

void AJsonBox::setValues(FString name, TArray <int> color, int HP, int score)
{
	UE_LOG(LogTemp, Display, TEXT("Name: %s"), *name);

	HitCounter = HP;
	Score = score;

	UMaterialInstanceDynamic* DyMaterial = UMaterialInstanceDynamic::Create(Material,this);
	DyMaterial->SetVectorParameterValue(TEXT("Color"), FVector(color[0],color[1],color[2]));
	BoxMesh->SetMaterial(0, DyMaterial);
}

// Called every frame
void AJsonBox::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

