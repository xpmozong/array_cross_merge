### PHP数组交叉合并

    
```
    $list = ['a', 'b', 'c'];
    $list2 = ['d', 'e'];
    $list3 = ['x', 'y', 'z'];

    $arr = array_cross_merge($list, $list2, $list3);
    print_r($arr);
```

以上输出：

    
```
    Array
    (
        [0] => a
        [1] => d
        [2] => x
        [3] => b
        [4] => e
        [5] => y
        [6] => c
        [7] => z
    )
```


### 注意

** 数组的key必须是数字 **