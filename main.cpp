#include <vector>
#include "gtest/gtest.h"

using namespace std;

vector<int> arr(10);

template <class T>
T order_statistics (vector<T> a, unsigned n, unsigned k)
{
	using std::swap;
	for (unsigned l=1, r=n; ; )
	{
		
		if (r <= l+1)
		{
			if (r == l+1 && a[r] < a[l])
				swap (a[l], a[r]);
			return a[k];
		}
		
		unsigned mid = (l + r) >> 1;
		swap (a[mid], a[l+1]);
		if (a[l] > a[r])
			swap (a[l], a[r]);
		if (a[l+1] > a[r])
			swap (a[l+1], a[r]);
		if (a[l] > a[l+1])
			swap (a[l], a[l+1]);

		unsigned
			i = l+1,
			j = r;
		const T
			cur = a[l+1];
		for (;;)
		{
			while (a[++i] < cur) ;
			while (a[--j] > cur) ;
			if (i > j)
				break;
			swap (a[i], a[j]);
		}

		
		a[l+1] = a[j];
		a[j] = cur;

		if (j >= k)
			r = j-1;
		if (j <= k)
			l = i;

	}
}

TEST(order_statistics, statistic){arr[0] = 4;
    arr[1] = 10;
    arr[2] = 23;
    arr[3] = 5;
    arr[4] = -5;
    arr[5] = 3;
	arr[6] = 14;
    arr[7] = 2;
    arr[8] = 22;
	arr[9] = -9;

	int k = order_statistics (arr , 9, 4);

	ASSERT_TRUE(k == 3 );
};


int main(int argc, char *argv[]){
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}