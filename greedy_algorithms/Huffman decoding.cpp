// 由于代码过长，这里只给出了部分代码，完整代码请参考相关教程或书籍。
struct MinHeapNode {
    char data;
    unsigned freq;
    MinHeapNode* left, * right;
};

void decode_file(struct MinHeapNode* root, string s) {
    string ans = "";
    struct MinHeapNode* curr = root;
    for (int i = 0; i < s.size(); i++) {
        if (s[i] == '0')
            curr = curr->left;
        else
            curr = curr->right;

        if (curr->left == NULL and curr->right == NULL) {
            ans += curr->data;
            curr = root;
        }
    }
    cout << ans << endl;
}

int main() {
    // 请根据实际情况添加边和顶点
    return 0;
}
