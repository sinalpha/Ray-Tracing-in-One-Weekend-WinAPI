# ray-tracing

## reference   
https://raytracing.github.io/books/RayTracingInOneWeekend.html   
렌더링 속도 향상 방법; 멀티 쓰레딩을 이용한다.   
화면을 2엔제곱 분할하여 각 영역에 대하여서 렌더링한다.   
가능한 이유는 각 광선이 씬과 상호작용을 하였을 때 씬의 정보는 바뀌지 않기 때문이다.
