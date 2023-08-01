# Item 31: 避免使用默认捕获模式

- 默认的按引用捕获可能会导致悬空引用。
- 默认的按值捕获对于悬空指针很敏感（尤其是this指针），并且它会误导人产生lambda是独立的想法。