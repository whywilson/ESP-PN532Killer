/**
 * @file PN532Killer.cpp
 * @brief Control PN532Killer via UART
 * @version 0.1
 * @date 2025-03-31
 */

#include "PN532Killer.h"

PN532Killer::PN532Killer(HardwareSerial &serial) : PN532_UART(serial) {}

PN532Killer::~PN532Killer() {}

bool PN532Killer::setWorkMode(uint8_t mode, uint8_t type, uint8_t index) {
    std::vector<uint8_t> response = writeCommand(PN532KillerCmd::SetWorkMode, {mode, type, index});
    return response.size() > 6;
}

bool PN532Killer::switchReaderMode() {
    return setWorkMode(PN532KillerCmd::WorkMode::Reader, PN532KillerCmd::TagType::MFC1K, 0x00);
}

bool PN532Killer::switchEmulatorMifareSlot(uint8_t slot) {
    return setWorkMode(PN532KillerCmd::WorkMode::Emulator, 0x01, slot);
}

bool PN532Killer::switchEmulatorIso15693Slot(uint8_t slot) {
    return setWorkMode(PN532KillerCmd::WorkMode::Emulator, PN532KillerCmd::TagType::ISO15693, slot);
}

bool PN532Killer::switchEmulatorEm4100Slot(uint8_t slot) {
    return setWorkMode(PN532KillerCmd::WorkMode::Emulator, PN532KillerCmd::TagType::EM4100, slot);
}

bool PN532Killer::setMfkey32v2Sniffing() {
    return setWorkMode(PN532KillerCmd::WorkMode::Sniffer, PN532KillerCmd::TagType::MFC1K, 0x00);
}

bool PN532Killer::setMfkey64Sniffing() {
    return setWorkMode(PN532KillerCmd::WorkMode::Sniffer, PN532KillerCmd::TagType::MFC1K, 0x01);
}

PN532KillerTagTechnology::Iso15693TagInfo PN532Killer::hf15Scan() {
    std::vector<uint8_t> result = writeCommand(PN532KillerCmd::InListPassiveTarget, {0x01, 0x05}, 1000);
    if (result.size() < 9) {
        return PN532KillerTagTechnology::Iso15693TagInfo();
    }

    return tagTechnology.parseIso15693Tag(result.data(), result.size());
}

PN532KillerTagTechnology::Em4100TagInfo PN532Killer::lfEm4100Scan() {
    std::vector<uint8_t> result = writeCommand(PN532KillerCmd::InListPassiveTarget, {0x01, 0x06}, 1000);
    if (result.size() < 6) {
        return PN532KillerTagTechnology::Em4100TagInfo();
    }
    return tagTechnology.parseEm4100Tag(result.data(), result.size());
}
