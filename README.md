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
        <li>HitBox</li>
          <img src="https://github.com/user-attachments/assets/823690c8-aac5-4d1f-a1f9-4ad02955d9ac">
        <li>Effect</li>
          <img width="400" height="290" alt="Image" src="https://github.com/user-attachments/assets/1c6ef72d-b073-4f55-b95a-b1e80958f976" />
      </ul>
  </details>

- **콜백**
  <details>
    <summary>애니메이터 콜백</summary>

    - **사용처**
      - <details>
          <summary>종료 & 특정 시점 FSM 로직 처리</summary>
              상태 전이간, 우선순위가 낮은 입력 무시 & 속도 제어
        
          ![Image](https://github.com/user-attachments/assets/eb605204-c52d-400d-8228-482d24045144)
        
          ![Image](https://github.com/user-attachments/assets/32a12642-f748-4a7f-acfe-8ab2cf6c59d7)
 
          ![Image](https://github.com/user-attachments/assets/dad2af25-330a-4863-ac03-7b6a34c0352f)
        </details>
    
      - <details>
          <summary>공격 애니메이션 중, 정확한 스프라이트 타이밍에 HitBox 생성 요청</summary>
        
          ![Image](https://github.com/user-attachments/assets/6848f058-e8c6-4bd0-9dde-fd271698f1a7)
    </details>
  </details>

- **객체지향**
  <details>
    <summary>씬 오브젝트 설계</summary>
      게임 내 씬에 보여지는 모든 객체를 기본 클래스인 `Object`로 정의하고 역활(Static, Interactable, Living)에 따라 확장 구현.<br>
      게임의 업데이트, 렌더링시, 삭제&추가 베이스 클래스 'Object'로 일괄 관리

    <img width="717" height="487" alt="Image" src="https://github.com/user-attachments/assets/5cdd0c88-a3c5-44c5-94d8-426ce9861e05" />
  </details>

  <details>
    <summary>씬 설계</summary>
      인게임에서 보여지는 모든 씬을 기본 클래스인 'Scene'으로 정의하고 역활(Lobby, Game, Edit)에 따라 확장 구현.<br>
      기본 클래스 Scene을 이용한 유연한 씬 전환, 맞춤 Update

    <img width="1047" height="747" alt="Image" src="https://github.com/user-attachments/assets/2f0f6f3b-a66d-416d-b5da-d0c8c4d66b83" />
  </details>

# 흐름
  - 초기화
    
    <img width="1083" height="382" alt="Image" src="https://github.com/user-attachments/assets/7f9ed4f9-455d-4060-8a99-57d42998c05c" />
  - 업데이트 & 렌더
    
    <img width="874" height="589" alt="Image" src="https://github.com/user-attachments/assets/25e28711-69df-43ec-b0c8-4170405ae05f" />

# 작업일지
  -https://blog.naver.com/qnvudch03/223954253559
