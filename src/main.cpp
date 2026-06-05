// Copyright 2022 NNTU-CS
#include "tree.h"
#include <cstdlib>
#include <ctime>
#include <iostream>

using namespace std;

int main() {
  setlocale(LC_ALL, "Russian");
  PMTree tree({'1', '2', '3'});

  cout << "Перестановки: ";
  auto perms = getAllPerms(tree);
  for (auto& p : perms) {
    for (char c : p) cout << c;
    cout << " ";
  }

  cout << "\ngetPerm1(1)=" << getPerm1(tree, 1)[0]
       << getPerm1(tree, 1)[1] << getPerm1(tree, 1)[2];
  cout << "\ngetPerm2(2)=" << getPerm2(tree, 2)[0]
       << getPerm2(tree, 2)[1] << getPerm2(tree, 2)[2];
  cout << "\ngetPerm1(6)=" << getPerm1(tree, 6)[0]
       << getPerm1(tree, 6)[1] << getPerm1(tree, 6)[2];
  cout << "\ngetPerm2(8) size=" << getPerm2(tree, 8).size() << "\n\n";

  cout << "n\tall\tp1\tp2\n";
  srand(time(nullptr));

  for (int n = 3; n <= 8; ++n) {
    vector<char> a;
    for (int i = 0; i < n; ++i) a.push_back('A' + i);
    PMTree t(a);

    double t1 = clock();
    getAllPerms(t);
    double all = (clock() - t1) * 1000.0 / CLOCKS_PER_SEC;

    int q = 50;
    int total = t.factorial(n);
    double sum1 = 0;
    double sum2 = 0;

    for (int i = 0; i < q; ++i) {
      int num = rand() % total + 1;

      t1 = clock();
      getPerm1(t, num);
      sum1 += (clock() - t1) * 1000.0 / CLOCKS_PER_SEC;

      t1 = clock();
      getPerm2(t, num);
      sum2 += (clock() - t1) * 1000.0 / CLOCKS_PER_SEC;
    }

    cout << n << "\t" << all << "\t" << sum1 / q << "\t" << sum2 / q << "\n";
  }

  return 0;
}
