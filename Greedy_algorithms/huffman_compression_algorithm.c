#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HEIGHT_MAX 5
#define ASCII 128
#define STR_MAX 1000

// 노드 구조체
struct MinHeapNode {
    char data; // A,C,G,T
    unsigned frequency; // 문자 빈도 수
    struct MinHeapNode *left, *right; // 자식 노드
};

// 힙 구조체 정의
struct MinHeap {
    unsigned size; // 노드 개수
    unsigned capacity;
    struct MinHeapNode** array; // 각 노드 포인터 배열
};

// 새로운 노드 생성
struct MinHeapNode* newNode(char data, unsigned frequency) {
    struct MinHeapNode* temp = (struct MinHeapNode*)malloc(sizeof(struct MinHeapNode));
    temp->left = temp->right = NULL; // 초기 상태
    temp->data = data;
    temp->frequency = frequency;
    return temp;
}

// 힙 생성
struct MinHeap* createMinHeap(unsigned capacity) {
    struct MinHeap* minHeap = (struct MinHeap*)malloc(sizeof(struct MinHeap));
    minHeap->size = 0;
    minHeap->capacity = capacity;
    minHeap->array = (struct MinHeapNode**)malloc(minHeap->capacity * sizeof(struct MinHeapNode*));
    return minHeap;
}

// 두 노드를 교환
void swapMinHeapNode(struct MinHeapNode** a, struct MinHeapNode** b) {
    struct MinHeapNode* t = *a;
    *a = *b;
    *b = t;
}

// 힙 정렬을 유지하는 함수
// 부모 노드가 자식 노드보다 크도록 재귀적으로 함수 호출 시키기
void heapMaintenance(struct MinHeap* minHeap, int idx) {
    int smallest = idx;
    int left = 2 * idx + 1;
    int right = 2 * idx + 2;

    if (left < minHeap->size && minHeap->array[left]->frequency < minHeap->array[smallest]->frequency)
        smallest = left;

    if (right < minHeap->size && minHeap->array[right]->frequency < minHeap->array[smallest]->frequency)
        smallest = right;

    if (smallest != idx) {
        swapMinHeapNode(&minHeap->array[smallest], &minHeap->array[idx]);
        heapMaintenance(minHeap, smallest);
    }
}

// 힙에서 가장 빈도가 작은 노드를 제거하고 반환하는 함수
struct MinHeapNode* extractMin(struct MinHeap* minHeap) {
    struct MinHeapNode* temp = minHeap->array[0];
    minHeap->array[0] = minHeap->array[minHeap->size - 1];
    --minHeap->size;
    heapMaintenance(minHeap, 0);
    return temp;
}

// 힙에 노드 삽입
void insertMinHeap(struct MinHeap* minHeap, struct MinHeapNode* minHeapNode) {
    ++minHeap->size;
    int i = minHeap->size - 1;

    while (i && minHeapNode->frequency < minHeap->array[(i - 1) / 2]->frequency) {
        minHeap->array[i] = minHeap->array[(i - 1) / 2];
        i = (i - 1) / 2;
    }
    minHeap->array[i] = minHeapNode;
}

// 힙 노드가 하나인지 확인하기
int isSizeOne(struct MinHeap* minHeap) {
    return (minHeap->size == 1);
}

// 최소 힙 생성
struct MinHeap* createAndBuildMinHeap(char data[], int frequency[], int size) {
    struct MinHeap* minHeap = createMinHeap(size);

    for (int i = 0; i < size; ++i)
        minHeap->array[i] = newNode(data[i], frequency[i]);

    minHeap->size = size;
    for (int i = (minHeap->size - 1) / 2; i >= 0; --i)
        heapMaintenance(minHeap, i); // 힙 정렬 유지

    return minHeap;
}

// 허프만 트리 생성
struct MinHeapNode* buildHuffmanTree(char data[], int frequency[], int size) {
    struct MinHeapNode *left, *right, *parent;

    struct MinHeap* minHeap = createAndBuildMinHeap(data, frequency, size);

