#include "pch.h"
#include "AIController.h"
#include "TimeManager.h"
#include "Game.h"
#include "GameScene.h"

#include <random>

AIController::AIController()
{
    target = &(Game::GetInstance()->GetGameScene()->GetStage()->GetPlayer());
}

void AIController::Update(float deltatime)
{
    if (target == nullptr || (*target) == nullptr || (*target)->IsActive == false)
        return;

    pastInput = currentInput;

    LivingObject* Target = (*target);
    Vector ObjPos = owningLivingObject->GetPos();
    Vector targetPos = Target->GetPos();

    
    {
        float distanceX = fabsf(Target->GetPos().x - ObjPos.x);

        if (distanceX < owningLivingObject->GetStat().attack_range)
            state = AI_Attack;

        else if (distanceX < owningLivingObject->GetDetectRange())
            state = AI_Chase;

        else
            state = AI_Patrol;
    }

    if (fabsf(Target->GetPos().y - ObjPos.y) > 50)
        state = AI_Patrol;

    decideInput();

    patrolTimer += deltatime;
    attackTimer += deltatime;

}

void AIController::decideInput()
{
    switch (state)
    {
    case AIController::AI_Patrol:

        if (patrolTimer >= patrolInterval)
        {
            patrolTimer = 0.0f;

            int r = rand() % 3;
            switch (r)
            {
                case 0: currentInput = KeyType::MAX; break;


                case 1:
                {
                    if (pastInput == KeyType::KeepLeft || pastInput == KeyType::Left)
                        currentInput = KeyType::Right;

                    else
                        currentInput = KeyType::KeepRight;

                     break;
                }

                case 2:
                {
                    if (pastInput == KeyType::KeepRight || pastInput == KeyType::Right)
                        currentInput = KeyType::Left;

                    else
                        currentInput = KeyType::KeepLeft;

                    break;

                    //currentInput = KeyType::KeepLeft; break;
                }
            }
        }

        break;

    case AIController::AI_Chase:
        moveDir = (owningLivingObject->GetPos().x - (*target)->GetPos().x >= 0) ? -1 : 1;

        if (moveDir == -1)
        {
            /*if (pastInput != KeyType::KeepLeft)
                currentInput = KeyType::Left;

            else
                currentInput = KeyType::KeepLeft;*/
            currentInput = KeyType::KeepLeft;
        }


        else
        {
            /*if (pastInput != KeyType::KeepRight)
                currentInput = KeyType::Right;

            else
                currentInput = KeyType::KeepRight;*/

            currentInput = KeyType::KeepRight;
        }

        break;
    case AIController::AI_Attack:

        if (attackTimer >= attackInterval)
        {
            LookTarget();

            attackTimer = 0;

            if (attackNum <= 1)
            {
                currentInput = KeyType::AttackKey1;
                break;
            }
                
            else
            {
                std::random_device rd;

                int r = rd() % attackNum;
                switch (r)
                {
                    case 0: currentInput = KeyType::AttackKey1; break;
                    case 1: currentInput = KeyType::AttackKey2; break;
                    case 2: currentInput = KeyType::AttackKey3; break;
                    case 3: currentInput = KeyType::AttackKey4; break;
                    case 4: currentInput = KeyType::AttackKey5; break;
                    case 5: currentInput = KeyType::AttackKey6; break;
                }
            }
            
        }
        break;
    case AIController::AI_Default:
        currentInput = KeyType::MAX;
        break;
    default:
        break;
    }
}

int AIController::LookTarget()
{
    int moveDir = (owningLivingObject->GetPos().x - (*target)->GetPos().x >= 0) ? -1 : 1;

    if (moveDir != 0)
        owningLivingObject->forwordDirection = moveDir;

    owningLivingObject->renderingFlipOrder = (moveDir == -1) ? true : (moveDir == 1) ? false : owningLivingObject->renderingFlipOrder;

    return moveDir;
}
