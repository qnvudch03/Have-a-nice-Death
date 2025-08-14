#include "pch.h"
#include "AIController.h"
#include "TimeManager.h"

#include <random>

void AIController::Update()
{
    //float delta = TimeManager::GetDeltaTime(); // 프레임 보정

    //// 쿨타임 중이면 입력 없음
    //if (isInCoolTime)
    //{
    //    coolTimer += delta;
    //    currentInput = KeyType::MAX;

    //    if (coolTimer >= coolDuration)
    //    {
    //        coolTimer = 0.0f;
    //        isInCoolTime = false;
    //    }
    //    return;
    //}

    //// 현재 입력 유지 중이면
    //if (inputTimer < inputDuration)
    //{
    //    inputTimer += delta;
    //    return; // 기존 입력 유지
    //}

    //// 새로운 랜덤 입력 생성
    //std::random_device rd;
    //AIInputList randomInput = static_cast<AIInputList>(rd() % (AIInputList::AI_InputMax));

    //switch (randomInput)
    //{
    //case AIController::AI_InputLeft:
    //    currentInput = KeyType::Move;
    //    owningLivingObject->forwordDirection = -1;
    //    owningLivingObject->renderingFlipOrder = true;
    //    break;
    //case AIController::AI_InputRight:
    //    currentInput = KeyType::Move;
    //    owningLivingObject->forwordDirection = 1;
    //    owningLivingObject->renderingFlipOrder = false;
    //    break;
    //case AIController::AI_InputJump:
    //    currentInput = KeyType::SpaceBar;
    //    break;
    //case AIController::AI_InputAttack:
    //    currentInput = KeyType::Z;
    //    break;
    //default:
    //    currentInput = KeyType::MAX;
    //    break;
    //}

    //// 입력 유지 타이머 리셋
    //inputTimer = 0.0f;

    //// 3초 유지가 끝나면 쿨타임 시작
    //if (inputDuration > 0)
    //{
    //    isInCoolTime = true;
    //    coolTimer = 0.0f;
    //}

    if (stack_counter == 0)
    {
        std::random_device rd;
        //std::srand(std::time(nullptr));

        AIInputList randomInput = static_cast<AIInputList>(rd() % (AIInputList::AI_InputMax));

        //입력 그거에 따라서 
        switch (randomInput)
        {
        case AIController::AI_InputLeft:

            if (pastInput == KeyType::Left || pastInput == KeyType::KeepLeft)
                currentInput = KeyType::KeepLeft;

            else
                currentInput = KeyType::Left;

            
            /*owningLivingObject->forwordDirection = -1;
            owningLivingObject->renderingFlipOrder = (owningLivingObject->forwordDirection == -1) ?
                true : (owningLivingObject->forwordDirection == 1) ? false : owningLivingObject->renderingFlipOrder;*/
            break;

        case AIController::AI_InputRight:
            
            if (pastInput == KeyType::Right || pastInput == KeyType::KeepRight)
                currentInput = KeyType::KeepRight;

            else
                currentInput = KeyType::Right;
            break;

        case AIController::AI_InputJump:
            currentInput = KeyType::SpaceBar;
            break;

        case AIController::AI_InputAttack:
            currentInput = KeyType::Z;
            break;

        case AIController::AI_InputDash:
            currentInput = KeyType::Shift;
            break;

        case AIController::AI_InputMax:
            currentInput = KeyType::MAX;
            break;
        default:
            break;
        }

        stack_counter = input_Interver;
    }

    pastInput = currentInput;

    stack_counter--;
}
