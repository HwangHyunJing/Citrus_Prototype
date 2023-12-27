#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "HUD/GameModeWidget.h"
#include "LemonSourGameModeBase.generated.h"

class UWidgetComponent;
class UGameModeWidget;

class AEvent_CameraLock;
class AEvent_SavePoint;

class ALemonCharacter;

UCLASS()
class LEMONSOUR_API ALemonSourGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	// ������
	ALemonSourGameModeBase();

	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = "ClassTypes")
	TSubclassOf<UUserWidget> WidgetClass;

	UPROPERTY(VisibleInstanceOnly, Category = "Runtime")
	UGameModeWidget* GameModeWidget;

public:
	// �������� ���� ���� �����մϴ�
	void SetCameraActor(AEvent_CameraLock* Actor);
	void SetSaveActor(AEvent_SavePoint* Actor);
	// �ݴ�� �ܺο��� �����մϴ�
	AEvent_CameraLock* GetCameraActor();
	AEvent_SavePoint* GetSaveActor();

	void RespawnCharacter(ALemonCharacter* LemonCharacter);

private:
	// �������� ���� ���� �������Դϴ�
	AEvent_CameraLock* Tmp_CameraActor;
	AEvent_CameraLock* CameraActor;
	AEvent_SavePoint* SaveActor;
};
