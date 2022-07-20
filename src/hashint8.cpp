#include <ios>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>
#include <math.h>
#include "hashint.h"
#include "hashint8.h"

// #define EULER 2.7182818284590452354

uint64_t generate_seed8(std::string secret) {
    uint64_t seed = 0x00;
    uint8_t sp[3]/* 12b */,jmp[3]/* 12b */,mn/* 2b */,shf/* 4b */,shfo/* 1b */,path[3]/* 6b */; // 37b
    int i;
    // get secret len
    uint16_t s_len = secret.length();
    // get most frequently character in secret
    uint16_t ocurr[256] = {0};
    char idx[256],idx_size=0;
    int s_sum = 0;
    for(i=0;i<s_len;i++) {
        if(ocurr[secret[i]] == 0) {
            idx[idx_size] = secret[i];
            idx_size ++;
        }
        ocurr[secret[i]]++;
        s_sum += secret[i];
    }
    char most_freq = idx[0];
    for(i=1;i<idx_size;i++){
        if(ocurr[most_freq] < ocurr[idx[i]])
            most_freq = idx[i];
    }
    char less_freq = idx[0];
    for(i=1;i<idx_size;i++){
        if(ocurr[less_freq] > ocurr[idx[i]])
            less_freq = idx[i];
    }

    double s_avg = s_sum/(double)s_len;
    mn = HI8_MN[(uint8_t)round((sin(s_sum)+1)/2*HI8_MN_LPOS)];
    seed = mn;
    shf = HI8_SHF[(uint8_t)round((sin(less_freq)+1)/2*HI8_SHF_LPOS)];
    seed = (seed << 4) | shf;
    shfo = HI8_SHFO[s_sum%2];
    seed = (seed << 1) | shfo;
    uint8_t x,y;
    std::vector<uint8_t> AUX_PATH = HI8_PATH;
    for(i=0; i<3; i++) {
        x = (uint8_t)((sin(s_avg/pow(EULER,s_len))+1)/2*(2-i));
        path[i] = AUX_PATH[x];
        seed = (seed << 2) | path[i];
        for(;x<2;x++)
            AUX_PATH[x] = AUX_PATH[x+1];
    }
    std::vector<uint8_t> AUX_SP = HI8_SP;
    std::vector<uint8_t> AUX_JMP = HI8_JMP;
    for(i=0; i<3; i++) {
        x = (uint8_t)round((sin(s_len)+1)/2*(HI8_SP_LPOS-i));
        y = (uint8_t)round((sin(most_freq)+1)/2*(HI8_JMP_LPOS-i));
        sp[i] = AUX_SP[x];
        jmp[i] = AUX_JMP[y];
        seed = (seed << 4) | sp[i];
        seed = (seed << 4) | jmp[i];
        for(;x<HI8_SP_LPOS;x++)
            AUX_SP[x] = AUX_SP[x+1];
        for(;y<HI8_JMP_LPOS;y++)
            AUX_JMP[y] = AUX_JMP[y+1];
    }
    return seed;
}

std::string hashint8(uint8_t input, std::string secret) {
    char i,j;
    uint64_t seed = generate_seed8(secret); // a 64bit value where: (+s) <unused bit> + <mn> + <shf> + <shfo> + <path[5]> + <(<sp> + <jmp>)[5]> (-s)
    uint8_t the_start = (uint8_t)((sin(log10(seed))+1)/2*255),the_jmp = 1 + ((uint16_t)((cos(log10(seed))+1)/2*127)*2);
    HASH_GROUP gps[3];
    uint8_t mn = seed >> 35;
    uint8_t shf = (seed >> 31) & 0x0F;
    uint8_t shfo = (seed >> 30) & 0x01;
    uint8_t path[3];
    for(i=0; i<3; i++){
        path[i] = (seed >> (28 - (2*i))) & 0x03;
        gps[i].values[0] = gps[i].sp = (seed >> (20 - (8*i))) & 0x0F;
        gps[i].jmp = (seed >> (16 - (8*i))) & 0x0F;
        gps[i].len = (i==mn)?16:8;
        for(j=1; j<16; j++){
            gps[i].values[j] = (gps[i].values[j-1] + gps[i].jmp) % 16;
        }
        // TODO shuffle
    }
    char hex[3];
    char hash[4]={0,0,0,'\0'};
    uint16_t x;
    uint16_t src = (the_start + input * the_jmp) % 255;
    // get number of possibility childs for each level in order of `path`
    uint32_t xpto[3];
    xpto[path[2]] = 1;
    for(i=1; i>=0; i--)
        xpto[path[i]] = gps[path[i+1]].len * xpto[path[i+1]];
    for(i=0; i<3; i++){
        // how many times did the `src` pass at this level?
        x = src / xpto[path[i]];
        // how many steps are left?
        src %= xpto[path[i]];
        // get the current value accordingly level jump value and current level interact
        hex[i] = (gps[path[i]].values[0] + gps[path[i]].jmp * x) % 16;
    }
    for(i=0; i<3; i++)
        sprintf(&hash[i],"%01x",hex[path[i]]);
    return hash;
}
