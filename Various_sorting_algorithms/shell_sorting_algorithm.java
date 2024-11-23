import java.io.*;
import java.util.*;

public class shell_sorting_algorithm {
    public static void main(String[] args) {
        String input_file = "unsort_input.txt";
        String output_file = "shell_output.txt";

        try {
            List<Integer> numbers = file_read(input_file);
            int[] array = numbers.stream().mapToInt(Integer::intValue).toArray();

            long start = System.nanoTime();
            shell_sort(array);
            long end = System.nanoTime();
            long shell_time = end - start;

            file_write(output_file, array);
            System.out.println("정렬 완료\n소요 시간: " + shell_time + "ns");

        } catch (IOException e) {
            System.err.println("file error");
        }
    }

    public static void shell_sort(int[] array) {
        int n = array.length;

        // h=100 -> h=50 -> h=10 -> h=5 -> h=1 순으로 정렬
        int[] gaps = {100, 50, 10, 5, 1};

        for (int h : gaps) {
            for (int i = h; i < n; i++) {
                int current_element = array[i];
                int j = i;

                // h 간격으로 정렬 유지
                while (j >= h && array[j - h] > current_element) {
                    array[j] = array[j - h];
                    j -= h;
                }

                // 현재 요소를 올바른 위치에 삽입
                array[j] = current_element;
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

    // 파일에 정렬된 배열 쓰기
    public static void file_write(String file_name, int[] array) throws IOException {
        try (BufferedWriter bw = new BufferedWriter(new FileWriter(file_name))) {
            for (int num : array) {
                bw.write(num + "\n");
            }
        }
    }
}
