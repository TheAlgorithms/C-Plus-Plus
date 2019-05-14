//Bubble Sort

#include<iostream>
#include<vector>
using namespace std;

int main()
{
	int n;
	short swap_check=0;
  	cout << "Enter the amount of numbers to sort: ";
	cin >> n;
	vector<int> numbers;
	cout << "Enter " << n << " numbers: ";
	int num;

  	//Input
	for(int i=0; i<n; i++)
	{
		cin >> num;
		numbers.push_back(num);
	}

	//Bubble Sorting
	for(int i=0; i<n; i++)
	{
	    swap_check=0;
		
		for(int j=0; j<n-1-i; j++)
		{
			if(numbers[j]>numbers[j+1])
			{
				swap_check=1;
				swap(numbers[j], numbers[j+1]); //swap yer değiştirme demektir. Yani j. sayi, j+1. sayıdan büyükse yer değiştir anlamındadır.
			}
		}
		if(swap_check == 0)
		{	
			break;
		}
	}

	//Output
	cout<<"\nSorted Array : ";
	for(int i=0; i<numbers.size(); i++)
	{
		if(i != numbers.size() -1)
		{
			cout << numbers[i] << ", ";
		}else
		{
			cout << numbers[i] << endl;
		}
	}
  return 0;
}

/*
Bubble sort algoritmasının çalışma prensibi:

Bubble sort algoritmasının türkçesi kabarcık sıralama algoritmasıdır. Kabarcık denmesinin en önemli sebebi bu algoritmada en büyük sayının en sona atılmasıdır. 
Tüm mantığını bunun üzerinedir.
Her iterasyonda en büyük sayı sona atılır ve iterasyonlar tamamlandığında sıralama gerçekleşmiş olur.

Swap Ne Demektir?

Yazılımda Swap demek iki değişkenin yer değiştirmesi demektir. 
Bu işlem için ek bir değişkene ihtiyaç duyulur. x = 5, y = 10 olsun.
Biz istiyoruz ki x = 10, y = 5 olsun. İşte bunu yapmak için en bir değişken oluştururuz.

int z;
z = x;
x = y;
y = z;

Yukarıdaki işlem tipik bir yer değiştirme işlemidir. 
x değerine y’yi atayınca x’in eski değeri kaybolur. 
Bu yüzden biz z diye bir değişken oluşturup ilk başka x değerini orada sakladık, en son olarak da y’ye atadık.

Bubble Sort Algoritma Analizi (Best Case – Worst Case – Avarage Case) En iyi Durum – En Kötü Durum:
 
Bubble Sort En Kötü Durum (Worst Case) Performansı O(n²) şeklindedir. Neden? Çünkü Big O Notasyonu yazımızdan hatırlarsanız iç içe döngülerde algoritma karmaşıklığı hesaplarken döngülerin çarpımını alıyorduk. 
n * (n – 1) çarpımı üzerinden bize yine O(n²) performansı gelir. En kötü durumda döngünün tüm adımları gerçekleşecektir.
Bubble Sort Ortalama Durum (Avarage Case) Performansı. Bubble Sort optimal bir algoritma değildir. 
ortalama durumda da O(n²) performansı alınmaktadır.
Bubble Sort En iyi Durum (Best Case) Performansı. O(n) şeklindedir. 
Ancak yukarıda paylaştığımız kodda en iyi durumu elde edemezsiniz. İyileştirilmiş bubble sort algoritması üzerinde bu durum gerçekleşir. Hemen aşağıda bulunmakta.
*/
