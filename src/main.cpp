// Copyright 2022 NNTU-CS
#include "tree.h"

#include <cstdlib>
#include <ctime>
#include <iostream>
#include <vector>

int main() {
  std::setlocale(LC_ALL, "Russian");
  PMTree tree({'1', '2', '3'});

  std::cout << "Перестановки: ";
  std::vector<std::vector<char>> perms = getAllPerms(tree);
  for (std::vector<char>& p : perms) {
    for (char c : p) std::cout << c;
    std::cout << " ";
  }

  std::cout << "\ngetPerm1(1)=" << getPerm1(tree, 1)[0]
            << getPerm1(tree, 1)[1] << getPerm1(tree, 1)[2];
  std::cout << "\ngetPerm2(2)=" << getPerm2(tree, 2)[0]
            << getPerm2(tree, 2)[1] << getPerm2(tree, 2)[2];
  std::cout << "\ngetPerm1(6)=" << getPerm1(tree, 6)[0]
            << getPerm1(tree, 6)[1] << getPerm1(tree, 6)[2];
  std::cout << "\ngetPerm2(8) size=" << getPerm2(tree, 8).size() << "\n\n";

  std::cout << "n\tall\tp1\tp2\n";

  for (int n = 3; n <= 8; ++n) {
    std::vector<char> a;
    for (int i = 0; i < n; ++i) a.push_back('A' + i);
    PMTree t(a);

    std::clock_t t1 = std::clock();
    getAllPerms(t);
    double all = (std::clock() - t1) * 1000.0 / CLOCKS_PER_SEC;

    int q = 50;
    int total = t.factorial(n);
    double sum1 = 0;
    double sum2 = 0;

    for (int i = 0; i < q; ++i) {
      int num = std::rand() % total + 1;

      t1 = std::clock();
      getPerm1(t, num);
      sum1 += (std::clock() - t1) * 1000.0 / CLOCKS_PER_SEC;

      t1 = std::clock();
      getPerm2(t, num);
      sum2 += (std::clock() - t1) * 1000.0 / CLOCKS_PER_SEC;
    }

    std::cout << n << "\t" << all << "\t"
              << sum1 / q << "\t" << sum2 / q << "\n";
  }

  return 0;
}
