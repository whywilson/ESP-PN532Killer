#ifndef PN532_KILLER_COMMAND_H
#define PN532_KILLER_COMMAND_H

#include "PN532Cmd.h"

namespace PN532KillerCmd {
using namespace PN532Cmd;

static constexpr uint8_t SetWorkMode = 0xAC;

enum WorkMode { Reader = 0x01, Emulator = 0x02, Sniffer = 0x03 };
enum TagType { MFC1K = 0x01, ISO15693 = 0x03, EM4100 = 0x04 };
enum ReaderProtocol { HF_ISO14443A = 0x01, HF_ISO15693 = 0x02, LF_EM4100 = 0x03 };
} // namespace PN532KillerCmd

#endif // PN532_KILLER_COMMAND_H
