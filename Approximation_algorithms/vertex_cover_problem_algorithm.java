import java.io.*;
import java.util.*;

public class vertex_cover_problem_algorithm {
    public static List<String> approx_matching_vc(List<String> edges) {
        Set<String> matched = new HashSet<>(); // 이미 매칭된 정점
        List<String> maximal_matching = new ArrayList<>(); // Maximal Matching에 포함된 간선


        for (String edge : edges) {
            // 간선 추출
            String[] vertices = edge.split("-");
            String vertex1 = vertices[0];
            String vertex2 = vertices[1];

            // 두 정점 모두 매칭되지 않은 경우
            if (!matched.contains(vertex1) && !matched.contains(vertex2)) {
                maximal_matching.add(edge); // 간선을 Maximal Matching에 추가
                // 매칭된 상태로 등록
                matched.add(vertex1);
                matched.add(vertex2); 
            }
        }
        return maximal_matching;
    }

    public static void main(String[] args) {
        String edge_input = "vertex_cover_input.txt"; // 입력 파일 이름
        List<String> edges = new ArrayList<>(); // 간선 저장

        // 입력 파일 읽기
        try (BufferedReader br = new BufferedReader(new FileReader(edge_input))) {
            String line;
            while ((line = br.readLine()) != null) {
                edges.add(line.trim()); // 간선을 리스트에 추가
            }
        } catch (IOException e) {
            System.err.println("file error");
            return;
        }

        List<String> maximal_matching = approx_matching_vc(edges);

        System.out.println("◎ Maximal Matching Edges");
        for (String edge : maximal_matching) {
            System.out.println(edge);
        }
    }
}
