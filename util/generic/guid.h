#pragma once

#include "fwd.h"

#include <util/str_stl.h>

/**
 * UUID generation
 *
 * NOTE: It is not a real GUID (RFC 4122), as described in
 * https://en.wikipedia.org/wiki/Universally_unique_identifier
 * https://en.wikipedia.org/wiki/Globally_unique_identifier
 *
 * See https://clubs.at.yandex-team.ru/stackoverflow/10238/10240
 * and https://st.yandex-team.ru/IGNIETFERRO-768 for details.
 **/
struct TGUID {
    ui32 dw[4] = {};

    constexpr TGUID() {
    }

    constexpr bool IsEmpty() const noexcept {
        return (dw[0] | dw[1] | dw[2] | dw[3]) == 0;
    }

    constexpr explicit operator bool() const noexcept {
        return !IsEmpty();
    }
};

constexpr bool operator==(const TGUID& a, const TGUID& b) noexcept {
    return a.dw[0] == b.dw[0] && a.dw[1] == b.dw[1] && a.dw[2] == b.dw[2] && a.dw[3] == b.dw[3];
}

constexpr bool operator!=(const TGUID& a, const TGUID& b) noexcept {
    return !(a == b);
}

struct TGUIDHash {
    constexpr int operator()(const TGUID& a) const noexcept {
        return a.dw[0] + a.dw[1] + a.dw[2] + a.dw[3];
    }
};

template <>
struct THash<TGUID> {
    constexpr size_t operator()(const TGUID& g) const noexcept {
        return (unsigned int)TGUIDHash()(g);
    }
};

/**
 * NOTE: Not fork()-safe, see IGNIETFERRO-610
 **/
void CreateGuid(TGUID* res);

/**
 * NOTE: Not fork()-safe, see IGNIETFERRO-610
 **/
TString GetGuidAsString(const TGUID& g);
TString CreateGuidAsString();
TGUID GetGuid(const TString& s);
bool GetGuid(const TString& s, TGUID& result);

/**
* Functions for correct parsing RFC4122 GUID, which described in
* https://en.wikipedia.org/wiki/Universally_unique_identifier
**/
TGUID GetUuid(const TString& s);
bool GetUuid(const TString& s, TGUID& result);
