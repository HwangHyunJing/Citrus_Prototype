// Copyright Epic Games, Inc. All Rights Reserved.


#include "LemonSourGameModeBase.h"

// ���� ������Ʈ
#include "Components/WidgetComponent.h"

// ĳ����
#include "Character/LemonCharacter.h"
// �ܺ� ���� (all actors of class)
#include "Kismet/GameplayStatics.h"

// �̺�Ʈ
#include "Events/Event_CameraLock.h"
#include "Events/Event_SavePoint.h"

// ���� ����
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

	// ĳ���͸� �����մϴ�
	SearchLemonCharacter();

	// ���� ���� �����͸� �����մϴ�
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



void ALemonSourGameModeBase::RespawnCharacter()
{

	// (2-1) ī�޶� ȣ��
	// AEvent_CameraLock* CameraLock = GetCameraEvent();
	if (CameraEvent)
	{
		UE_LOG(LogTemp, Warning, TEXT("Cam Lock called by game mode base"));
		CameraEvent->LockCamera(LemonCharacter);
	}
	else if(Tmp_CameraEvent)
	{
		// ���� ��� �׳� �����ؾ� ��
		Tmp_CameraEvent->ResetCamera(LemonCharacter);
	}
	
	// (2-2) ��ġ ����
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
