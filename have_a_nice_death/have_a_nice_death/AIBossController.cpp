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
        isIdlePhase = (rand() % 2 == 0);
        if (isIdlePhase)
            attackInterval = 1.5f;
        else
            attackInterval = 2.0f;
    }
    else
    {
        currentInput = KeyType::MAX;
        attackInterval = 1.5f; // ���� �Ұ� �� Move/Idle ó��
        isIdlePhase = true;
    }
}

int AIBossController::CalcAttackWeight(std::vector<int>& readyAttacks)
{
    LivingObject* AIBossObject = GetOwner();


    float dx = (AIBossObject->GetPos().x - target->GetPos().x) * 0.01;
    float dy = (AIBossObject->GetPos().y - target->GetPos().y) * 0.01;
    float distance = (dx * dx + dy * dy);

    std::vector<std::pair<int, float>> weightedAttacks;
    for (int i : readyAttacks)
    {
        float weight = 1.0f; // �⺻ Ȯ��

        switch (i)
        {
        case 0: case 4: // �ٰŸ�
            if (distance <= 4.0f) weight *= 2.0f;
            break;

        case 1: case 5: // �߰Ÿ�
            if (distance >= 9.0f && distance <= 26.0f) weight *= 2.0f;
            break;

        case 2: case 3: // ���Ÿ�
            if (distance >= 25.0f) weight *= 2.0f;
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
