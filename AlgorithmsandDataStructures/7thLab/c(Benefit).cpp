#include <fstream>
#include <algorithm>

using namespace std;

struct cond {
	double price;
	int cost, amount;
};

cond a[7];

bool sortx(cond fi, cond se) {
	return fi.price < se.price;
}

int cheapest(int i, int n) {
	if (!n) return 0;
	return (n / a[i].amount) * a[i].cost + min(a[i].cost, cheapest(i + 1, n % a[i].amount));
}

int main() {
    ifstream in;
	in.open("printing.in");
	ofstream out;
	out.open("printing.out");
	int n;
	in >> n;
	int quantity = 1;
	for (short i = 0; i < 7; ++i) {
		in >> a[i].cost;
		a[i].price = 1.0 * a[i].cost / quantity;
		a[i].amount = quantity;
		quantity *= 10;
	}
	sort(a, a + 7, sortx);
	out << cheapest(0, n);
	in.close();
	out.close();
}
	
	
