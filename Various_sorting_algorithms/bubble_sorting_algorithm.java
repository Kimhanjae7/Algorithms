import java.io.*;
import java.util.*;

public class bubble_sorting_algorithm {
    public static void main(String[] args) {
        String input_file = "unsort_input.txt";
        String output_file = "bubble_output.txt";

        try {
            List<Integer> numbers = file_read(input_file);

            // 숫자 배열로 변환
            int[] array = numbers.stream().mapToInt(Integer::intValue).toArray();

            long start = System.nanoTime();
            bubble_sort(array);
            long end= System.nanoTime();

            long bubble_time = end - start;
            

            file_write(output_file, array);

            System.out.println("정렬 완료\n소요 시간: " + bubble_time +"ns");
        } catch (IOException e) {
            System.err.println("file error");
        }
    }

    // 버블 정렬 알고리즘
    public static void bubble_sort(int[] array) {
        int n = array.length;
        for (int pass = 1; pass < n; pass++) {
            for (int i = 1; i < n - pass; i++) {
                // 이전 원소가 현재 원소보다 값이 크면
                if (array[i-1] > array[i]) { 
                    // 원소 교체
                    int temp = array[i-1];
                    array[i-1] = array[i];
                    array[i] = temp;
                }
            }
        }
    }

    // 파일에서 숫자 읽기
    public static List<Integer> file_read(String file_name) throws IOException {
        List<Integer> numbers = new ArrayList<>();
        try (BufferedReader br = new BufferedReader(new FileReader(file_name))) {
            String line;
            while ((line = br.readLine()) != null) {
                numbers.add(Integer.parseInt(line.trim()));
            }
        }
        return numbers;
    }

    // 파일에 정렬 값 쓰기
    public static void file_write(String file_name, int[] array) throws IOException {
        try (BufferedWriter bw = new BufferedWriter(new FileWriter(file_name))) {
            for (int num : array) {
                bw.write(num + "\n");
            }
        }
    }
}
