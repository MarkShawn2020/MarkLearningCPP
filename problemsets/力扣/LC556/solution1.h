//
// Created by 南川 on 2021/1/14.
//

#ifndef MARKLEARNINGCPP_SOLUTION1_H
#define MARKLEARNINGCPP_SOLUTION1_H

#endif //MARKLEARNINGCPP_SOLUTION1_H

int nextGreaterElement(int n) {
    long long ans;

    stringstream ss;
    ss << n;
    string s;
    ss >> s;
    ss.clear();

    const int N = s.size();
    queue<char> Q;

    int i = N-1;
    for(; i>0 && s[i-1]>=s[i]; --i) Q.push(s[i]);
    if(i==0) return -1;
    Q.push(s[i]);

    int j = --i;
    // 从i（即j+1）开始更新从小到大的队列值
    while (Q.front()<=s[i])
    {
        s[++j] = Q.front();
        Q.pop();
    }

    // 更新i、j的值
    s[++j] = s[i]; // 关键
    s[i] = Q.front();
    Q.pop();

    // 继续更新从小到大的队列值
    while (!Q.empty())
    {
        s[++j] = Q.front();
        Q.pop();
    }

    ss << s;
    ss >> ans;
    if(ans>INT_MAX) return -1;
    return int(ans);
}

