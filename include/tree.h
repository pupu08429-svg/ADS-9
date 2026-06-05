// Copyright 2022 NNTU-CS
#ifndef INCLUDE_TREE_H_
#define INCLUDE_TREE_H_
#include <vector>

struct PMTreeNode {
  char value;
  std::vector<PMTreeNode*> children;

  explicit PMTreeNode(char v) : value(v) {}

  ~PMTreeNode() {
    for (PMTreeNode* child : children) delete child;
  }
};

class PMTree {
 public:
  explicit PMTree(const std::vector<char>& elements);
  ~PMTree() { delete root_; }

  PMTreeNode* getRoot() { return root_; }
  int getTotalElements() const { return total_elements_; }
  int factorial(int n) const;
  void findNth(PMTreeNode* node, std::vector<char>* path, int num,
               int* count, std::vector<char>* result, bool* found);
  std::vector<std::vector<char>> getAllPermutations();

 private:
  void buildTree(PMTreeNode* node, std::vector<char> remaining);
  void collectAll(PMTreeNode* node, std::vector<char>* path,
                  std::vector<std::vector<char>>* result);

  PMTreeNode* root_;
  int total_elements_;
};

std::vector<std::vector<char>> getAllPerms(PMTree& tree);
std::vector<char> getPerm1(PMTree& tree, int num);
std::vector<char> getPerm2(PMTree& tree, int num);

#endif  // INCLUDE_TREE_H_
