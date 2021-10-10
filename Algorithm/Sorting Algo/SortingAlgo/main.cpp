#include <bits/stdc++.h>

using namespace std;

/*
 * 比较算法：
 *      1. 冒泡
 *      2. 归并排序
 *      3. 快速排序
 * 线性算法：
 *      1. 计数排序
 *      2. 桶排序
 */
const int N = 9;

vector<int> arr = {2 , 3, 1, 4 , 6, 7, 5, 8, 5};

void init(vector<int> &arr) {
        arr = {2 , 3, 1, 4 , 6, 7, 5, 8, 5};
}

void print(vector<int> arr) {
        for (auto x : arr) {
                printf("%d ", x);
        }
        cout << endl;
}

/*
 * 冒泡排序:重复得走过要排序的数列 每次比较相邻的两个元素 如果顺序错误则交换 大的数会冒泡到底端
 */
void bubbleSort(vector<int> &arr) {
        int temp = 0;
        bool swap;
        for (int i = arr.size() - 1; i > 0; i--) { // 每次需要排序得长度
                swap = false;
                for (int j = 0; j < i; j++) { // 从第1个元素到第i个元素
                        if (arr[j] > arr[j + 1]) {
                                ::swap(arr[j], arr[j + 1]);
                                swap = 1;
                        }
                }
                if (!swap) break; // 优化：如果有序就不需要再排序
        }
}

/*
 * 归并排序：将数据切分为一半 对每一半进行排序 最后合并(递归)
 */
// 合并两个有序数组
void mergeSortedArray(vector<int> &arr, vector<int> &tmp, int left, int mid, int right) {
        int i = left, j = mid + 1, k = 0;
        // 处理两个公共的长度
        while (i <= mid && j <= right) {
                tmp[k++] = arr[i] < arr[j] ? arr[i++]:arr[j++];
        }
        // 处理剩余的左区间
        while (i <= mid) tmp[k++] = arr[i++];
        // 处理剩余的右区间
        while (j <= right) tmp[k++] = arr[j++];

        // 复制回原数组
        for (int i = 0; i < k; i++) {
                arr[left + i] = tmp[i];
        }
}

void internalMergeSort(vector<int> &arr, vector<int> &tmp, int left, int right) {
        if (left < right) {
                int mid = (left + right) >> 1;
                internalMergeSort(arr, tmp, left, mid);
                internalMergeSort(arr, tmp, mid + 1, right);
                mergeSortedArray(arr, tmp, left, mid, right);
        }
}

void mergeSort(vector<int> &arr){
        vector<int> tmp(arr.size(), 0);
        internalMergeSort(arr, tmp, 0, arr.size() - 1);
}


/*
 * 快速排序：在待排序的数组中选择一个元素为基准 将待排序的元素分区 大于基准的在右边
 */
int partition(vector<int> &arr, int low, int high) {
        int pivot = arr[low];
        while (low < high) {
                while (low < high && arr[high] >= pivot) high--;
                arr[low] = arr[high];
                while (low < high && arr[low] <= pivot) low++;
                arr[high] = arr[low];
        }
        arr[low] = pivot;
        return low;
}
void quick_sort(vector<int> &arr, int low, int high) {
        if (low >= high) return;
        int pivot = partition(arr, low, high);
        quick_sort(arr, low, pivot);
        quick_sort(arr, pivot + 1, high);
}
void quickSort(vector<int> &arr) {
        quick_sort(arr, 0, arr.size() - 1);
}

/*
 * 计数排序
 * 统计数组中的最大值最小值 然后统计每个元素中出现的次数 反向填充目标数组
 */

void countSort(vector<int> &arr) {
        int MAX = INT_MIN;
        int MIN = INT_MAX;

        for (int i = 0; i < arr.size(); i++) {
                MAX = max(MAX, arr[i]);
                MIN = min(MIN, arr[i]);
        }
        vector<int> tmp(arr.size(), 0);
        vector<int> count(MAX - MIN + 1, 0);

        for (int i = 0; i < arr.size(); i++) {
                count[arr[i] - MIN]++; // 此时count[i]表示等于i的个数
        }

        for (int i = MIN + 1; i <= MAX; i++) {
                count[i - MIN] += count[i - MIN - 1]; //  count[i]表示小于等于i的元素个数
        }

        for (int i = 0; i < arr.size(); i++) {
                int num = arr[i];
                int idx = count[num - MIN] - 1; // 前面有几个元素
                tmp[idx] = num;
                count[num - MIN]--; //  前面元素减少1
        }
        for (int i = 0; i < arr.size(); i++) {
                arr[i] = tmp[i];
        }
}

/*
 * 桶排序：桶自有序 计算每个元素属于哪个桶 每个桶各自排序放入数组中
 */
void bucketSort(vector<int> &arr) {
        int MAX = INT_MIN;
        int MIN = INT_MAX;

        for (int i = 0; i < arr.size(); i++) {
                MAX = max(MAX, arr[i]);
                MIN = min(MIN, arr[i]);
        }
        int bucketNum = (MAX - MIN) / arr.size() + 1;
        vector<vector<int>> bucketArr(bucketNum);

        for (int i = 0; i < arr.size(); i++) {
                int num = (arr[i] - MIN) / arr.size();
                bucketArr[num].push_back(arr[i]);
        }

        // 对每个桶排序
        int cnt = 0;
        for (int i = 0; i < bucketNum; i++) {
                sort(bucketArr[i].begin(), bucketArr[i].end());
                for (int j = 0; j < bucketArr[i].size(); j++) {
                        arr[cnt++] = bucketArr[i][j];
                }
        }
}


int main() {
        //bubbleSort(arr);

        //mergeSort(arr);

        //quickSort(arr);

        //countSort(arr);

        bucketSort(arr);
        print(arr);
        init(arr);
        return 0;
}
