#include <iostream>
using namespace std;

int hanoi_ct = 0;
const int N = 100010;
int n, m;
int a[N];

void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

// 冒泡排序
    // 时间复杂度：
    // for的两层嵌套，因此时间复杂度为O(n^2)
    // 空间复杂度：
    // O(1)
void bubble_sort(int q[], int n)
{   
    for (int j = 0; j < n; j ++ )
    {
        for (int i = 0 ; i < n; i ++ )
        { 
            if (q[i] > q[i + 1])
            {
                swap(&q[i], &q[i + 1]);
            }
        }
    }
}

//  冒泡排序递归算法
    // 时间复杂度 最坏O(n^2),最好O(n)
    // 空间复杂度 O(n)
void bubbleSort(int arr[], int n)
{
    if (n == 1)return;

    for (int i = 0; i < n - 1; i++) {
        if (arr[i] > arr[i + 1]) {
            swap(arr[i], arr[i + 1]);
        }
    }

    bubbleSort(arr, n - 1);
}

// 选择排序
    // 时间复杂度
    // 两层for嵌套最大次数为 n^2 , 因此时间复杂度为O(n^2)
    // 空间复杂度
    // O(1)
void se_sort(int q[], int n)
{
    for (int i = 0; i < n; i ++ )
    {
        int temp_i = i;
        for (int j = i; j < n; j ++ )
        {
            temp_i = q[temp_i]>q[j] ? j:temp_i;
        }
        swap(q[temp_i],q[i]);
    }
}

// 选择排序递归实现
    // 时间复杂度 O(n^2)
    // 空间复杂度 最好O(0),最差O(n)
void sort(int x[], int n, int index)
{
    if (index >= n - 1)
        return;
    else
    {
        int min = x[index], ii = index;
        for (int j = index + 1; j < n; j++)
            if (x[j] < min)
            {
                min = x[j];
                ii = j;
            }
        if (ii != index)
        {
            int t = x[index];
            x[index] = x[ii];
            x[ii] = t;
        }
    }
    sort(x, 10, index + 1);
}


// 插入排序
    // 时间复杂度
    // 最坏情况下O(n(n + 1)/2) = O(n^2)
    // 空间复杂度
    // O(1)
void ins_sort(int a[], int length)
{
    for (int i = 1; i < length; i++)
	{
		for (int j = i - 1; j >= 0 && a[j + 1] < a[j]; j--)
		{
			swap(a[j], a[j + 1]);
		}
	}
}

// 插入排序递归算法
    // 时间复杂度 O(n)
    // 空间复杂度 O(1)
void sort(int arr[],int k) {
	if(k==0) {					//递归的出口
		return;								//第一个元素不用去排序
        
    }
    sort(arr,k-1);					//对从0到倒数第二个元素排序
    int x=arr[k];					
    int index=k-1;						//设置指针
    while(index>-1&& x<arr[index]) {			//对最后一个元素进行插入
        arr[index+1]=arr[index];					//交换
        index--;
        
    }
    arr[index+1]=x;											//指针的边界
	}


// 角谷猜想
void JG()
{
    int p = 0, num = 0;
    for (int i = 1; i <= 100; i ++)
    {
        int cnt =0;
        int t = i;
        while (t != 1)
        {
            if (t % 2 == 0)
                t /= 2;
            else 
                t = 3*t + 1;
            cnt ++;
        }

        if (cnt > num)
        {
            p = i;
            num = cnt;
        }
    }
    cout << "The max is " << p << " and the number is " << num << endl;
    while (p != 1)
    {
        cout << p << ' ';
        if (p % 2 == 0)
            p /= 2;
        else 
            p = 3*p + 1;
    }
    cout << p;
}

//汉诺塔递归函数
void Hanoi(int n, char a[], char b[], char c[]) {
	if (n == 1) {
		printf("%d. from %s move to %s\n", ++hanoi_ct , a, c);		//递归截至条件
	}
	else {
		Hanoi(n - 1, a, c, b);		//将n上面的n-1个模块借助c移动到b
		printf("%d. from %s move to %s\n", ++hanoi_ct, a, c);		//将n从a移动到c
		Hanoi(n - 1, b, a, c);		//将n-1个模块从b借助a移动到c
	}
}

int main()
{
    // n = 5;
    // cout << "Init:";
    // for (int i = 0; i < 5; i ++ )
    // {
        // a[i] = 5 - i; 
        // cout << a[i];
    // }
    // cout << endl;
    
    // cout << "insert_sort:" ;
    // bubble_sort(a, n - 1);
    // se_sort(a, n);
    // ins_sort(a, n);
    // Hanoi(4, "A", "B", "C");

    // for (int i = 0; i < n; i ++ )
    //     cout << a[i] << ' ';

    JG();

    system("pause");
    return 0;
}