// Copyright Epic Games, Inc. All Rights Reserved.


#include "LemonSourGameModeBase.h"

// À§Á¬ ÄÄÆ÷³ÍÆ®
#include "Components/WidgetComponent.h"

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
