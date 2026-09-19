# Top-K & Selection Algorithms

C와 Python으로 최소 힙 기반 Top-K와 Quickselect 기반 선택 알고리즘을 구현하고 비교한 알고리즘 수업 프로젝트입니다.

## 구현 내용

- 최소 힙으로 가장 큰 K개 원소 찾기: `O(n log k)`
- Quickselect로 k번째 순서 통계량 찾기: 평균 `O(n)`, 최악 `O(n²)`
- 동일한 문제를 C와 Python으로 구현해 언어별 구현 차이 비교

## 담당 내용

- Top-K & Selection 문제와 알고리즘 구현
- 팀 발표 자료 구성

## 구조

```text
src/
├─ c/
│  ├─ min_heap.c
│  └─ quickselect.c
└─ python/
   ├─ min_heap.py
   └─ quickselect.py
```

## 실행 예시

```bash
python src/python/min_heap.py
python src/python/quickselect.py
gcc src/c/min_heap.c -o min_heap
gcc src/c/quickselect.c -o quickselect
```

원본 발표 자료에는 팀원 정보가 포함되어 있어 저장소에서 제외했습니다.
