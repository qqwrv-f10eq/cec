# Color Embed Converter (CEC)

[![Build status](https://ci.appveyor.com/api/projects/status/2qswo7s6hk8jiovf?svg=true)](https://ci.appveyor.com/project/Brian-Less/cec/branch/master) [![Build Status](https://app.travis-ci.com/Brian-Less/cec.svg?branch=master)](https://app.travis-ci.com/Brian-Less/cec) ![License: MIT](https://img.shields.io/badge/License-MIT-red.svg)

## What is CEC?

**CEC (Color Embed Converter)** is a SA:MP (San Andreas Multiplayer) plugin that fixes color tag rendering issues in text, especially for languages with complex character compositions like Thai.

### The Problem It Solves

In SA:MP, color tags use the format `{RRGGBB}` to colorize text. However, when text contains special characters like Thai vowel marks (sara) and tone marks, these characters can merge with adjacent characters, causing color tags to shift incorrectly and breaking text display.

**Example:**
- **Before CEC:** `ทด{FFFF00}สอบของค{FFFFFF}นสบาย` → Renders incorrectly
- **After CEC:** Text renders with correct color positioning and proper character alignment

### Features

- **Automatic Color Tag Correction:** Intelligently shifts color tags to proper positions
- **Thai Language Support:** Handles Thai vowel marks (อิ, อี, อึ, อื, etc.) and tone marks (่, ้, ๊, ๋, etc.)
- **API Functions:**
  - `CE_Convert()` - Convert text with correct color tag positions
  - `CE_Convert_Dialog()` - Convert dialog text with color corrections
  - `CE_CountTag()` - Count color tags in text
  - `CE_CountVowel()` - Count Thai vowel marks in text

---

## Installation

### Using sampctl (Recommended)

```bash
sampctl p install Brian-Less/cec
```

### Manual Installation

1. Download the plugin file for your operating system (Windows or Linux)
2. Place it in your `plugins` folder
3. Add `cec` (or `cec.so` for Linux) to your `server.cfg`
4. Include [cec.inc](cec.inc) in your Pawn code

### Usage (v2.3+)

```pawn
#include <a_samp>
#include <Pawn.RakNet>  // Required dependency
#include <cec>          // Always include after Pawn.RakNet
```

**Basic Example:**
```pawn
new input[144] = "ทด{FFFF00}สอบของค{FFFFFF}นสบาย";
new output[144];
CE_Convert(input, output);
// output now contains properly formatted text
```

## Building from Source

**Note:** Only needed if you want to contribute or modify the plugin.

### Prerequisites
- [sampctl](https://github.com/Southclaws/sampctl) for testing
- CMake 3.0 or higher
- C++ compiler

### Steps

1. Clone the repository:
```bash
git clone https://github.com/Brian-Less/cec.git
```

2. Prepare test environment:
```bash
make test-setup
```

3. Run tests:
```bash
make test-native
```

4. Build the plugin:
```bash
make build-inside
```

Or manually:
```bash
mkdir build
cd build
cmake .. -G "Visual Studio 10 2010"
```

---

## ภาษาไทย

### CEC คืออะไร?

**CEC (Color Embed Converter)** เป็นปลั๊กอินสำหรับ SA:MP (San Andreas Multiplayer) ที่ช่วยแก้ไขปัญหาการแสดงผลแท็กสีในข้อความ โดยเฉพาะกับภาษาไทยที่มีสระและวรรณยุกต์

### ปัญหาที่ CEC แก้ไข

ใน SA:MP แท็กสีใช้รูปแบบ `{RRGGBB}` เพื่อใส่สีให้กับข้อความ แต่เมื่อข้อความมีอักขระพิเศษ เช่น สระ (อิ, อี, อึ, อื, ฯลฯ) และวรรณยุกต์ (่, ้, ๊, ๋, ฯลฯ) ของภาษาไทย อักขระเหล่านี้จะรวมตัวกับอักขระข้างเคียง ทำให้แท็กสีเลื่อนไปอย่างไม่ถูกต้องและทำให้การแสดงผลพัง

### ฟีเจอร์

- **แก้ไขตำแหน่งแท็กสีอัตโนมัติ:** เลื่อนแท็กสีไปยังตำแหน่งที่ถูกต้องอย่างชาญฉลาด
- **รองรับภาษาไทย:** รองรับสระและวรรณยุกต์ทุกตัว
- **ฟังก์ชัน API:**
  - `CE_Convert()` - แปลงข้อความให้แท็กสีอยู่ในตำแหน่งที่ถูกต้อง
  - `CE_Convert_Dialog()` - แปลงข้อความไดอะล็อกพร้อมแก้ไขสี
  - `CE_CountTag()` - นับจำนวนแท็กสีในข้อความ
  - `CE_CountVowel()` - นับจำนวนสระในข้อความ

---

## การติดตั้ง

หากคุณเป็นผู้ใช้ sampctl

`sampctl p install Brian-Less/cec`

#### หรือ
* โหลดไฟล์ที่เข้ากับระบบปฏิบัติการของคุณ (Windows หรือ Linux)
* ใส่มันลงไปที่โฟลเดอร์ `plugins`
* เพิ่ม `cec` ที่ server.cfg หรือ `cec.so` (สำหรับ Linux)
* นำไฟล์ [cec.inc](cec.inc) ใส่ในโฟลเดอร์ Includes ของคุณ

## การบิ้ว (ใครที่ไม่ได้จะนำไปพัฒนาต่อข้ามไปได้เลย)

* ติดตั้ง [sampctl](https://github.com/Southclaws/sampctl) เพื่อใช้ในการทดสอบ

* โคลนที่เก็บไฟล์

	`git clone https://github.com/Brian-Less/cec.git`

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
#include <cec> // อยู่ใต้ Pawn.Raknet เสมอ
```
