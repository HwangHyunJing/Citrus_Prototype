// Copyright Epic Games, Inc. All Rights Reserved.


#include "LemonSourGameModeBase.h"

// 위젯 컴포넌트
#include "Components/WidgetComponent.h"

// 캐릭터
#include "Character/LemonCharacter.h"
// 외부 참조 (all actors of class)
#include "Kismet/GameplayStatics.h"

// 이벤트
#include "Events/Event_CameraLock.h"
#include "Events/Event_SavePoint.h"

// 시작 지점
#include "GameFramework/PlayerStart.h"


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

	// 캐릭터를 참조합니다
	SearchLemonCharacter();

	// 시작 지점 데이터를 저장합니다
	TArray<AActor*> Arr;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), APlayerStart::StaticClass(), Arr);
	if (!Arr.IsEmpty() && Arr[0])
	{
		StartPoint = Cast<APlayerStart>(Arr[0]);
	}
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



void ALemonSourGameModeBase::RespawnCharacter()
{

	// (2-1) 카메라 호출
	// AEvent_CameraLock* CameraLock = GetCameraEvent();
	if (CameraEvent)
	{
		UE_LOG(LogTemp, Warning, TEXT("Cam Lock called by game mode base"));
		CameraEvent->LockCamera(LemonCharacter);
	}
	else if(Tmp_CameraEvent)
	{
		// 없을 경우 그냥 리셋해야 함
		Tmp_CameraEvent->ResetCamera(LemonCharacter);
	}
	
	// (2-2) 위치 조정
	FVector RespawnLocation = FVector(0, 0, 0);
	if (SaveEvent)
	{		
		RespawnLocation = SaveEvent->GetRespawnLocation();
	}
	else if(StartPoint)
	{
		RespawnLocation = StartPoint->GetActorLocation();
	}

	LemonCharacter->SetActorLocation(RespawnLocation);
}

void ALemonSourGameModeBase::InvokeEvents(EEventCode EventCode)
{
	UE_LOG(LogTemp, Error, TEXT("Invoke: Gmode Base called"));
}

ALemonCharacter* ALemonSourGameModeBase::SearchLemonCharacter()
{
	if(GetWorld())
		LemonCharacter = Cast<ALemonCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

	return LemonCharacter;
}
