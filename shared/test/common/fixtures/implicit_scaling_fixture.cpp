/*
 * Copyright (C) 2021 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 */

#include "shared/test/common/fixtures/implicit_scaling_fixture.h"

#include "shared/source/helpers/aligned_memory.h"
#include "shared/source/os_interface/os_interface.h"

void ImplicitScalingFixture::SetUp() {
    CommandEncodeStatesFixture::SetUp();
    apiSupportBackup = std::make_unique<VariableBackup<bool>>(&ImplicitScaling::apiSupport, true);
    osLocalMemoryBackup = std::make_unique<VariableBackup<bool>>(&OSInterface::osEnableLocalMemory, true);

    singleTile = DeviceBitfield(static_cast<uint32_t>(maxNBitValue(1)));
    twoTile = DeviceBitfield(static_cast<uint32_t>(maxNBitValue(2)));

    alignedMemory = alignedMalloc(bufferSize, 4096);

    cmdBufferAlloc.setCpuPtrAndGpuAddress(alignedMemory, gpuVa);

    commandStream.replaceBuffer(alignedMemory, bufferSize);
    commandStream.replaceGraphicsAllocation(&cmdBufferAlloc);
}

void ImplicitScalingFixture::TearDown() {
    alignedFree(alignedMemory);
    CommandEncodeStatesFixture::TearDown();
}
