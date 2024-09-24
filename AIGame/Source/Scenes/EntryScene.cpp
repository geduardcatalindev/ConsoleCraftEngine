#include "EntryScene.h"
#include "../GameObjects/PlayerShip.h"
#include "../GameObjects/Enemy.h"
#include "../GameObjects/Brick.h"

EntryScene::
    ~EntryScene()
{
}
void EntryScene::Init()
{
    Scene::Init();
}

void EntryScene::Start()
{
    Scene::Start();
    playerShip = new PlayerShip(*this);
    enemy = new Enemy(*this);
    AddGameObject(playerShip, Vector2(15, 5));
    AddGameObject(enemy, Vector2(7, 8));
    AddGameObject(new Brick(*this), Vector2(11, 5));
    AddGameObject(new Brick(*this), Vector2(23, 5));
    AddGameObject(new Brick(*this), Vector2(11, 10));
    AddGameObject(new Brick(*this), Vector2(23, 15));
    AddGameObject(new Brick(*this), Vector2(5, 15));
    
    m_Linedrawer = new LineDrawer(*this);

    m_Linedrawer->CreateLineParticles(100, 1);
}

void EntryScene::Update(float deltaTime)
{
    Scene::Update(deltaTime);
    m_Linedrawer->ResetDrawingParticleIndex();
    PathNode start(enemy->transform.GetCenterPosition().X, enemy->transform.GetCenterPosition().Y);
    PathNode goal(playerShip->transform.GetCenterPosition().X , playerShip->transform.GetCenterPosition().Y);
    std::vector<PathNode> path = pathfinder->FindPath(start, goal);
    if (!path.empty())
    {

        for (int i = 0; i < path.size() - 1; i++)
        {
            Vector2 posStart = Vector2(path[i].x, path[i].y);
            Vector2 posEnd = Vector2(path[i + 1].x, path[i + 1].y);

            m_Linedrawer->DrawLine(posStart, posEnd);
        }
    }
    std::cout<< playerShip->transform.GetCenterPosition();
}
