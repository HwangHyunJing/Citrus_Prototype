// Copyright Epic Games, Inc. All Rights Reserved.


#include "LemonSourGameModeBase.h"

// ���� ������Ʈ
#include "Components/WidgetComponent.h"

// ĳ����
#include "Character/LemonCharacter.h"

// �̺�Ʈ
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

	// ����Ʈ ������ �����Դϴ�: ���� ���� > ĳ���� > 0 ���� ����
	
}

void ALemonSourGameModeBase::SetCameraEvent(AEvent_CameraLock* Actor)
{
	Tmp_CameraEvent = Actor;
}

void ALemonSourGameModeBase::SetSaveEvent(AEvent_SavePoint* Actor)
{
	SaveEvent = Actor;
	// ī�޶� ��� ���͵� �����մϴ�
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
		// (2-2) ī�޶� ȣ��
		AEvent_CameraLock* CameraLock = GetCameraEvent();
		if (CameraLock)
		{
			UE_LOG(LogTemp, Warning, TEXT("Cam Lock called by game mode base"));
			CameraLock->LockCamera(LemonCharacter);
		}

		// (2-1) ��ġ ����
		FVector RespawnLocation = FVector(0, 0, 0);
		RespawnLocation = SaveEvent->GetRespawnLocation();
		LemonCharacter->SetActorLocation(RespawnLocation);

		
	}
		

}
