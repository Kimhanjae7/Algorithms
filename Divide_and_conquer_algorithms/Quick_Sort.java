import java.io.*;
import java.util.*;

public class Quick_sort {
    public static void main(String[] args) throws Exception {
        //입출력 파일 경로
        String inputFile = "input_sort.txt";
        String outputFile = "output_quick_sort.xlsx";

        try {
            // 읽은 숫자를 담을 리스트 객체
            List<Integer> arr = new ArrayList<>();
            // inputFile을 읽을 객체
            BufferedReader reader = new BufferedReader(new FileReader(inputFile));
            // 읽은 라인 문자열 변수 BufferedReader은 문자열로 읽어오기 때문에 String
            String line;

            while ((line = reader.readLine()) != null) { //파일의 끝까지 한 줄씩 읽기 (파일 끝 = 종료조건)
                try {
                    // 읽어온 라인을 숫자로 변환 후 리스트에 삽입 / trim()-> 문자열 앞뒤 공백 제거
                    int number = Integer.parseInt(line.trim());
                    arr.add(number);
                } catch (NumberFormatException e) {
                    System.out.println("읽은 문자가 숫자가 아닙니다: " + line);
                }
            }
            reader.close();
            // 시작 시간 측정
            long start = System.nanoTime();

            // QuickSort 수행
            QuickSort(arr, 0, arr.size() - 1);

            // 종료 시간 측정
            long end = System.nanoTime();
            long QuickSortTime = end - start;

            // outputFile에 데이터를 쓰기 위한 객체 
            BufferedWriter writer = new BufferedWriter(new FileWriter(outputFile));
            // 퀵 정렬시킨 배열을 읽은 후 작성
            for (int number : arr) {
                writer.write(String.valueOf(number)); // 문자열만을 다루기 때문에 다시 문자열로 변환 후 작성
                writer.newLine();
            }
            writer.close();

            System.out.println("정렬이 완료되었습니다. " + outputFile + " 파일을 확인해주세요");
            System.out.println("퀵정렬 소요시간: " + QuickSortTime + "ns");
        } catch (IOException e) {
            e.printStackTrace(); //예외 처리 상세정보를 출력해주는 함수
        }
    }

    // QuickSort 구현
    public static void QuickSort(List<Integer> arr, int first, int last) {
        if (first < last) {
            // 중간 요소를 피벗으로 선정 후, 가장 좌측요소와 교환
            int mid = (first + last) / 2;
            swap(arr, first, mid);

            // 피벗을 기준으로 배열 분할
            int p = partition(arr, first, last);
            // 피벗보다 작은 그룹 정렬
            QuickSort(arr, first, p - 1);
            // 피벗보다 큰 그룹 정렬
            QuickSort(arr, p + 1, last);
        }
    }

    // 피벗을 기준 배열 분할 함수
    public static int partition(List<Integer> arr, int first, int last) {
        int pivot = arr.get(first); // 피벗은 가장 좌측에 위치(스왑했기 때문)
        int left = first + 1; // first에는 피벗이 위치하므로 +1부터 피벗보다 큰 값 찾기
        int right = last; // 배열 끝에서부터 피벗보다 작은 값 찾기

        while (left <= right) {
            // left는 피벗보다 큰 값을 찾을 때까지 이동
            while (left <= last && arr.get(left) <= pivot) {
                left++;
            }
            // right는 피벗보다 작은 값을 찾을 때까지 이동
            while (right > first && arr.get(right) >= pivot) {
                right--;
            }
            // left와 right가 교차하지 않았으면, 값을 교환
            if (left < right) {
                swap(arr, left, right);
            }
        }
        // 피벗을 자신의 최종 위치로 이동
        swap(arr,first,right);
        // 피벗 최종위치 반환
        return right;
    }

    // 요소를 교환하는 swap 함수
    public static void swap(List<Integer> arr, int i, int j) {
        int temp = arr.get(i);
        arr.set(i, arr.get(j));
        arr.set(j, temp);
    }
}
