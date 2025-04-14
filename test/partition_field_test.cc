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

#include "iceberg/partition_field.h"

#include <format>

#include <gtest/gtest.h>
#include <iceberg/type.h>

#include "iceberg/transform.h"
#include "iceberg/util/formatter.h"

namespace iceberg {

TEST(PartitionFieldTest, Basics) {
  {
    auto transform = Transform::Identity();
    PartitionField field(1, 1000, "pt", transform);
    EXPECT_EQ(1, field.source_id());
    EXPECT_EQ(1000, field.field_id());
    EXPECT_EQ("pt", field.name());
    EXPECT_EQ(*transform, *field.transform());
    EXPECT_EQ("pt (1000 identity(1))", field.ToString());
    EXPECT_EQ("pt (1000 identity(1))", std::format("{}", field));
  }
}

TEST(PartitionFieldTest, Equality) {
  const auto bucket_transform = Transform::Bucket(8);
  const auto identity_transform = Transform::Identity();

  PartitionField field1(1, 10000, "pt", bucket_transform);
  PartitionField field2(2, 10000, "pt", bucket_transform);
  PartitionField field3(1, 10001, "pt", bucket_transform);
  PartitionField field4(1, 10000, "pt2", bucket_transform);
  PartitionField field5(1, 10000, "pt", identity_transform);

  ASSERT_EQ(field1, field1);
  ASSERT_NE(field1, field2);
  ASSERT_NE(field2, field1);
  ASSERT_NE(field1, field3);
  ASSERT_NE(field3, field1);
  ASSERT_NE(field1, field4);
  ASSERT_NE(field4, field1);
  ASSERT_NE(field1, field5);
  ASSERT_NE(field5, field1);
}
}  // namespace iceberg
