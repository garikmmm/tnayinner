<?php

$limit = 4000000;

$last1 = 2;
$last2 = 1;
$current = 3;
$sum = 2;
do  {
    $last2 = $last1;
    $last1 = $current;
    $current = $last1 + $last2;
    if (($current % 2) === 0 && $current < $limit) {
        $sum += $current;
    }
} while($current < $limit);

print_r($sum);