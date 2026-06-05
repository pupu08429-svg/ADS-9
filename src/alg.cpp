// Copyright 2022 NNTU-CS

#include <vector>

#include  "tree.h"

int PMTree::factorial(int n) const {
  int res = 1;
  for (int i = 2; i <= n; ++i) {
    res *= i;
  }
  return res;
}

PMTree::PMTree(const std::vector<char>& elements) {
  total_elements_ = elements.size();

  std::vector<char> sorted = elements;
  for (int i = 0; i < static_cast<int>(sorted.size()); ++i) {
    for (int j = i + 1; j < static_cast<int>(sorted.size()); ++j) {
      if (sorted[i] > sorted[j]) {
        char tmp = sorted[i];
        sorted[i] = sorted[j];
        sorted[j] = tmp;
      }
    }
  }

  root_ = new PMTreeNode('\0');
  buildTree(root_, sorted);
}

void PMTree::buildTree(PMTreeNode* node, std::vector<char> remaining) {
  if (remaining.empty()) return;

  for (int i = 0; i < static_cast<int>(remaining.size()); ++i) {
    PMTreeNode* child = new PMTreeNode(remaining[i]);
    node->children.push_back(child);

    std::vector<char> new_remaining;
    for (int j = 0; j < static_cast<int>(remaining.size()); ++j) {
      if (j != i) {
        new_remaining.push_back(remaining[j]);
      }
    }

    buildTree(child, new_remaining);
  }
}

void PMTree::collectAll(PMTreeNode* node, std::vector<char>* path,
                        std::vector<std::vector<char>>* result) {
  if (node->value == '\0') {
    for (int i = 0; i < static_cast<int>(node->children.size()); ++i) {
      collectAll(node->children[i], path, result);
    }
    return;
  }

  path->push_back(node->value);

  if (node->children.empty()) {
    result->push_back(*path);
  } else {
    for (int i = 0; i < static_cast<int>(node->children.size()); ++i) {
      collectAll(node->children[i], path, result);
    }
  }

  path->pop_back();
}

std::vector<std::vector<char>> PMTree::getAllPermutations() {
  std::vector<std::vector<char>> result;
  std::vector<char> path;
  collectAll(root_, &path, &result);
  return result;
}

void PMTree::findNth(PMTreeNode* node, std::vector<char>* path, int num,
                     int* count, std::vector<char>* result, bool* found) {
  if (*found) return;

  if (node->value == '\0') {
    for (int i = 0; i < static_cast<int>(node->children.size()); ++i) {
      if (*found) return;
      findNth(node->children[i], path, num, count, result, found);
    }
    return;
  }

  path->push_back(node->value);

  if (node->children.empty()) {
    (*count)++;
    if (*count == num) {
      *result = *path;
      *found = true;
    }
  } else {
    for (int i = 0; i < static_cast<int>(node->children.size()); ++i) {
      if (*found) break;
      findNth(node->children[i], path, num, count, result, found);
    }
  }

  path->pop_back();
}

std::vector<std::vector<char>> getAllPerms(PMTree& tree) {
  return tree.getAllPermutations();
}

std::vector<char> getPerm1(PMTree& tree, int num) {
  if (num < 1) return std::vector<char>();

  int total = tree.factorial(tree.getTotalElements());
  if (num > total) return std::vector<char>();

  std::vector<std::vector<char>> all = tree.getAllPermutations();
  if (num <= static_cast<int>(all.size())) {
    return all[num - 1];
  }

  return std::vector<char>();
}

std::vector<char> getPerm2(PMTree& tree, int num) {
  if (num < 1) return std::vector<char>();

  int total = tree.factorial(tree.getTotalElements());
  if (num > total) return std::vector<char>();

  std::vector<char> result;
  std::vector<char> path;
  int counter = 0;
  bool found = false;

  tree.findNth(tree.getRoot(), &path, num, &counter, &result, &found);
  return result;
}
