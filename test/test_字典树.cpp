const int N = 20;

struct Trie {
  int next[N][26], cnt=0;
  bool exist[N];  // 该结点结尾的字符串是否存在

  void insert(const char *s, int l) {  // 插入字符串
    int p = 0;
    for (int i = 0; i < l; i++) {
      int c = s[i] - 'a';
      if (!next[p][c]) next[p][c] = ++cnt;  // 如果没有，就添加结点
      p = next[p][c];
    }
    exist[p] = 1;
  }
  bool find(const char *s, int l) {  // 查找字符串
    int p = 0;
    for (int i = 0; i < l; i++) {
      int c = s[i] - 'a';
      if (!next[p][c]) return 0;
      p = next[p][c];
    }
    return exist[p];
  }
};


int main()
{
    Trie t;
    t.insert("a", 1);
    t.insert("acd", 3);
    t.insert("ba", 2);
    t.insert("bba", 3);

    t.find("ba", 2);
    t.find("ac", 2);
    return 0;
}