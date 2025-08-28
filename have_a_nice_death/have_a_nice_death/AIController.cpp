#include "pch.h"
#include "AIController.h"
#include "TimeManager.h"
#include "Game.h"
#include "GameScene.h"
#include "Sensor.h"

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
        float combatEnterRange = GetCombatEnterRange();

        if (distanceX < combatEnterRange)
        {
            if (attackTimer < attackInterval)
                state = AI_Patrol;
            else
                state = AI_Attack;
        }
            

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

        if (!owningLivingObject->cornerSensor->IsActive() && owningLivingObject->groundSensor->IsActive())
        {

            owningLivingObject->velocity.x = 0;

            if (currentInput == KeyType::Left)      currentInput = KeyType::Right;
            else if (currentInput == KeyType::KeepLeft)  currentInput = KeyType::KeepRight;
            else if (currentInput == KeyType::Right)     currentInput = KeyType::Left;
            else if (currentInput == KeyType::KeepRight) currentInput = KeyType::KeepLeft;
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

            float distX = fabsf((*target)->GetPos().x - owningLivingObject->GetPos().x);
            currentInput = ChooseAttackByDistance(distX);

            /*if (attackNum <= 1)
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
            }*/
            
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

float AIController::GetCombatEnterRange() const
{
    const auto& prof = owningLivingObject->AttackProfile;
    if (prof.empty()) {
        // 하위호환: 예전 방식 유지 (프로필이 세팅 안 된 몬스터)
        return owningLivingObject->GetStat().attack_range;
    }
    float mx = 0.f;
    for (const auto& s : prof)
    {
        if (s.maxDist > mx)
            mx = s.maxDist;
    }

    return mx;
}

KeyType AIController::ChooseAttackByDistance(float distX)
{
    const auto& prof = owningLivingObject->AttackProfile;
    std::vector<const AttackSlot*> candidates;

    for (const auto& s : prof) {
        if (distX >= s.minDist && distX <= s.maxDist) {
            // 쿨타임 체크가 필요하면 여기서 조건 추가
            candidates.push_back(&s);
        }
    }

    //걸릴 일 거의 없음
    if (candidates.empty()) {
        // 사거리 안 맞으면 접근/리포지션(추격) 입력으로 대체
        return (moveDir == -1) ? KeyType::KeepLeft : KeyType::KeepRight;
    }

    // 가중치 랜덤 선택 (균등이면 간단히 랜덤 인덱스)
    /*int sumW = 0.0f;
    for (auto* c : candidates) sumW += c->weight;*/

    std::random_device rd;

    int randomIndex = rd() % candidates.size();
    int choosenAttack = candidates[randomIndex]->atkNum;
    switch (choosenAttack)
    {
    case 1:     return KeyType::AttackKey1;
    case 2:     return KeyType::AttackKey2;
    case 3:     return KeyType::AttackKey3;
    case 4:     return KeyType::AttackKey4;
    case 5:     return KeyType::AttackKey5;
    case 6:     return KeyType::AttackKey6;
    default:
        break;
    }

    return KeyType::MAX;
}
