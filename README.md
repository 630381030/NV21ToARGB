### 使用

- 1.连接Android手机
- 2.打开USB调试
- 3.执行run.sh

如果没有错误，会得到转换后的文件 **640x480.argb**

可以用**ffplay**预览

```sh
ffplay -f rawvideo -pixel_format bgra -s 640x480 640x480.argb
```
