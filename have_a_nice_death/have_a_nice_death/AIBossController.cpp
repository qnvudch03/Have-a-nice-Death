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

    // ���� ���͹� ����
    if (attackInterval > 0.0f)
    {
        attackInterval -= deltatime;

        // Idle / Move ����
        if (isIdlePhase)
        {
            currentInput = KeyType::MAX; // Idle ���� �Է� ����
        }
        else
        {
            currentInput = KeyType::KeepLeft; // Move ���� ���� �Է�
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
        attackInterval = 1.5f; // ���� �Ұ� �� Move/Idle ó��
        isIdlePhase = true;
    }
}
