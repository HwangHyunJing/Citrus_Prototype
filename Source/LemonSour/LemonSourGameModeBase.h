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
class APlayerStart;

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

	// �������� ���� ���� �������Դϴ�
	AEvent_CameraLock* Tmp_CameraEvent;
	// 231228; �ڲ� call ref�Ǽ� �׳� save point �̺�Ʈ�� �Űܹ��Ƚ��ϴ�
	AEvent_CameraLock* CameraEvent;
	AEvent_SavePoint* SaveEvent;

public:
	// �������� ���� ���� �����մϴ�
	void SetCameraEvent(AEvent_CameraLock* Actor);
	void SetSaveEvent(AEvent_SavePoint* Actor);
	// �ݴ�� �ܺο��� �����մϴ�
	AEvent_CameraLock* GetCameraEvent();
	AEvent_SavePoint* GetSaveEvent();
	// [TEST] 231228; call by ref ���� ������... �ӽ÷� ����
	// void FORCE_CopyCameraActor(AEvent_CameraLock* Actor);

	void RespawnCharacter();

protected:
	ALemonCharacter* LemonCharacter;
	APlayerStart* StartPoint;

	// ���� null ���� ������
	ALemonCharacter* SearchLemonCharacter();


private:
	FVector DefaultRespawnPoint;
};
