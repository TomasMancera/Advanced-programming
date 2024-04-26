#include <iostream>
#include <fstream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <random>

int generate_random(int lowlimit, int suplimit) {
    return lowlimit + rand() % (suplimit - lowlimit + 1);
}

void write_data(const std::string& filename) {
    std::ofstream file(filename, std::ios::app);
    if (file.is_open()) {
        for (int i = 0; i < 1048576; i++) {
            file << generate_random(0, 16383) << "\n";
        }
    }
    file.close();
}

std::pair<std::vector<int>, int> read_data(const std::string& filename) {
    std::vector<int> num_list;
    std::ifstream file(filename);
    int number, maxi = 0;

    if (file.is_open()) {
        while (file >> number) {
            num_list.push_back(number);
            if (number > maxi) {
                maxi = number;
            }
        }
    }
    return {num_list, maxi};
}

void write_sorted_data(const std::string& filename, const std::vector<int>& list) {
    std::ofstream file(filename, std::ios::app);
    if (file.is_open()) {
        for (int i : list) {
            file << i << "\n";
        }
    }
    file.close();
}

std::vector<int> count_sort(const std::vector<int>& odd_list, int maxi) {
    std::vector<int> list_count(maxi + 1, 0);
    std::vector<int> list_sorted(odd_list.size(), 0);

    for (int i : odd_list) {
        list_count[i]++;
    }

    int total = 0;
    for (int i = 0; i <= maxi; ++i) {
        int oldCount = list_count[i];
        list_count[i] = total;
        total += oldCount;
    }

    for (int index : odd_list) {
        list_sorted[list_count[index]] = index;
        list_count[index]++;
    }
    return list_sorted;
}

int main(){
  double start, end;
  start = std::clock();
  write_data("numbers.txt");
  std::pair<std::vector<int>, int> result = read_data("numbers.txt");
  std::vector<int> sorted_list = count_sort(result.first, result.second);
  write_sorted_data("sortednumbers.txt", sorted_list);
  end = std::clock();

  std::cout << "RunTime was: " << (double)(end - start) / CLOCKS_PER_SEC << " seconds" << std::endl;
  return 0;
}