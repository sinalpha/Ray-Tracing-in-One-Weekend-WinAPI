# ray-tracing
Porting CLI RTOW into WinAPI RTOW   

## Purpose   
study Ray-tracing

## reference   
https://raytracing.github.io/books/RayTracingInOneWeekend.html  

## 메모장  
렌더링 속도 향상 방법; 멀티 쓰레딩을 이용한다.   
화면을 2엔제곱 분할하여 각 영역에 대하여서 렌더링한다.   
가능한 이유는 각 광선이 씬과 상호작용을 하였을 때 씬의 정보는 바뀌지 않기 때문이다.   

코드를 모두 실행시키(학습하)고 나서 학습했던 내용을 다이어그램으로 그려보기   

내부 반사(Total internal reflection)이 일어나면 카메라(눈)에 어떻게 상이 맺히는 지 공부하기(물리학 책을 이용해서)   

번거로움을 간소화하기 위해서 2024/01/24부터 커밋되는 소스코드는 정의과 선언을 분리하지 않는다.
