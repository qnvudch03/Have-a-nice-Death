#pragma once
#include "Controller.h"
#include "Game.h"
#include "GameScene.h"

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

    void InitBossController(int num_Attack, std::vector<float> attackCollDowns)
    {
        target = &Game::GetInstance()->GetGameScene()->GetStage()->GetPlayer();

        numAttacks = num_Attack;
        attackCooldowns = attackCollDowns;

        attackTimers.resize(numAttacks, 0.0f);
    }

    LivingObject* GetTarget()
    {
        if (target != nullptr)
            return *target;
    }

    virtual void Update(float deltatime) override;

    void StartAttackInterval();

    int LookTarget();

private:
    int numAttacks = 0;
    bool isIdlePhase = false;

    LivingObject** target = nullptr;

    int CalcAttackWeight(std::vector<int>& readyAttacks);
    void DecideAttack();

    float attackInterval = 1.7f;
    float IdleTime = 1.0;
    float MoveTime = 1.0;

    std::vector<float> attackCooldowns;
    std::vector<float> attackTimers;

    bool targetDead = false;
};

