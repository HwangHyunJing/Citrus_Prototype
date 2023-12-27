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
}

void ALemonSourGameModeBase::SetCameraActor(AEvent_CameraLock* Actor)
{
	Tmp_CameraActor = Actor;
}

void ALemonSourGameModeBase::SetSaveActor(AEvent_SavePoint* Actor)
{
	SaveActor = Actor;
	// ī�޶� ��� ���͵� �����մϴ�
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
	// (2-1) ��ġ ����
	FVector RespawnLocation = FVector(0, 0, 0);
	if (SaveActor)
		RespawnLocation = SaveActor->GetRespawnLocation();

	LemonCharacter->SetActorLocation(RespawnLocation);
	
	// (2-2) ī�޶� �� ȣ��
	if (CameraActor)
	{
		UE_LOG(LogTemp, Warning, TEXT("Cam Lock called by game mode base"));
		CameraActor->LockCamera(LemonCharacter);
	}
		
}
