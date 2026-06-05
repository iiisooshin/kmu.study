def fifo(reference, frame_count):
    frames = []          # 현재 메모리 프레임
    result = []          # F(부재), S(적중) 저장
    history = []         # 각 단계의 프레임 상태 저장
    faults = 0           # 페이지 부재 횟수
    pointer = 0          # FIFO 교체 위치

    for page in reference:

        # 페이지가 이미 프레임에 존재하는 경우
        if page in frames:
            result.append("S")

        # 페이지 부재 발생
        else:
            result.append("F")
            faults += 1

            # 빈 프레임이 있으면 추가
            if len(frames) < frame_count:
                frames.append(page)

            # 가장 먼저 들어온 페이지 교체
            else:
                frames[pointer] = page
                pointer = (pointer + 1) % frame_count

        # 현재 프레임 상태 저장
        history.append(frames.copy())

    print_result("FIFO", reference, result, history, faults, frame_count)


def lru(reference, frame_count):
    frames = []
    result = []
    history = []
    faults = 0

    # 각 페이지의 마지막 사용 위치 저장
    last_used = {}

    for i, page in enumerate(reference):

        if page in frames:
            result.append("S")

        else:
            result.append("F")
            faults += 1

            if len(frames) < frame_count:
                frames.append(page)

            else:
                # 가장 오래 사용되지 않은 페이지 선택
                lru_page = min(frames, key=lambda x: last_used[x])

                idx = frames.index(lru_page)
                frames[idx] = page

        # 현재 페이지 사용 위치 기록
        last_used[page] = i

        history.append(frames.copy())

    print_result("LRU", reference, result, history, faults, frame_count)


def opt(reference, frame_count):
    frames = []
    result = []
    history = []
    faults = 0

    for i, page in enumerate(reference):

        if page in frames:
            result.append("S")

        else:
            result.append("F")
            faults += 1

            if len(frames) < frame_count:
                frames.append(page)

            else:
                # 현재 시점 이후의 참조열
                future = reference[i + 1:]

                victim = None
                farthest = -1

                for p in frames:

                    # 앞으로 사용되지 않는 페이지 우선 제거
                    if p not in future:
                        victim = p
                        break

                    # 다음 사용 시점 계산
                    distance = future.index(p)

                    # 가장 나중에 사용될 페이지 선택
                    if distance > farthest:
                        farthest = distance
                        victim = p

                idx = frames.index(victim)
                frames[idx] = page

        history.append(frames.copy())

    print_result("OPT", reference, result, history, faults, frame_count)


def print_result(name, reference, result, history, faults, frame_count):

    print("\n==============================")
    print(name)
    print("==============================")

    # 참조열 출력
    print("Reference :", " ".join(reference))

    # 적중/부재 결과 출력
    print("Result    :", " ".join(result))

    print("\nFrame State")

    for i in range(len(reference)):
        frame = history[i].copy()

        # 비어있는 프레임은 -로 표시
        while len(frame) < frame_count:
            frame.append("-")

        print(f"{reference[i]} -> {' '.join(frame)}")

    print(f"\nPage Faults : {faults}")

    # 페이지 부재율 계산
    print(f"Fault Rate  : {faults / len(reference) * 100:.2f}%")


def main():
    # 사용자 입력
    frame_count = int(input("프레임 수 입력: "))
    reference = input("참조열 입력: ").upper()

    # 각 알고리즘 실행
    fifo(reference, frame_count)
    lru(reference, frame_count)
    opt(reference, frame_count)


# 프로그램 시작점
if __name__ == "__main__":
    main()