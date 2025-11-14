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

- **함수포인터**
  <details>
    <summary>애니메이션 콜백</summary>

    - **사용 목적**
      - 종료 & 특정 시점 상태 전이
      - 정확한 시점 HitBox 생성

    <details>
      <summary>상태 전이</summary>
      이동 금지, 속도 조절, 조작불가 등 전이 로직 처리

  ![Image](https://github.com/user-attachments/assets/eb605204-c52d-400d-8228-482d24045144)

  ![Image](https://github.com/user-attachments/assets/32a12642-f748-4a7f-acfe-8ab2cf6c59d7)

    </details>

    <details>
      <summary>HitBox</summary>
      공격 애니메이션 재생 시, 정확한 스프라이트 타이밍에 HitBox 생성 요청

  ![Image](https://github.com/user-attachments/assets/6848f058-e8c6-4bd0-9dde-fd271698f1a7)

    </details>

  </details>
