# Have-a-nice-Death(모작)
![게임 로비씬](https://github.com/user-attachments/assets/dd0410bb-55cc-41f3-8b8c-85195fc11c7a)

---

# 프로젝트 소개
WinAPI로 제작한 1개월 규모의 모작 프로젝트  
게임 루프, 이벤트 처리, 리소스 관리 기능을 학습한 내용을 활용해 직접 구현

## 기술 스택
- **언어**: C++  
- **플랫폼**: WinApi
- **라이브러리/툴**: Visual Studio, Direct2D

---

# 기술 경험

- **디자인 패턴**
  <details>
    <summary>Singleton</summary>
      <ul>
        <p>시스템 규모의 객체들은 SingleTone 베이스로 구현해, 인게임에서 전역적으로 활용</p>
        <img src="https://github.com/user-attachments/assets/e8bc9409-e7b5-47dc-b2a9-7060c6c9fad3">
      </ul>
  </details>
  <details>
    <summary>Object Pool</summary>
      <ul>
        <p>짧은시간에 많은 입력이 들어오는 액션게임이기에, 인게임 중 동적 메모리 할당을 최소화 하기 위해 사용</p>
        <p><strong>1. 초기화 시 미리 풀에 객체 생성</strong></p>
        <pre><code>void HitBoxManager::Init()
          {
              for (int i = 0; i &lt; 20; i++)
                  hitBoxPull.push(new HitBox());
          }</code></pre>
    
        <p><strong>2. 필요할 때 풀에서 객체를 꺼내 재사용</strong></p>
        <pre><code>HitBox* HitBoxManager::CallHitBox()
          {
              if (hitBoxPull.empty()) return nullptr;
              HitBox* hitBox = hitBoxPull.front();
              hitBoxPull.pop();
              return hitBox;
          }</code></pre>
    
        <p><strong>3. 사용 후 다시 풀에 반환</strong></p>
        <pre><code>void HitBoxManager::ReturnHitBox(HitBox* hitbox)
          {
              if (!hitbox) return;
              hitBoxPull.push(hitbox);
              spanwedHitBoxVec.erase(hitbox);
          }</code></pre>
      </ul>
  </details>

<details>
  <summary>리소스</summary>
  <ul>
    <li>SingleTon 패턴의 SpriteManager에서 Map에 매핑되어있는 데이터를 포인터로 접근</li>
  </ul>
</details>

<details>
  <summary>입력</summary>
  <ul>
    <li>CurrentInput / PastInput Key 으로 입력값을 저장</li>

    <details>
      <summary>PlayerController</summary>
      <ul>
        <li>WinAPI 메시지 루프 기반 InputManager의 KeyMap 갱신</li>
      </ul>
    </details>

    <details>
      <summary>AIController</summary>
      <ul>
        <li>FSM 기반. Player와의 거리로 CurrentInput 갱신</li>
      </ul>
    </details>
  </ul>
</details>

<details>
  <summary>Object</summary>
  <ul>
    <li>인게임 내부에 존재하는 객체들</li>

    <details>
      <summary>LiginObject</summary>
      <ul>
        <li>상태를 지니고 있는 Playable Character</li>
        <li>FSM패턴으로 컨트롤러의 입력값을 받아 상태를 전이</li>
      </ul>
    </details>

    <details>
      <summary>StaticObject</summary>
      <ul>
        <li>여기에 StaticObject 설명 추가</li>
      </ul>
    </details>

    <details>
      <summary>InteractableObject</summary>
      <ul>
        <li>여기에 InteractableObject 설명 추가</li>
      </ul>
    </details>

    <li>콜백 패턴으로, 애니메이션 종료 / 원하는 스프라이트 시점에 원하는 로직 수행</li>
  </ul>
</details>

<details>
  <summary>애니메이션</summary>
  <ul>
    <li>프레임 기반 애니메이션 재생 시스템</li>
    <li>콜백 패턴으로, 애니메이션 종료 / 원하는 스프라이트 시점에 원하는 로직 수행</li>
  </ul>
</details>
