#include "pch.h"
#include "AIBossController.h"

void AIBossController::Update(float deltatime)
{
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
            currentInput = KeyType::KeepLeft; // Move 동안 지속 입력
        }

        return;
    }

    DecideAttack();

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
        int idx = readyAttacks[rand() % readyAttacks.size()];

        switch (idx)
        {
        case 1:
            currentInput = KeyType::AttackKey1;         break;
        case 2:
            currentInput = KeyType::AttackKey2;         break;
        case 3:
            currentInput = KeyType::AttackKey3;         break;
        case 4:
            currentInput = KeyType::AttackKey4;         break;
        case 5:
            currentInput = KeyType::AttackKey5;         break;
        case 6:
            currentInput = KeyType::AttackKey6;         break;
        default:
            currentInput = KeyType::MAX;                break;
        }

        //currentInput = static_cast<KeyType>(idx);
        attackTimers[idx] = attackCooldowns[idx];

        
        attackInterval = attackTimers[idx];
        isIdlePhase = (rand() % 2 == 0);
        if (isIdlePhase)
            attackInterval = 2.0f;
        else
            attackInterval = 1.5f;
    }
    else
    {
        currentInput = KeyType::MAX;
        attackInterval = 1.5f; // 공격 불가 시 Move/Idle 처리
        isIdlePhase = true;
    }
}
