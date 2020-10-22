<?php
function intToRoman($num) {
    $result = '';
    $powerOf10 = 1;
    $stringNum = strval($num);
    $length = strlen($stringNum);
    for($i = 0; $i < $length; ++$i) {
        $symbol = $stringNum[$length - $i -1];
        $roman = digitToRoman($symbol, $powerOf10);
        $result = $roman . $result;
        $powerOf10 *= 10;
    }

    return $result;
}

function digitToRoman($digit, $powerOf10) {
    $nominalMap = [
        1       => 'I',
        5       => 'V',
        10      => 'X',
        50      => 'L',
        100     => 'C',
        500     => 'D',
        1000    => 'M',
    ];
    $number = $digit * $powerOf10;
    $oneValue = $powerOf10;
    $lesserValue = 0;
    $greaterValue = 0;
    foreach($nominalMap as $value => $romanSymbol) {
        if ($number >= $value) {
            $lesserValue = $value;
        } else {
            $greaterValue = $value;
            break;
        }
    }
    $oneNominal = $nominalMap[$oneValue];
    $lesserNominal = $nominalMap[$lesserValue];
    $greaterNominal = $nominalMap[$greaterValue];
    $result = '';
    if ($digit == 4 || $digit == 9) {
        $result = $oneNominal . $greaterNominal;
    } elseif ($digit < 5) {
        for($i = 0; $i < $digit; ++$i) {
            $result .= $lesserNominal;
        }
    } elseif ($digit > 5) {
        $result = $lesserNominal;
        for($i = 0; $i < $digit - 5; ++$i) {
            $result .= $oneNominal;
        }
    } else {
        $result = $lesserNominal;
    }

    return $result;
}

var_dump(intToRoman(58));