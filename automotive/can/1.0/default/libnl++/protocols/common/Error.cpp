/*
 * Copyright (C) 2020 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "Error.h"

#include "../MessageDefinition.h"

#include <libnl++/printer.h>

namespace android::nl::protocols::base {

using DataType = AttributeDefinition::DataType;

// clang-format off
Error::Error(int protocol) : MessageDefinition<nlmsgerr>("nlmsg", {
    {NLMSG_ERROR, {"ERROR", MessageGenre::ACK}},
}, {
    {NLMSGERR_ATTR_MSG, {"MSG", DataType::String}},
    {NLMSGERR_ATTR_OFFS, {"OFFS", DataType::Uint}},
    {NLMSGERR_ATTR_COOKIE, {"COOKIE", DataType::Raw}},
}), mProtocol(protocol) {}
// clang-format on

void Error::toStream(std::stringstream& ss, const nlmsgerr& data) const {
    ss << "nlmsgerr{error=" << data.error
       << ", msg=" << toString({&data.msg, sizeof(data.msg)}, mProtocol, false) << "}";
}

}  // namespace android::nl::protocols::base
