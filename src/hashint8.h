#pragma once
#include <string>
#include <vector>

static const std::vector<uint8_t> HI8_SP = {0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09,0x0a,0x0b,0x0c,0x0d,0x0e,0x0f};
static const uint8_t HI8_SP_SIZE = 16;
static const uint8_t HI8_SP_LPOS = 15;
static const std::vector<uint8_t> HI8_JMP = {0x01,0x03,0x05,0x07,0x09,0x0b,0x0d,0x0f};
static const uint8_t HI8_JMP_SIZE = 8;
static const uint8_t HI8_JMP_LPOS = 7;
static const std::vector<uint8_t> HI8_MN = {0x00,0x01,0x02,0x03,0x04};
static const uint8_t HI8_MN_SIZE = 5;
static const uint8_t HI8_MN_LPOS = 4;
static const std::vector<uint8_t> HI8_SHF = {0x01,0x02,0x04,0x08};
static const uint8_t HI8_SHF_SIZE = 4;
static const uint8_t HI8_SHF_LPOS = 3;
static const std::vector<uint8_t> HI8_SHFO = {0x00,0x01};
static const uint8_t HI8_SHFO_SIZE = 2;
static const uint8_t HI8_SHFO_LPOS = 1;
static const std::vector<uint8_t> HI8_PATH = {0x00,0x01,0x02};
static const uint8_t HI8_PATH_SIZE = 3;
static const uint8_t HI8_PATH_LPOS = 2;

uint64_t generate_seed8(std::string secret);

std::string hashint8(uint8_t input, std::string secret);
