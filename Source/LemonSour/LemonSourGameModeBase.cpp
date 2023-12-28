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

	// 디폴트 리스폰 지점입니다: 시작 지점 > 캐릭터 > 0 벡터 순서
	
}

void ALemonSourGameModeBase::SetCameraEvent(AEvent_CameraLock* Actor)
{
	Tmp_CameraEvent = Actor;
}

void ALemonSourGameModeBase::SetSaveEvent(AEvent_SavePoint* Actor)
{
	SaveEvent = Actor;
	// 카메라 모드 엑터도 저장합니다
	CameraEvent = Tmp_CameraEvent;
		
}

AEvent_CameraLock* ALemonSourGameModeBase::GetCameraEvent()
{
	return CameraEvent;
}

AEvent_SavePoint* ALemonSourGameModeBase::GetSaveEvent()
{
	return SaveEvent;
}



void ALemonSourGameModeBase::RespawnCharacter(ALemonCharacter* LemonCharacter)
{
	
	if (SaveEvent)
	{
		// (2-2) 카메라 호출
		AEvent_CameraLock* CameraLock = GetCameraEvent();
		if (CameraLock)
		{
			UE_LOG(LogTemp, Warning, TEXT("Cam Lock called by game mode base"));
			CameraLock->LockCamera(LemonCharacter);
		}

		// (2-1) 위치 조정
		FVector RespawnLocation = FVector(0, 0, 0);
		RespawnLocation = SaveEvent->GetRespawnLocation();
		LemonCharacter->SetActorLocation(RespawnLocation);

		
	}
		

}
