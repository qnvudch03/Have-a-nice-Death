# Have-a-nice-Death
WinApi 모작 🎮

---

## 📌 프로젝트 소개
`Have-a-nice-Death`는 **WinAPI 기반**으로 구현된 게임 프로젝트로,  
게임 루프, 렌더링, 이벤트 처리, 리소스 관리 등을 직접 설계하며 제작한 모작입니다.  

---

## 🛠️ 기술 스택
- **언어**: C++  
- **플랫폼**: WinApi
- **라이브러리/툴**: Visual Studio, Direct2D

---

## 주요 시스템

<details>
<summary>🖼 리소스</summary>
<ul>
  <li>SingleTon 패턴의 SpriteManager에서 Map에 매핑되어있는 데이터를 포인터로 접근</li>
</ul>
</details>

<details>
<summary>🎮 입력</summary>
<ul>
  <li>CurrentInput / PastInput Key 으로 입력값을 저장</li>
 <summary>PlayerController</summary>
  
<ul>
  <li>WinAPI 메시지 루프 기반 InputManager의 KeyMap 갱신</li>
</ul>

  <summary>AIController</summary>
<ul>
  <li>FSM 기반. Player와의 거리로 CurrentInput 갱신</li>
</ul>

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


