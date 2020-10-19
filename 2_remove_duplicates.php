<?php

function removeDuplicates(&$nums) {
    if (1 >= count($nums)) {
        return count($nums);
    }
    $previousElement = $nums[0];
    $initialCount = count($nums);
    for($index = 1; $index < $initialCount; ++$index) {
        if ($nums[$index] == $previousElement) {
            unset($nums[$index]);
        } else {
            $previousElement = $nums[$index];
        }
    }
    return count($nums);
}
$a = [0,0,1,1,1,2,2,3,3,4];
removeDuplicates($a);
print_r($a);