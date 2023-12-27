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
	// 생성자
	ALemonSourGameModeBase();

	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = "ClassTypes")
	TSubclassOf<UUserWidget> WidgetClass;

	UPROPERTY(VisibleInstanceOnly, Category = "Runtime")
	UGameModeWidget* GameModeWidget;

public:
	// 리스폰을 위한 값을 설정합니다
	void SetCameraActor(AEvent_CameraLock* Actor);
	void SetSaveActor(AEvent_SavePoint* Actor);
	// 반대로 외부에서 참조합니다
	AEvent_CameraLock* GetCameraActor();
	AEvent_SavePoint* GetSaveActor();

	void RespawnCharacter(ALemonCharacter* LemonCharacter);

private:
	// 리스폰을 위한 엑터 데이터입니다
	AEvent_CameraLock* Tmp_CameraActor;
	AEvent_CameraLock* CameraActor;
	AEvent_SavePoint* SaveActor;
};
