#pragma once
#include "Controller.h"

class AIBossController : public Controller
{
public:
    // 생성자: 공격 모션 개수와 각 공격 쿨타임 배열을 받음
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

