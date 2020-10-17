class Solution {

    /**
     * @param String $s
     * @return Integer
     */
    function lengthOfLongestSubstring($s) {
        $maxCount = 0;
        $substring = '';
        $index = 0;
        while($index < strlen($s)) {
            $currentCharacter = $s[$index];
            $repeatingCharacterPositionInSubstring = strpos($substring, $currentCharacter);
            if (false === $repeatingCharacterPositionInSubstring) {
                $substring .= $currentCharacter;
            } else {
                $maxCount = $maxCount > strlen($substring) ? $maxCount : strlen($substring);
                if ($repeatingCharacterPositionInSubstring == strlen($substring) - 1) {
                    $substring = $currentCharacter;
                } else {
                    $substring = substr($substring, $repeatingCharacterPositionInSubstring + 1) . $currentCharacter;

                }
            }
            ++$index;
        }
        $maxCount = $maxCount > strlen($substring) ? $maxCount : strlen($substring);
        return $maxCount;
    }
}
