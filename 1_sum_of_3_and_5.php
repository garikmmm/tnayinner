<?php

/**
 * If we list all the natural numbers below 10 that are multiples of 3 or 5, we get 3, 5, 6 and 9.
 * The sum of these multiples is 23.
 * Find the sum of all the multiples of 3 or 5 below 1000.
 */
function sum_of_3_and_5() {

    /*
     * Algorithmic solution
     * count of multiples of 3 = 1000 / 3 = 333;
     * count of multiples of 5 = 1000 / 5 = 199;
     *
     * sum of multiplies of 3
     * 1 * 3 + 2 * 3 + ... + 333 * 3 = 3 * (1 + ... + 333) = 3 * 333 * (333 + 1) / 2
     * sum of multiplies of 5
     * 1 * 5 + 2 * 5 + ... + 199 * 5 = 5 * (1 + ... + 199) = 5 * 199 * (199 + 1) / 2
     *
     * sum = 166833 + 99500 = 266333
     *
     */

    $sum = 0;
    for($i = 3; $i < 1000; $i += 3) {
        $sum += $i;
    }

    for($i = 5; $i < 1000; $i += 5) {
        $sum += $i;
    }

    return $sum; // 266333
}

echo sum_of_3_and_5();