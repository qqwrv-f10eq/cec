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

/*
    // Required: YSI-Server/y_colours

    // ทดสอบชุด 1
    ShowPlayerDialog(
        playerid,
        0,
        DIALOG_STYLE_MSGBOX,
        "ก ไก่",
        "FIREBRICK"คำที่มักเขียนผิด   "FORESTGREEN"คำที่เขียนถูก "WHITE"หมายเหตุ\n\
        กงกำกงเกวียน   กงเกวียนกำเกวียน   "ORANGE"กง "WHITE"และ "ORANGE"กำ "WHITE"เป็นส่วนประกอบของล้อเกวียน\n\
        กงศุล   กงสุล\n\
        กฏ   กฎ   กฎ ทุกอย่าง ใช้ ฎ ชฎา เช่น กฎหมาย ยกเว้น ปรากฏ ใช้ ฏ ปฏัก\n\
        "SLATEBLUE"กบฎ"WHITE", กบถ  กบฏ   ถ้าออกเสียง \""INDIANRED"ขะ-บด"WHITE"\" เขียน \""INDIANRED"ขบถ"WHITE"\"\n\
        กระพริบ    กะพริบ\n\
        กระแนะกระแหน    กระแหนะกระแหน    พูดกระทบหรือพูดเป็นเชิงเสียดสี\n\
        กริยา    กิริยา    \""INDIANRED"กิริยา"WHITE"\" คือ อาการ การกระทำ เช่น ปฏิกิริยา\n\
        กิริยา    กริยา    \""INDIANRED"กริยา"WHITE"\" ("ORANGE"กฺริ-"WHITE") คือ "ORANGE"คำชนิดหนึ่ง "WHITE"บอกอาการ การกระทำ เช่น "RED"เดิน "GREEN"วิ่ง "BLUE"เขียน "BLACK"เหล่านี้ "ORANGE"คือ"WHITE" "TOMATO"คำกริยา"WHITE"\n\
        "SLATEBLUE"กรีธา"WHITE", กรีทา    กรีฑา    กีฬาประเภทหนึ่ง\n\
        กรีฑา    กรีธา    เคลื่อน ยก เดินเป็นหมู่หรือเป็นกระบวน เช่น กรีธาทัพ\n\
        กเลวราก    กเฬวราก\n\
        กระโหลก    กะโหลก    จำไว้ว่า กะโหลก กะลา\n\
        กลาสี    กะลาสี    เขียนเรียงพยางค์ปกติ\n\
        "SLATEBLUE"กอร์ป"WHITE", กอปร์    กอปร    "YELLOW"อ่านว่า"WHITE" \""INDIANRED"กอบ"WHITE"\"\n\
        กังวาล    กังวาน\n\
        กานเวลา    กาลเวลา    กาล หมายถึง เวลา\n\
        กาละเทศะ    กาลเทศะ\n\
        กำเหน็ด    กำเหน็จ\n\
        กิติมศักดิ์    กิตติมศักดิ์    "YELLOW"อ่านว่า"WHITE" \""INDIANRED"กิด-ติ-มะ-สัก"WHITE"\"\n\
        กินนรี    กินรี    แต่ \""INDIANRED"กิน-นอน"WHITE"\" เขียน 'กินนร'\n\
        "SLATEBLUE"กุฎ"WHITE", กุฎิ    "SLATEBLUE"กุฎี"WHITE", กุฏิ    \""INDIANRED"กุฏิ"WHITE"\" "YELLOW"อ่านว่า"WHITE" \""INDIANRED"กุด"WHITE"\" หรือ \""INDIANRED"กุด-ติ"WHITE"\" , ถ้าต้องการอ่าน \""INDIANRED"กุ-ดี"WHITE"\" ต้องเขียน \""INDIANRED"กุฎี"WHITE"\" (ใช้คำไหนก็ได้)\n\
        เกียรติ์    เกียรติ    "YELLOW"อ่านว่า"WHITE" \""INDIANRED"เกียด"WHITE"\", ถ้าเขียน \""INDIANRED"เกียรติ์"WHITE"\" "YELLOW"อ่านว่า"WHITE" \""INDIANRED"เกียน"WHITE"\" เช่น รามเกียรติ์ "FORESTGREEN"จบ"WHITE"แล้ว\
    ",
        "ตกลง",
        ""
    );

*/