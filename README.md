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


### 语法

array_merge(array1, array2, array3...)


参数 | 描述
---|---
array1 | 必需。规定数组。
array2 | 可选。规定数组。
array3 | 可选。规定数组。


### 注意

** 数组的key必须是数字 **