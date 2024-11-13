public class edit_distance_algorithm {
    public static int editDistance(String S, String T) {
        int m = S.length();
        int n = T.length();
        int[][] E = new int[m + 1][n + 1];

        // 0번 열의 초기화
        for (int i = 0; i <= m; i++) { 
            E[i][0] = i;
        }

        // 0번 행의 초기화
        for (int j = 0; j <= n; j++) {
            E[0][j] = j;
        }

        // 행렬 채우기
        for (int i = 1; i <= m; i++) {
            for (int j = 1; j <= n; j++) {
                // cost는 두 문자가 같으면 0이고, 다르면 1 -> 교체에 사용
                int cost = (S.charAt(i-1) == T.charAt(j-1)) ? 0 : 1;

                // E[i][j-1]은 삽입, E[i-1][j]는 삭제, E[i-1][j-1]은 교체
                E[i][j] = Math.min(Math.min(E[i][j-1] + 1, E[i-1][j] + 1), E[i-1][j-1] + cost);
            }
        }

        printTable(E, S, T);

        return E[m][n];
    }

    // 테이블 출력 
    public static void printTable(int[][] E, String S, String T) {
        int m = S.length();
        int n = T.length();

        System.out.print("    "); 
        for (int j = 0; j < T.length(); j++) {
            System.out.print(T.charAt(j) + " ");
        }
        System.out.println();

        for (int i = 0; i <= m; i++) {
            if (i > 0) {
                System.out.print(S.charAt(i - 1) + " ");
            } else {
                System.out.print("  ");
            }

            for (int j = 0; j <= n; j++) {
                System.out.print(E[i][j] + " ");
            }
            System.out.println();
        }
    }

    public static void main(String[] args) {
        String S = "strong";
        String T = "stone";
        editDistance(S, T);
    }
}
