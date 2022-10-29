#include <iostream>
#include <queue>
#include <map>
#include <random>
#include <stack>
#include <vector>

struct Node {
  uint32_t left;
  uint32_t right;
  std::vector<Node*> links;
  Node* link;
  Node* father;

  Node(uint32_t left_, uint32_t right_, Node *father_=nullptr) {
    left = left_;
    right = right_; 
    father = father_;
    link = nullptr;
    links.resize(26);
  }
};

struct State {
  Node* node;
  uint32_t pos;

  State(Node* node_, uint32_t pos_) : node(node_), pos(pos_) {}
  uint32_t ind() {
    return node->left + pos;
  }
};

struct Ans {
  uint32_t v1, v2, l, r;

  Ans(uint32_t a, uint32_t b, uint32_t c, uint32_t d) : v1(a), v2(b), l(c), r(d) {}
  bool operator!=(const Ans &o) const {
    return v1 != o.v1 || v2 != o.v2 || l != o.l || r != o.r;
  }
};

class SuffixTree {
  public:
    SuffixTree(const std::string &s);
    State move_to_suffix(State state);
    Node *root;
    ~SuffixTree();
  private: 
    std::string _str;

    State split_node(State state);
    State go(State state, uint32_t len, uint32_t ind); 
};

State SuffixTree::split_node(State state) {
  Node* node = state.node;
  uint32_t pos = state.pos;
  Node* new_node = new Node(node->left, node->left + pos, node->father);
  node->father->links[_str[node->left] - 'a'] = new_node;
  node->left += pos;
  new_node->links[_str[node->left] - 'a'] = node;
  node->father = new_node;
  return State(new_node, pos);
}

State SuffixTree::go(State state, uint32_t len, uint32_t ind) {
  while (len > 0) {
    if (state.ind() + len <= state.node->right) {
      state.pos += len;
      break;
    }
    len -= state.node->right - state.ind();
    ind += state.node->right - state.ind();
    state.node = state.node->links[_str[ind] - 'a'];
    state.pos = 0;
  }
  return state;
}

State SuffixTree::move_to_suffix(State state) {
  uint32_t up = (state.node->father == root ? 1 : 0);
  if (state.node->link != nullptr) {
    return go(State(state.node->link, 0), state.pos - up, state.node->left + up);
  }
  if (state.node == root) {
    return State(root, 0);
  }
  State suf = move_to_suffix(State(state.node->father, state.node->father->right - state.node->father->left));
  suf = go(suf, state.pos - up, state.node->left + up);
  if (state.pos != 0 && state.node->right == state.pos) {
    if (suf.pos != suf.node->right - suf.node->left) {
      suf = split_node(suf);
    }
    state.node->link = suf.node;
  }
  return suf;
}

SuffixTree::SuffixTree(const std::string &s) {
  _str = s;
  root = new Node(0, 0);
  State state(root, 0);
  uint32_t len = 0;
  for (uint32_t pos = 0; pos < _str.size(); ++pos) {
    while (true) {
      if (state.ind() < state.node->right) {
        if (state.ind() == pos) {
          state = move_to_suffix(state);
          continue;
        }
        if (_str[pos] == _str[state.ind()]) {
          ++state.pos;
          break;
        }
        state = split_node(state);
        state.node->links[_str[pos] - 'a'] =  new Node(pos, INT32_MAX, state.node);
        state = move_to_suffix(state);
        continue;
      }
      if (state.node->links[_str[pos] - 'a'] == nullptr) {
        state.node->links[_str[pos] - 'a'] = new Node(pos, UINT32_MAX, state.node);
        state = move_to_suffix(state);
        continue;
      }
      state.node = state.node->links[_str[pos] - 'a'];
      state.pos = 1;
      break;
    }
  }
}

SuffixTree::~SuffixTree() {
  std::stack<Node*> s;
  std::queue<Node*> q;
  q.push(root);
  while (!q.empty()) {
    s.push(q.front());
    q.pop();
    for (Node *node : s.top()->links) {
      if (node != nullptr) {
        q.push(node);
      }
    }
  }
  while (!s.empty()) {
    delete s.top();
    s.pop();
  }
}

std::vector<Ans> solve(const std::string &str) {
  SuffixTree suf(str);
  int k = 2;
  std::queue<std::pair<Node*, int> > q;
  q.emplace(suf.root, 1);
  std::vector<Ans> ans;
  while (!q.empty()) {
    int j = q.front().second;
    Node* node = q.front().first;
    q.pop();
    for (int i = 0; i < 26; ++i) {
      if (node->links[i] != nullptr) {
        ans.emplace_back(j, k, node->links[i]->left + 1, std::min(node->links[i]->right, (uint32_t) str.length()));
        q.emplace(node->links[i], k);
        ++k;
      }
    }
  }
  return ans;
}

std::vector<Ans> brute(const std::string &str) {
  std::vector<std::map<char, uint32_t> > v(1);
  std::vector<uint32_t> w(1);
  for (uint32_t i = 0; i < str.size(); ++i) {
    uint32_t node = 0;
    for (uint32_t j = i; j < str.size(); ++j) {
      if (v[node].find(str[j]) == v[node].end()) {
        v[node][str[j]] = v.size();
        v.emplace_back();
        w.push_back(j + 1);
      }
      node = v[node][str[j]];
    }
  }
  std::queue<uint32_t> q;
  std::queue<uint32_t> nodes;
  std::vector<Ans> ans;
  uint32_t i = 2;
  q.push(1);
  nodes.push(0);
  while (!q.empty()) {
    uint32_t j = q.front();
    q.pop();
    uint32_t node = nodes.front();
    nodes.pop();
    for (auto e : v[node]) {
      uint32_t pos = e.second;
      uint32_t l = w[pos];
      uint32_t r = l;
      while (v[pos].size() == 1) {
        ++r;
        pos = v[pos].begin()->second;
      }
      ans.emplace_back(j, i, l, r);
      if (!v[pos].empty()) {
        q.push(i);
        nodes.push(pos);
      }
      ++i;
    }
  }
  return ans;
}

void output(const std::vector<Ans> &ans) {
  std::cout << ans.size() + 1 << " " << ans.size() << std::endl;
  for (auto i : ans) {
    std::cout << i.v1 << " " << i.v2 << " " << i.l << " " << i.r << std::endl;
  }
}

void test() {
  std::mt19937 gen(42);
  while(true) {
    uint32_t len = std::uniform_int_distribution<>(1, 1000)(gen);
    std::string str = "";
    for (uint32_t i = 0; i < len; ++i) {
      str += std::uniform_int_distribution<>('a', 'z')(gen);
    }
    auto ans1 = brute(str);
    auto ans2 = solve(str);
    if (ans1.size() != ans2.size()) {
      std::cout << "FAIL\n";
      std::cout << str << std::endl;
      output(ans1);
      output(ans2);
      return;
    }
    for (uint32_t i = 0; i < ans1.size(); ++i) {
      if (ans1[i] != ans2[i]) {
        std::cout << "FAIL\n";
        std::cout << str << std::endl;
        output(ans1);
        output(ans2);
        return;
      }
    }
    std::cout << "OK" << std::endl;
  }
}

void work() {
  std::ios_base::sync_with_stdio(false);
  std::string str;
  std::cin >> str;
  output(solve(str));
}

int main() {
  test();
//  work();
  return 0;
}