    while (!isSizeOne(minHeap)) { // 힙 크기가 1이 될 때까지 수행
        left = extractMin(minHeap);
        right = extractMin(minHeap); // 최소 빈도 수 노드 두개 추출

        // 두 노드를 자식으로 하는 새로운 부모 노드 생성
        parent = newNode('$', left->frequency + right->frequency);
        parent->left = left;
        parent->right = right;

        // 생성된 노드를 힙에 삽입
        insertMinHeap(minHeap, parent);
    }

    return extractMin(minHeap);
}

// 코드 생성
// 허프만 트리의 루트에서 리프까지의 경로를 탐색해 각 문자의 허프만 코드를 출력
void printCodes(struct MinHeapNode* root, int arr[], int parent, char huffCodes[ASCII][HEIGHT_MAX]) {
    if (root->left) {
        arr[parent] = 0; // 부모의 좌측 노드는 0
        printCodes(root->left, arr, parent + 1, huffCodes); 
    }

    if (root->right) {
        arr[parent] = 1; // 부모의 우측 노드는 1
        printCodes(root->right, arr, parent + 1, huffCodes);
    }
    // 리프 노드에 도달시에 해당 문자의 코드를 출력
    if (!root->left && !root->right) {
        printf("%c: ", root->data);
        for (int i = 0; i < parent; ++i)
            printf("%d", arr[i]);
        printf("\n");

        for (int i = 0; i < parent; ++i)
            huffCodes[(int)root->data][i] = arr[i] + '0';
        huffCodes[(int)root->data][parent] = '\0';
    }
}

// 허프만 코드를 생성하고 출력
void HuffmanCodes(char data[], int frequency[], int size, char huffCodes[ASCII][HEIGHT_MAX]) {
    struct MinHeapNode* root = buildHuffmanTree(data, frequency, size);

    int arr[HEIGHT_MAX], parent = 0;
    printCodes(root, arr, parent, huffCodes);
}

// 허프만 해독
void decodeHuffman(char huffCodes[ASCII][HEIGHT_MAX], char* encodedStr) {
    char* decoded = (char*)malloc(strlen(encodedStr) + 1); // 해독된 문자열에서의 인덱스
    char* temp = (char*)malloc(HEIGHT_MAX); // 이진 문자열을 저장할 임시 배열

    int decodedIndex = 0, tempIndex = 0;

    for (int i = 0; i <= strlen(encodedStr); i++) {
        temp[tempIndex++] = encodedStr[i];
        temp[tempIndex] = '\0';

        for (int j = 0; j < ASCII; j++) { 
            if (strlen(huffCodes[j]) > 0 && strcmp(temp, huffCodes[j]) == 0) { // 대응하는 코드가 있는지 확인
                decoded[decodedIndex++] = j; 
                tempIndex = 0; // 대응 되었으므로 초기화
                temp[0] = '\0';
                break;
            }
        }
    }

    decoded[decodedIndex] = '\0';
    printf("Decoded String: %s\n", decoded);

    free(decoded);
    free(temp);
}

int main() {
    char str[STR_MAX];

    FILE *file = fopen("huffman_input.txt", "r"); 
    if (!file) {
        printf("파일을 열 수 없습니다: %s\n", "huffman_input.txt");
        exit(1); 
    }

    if (fgets(str, STR_MAX, file) == NULL) {
        printf("파일에서 데이터를 읽어오지 못했습니다.\n");
        fclose(file); 
        exit(1);
    }

    fclose(file);

    // 각 문자의 빈도를 계산
    int frequency[ASCII] = {0};
    for (int i = 0; str[i]; i++) {
        frequency[(int)str[i]]++;
    }

    char data[] = {'A', 'C', 'G', 'T'};
    int frequencys[] = {frequency['A'], frequency['C'], frequency['G'], frequency['T']};

    int size = sizeof(data) / sizeof(data[0]);

    char huffCodes[ASCII][HEIGHT_MAX] = {{0}};
    printf("\n[Huffman Code]\n");
    HuffmanCodes(data, frequencys, size, huffCodes);
    printf("\n");

    char encodedStr[] = "10110010001110101010100";
    decodeHuffman(huffCodes, encodedStr);

    return 0;
}
