#include "bitset.h"
#include <chrono>
#include <vector>
#include <iomanip>

void test() {
	bitset<32> bs;
	bitset<32> cp_bs;

	while (true) {
		std::cout << "1. Bitset status" << std::endl;
		std::cout << "2. Test bit" << std::endl;
		std::cout << "3. Flip bit" << std::endl;
		std::cout << "4. Set bit" << std::endl;
		std::cout << "5. Reset bit" << std::endl;
		std::cout << "6. Print string" << std::endl;
		std::cout << "7. Print ulong" << std::endl;
		std::cout << "8. Print ullong" << std::endl;
		std::cout << "9. Shift left" << std::endl;
		std::cout << "10. Shift right" << std::endl;
		std::cout << "11. Invert bitset" << std::endl;
		std::cout << "12. Compare equal" << std::endl;
		std::cout << "13. Compare not equal" << std::endl;
		std::cout << "0. Exit" << std::endl;
		std::cout << "> ";

		int option = 0, subopt = 0;
		std::cin >> option;
		std::cout << std::endl;

		switch (option) {
		case 1:
			std::cout << "=== Bitset Status ===" << std::endl;
			std::cout << "ALL: " << bs.all() << std::endl;
			std::cout << "ANY: " << bs.any() << std::endl;
			std::cout << "NONE: " << bs.none() << std::endl;
			std::cout << "COUNT: " << bs.count() << std::endl;
			std::cout << "SIZE: " << bs.size() << std::endl;
			std::cout << std::endl;
			break;
		case 2:
			std::cout << "=== Test Bit ===" << std::endl;
			std::cout << "Enter bit number: ";
			std::cin >> subopt;
			std::cout << "TEST: " << bs.test(subopt) << std::endl;
			std::cout << std::endl;
			break;
		case 3:
			std::cout << "=== Flip Bit ===" << std::endl;
			std::cout << "Enter bit number: ";
			std::cin >> subopt;
			bs.flip(subopt);
			std::cout << "FLIP: " << bs.to_string() << std::endl;
			std::cout << std::endl;
			break;
		case 4:
			std::cout << "=== Set Bit ===" << std::endl;
			std::cout << "Enter bit number: ";
			std::cin >> subopt;
			bs.set(subopt);
			std::cout << "SET: " << bs.to_string() << std::endl;
			std::cout << std::endl;
			break;
		case 5:
			std::cout << "=== Reset Bit ===" << std::endl;
			std::cout << "Enter bit number: ";
			std::cin >> subopt;
			bs.reset(subopt);
			std::cout << "RESET: " << bs.to_string() << std::endl;
			std::cout << std::endl;
			break;
		case 6:
			std::cout << "=== Print String ===" << std::endl;
			std::cout << bs.to_string() << std::endl;
			std::cout << std::endl;
			break;
		case 7:
			std::cout << "=== Print Ulong ===" << std::endl;
			std::cout << bs.to_ulong() << std::endl;
			std::cout << std::endl;
			break;
		case 8:
			std::cout << "=== Print Ullong ===" << std::endl;
			std::cout << bs.to_ullong() << std::endl;
			std::cout << std::endl;
			break;
		case 9:
			std::cout << "=== Shift Left ===" << std::endl;
			std::cout << "Enter shift size: ";
			std::cin >> subopt;
			bs <<= subopt;
			std::cout << bs.to_string() << std::endl;
			std::cout << std::endl;
			break;
		case 10:
			std::cout << "=== Shift Right ===" << std::endl;
			std::cout << "Enter shift size: ";
			std::cin >> subopt;
			bs >>= subopt;
			std::cout << bs.to_string() << std::endl;
			std::cout << std::endl;
			break;
		case 11:
			std::cout << "=== Invert ===" << std::endl;
			bs.flip();
			std::cout << "INVERT: " << bs.to_string() << std::endl;
			std::cout << std::endl;
			break;
		case 12:
			std::cout << "=== Compare Equality ===" << std::endl;
			cp_bs.reset();
			cp_bs |= bs;
			std::cout << "ORIG: " << bs.to_string() << std::endl;
			std::cout << "COPY: " << cp_bs.to_string() << std::endl;
			std::cout << "IS EQUAL: " << (bs == cp_bs) << std::endl;
			std::cout << std::endl;
			break;
		case 13:
			std::cout << "=== Compare Inequality ===" << std::endl;
			cp_bs.reset();
			cp_bs |= bs;
			cp_bs.flip(0);
			std::cout << "ORIG: " << bs.to_string() << std::endl;
			std::cout << "COPY: " << cp_bs.to_string() << std::endl;
			std::cout << "IS INEQUAL: " << (bs != cp_bs) << std::endl;
			std::cout << std::endl;
			break;
		case 0:
			return;
		default:
			std::cout << "Wrong option!" << std::endl;
			std::cout << std::endl;
			break;
		}
	}
}

template<size_t N>
double time() {
	bitset<N> bs;

	auto start = std::chrono::high_resolution_clock::now();

	bs.set(N / 2 * 1.5);

	auto end = std::chrono::high_resolution_clock::now();

	std::chrono::duration<double, std::milli> res = end - start;
	return res.count();
}

int main(int argc, char* argv[]) {
	
	if (argc != 2)
		throw (std::invalid_argument("1 argument expected"));

	if (strcmp(argv[1], "test") == 0) {
		test();
	} else if (strcmp(argv[1], "time") == 0) {
		std::vector<size_t> sizes = { 100000, 200000, 300000, 400000, 500000, 600000, 700000, 800000, 900000, 1000000 };

		for (size_t size : sizes) {
			double res = 0;
			for (int i = 0; i < 100; i++) {
				switch (size) {
				case 100000: res += time<100000>(); break;
				case 200000: res += time<200000>(); break;
				case 300000: res += time<300000>(); break;
				case 400000: res += time<400000>(); break;
				case 500000: res += time<500000>(); break;
				case 600000: res += time<600000>(); break;
				case 700000: res += time<700000>(); break;
				case 800000: res += time<800000>(); break;
				case 900000: res += time<900000>(); break;
				case 1000000: res += time<1000000>(); break;
				}
			}
			std::cout << std::fixed;
			std::cout << std::setprecision(6);
			std::cout << size << " " << res / 100 << std::endl;
		}
	} else {
		std::cout << "No " << argv[1] << " parameter" << std::endl;
	}

	system("pause");
	return 0;
}
