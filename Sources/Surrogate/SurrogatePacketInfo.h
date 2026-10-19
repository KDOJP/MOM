#ifndef SurrogatePacketInfo_h
#define SurrogatePacketInfo_h

#include <stdbool.h>
#include <stdint.h>

// 値は全てnetwork byte order。OSのinterface列挙と切り離し、alias/複数NICも
// 同じ条件で検証する。peerの送信元IPはローカル宛先の判定に一切使用しない。
static inline bool _MOMPacketInfoMatchesInterface(
    uint32_t receivedIndex, uint32_t interfaceIndex,
    uint32_t destination, uint32_t receivedLocal, uint32_t interfaceLocal,
    uint32_t directedBroadcast, bool hasBroadcast, uint32_t configuredLocal) {
    if (receivedIndex == 0 || receivedIndex != interfaceIndex)
        return false;
    if (configuredLocal != 0 && configuredLocal != interfaceLocal)
        return false;
    // Linux等でlocal addressが提供される場合も、実在する当該NICのIPだけを採用する。
    if (receivedLocal != 0 && receivedLocal != interfaceLocal)
        return false;
    // unicastは宛先IPの完全一致。broadcastは受信NICのbroadcastに限る。
    // aliasが複数ある場合も、特定MOM向けunicastを他のaliasへ読み替えない。
    return destination == interfaceLocal || destination == UINT32_MAX ||
           (hasBroadcast && destination == directedBroadcast);
}
#endif
