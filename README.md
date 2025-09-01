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

## 주요 기능

<details>
<summary>보스 AI</summary>
<ul>
  <li>상태 패턴(State Pattern)을 활용한 보스 행동 제어</li>
  <li>패턴별 타이머를 이용한 공격 주기 관리</li>
  <li>페이즈 전환 로직 구현</li>
</ul>
</details>

<details>
<summary>🎮 입력 및 충돌 처리</summary>
<ul>
  <li>WinAPI 메시지 루프 기반 입력 처리</li>
  <li>AABB 충돌 감지 및 반응 처리</li>
  <li>플레이어/적/투사체 간 상호작용</li>
</ul>
</details>

<details>
<summary>🖼 리소스 관리</summary>
<ul>
  <li>텍스처/스프라이트 로딩 및 캐싱</li>
  <li>상대 경로 기반 리소스 접근</li>
  <li>SpriteManager를 통한 렌더링 일원화</li>
</ul>
</details>
