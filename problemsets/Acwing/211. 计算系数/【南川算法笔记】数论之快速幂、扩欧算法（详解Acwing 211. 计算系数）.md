# 【南川算法笔记】数论之快速幂、扩欧算法（详解Acwing 211. 计算系数）



![南川算法笔记-快速幂、扩欧算法.001](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/20210213_020829_817549-%E5%8D%97%E5%B7%9D%E7%AE%97%E6%B3%95%E7%AC%94%E8%AE%B0-%E5%BF%AB%E9%80%9F%E5%B9%82%E3%80%81%E6%89%A9%E6%AC%A7%E7%AE%97%E6%B3%95.001.jpeg)

![南川算法笔记-快速幂、扩欧算法.002](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/20210213_020829_817525-%E5%8D%97%E5%B7%9D%E7%AE%97%E6%B3%95%E7%AC%94%E8%AE%B0-%E5%BF%AB%E9%80%9F%E5%B9%82%E3%80%81%E6%89%A9%E6%AC%A7%E7%AE%97%E6%B3%95.002.jpeg)

![南川算法笔记-快速幂、扩欧算法.003](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/20210213_020829_817529-%E5%8D%97%E5%B7%9D%E7%AE%97%E6%B3%95%E7%AC%94%E8%AE%B0-%E5%BF%AB%E9%80%9F%E5%B9%82%E3%80%81%E6%89%A9%E6%AC%A7%E7%AE%97%E6%B3%95.003.jpeg)

![南川算法笔记-快速幂、扩欧算法.004](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/20210213_020829_817930-%E5%8D%97%E5%B7%9D%E7%AE%97%E6%B3%95%E7%AC%94%E8%AE%B0-%E5%BF%AB%E9%80%9F%E5%B9%82%E3%80%81%E6%89%A9%E6%AC%A7%E7%AE%97%E6%B3%95.004.jpeg)

![南川算法笔记-快速幂、扩欧算法.005](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/20210213_020829_817504-%E5%8D%97%E5%B7%9D%E7%AE%97%E6%B3%95%E7%AC%94%E8%AE%B0-%E5%BF%AB%E9%80%9F%E5%B9%82%E3%80%81%E6%89%A9%E6%AC%A7%E7%AE%97%E6%B3%95.005.jpeg)

![南川算法笔记-快速幂、扩欧算法.006](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/20210213_020829_817525-%E5%8D%97%E5%B7%9D%E7%AE%97%E6%B3%95%E7%AC%94%E8%AE%B0-%E5%BF%AB%E9%80%9F%E5%B9%82%E3%80%81%E6%89%A9%E6%AC%A7%E7%AE%97%E6%B3%95.006.jpeg)

![南川算法笔记-快速幂、扩欧算法.007](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/20210213_020829_817521-%E5%8D%97%E5%B7%9D%E7%AE%97%E6%B3%95%E7%AC%94%E8%AE%B0-%E5%BF%AB%E9%80%9F%E5%B9%82%E3%80%81%E6%89%A9%E6%AC%A7%E7%AE%97%E6%B3%95.007.jpeg)

![南川算法笔记-快速幂、扩欧算法.008](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/20210213_020829_817521-%E5%8D%97%E5%B7%9D%E7%AE%97%E6%B3%95%E7%AC%94%E8%AE%B0-%E5%BF%AB%E9%80%9F%E5%B9%82%E3%80%81%E6%89%A9%E6%AC%A7%E7%AE%97%E6%B3%95.008.jpeg)

![南川算法笔记-快速幂、扩欧算法.009](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/20210213_020829_817662-%E5%8D%97%E5%B7%9D%E7%AE%97%E6%B3%95%E7%AC%94%E8%AE%B0-%E5%BF%AB%E9%80%9F%E5%B9%82%E3%80%81%E6%89%A9%E6%AC%A7%E7%AE%97%E6%B3%95.009.jpeg)