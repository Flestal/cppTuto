// Fill out your copyright notice in the Description page of Project Settings.


#include "CameraDirector.h"
#include "Kismet/GameplayStatics.h"

const float TimeBetweenCameraChanges = 2.0f;
const float SmoothBlendTime = 0.75f;
// Sets default values for this component's properties
UCameraDirector::UCameraDirector()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UCameraDirector::BeginPlay()
{
	Super::BeginPlay();
	TimeToNextCameraChange = TimeBetweenCameraChanges;
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(this, 0);
	PlayerController->SetViewTarget(StartCamera);
	
	// ...
	
}

int i;
// Called every frame
void UCameraDirector::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	TimeToNextCameraChange -= DeltaTime;
	if (TimeToNextCameraChange <= 0.0f) {
		TimeToNextCameraChange += TimeBetweenCameraChanges;
		APlayerController* PlayerController = UGameplayStatics::GetPlayerController(this, 0);
		if (PlayerController) {
			if ((PlayerController->GetViewTarget() == StartCamera)) {
				PlayerController->SetViewTargetWithBlend(Cameras[0],SmoothBlendTime);
				i = 1;
			}
			else if (i<Cameras.Num()) {
				PlayerController->SetViewTargetWithBlend(Cameras[i], SmoothBlendTime);
				i++;
			}
			else {
				PlayerController->SetViewTargetWithBlend(StartCamera,SmoothBlendTime);
			}
		}
	}
	// ...
}

