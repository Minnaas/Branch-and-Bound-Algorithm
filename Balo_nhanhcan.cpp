#include<iostream>
using namespace std;
struct Object {
	int Weight;
	int value;
	float Key; //dùng để làm giá trị so sánh giữa các loại được tính= weight/value; 
	char Type; // loại (A,B,C)...
};
int MAX_weight = INT_MIN;
int Result[50];
//Merge Sort 
void Merge(Object  arr[], int mid, int left, int right) {
	int pos_l = left;
	int pos_r = mid + 1;
	Object* Temp = new Object[right - left + 1];
	int pos = 0;
	while (pos_l <= mid && pos_r <= right) {
		if (arr[pos_l].Key > arr[pos_r].Key) {
			Temp[pos++] = arr[pos_l];
			pos_l++;
		}
		else {
			Temp[pos++] = arr[pos_r];
			pos_r++;
		}
	}
	while (pos_l <= mid) {
		Temp[pos++] = arr[pos_l];
		pos_l++;
	}
	while (pos_r <= right) {
		Temp[pos++] = arr[pos_r];
		pos_r++;
	}
	for (int i = right; i >= left; i--) {
		arr[i] = Temp[pos - 1];
		pos--;
	}
	delete[] Temp;
}
void MergeSort(Object arr[], int left, int right)
{
	if (left < right) {
		int mid = (left + right) / 2;
		MergeSort(arr, left, mid);
		MergeSort(arr, mid + 1, right);
		Merge(arr, mid, left, right);
	}
}
void Solved(int i, int n, int weight, int TGT, Object a[], int Temp[])
{
	if (i == n || weight == 0) //xét đến đồ vật cuối cùng, cập nhật Weight max 
	{
		MAX_weight = TGT;
		for (int z = 0; z < i; z++) {
			Result[a[z].Type - 65] = Temp[a[z].Type - 65];
		}
		return;
	}
	int max_numobject = weight / a[i].Weight; // số lượng tối đa của mỗi loại đồ vật 
	for (int j = max_numobject; j >= 0; j--)
	{
		TGT += j * a[i].value; // tổng giá trị = số lượng * giá trị của mỗi loại 
		weight -= j * a[i].Weight; // trọng lượng còn lại
		float upper_bound = TGT + a[i + 1].Key * weight;// cận dùng để kiểm tra cắt tỉa
		if (upper_bound > MAX_weight)
		{
			Temp[a[i].Type - 65] = j;//Lưu số lượng đồ vật của mỗi loại
			Solved(i + 1, n, weight, TGT, a, Temp);
		}
		TGT -= j * a[i].value; //Sau khi đệ quy thì cập nhật lại để xét cho đk tiếp theo
		weight += j * a[i].Weight;//
	}
}
int main()
{
	int n; // so loại đồ vật
     cin >> n;
	Object* a = new Object[n+1];
	char x; // loại (A,B,C)
	int y, z; // lần lượt là trọng lượng và giá trị ứng với mỗi loại
	for (int i = 0; i < n; i++)
	{
		cin >> x >> y >> z;
	
		if (97 <=x && x <= 122)
		{
			x = x - 32;
		}
		a[i].Type = x;
		a[i].Weight = y;
		a[i].value = z;
		a[i].Key = float(z) / y; 
	}
	a[n].Key = 0;//Xét với đồ vật cuối. 
	MergeSort(a, 0, n - 1); // Sap xep theo don gia tang dan với đơn giá = giá trị/ trọng lượng 
	int Weight;
	cin >> Weight;
	int* Temp = new int[n]; //Dùng để luư kết quả tạm thời
	Solved(0, n, Weight, 0, a, Temp);
	cout << "Value max: "<<MAX_weight<<endl;
	for (int i = 0; i < n; i++)
	{
		cout <<char(i+65)<<": "<< Result[i] << "\n";
	}
}