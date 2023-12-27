// Copyright Epic Games, Inc. All Rights Reserved.


#include "LemonSourGameModeBase.h"

// 위젯 컴포넌트
#include "Components/WidgetComponent.h"

// 캐릭터
#include "Character/LemonCharacter.h"

// 이벤트
#include "Events/Event_CameraLock.h"
#include "Events/Event_SavePoint.h"

ALemonSourGameModeBase::ALemonSourGameModeBase()
{

}

void ALemonSourGameModeBase::BeginPlay()
{
	// UE_LOG(LogTemp, Warning, TEXT("begin play called!"));

	if (IsValid(WidgetClass))
	{
		GameModeWidget = Cast<UGameModeWidget>(CreateWidget(GetWorld(), WidgetClass));
		// UE_LOG(LogTemp, Warning, TEXT("casted!"));

		if (GameModeWidget != nullptr)
		{
			GameModeWidget->AddToViewport();
			// UE_LOG(LogTemp, Warning, TEXT("added!"));
		}
	}
}

void ALemonSourGameModeBase::SetCameraActor(AEvent_CameraLock* Actor)
{
	Tmp_CameraActor = Actor;
}

void ALemonSourGameModeBase::SetSaveActor(AEvent_SavePoint* Actor)
{
	SaveActor = Actor;
	// 카메라 모드 엑터도 저장합니다
	CameraActor = Tmp_CameraActor;
}

AEvent_CameraLock* ALemonSourGameModeBase::GetCameraActor()
{
	return CameraActor;
}

AEvent_SavePoint* ALemonSourGameModeBase::GetSaveActor()
{
	return SaveActor;
}

void ALemonSourGameModeBase::RespawnCharacter(ALemonCharacter* LemonCharacter)
{
	// (2-1) 위치 조정
	FVector RespawnLocation = FVector(0, 0, 0);
	if (SaveActor)
		RespawnLocation = SaveActor->GetRespawnLocation();

	LemonCharacter->SetActorLocation(RespawnLocation);
	
	// (2-2) 카메라 락 호출
	if (CameraActor)
	{
		UE_LOG(LogTemp, Warning, TEXT("Cam Lock called by game mode base"));
		CameraActor->LockCamera(LemonCharacter);
	}
		
}
