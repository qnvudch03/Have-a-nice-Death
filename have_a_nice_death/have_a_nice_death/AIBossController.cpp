#include "pch.h"
#include "AIBossController.h"

void AIBossController::Update(float deltatime)
{

    if ((*target)->IsActive == false && targetDead == false)
    {
        targetDead = true;
        return;
    }

    if (targetDead)
        return;

    pastInput = currentInput;

    for (int i = 0; i < numAttacks; i++)
    {
        if (attackTimers[i] > 0.0f)
        {
            attackTimers[i] = ( (attackTimers[i] - deltatime) <= 0) ? 0 : attackTimers[i] - deltatime;
        }
    }

    // 공격 인터벌 갱신
    if (attackInterval > 0.0f)
    {
        attackInterval -= deltatime;

        // Idle / Move 구분
        if (isIdlePhase)
        {
            currentInput = KeyType::MAX; // Idle 동안 입력 없음
        }
        else
        {
            //currentInput = KeyType::KeepLeft; // Move 동안 지속 입력
        }

        return;
    }

    DecideAttack();

}

void AIBossController::StartAttackInterval()
{
    attackInterval = 1.5f;

    if (rand() % 100 < 60)
    {
        isIdlePhase = true;
        currentInput = KeyType::MAX;
    }
    else
    {
        isIdlePhase = false;

        int moveDir = LookTarget();

        if(moveDir == 1)
            currentInput = KeyType::KeepRight;

        else if (moveDir == -1)
            currentInput = KeyType::KeepLeft;
    }
}

void AIBossController::DecideAttack()
{
    std::vector<int> readyAttacks;
    for (int i = 0; i < numAttacks; i++)
    {
        if (attackTimers[i] <= 0.0f)
            readyAttacks.push_back(i);
    }

    if (!readyAttacks.empty())
    {

        LookTarget();

        int sellectActionIndex = CalcAttackWeight(readyAttacks);

        switch (sellectActionIndex)
        {
        case 0:
            currentInput = KeyType::AttackKey1;         break;
        case 1:
            currentInput = KeyType::AttackKey2;         break;
        case 2:
            currentInput = KeyType::AttackKey3;         break;
        case 3:
            currentInput = KeyType::AttackKey4;         break;
        case 4:
            currentInput = KeyType::AttackKey5;         break;
        case 5:
            currentInput = KeyType::AttackKey6;         break;
        default:
            currentInput = KeyType::MAX;                break;
        }

        //currentInput = static_cast<KeyType>(idx);
        attackTimers[sellectActionIndex] = attackCooldowns[sellectActionIndex];

        
        //attackInterval = attackTimers[idx];
        /*isIdlePhase = (rand() % 2 == 0);
        if (isIdlePhase)
            attackInterval = 1.5f;
        else
            attackInterval = 2.0f;*/
    }
    else
    {
        currentInput = KeyType::MAX;
        attackInterval = 0.3f; // 공격 불가 시 Move/Idle 처리
        isIdlePhase = false;
    }
}

int AIBossController::LookTarget()
{
    int moveDir = (owningLivingObject->GetPos().x - (*target)->GetPos().x >= 0) ? -1 : 1;

    if (moveDir != 0)
        owningLivingObject->forwordDirection = moveDir;

    owningLivingObject->renderingFlipOrder = (moveDir == -1) ? true : (moveDir == 1) ? false : owningLivingObject->renderingFlipOrder;

    return moveDir;
}

int AIBossController::CalcAttackWeight(std::vector<int>& readyAttacks)
{
    LivingObject* AIBossObject = GetOwner();


    float dx = (AIBossObject->GetPos().x - (*target)->GetPos().x) * 0.01;
    float dy = (AIBossObject->GetPos().y - (*target)->GetPos().y) * 0.01;
    float distance = (dx * dx + dy * dy);

    std::vector<std::pair<int, float>> weightedAttacks;
    for (int i : readyAttacks)
    {
        float weight = 1.0f; // 기본 확률

        switch (i)
        {
        case 0: case 4: // 근거리
            if (distance < 12.0f) weight *= 2.0f;
            break;

        case 5: case 2: // 중거리
            if (distance >= 12.0f && distance < 40.0f) weight *= 8.0f;
            break;

        case 3: case 1: // 원거리
            if (distance >= 40.0f) weight *= 15.0f;
            break;
        }

        weightedAttacks.push_back({ i, weight });
    }


    float totalWeight = 0.0f;
    for (auto& w : weightedAttacks) totalWeight += w.second;

    float r = (float)rand() / RAND_MAX * totalWeight;

    int idx = weightedAttacks.back().first;
    for (auto& w : weightedAttacks)
    {
        if (r < w.second)
        {
            idx = w.first;
            break;
        }
        r -= w.second;
    }

    return idx;

}
