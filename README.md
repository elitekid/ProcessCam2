# "창백한 푸른 점"

<img src="https://private-user-images.githubusercontent.com/89232526/301347479-5c1fc6ad-2482-4e30-b6d7-b68f8c089c77.jpg?jwt=eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJpc3MiOiJnaXRodWIuY29tIiwiYXVkIjoicmF3LmdpdGh1YnVzZXJjb250ZW50LmNvbSIsImtleSI6ImtleTUiLCJleHAiOjE3MDY3NDcyNzksIm5iZiI6MTcwNjc0Njk3OSwicGF0aCI6Ii84OTIzMjUyNi8zMDEzNDc0NzktNWMxZmM2YWQtMjQ4Mi00ZTMwLWI2ZDctYjY4ZjhjMDg5Yzc3LmpwZz9YLUFtei1BbGdvcml0aG09QVdTNC1ITUFDLVNIQTI1NiZYLUFtei1DcmVkZW50aWFsPUFLSUFWQ09EWUxTQTUzUFFLNFpBJTJGMjAyNDAyMDElMkZ1cy1lYXN0LTElMkZzMyUyRmF3czRfcmVxdWVzdCZYLUFtei1EYXRlPTIwMjQwMjAxVDAwMjI1OVomWC1BbXotRXhwaXJlcz0zMDAmWC1BbXotU2lnbmF0dXJlPWM1ZWIyYWQ3YTkzNDEzYjQzMzc1MzEwOTg3NmFjNTJjOWRhNjU3ZTkwNDgyNzI3MDA1ZWYyNDBjZDQxZDU1ZWImWC1BbXotU2lnbmVkSGVhZGVycz1ob3N0JmFjdG9yX2lkPTAma2V5X2lkPTAmcmVwb19pZD0wIn0.t5konoNZd0qSuqJJ1AkFarQhVZiW6YN9_vmnvYob72M" alt="ProcessCam2_2" style="max-width: 55%;">

## :sparkles: 소개

"창백한 푸른 점"은 실시간 카메라 영상에서 정적인 부분을 색상 코드로 변환하여 표현하는 작품입니다.

작품은 다음과 같은 주요 특징을 갖습니다.

- 실시간 카메라 영상 처리: `OpenCV` 라이브러리를 사용하여 실시간으로 카메라 영상을 받아들여 처리합니다.
- 움직임 감지: `MOG2` 알고리즘을 사용하여 영상에서 움직이는 부분을 감지하고 정적인 부분만 추출합니다.
- 색상 코드 변환: 추출된 정적 영역을 32x32 크기의 검정색 사각형으로 표현하고, 각 사각형 내부에 해당 영역의 색상 코드를 표시합니다.
- 텍스트 렌더링: `FreeType` 라이브러리를 사용하여 색상 코드를 텍스트 형식으로 렌더링합니다.

## :gear: 기술 스택
<div>
  <img src="https://img.shields.io/badge/c-A8B9CC?style=for-the-badge&logo=c&logoColor=white">
  <img src="https://img.shields.io/badge/c++-00599C?style=for-the-badge&logo=c%2B%2B&logoColor=white">
  <img src="https://img.shields.io/badge/opencv-5C3EE8?style=for-the-badge&logo=opencv&logoColor=white">
  <img src="https://img.shields.io/badge/opengl-5586A4?style=for-the-badge&logo=opengl&logoColor=white">
  <img src="https://img.shields.io/badge/qt-41CD52?style=for-the-badge&logo=qt&logoColor=white">
</div>

## :art: 작품 구성

### 1. 실시간 카메라 영상 캡처

- `VideoCapture` 클래스를 사용하여 카메라 영상을 받아들입니다.
- 영상 데이터는 `Mat` 객체를 사용하여 저장됩니다.

### 2. 움직임 감지

- `createBackgroundSubtractorMOG2` 함수를 사용하여 배경 모델을 생성하고 움직이는 영역을 추출합니다.
- 추출된 움직이는 영역은 마스크 이미지로 저장됩니다.

### 3. 정적 영역 처리

- 마스크 이미지를 사용하여 정적 영역만 추출합니다.
- 추출된 정적 영역을 32x32 크기의 검정색 사각형으로 표현합니다.

### 4. 색상 코드 변환
- 추출된 정적 영역의 각 픽셀의 색상 값을 RGB 코드로 변환합니다.

### 5. 텍스트 렌더링
- FreeType 라이브러리를 사용하여 RGB 코드를 텍스트 형식으로 렌더링합니다.
### 6. 사각형 텍스처 생성 및 적용
- 정적 영역을 나타내는 사각형 텍스처를 생성하고 텍스트 렌더링 결과를 적용합니다.
### 7. OpenGL 그래픽 출력
- OpenGL 라이브러리를 사용하여 사각형 텍스처를 화면에 출력합니다.
