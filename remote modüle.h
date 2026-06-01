#pragma once

/*
 * Remote Control Module
 * M5Stack Cardputer
 * Header File
 */

#include <M5Cardputer.h>
#include <IRremoteESP8266.h>
#include <IRrecv.h>
#include <IRsend.h>
#include <IRutils.h>
#include <SD.h>
#include <SPI.h>

// ─── Pin & Donanım Tanımları ─────────────────────────────────────────────────
#define IR_RECV_PIN 1
#define IR_SEND_PIN 2
#define SD_CS_PIN   12

// ─── Renk Tanımları ──────────────────────────────────────────────────────────
#define COLOR_BG     0x0000
#define COLOR_BAR    0x1082
#define COLOR_GREEN  0x07E0
#define COLOR_WHITE  0xFFFF
#define COLOR_GRAY   0x8410
#define COLOR_YELLOW 0xFFE0
#define COLOR_RED    0xF800
#define COLOR_DARK   0x18C3

// ─── Ekran Layout Sabitleri ───────────────────────────────────────────────────
#define TOP_BAR_H    18
#define SCREEN_W     240
#define SCREEN_H     135
#define SIGNAL_BOX_Y (TOP_BAR_H + 2)
#define SIGNAL_BOX_H 44
#define LIST_BOX_Y   (SIGNAL_BOX_Y + SIGNAL_BOX_H + 6)
#define LIST_BOX_H   (SCREEN_H - LIST_BOX_Y - 3)
#define LIST_START_Y (LIST_BOX_Y + 14)
#define LIST_ROW_H   13
#define LIST_VISIBLE ((LIST_BOX_H - 16) / LIST_ROW_H)

// ─── Veri Yapıları ────────────────────────────────────────────────────────────
struct IRFile {
    String name;
    String path;
};

// ─── Global Değişkenler (extern) ─────────────────────────────────────────────
extern IRrecv        irrecv;
extern IRsend        irsend;
extern decode_results results;

extern IRFile irFiles[50];
extern int    fileCount;
extern int    selectedFile;
extern int    scrollOffset;

extern String   lastHex;
extern String   lastProtocol;
extern uint64_t lastValue;
extern bool     newSignalReceived;
extern bool     sdMounted;

extern unsigned long lastNewSignalTime;

extern String pendingSaveName;
extern bool   namingMode;

extern unsigned long lastBlinkTime;
extern bool          blinkState;

// ─── Klavye Yardımcıları ─────────────────────────────────────────────────────
bool keyPressed(const Keyboard_Class::KeysState &ks, char c);
bool enterPressed(const Keyboard_Class::KeysState &ks);

// ─── SD Fonksiyonları ────────────────────────────────────────────────────────
bool mountSD();
void scanIRFiles();
bool saveIRSignalNamed(const String &hex, const String &protocol,
                       uint64_t value, const String &customName);

// ─── IR Fonksiyonları ────────────────────────────────────────────────────────
String decodeToHex(decode_results *res);
bool   sendIRFile(const String &path);

// ─── Çizim Fonksiyonları ─────────────────────────────────────────────────────
void drawTopBar();
void drawStaticFrames();
void redrawSignalContent();
void redrawListContent();
void fullRedraw();
void drawSendFlash();
void drawSaveFlash(bool ok);

// ─── İsimlendirme Ekranı ─────────────────────────────────────────────────────
void drawNamingScreenFull();
void updateNamingInputBox();

// ─── Loop Yardımcıları ───────────────────────────────────────────────────────
void handleNamingMode();
void handleIRReceive();
void handleKeyboard();
