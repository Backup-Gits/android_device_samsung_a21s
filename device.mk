#
# Copyright (C) 2020 The Android Open Source Project
# Copyright (C) 2020 The TWRP Open Source Project
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#

LOCAL_PATH := device/samsung/a21s

# Device identifier. This must come after all inclusions
PRODUCT_DEVICE := a21s
PRODUCT_NAME := omni_a21s
PRODUCT_BRAND := samsung
PRODUCT_MODEL := SM-A217M
PRODUCT_MANUFACTURER := samsung
PRODUCT_RELEASE_NAME := samsung SM-A217M

# Charger
PRODUCT_PACKAGES += \
    charger_res_images

PRODUCT_COPY_FILES += $(call find-copy-subdir-files,*,$(LOCAL_PATH)/recovery/root,recovery/root)

# HACK: Set vendor patch level
PRODUCT_PROPERTY_OVERRIDES += \
    ro.vendor.build.security_patch=2099-12-31
    
# HACK: Blacklist Properties
PRODUCT_SYSTEM_PROPERTY_BLACKLIST += \
    ro.build.date.utc \
    ro.build.date