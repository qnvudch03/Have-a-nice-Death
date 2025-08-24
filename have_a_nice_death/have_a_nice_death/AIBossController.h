#pragma once
#include "Controller.h"

class AIBossController : public Controller
{
public:
    // ������: ���� ��� ������ �� ���� ��Ÿ�� �迭�� ����
    /*AIBossController(int attackCount, std::vector<float> cooldowns)
        : numAttacks(attackCount)
    {
        attackCooldowns = cooldowns;
        attackTimers.resize(numAttacks, 0.0f);
    }*/

    void SetBossAttackCollInfo(int num_Attack, std::vector<float> attackCollDowns)
    {
        numAttacks = num_Attack;
        attackCooldowns = attackCollDowns;

        attackTimers.resize(numAttacks, 0.0f);
    }

    virtual void Update(float deltatime) override;

private:
    int numAttacks = 0;
    bool isIdlePhase = false;

    void DecideAttack();

    float attackInterval = 5.0f;
    std::vector<float> attackCooldowns;
    std::vector<float> attackTimers;
};

