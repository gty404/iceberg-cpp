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

#include <string>

#include "iceberg/expected.h"
#include "iceberg/iceberg_export.h"

namespace iceberg {

/// \brief Error types for iceberg.
/// TODO: add more and sort them based on some rules.
enum class ErrorKind {
  kNoSuchNamespace,
  kAlreadyExists,
  kNoSuchTable,
  kCommitStateUnknown,
  kInvalidSchema,
  kInvalidArgument,
  kIOError,
  kNotImplemented,
  kUnknownError,
  kNotSupported,
  kJsonParseError,
};

/// \brief Error with a kind and a message.
struct ICEBERG_EXPORT [[nodiscard]] Error {
  ErrorKind kind;
  std::string message;
};

/// /brief Default error trait
template <typename T>
struct DefaultError {
  using type = Error;
};

/// \brief Result alias
template <typename T, typename E = typename DefaultError<T>::type>
using Result = expected<T, E>;

using Status = Result<void>;

}  // namespace iceberg
