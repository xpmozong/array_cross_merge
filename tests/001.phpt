--TEST--
Check for array_cross_merge presence
--SKIPIF--
<?php if (!extension_loaded("array_cross_merge")) print "skip"; ?>
--FILE--
<?php
/*
    you can add regression tests for your extension here

  the output of your test code has to be equal to the
  text in the --EXPECT-- section below for the tests
  to pass, differences between the output and the
  expected text are interpreted as failure

    see php5/README.TESTING for further information on
  writing regression tests
*/

$list = ['a', 'b', 'c'];
$list2 = ['d', 'e'];
$list3 = ['x', 'y', 'z'];

$arr = array_cross_merge($list, $list2, $list3);
print_r($arr);

?>
--EXPECT--
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