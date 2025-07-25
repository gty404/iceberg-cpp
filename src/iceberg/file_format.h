/*
 * Licensed to the Apache Software Foundation (ASF) under one
 * or more contributor license agreements.  See the NOTICE file
 * distributed with this work for additional information
 * regarding copyright ownership.  The ASF licenses this file
 * to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance
 * with the License.  You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 * KIND, either express or implied.  See the License for the
 * specific language governing permissions and limitations
 * under the License.
 */

#pragma once

/// \file iceberg/file_format.h
/// File format used by Iceberg.

#include <string_view>
#include <utility>

#include "iceberg/iceberg_export.h"
#include "iceberg/result.h"
#include "iceberg/util/string_utils.h"

namespace iceberg {

/// \brief File format type
enum class ICEBERG_EXPORT FileFormatType {
  kParquet,
  kAvro,
  kOrc,
  kPuffin,
};

/// \brief Convert a FileFormatType to a string
ICEBERG_EXPORT inline std::string_view ToString(FileFormatType format_type) {
  switch (format_type) {
    case FileFormatType::kParquet:
      return "parquet";
    case FileFormatType::kAvro:
      return "avro";
    case FileFormatType::kOrc:
      return "orc";
    case FileFormatType::kPuffin:
      return "puffin";
  }
  std::unreachable();
}

/// \brief Convert a string to a FileFormatType
ICEBERG_EXPORT inline Result<FileFormatType> FileFormatTypeFromString(
    std::string_view str) noexcept {
  auto lower = StringUtils::ToLower(str);
  if (lower == "parquet") return FileFormatType::kParquet;
  if (lower == "avro") return FileFormatType::kAvro;
  if (lower == "orc") return FileFormatType::kOrc;
  if (lower == "puffin") return FileFormatType::kPuffin;
  return InvalidArgument("Invalid file format type: {}", str);
}

}  // namespace iceberg
