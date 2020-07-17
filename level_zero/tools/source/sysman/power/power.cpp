/*
 * Copyright (C) 2020 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 */

#include "level_zero/tools/source/sysman/power/power.h"

#include "level_zero/tools/source/sysman/power/power_imp.h"

namespace L0 {

PowerHandleContext::~PowerHandleContext() {
    for (Power *pPower : handleList) {
        delete pPower;
    }
}

void PowerHandleContext::init() {
    Power *pPower = new PowerImp(pOsSysman);
    if (pPower->initSuccess == true) {
        handleList.push_back(pPower);
    } else {
        delete pPower;
    }
}

ze_result_t PowerHandleContext::powerGet(uint32_t *pCount, zet_sysman_pwr_handle_t *phPower) {
    if (nullptr == phPower) {
        *pCount = static_cast<uint32_t>(handleList.size());
        return ZE_RESULT_SUCCESS;
    }
    uint32_t i = 0;
    for (Power *power : handleList) {
        if (i >= *pCount) {
            break;
        }
        phPower[i++] = power->toHandle();
    }
    *pCount = i;
    return ZE_RESULT_SUCCESS;
}

ze_result_t PowerHandleContext::powerGet(uint32_t *pCount, zes_pwr_handle_t *phPower) {
    if (nullptr == phPower) {
        *pCount = static_cast<uint32_t>(handleList.size());
        return ZE_RESULT_SUCCESS;
    }
    uint32_t i = 0;
    for (Power *power : handleList) {
        if (i >= *pCount) {
            break;
        }
        phPower[i++] = power->toZesPwrHandle();
    }
    *pCount = i;
    return ZE_RESULT_SUCCESS;
}

} // namespace L0
