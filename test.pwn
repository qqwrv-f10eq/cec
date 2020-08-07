#include <a_samp>

#define RUN_TESTS
#include <YSI_Core\y_testing>

#include "cec.inc"

main() { }

new 
    input[144] = "นาย{FFFF00}ดีนั้นมีของดี{FFFFFF}สบายไหม", 
    output[144]
;

// ทดสอบนับวรรณยุกต์
Test:TestCountVowel()
{
    printf("vowel: %d", CE_CountVowel(input));
    ASSERT(CE_CountVowel(input) == 5);
}

// ทดสอบนับ TAG สี
Test:TestCountTag()
{
    printf("tag: %d", CE_CountTag(input));
    ASSERT(CE_CountTag(input) == 2);
}

// ทดสอบแปลงข้อความ
Test:TestConvert()
{
    CE_Convert(input, output);
    printf("output: %s", output);
    ASSERT(!strcmp(output, "นาย{FFFF00}ดีนั้นมี{FFFFFF}ของดีสบายไหม", true));
}