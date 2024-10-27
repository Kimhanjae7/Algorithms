import java.util.*;

public class set_cover_algorithm {

    static int[] C = new int[10]; // 결과 집합
    static int[] U = new int[10]; // 커버할 U집합

    public static void main(String[] args) {

        // 인접한 마을 표시 인접행렬
        int[][] S = {
            {1, 1, 1, 0, 0, 0, 0, 1, 0, 0}, 
            {1, 1, 1, 1, 0, 0, 0, 1, 0, 0},  
            {1, 1, 1, 1, 0, 0, 0, 0, 0, 0}, 
            {0, 1, 1, 1, 1, 0, 1, 1, 0, 0}, 
            {0, 0, 0, 1, 1, 1, 1, 0, 0, 0},
            {0, 0, 0, 0, 1, 1, 1, 0, 1, 1}, 
            {0, 0, 0, 1, 1, 1, 1, 0, 0, 0}, 
            {1, 1, 0, 1, 0, 0, 0, 1, 0, 0},
            {0, 0, 0, 0, 0, 1, 0, 0, 1, 0}, 
            {0, 0, 0, 0, 0, 1, 0, 0, 0, 1} 
        };

        // Set Cover 실행
        long set_cover_start = System.nanoTime();
        set_cover(S);
        long set_cover_end = System.nanoTime();
        long set_cover_algorithm_running_time = set_cover_end - set_cover_start;
        System.out.println("- Set Cover Algorithm Running Time: " + set_cover_algorithm_running_time + " ns\n");

        // Optimal Set Cover 실행
        long optimal_set_cover_start = System.nanoTime();
        optimal_set_cover(S);
        long optimal_set_cover_end = System.nanoTime();
        long optimal_set_cover_algorithm_running_time = optimal_set_cover_end - optimal_set_cover_start;
        System.out.println("- Optimal Set Cover Algorithm Running Time: " + optimal_set_cover_algorithm_running_time + " ns");
    }

    static void set_cover(int[][] S) {

        // 초기화
        Arrays.fill(C, 0);
        Arrays.fill(U, 1);

        while (true) {
            // 모든 U의 요소가 커버되었는지 확인
            boolean all_cover_U = false;
            for (int i = 0; i < 10; i++) {
                if (U[i] == 1) {
                    all_cover_U = true;
                    break;
                }
            }
    
            // U의 모든 원소가 커버되었으면 종료
            if (!all_cover_U) {
                break;
            }
    
            // 가장 많은 마을을 커버하는 인덱스를 찾음
            int max_index = -1;
            int max = 0;
            for (int i = 0; i < 10; i++) {
                int cover_count = 0;
                for (int j = 0; j < 10; j++) {
                    if (U[j] == 1 && S[i][j] == 1) {
                        cover_count++;
                    }
                }
    
                if (cover_count > max) {
                    max = cover_count;
                    max_index = i;
                }
            }
    
            // 가장 많은 마을을 커버하는 max_index를 C에 추가
            if (max_index != -1) {
                C[max_index] = 1;
            }
    
            //선택된 인덱스의 마을을 U에서 제거
            for (int j = 0; j < 10; j++) {
                if (S[max_index][j] == 1 && U[j] == 1) {
                    U[j] = 0;
                }
            }
        }
    
        System.out.println("◎  Set cover algorithm result\n");
        System.out.print("- C = {");
        boolean comma = true;
        for (int i = 0; i < 10; i++) {
            if (C[i] == 1) {
                if (!comma) {
                    System.out.print(", ");
                }
                System.out.print("S" + (i + 1));
                comma = false;
            }
        }
        System.out.println("}");
    }
    
    static void optimal_set_cover(int[][] S) {

        // 초기화
        Arrays.fill(C, 0);
        Arrays.fill(U, 1);

        int n = S.length;
        int min_cover = Integer.MAX_VALUE; // 최소 집합 수 찾기
        int[] best_solution = new int[n];
        
        // 가능한 모든 집합의 조합 탐색
        for (int i = 0; i < (1 << n); i++) { // 1<<n은 집합 수를 의미 -> 모든 부분집합 탐색 (2의 n제곱)
            int[] covered = new int[10];  // 덮여진 마을들
            int count = 0;  // 선택된 집합 수
            int[] currentSolution = new int[n];
    
            // 선택된 집합들을 더해 나가면서 covered 배열 갱신
            for (int j = 0; j < n; j++) {
                if ((i & (1 << j)) > 0) {  // i에서 j번째 집합이 선택됨
                    currentSolution[j] = 1;  // 집합 선택 표시
                    for (int k = 0; k < 10; k++) {
                        if (S[j][k] == 1) {
                            covered[k] = 1;  // 해당 집합이 커버하는 마을을 표시
                        }
                    }
                    count++;
                }
            }
    
            // 모든 마을이 커버되었는지 확인
            boolean all_cover_U = true;
            for (int k = 0; k < 10; k++) {
                if (covered[k] == 0) {
                    all_cover_U = false;  
                    break;
                }
            }
    
            // 최소 집합으로 커버할 수 있으면 최적해 갱신
            if (all_cover_U && count < min_cover) {
                min_cover = count;
                System.arraycopy(currentSolution, 0, best_solution, 0, n);
            }
        }
    
        System.out.println("◎  Optimal Set cover algorithm result");
        System.out.print("- C = {");
        boolean comma = true;
        for (int i = 0; i < 10; i++) {
            if (best_solution[i] == 1) {
                if (!comma) {
                    System.out.print(", ");
                }
                System.out.print("S" + (i + 1));
                comma = false;
            }
        }
        System.out.println("}");
    }
    
}
