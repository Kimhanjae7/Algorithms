# 작업 클래스 정의
class Job:
    def __init__(self, job_id, start_time, end_time):
        self.job_id = job_id
        self.start_time = start_time
        self.end_time = end_time

    # 객체를 출력할 때 t1, t2 ... 형식으로 출력하기 위한 정의
    def __repr__(self):
        return f"t{self.job_id}"

def job_scheduling(jobs):
    # 작업들을 시작 시간을 기준으로 오름차순 정렬
    jobs.sort(key=lambda x: x.start_time)

    schedule = []  # 각 기계에 배정된 작업 리스트
    machines = []  # 기계가 마지막 작업을 끝내는 시간 저장
    machine_timeline = []  # 각 기계의 타임라인

    for job in jobs:
        # 각 기계의 끝나는 시간과 비교하여 작업을 수행할 수 있는 기계 찾기
        assigned = False
        for i in range(len(machines)):
            if machines[i] <= job.start_time:
                # 작업을 수행할 수 있으면 해당 기계에 배정
                schedule[i].append(job) # 작업을 해당 기계의 작업 리스트에 추가
                machines[i] = job.end_time   # 기계의 종료 시간을 현재 작업의 종료 시간으로 갱신

                # 작업 테이블에 기록
                for t in range(job.start_time, job.end_time):
                    machine_timeline[i][t] = job
                assigned = True
                break

        # 작업을 수행할 기계가 없으면 새로운 기계에 배정
        if not assigned:
            schedule.append([job])
            machines.append(job.end_time)
            machine_timeline.append([None] * 10)
            for t in range(job.start_time, job.end_time):
                machine_timeline[-1][t] = job

    return machine_timeline

def print_timeline_table(machine_timeline):
    print("time   ", end=" ")
    for t in range(len(machine_timeline[0])):
        print(f"{t}  ", end=" ")
    print()
    
    for i, timeline in enumerate(machine_timeline):
        print(f"Machine {i + 1}  ", end=" ")
        for job in timeline:
            if job:
                print(f"{job} ", end=" ")
            else:
                print("   ", end=" ")
        print()

# 작업 리스트
jobs = [
    Job(1, 7, 8),
    Job(2, 3, 7),
    Job(3, 1, 5),
    Job(4, 5, 9),
    Job(5, 0, 2),
    Job(6, 6, 8),
    Job(7, 1, 6),
]

machine_timeline = job_scheduling(jobs)

print_timeline_table(machine_timeline)
