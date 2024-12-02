import java.util.ArrayList;
import java.util.List;

public class job_scheduling_problem_algorithm {
    // 작업 테이블을 만들기 위한 클래스
    public static class Task {
        int id; // 작업 ID
        int start; // 작업 시작 시간
        int end; // 작업 종료 시간

        public Task(int id, int start, int end) {
            this.id = id;
            this.start = start;
            this.end = end;
        }
    }

    public static void approx_job_scheduling(int[] jobs, int m) {
        // 기계들에 배정된 마지막 작업 종료 시간 저장 배열 L
        int[] L = new int[m + 1]; 
        List<List<Task>> schedule = new ArrayList<>(); // 작업 리스트

        for (int i = 0; i <= m; i++) {
            schedule.add(new ArrayList<>());
        }

        // 작업을 순서대로 기계에 배정
        for (int i = 1; i <= jobs.length; i++) { 
            int min = 1; // 첫 번째 기계부터 시작

            // 가장 일찍 끝나는 기계 찾기 (두 번째 기계부터 비교)
            for (int j = 2; j <= m; j++) {
                if (L[j] < L[min]) {
                    min = j; // 더 빨리 끝나는 기계로 업데이트
                }
            }

            int start = L[min]; // 작업 시작 시간 (기계 현재 종료 시간이 시작시간임)
            int end = start + jobs[i - 1]; // 작업 종료 시간
            L[min] = end; // 기계의 종료 시간 갱신

            // 작업 배정
            schedule.get(min).add(new Task(i, start, end));
        }

        // 테이블 출력
        printSchedule(schedule, L, m);
    }

    public static void printSchedule(List<List<Task>> schedule, int[] L, int m) {
        int maxTime = 0;
        for (int i = 1; i <= m; i++) {
            maxTime = Math.max(maxTime, L[i]);
        }

        // 시간 헤더 출력
        System.out.print("m\\t ");
        for (int t = 0; t < maxTime; t++) {
            if (t>=10){
                System.out.print(t + " ");
            }
            else{
            System.out.print(t + "  ");
            }
        }
        System.out.println();

        for (int i = 1; i <= m; i++) {
            System.out.print(i + "   "); 
            int currentTime = 0;

            for (Task task : schedule.get(i)) {
                while (currentTime < task.start) {
                    System.out.print("    "); 
                    currentTime++;
                }
                for (int t = task.start; t < task.end; t++) {
                    System.out.print("t" + task.id + " ");
                    currentTime++;
                }
            }

            while (currentTime <= maxTime) {
                System.out.print("    ");
                currentTime++;
            }

            System.out.println();
        }
    }

    public static void main(String[] args) {
        int[] operation_time = {5, 2, 4, 3, 4, 7, 9, 2, 4, 1};
        int m = 4;

        approx_job_scheduling(operation_time, m);
    }
}
