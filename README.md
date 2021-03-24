# Color Embed Converter

[![Build status](https://ci.appveyor.com/api/projects/status/l1943xkew40t4rcv/branch/master?svg=true)](https://ci.appveyor.com/project/aktah/cec/branch/master) [![Build Status](https://travis-ci.org/aktah/cec.svg?branch=master)](https://travis-ci.org/aktah/cec) ![License: MIT](https://img.shields.io/badge/License-MIT-red.svg)

ปลั๊กอิน CEC ช่วยเลื่อนแท็กสีให้แสดงผลได้อย่างถูกต้อง

## การติดตั้ง

หากคุณเป็นผู้ใช้ sampctl

`sampctl p install aktah/cec`

#### หรือ
* โหลดไฟล์ที่เข้ากับระบบปฏิบัติการของคุณ (Windows หรือ Linux)
* ใส่มันลงไปที่โฟลเดอร์ `plugins`
* เพิ่ม `cec` ที่ server.cfg หรือ `cec.so` (สำหรับ Linux)
* นำไฟล์ [cec.inc](cec.inc) ใส่ในโฟลเดอร์ Includes ของคุณ

## การบิ้ว (ใครที่ไม่ได้จะนำไปพัฒนาต่อข้ามไปได้เลย)

* ติดตั้ง [sampctl](https://github.com/Southclaws/sampctl) เพื่อใช้ในการทดสอบ

* โคลนที่เก็บไฟล์

	`git clone https://github.com/aktah/cec.git`

* ใช้ makefile เพื่อคอมไพและทดสอบ (ควรมี cmake เวอร์ชั่นที่ไม่ต่ำกว่า 3.0) 

	* เพื่อเตรียมไฟล์สำหรับทดสอบ 
	 
	 `make test-setup`


	* เพื่อทดสอบ
	
	 `make test-native`


	* เพื่อสร้างไฟล์สำหรับบิ้วปลั๊กอิน (ควรมี cmake เวอร์ชั่นที่ไม่ต่ำกว่า 3.0)
	 
	 `make build-inside`

	   - หรือใช้คำสั่งตามนี้แทน
	      * mkdir build
	      * cd build
	      * cmake .. -G "Visual Studio 10 2010"
     
     
## ตัวอย่าง
**ปัญหาและการติดตั้ง**

* ปัญหา

ก่อนใช้งาน

![ก่อนใช้งาน](https://i.imgur.com/M14TACI.png)

หลังใช้งาน

![หลังใช้งาน](https://i.imgur.com/UiuOF5B.png)

* การติดตั้ง
```Pawn
#include <a_samp>
#include <streamer> // ถ้ามีให้ใส่ไว้ก่อน include cec
#define cec_auto // เปิดใช้งานอัตโนมัติ
#include <cec>
#include <easyDialog> // ถ้ามีให้ใส่ไว้หลัง include cec
```

* การติดตั้งสำหรับตั้งแต่ v2.3 ขึ้นไป
```Pawn
#include <a_samp>
#include <Pawn.RakNet> // <-- จำเป็นต้องมี
#include <cec> // ถ้ามีผู้เล่นบนมือถือให้โหลดและใช้ Filterscript ตัวนี้ -> https://github.com/Fairuz-Afdhal/IsPlayerUsingAndroid
```
