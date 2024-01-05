#include "Player.h"
#include "Weapons/PlasmaGun.h"
#include "../Components/PlayerUpgradeComponent.h"

#include <memory>
#include <functional>

#include "Core/Scene.h"
#include "Core/Input.h"
#include "Core/Component/PlayerController.h"
#include "Core/EventDispatcher.h"
void Player::Init()
{
    debugUIData.position = Vector2(0, 29);
    debugUIData.text = "Debug Text";
    debugUIDataPtr = std::make_shared<UIData>(debugUIData);
    GetCurrentScene().uiHandler->AddString(debugUIDataPtr);

    std::function<void(Event&)> OnRecievedEvent = std::bind(&Player::RecievedEvent, this, std::placeholders::_1);
    EventDispatcher::AddListener(OnRecievedEvent);
    
    
    PlayerController* playerController = new PlayerController(*this, 0);
    AddComponent(playerController);
    playerUpgradeComponent = new PlayerUpgradeComponent(*this);
    AddComponent(playerUpgradeComponent);
    
    sprite = {{0, 1, 0},
              {1, 1, 1},
              {1, 1, 1},
              {1, 0, 1}};
    Vector2 startPosition(10, 10);

    InitializeWeapon(startPosition);

  

    auto inputEvent = std::bind(&Player::OnKeyPressed, this, std::placeholders::_1);
    Input::AddListener(inputEvent);
}
void Player::OnKeyPressed(int input)
{
    if (input == SPACEBAR)
    {
        Vector2 StartPoint = transform.Position;
        auto nearestEnemy = GetCurrentScene().FindNearestGameObject(transform, "Enemy");
        if (nearestEnemy != nullptr)
        {

            Vector2 TargetPoint = nearestEnemy->transform.Position;

            Vector2 FireDirection = TargetPoint - StartPoint;
            FireDirection.Normalize();

            weapon->Fire(FireDirection);
        }
    }
}
void Player::RecievedEvent(Event& e)
{
    switch (e.GetEventType())
    {
    case EventType::OnEnemyKilled:
        playerUpgradeComponent->AddExperience(1);

        break;
    }
}
void Player::InitializeWeapon(Vector2 &startPosition)
{
    weapon = new PlasmaGun(GetCurrentScene());
    GetCurrentScene().AddGameObject(weapon), startPosition;
    weapon->transform.SetParent(transform);
    weapon->transform.Position = startPosition;
}
