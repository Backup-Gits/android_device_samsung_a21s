#include <stdlib.h>

#define _REALLY_INCLUDE_SYS__SYSTEM_PROPERTIES_H_
#include <sys/_system_properties.h>
#include <android-base/file.h>
#include <android-base/properties.h>
#include <android-base/logging.h>
#include "vendor_init.h"
#include "property_service.h"

using android::base::GetProperty;
using android::init::property_set;

void property_override(const std::string& name, const std::string& value)
{
    size_t valuelen = value.size();
    prop_info* pi = (prop_info*) __system_property_find(name.c_str());
    if (pi != nullptr) {
        __system_property_update(pi, value.c_str(), valuelen);
    }
    else {
        int rc = __system_property_add(name.c_str(), name.size(), value.c_str(), valuelen);
        if (rc < 0) {
            LOG(ERROR) << "property_set(\"" << name << "\", \"" << value << "\") failed: "
                       << "__system_property_add failed";
        }
    }
}

void property_override_quad(const std::string& boot_prop, const std::string& product_prop, const std::string& system_prop, const std::string& vendor_prop, const std::string& value)
{
    property_override(boot_prop, value);
    property_override(product_prop, value);
    property_override(system_prop, value);
    property_override(vendor_prop, value);
}

void vendor_load_properties()
{
    
    // Hack for bootimage
    property_set("ro.bootimage.build.date.utc", "0");

    std::string bootloader = GetProperty("ro.bootloader","");

    // International / Russia
    if (bootloader.find("A217F") == 0)
    {
        property_override_quad("ro.product.model", "ro.product.odm.model", "ro.product.system.model", "ro.product.vendor.model", "SM-A217F");
        property_override_quad("ro.product.name", "ro.product.odm.name", "ro.product.system.name", "ro.product.vendor.name", "a21s");
    }
    // USA
    else if (bootloader.find("A217M") == 0)
    {
        property_override_quad("ro.product.model", "ro.product.odm.model", "ro.product.system.model", "ro.product.vendor.model", "SM-A217M");
        property_override_quad("ro.product.name", "ro.product.odm.name", "ro.product.system.name", "ro.product.vendor.name", "a21s");
    }
    // South Korea
    else if (bootloader.find("A217N") == 0)
    {
        property_override_quad("ro.product.model", "ro.product.odm.model", "ro.product.system.model", "ro.product.vendor.model", "SM-A217N");
        property_override_quad("ro.product.name", "ro.product.odm.name", "ro.product.system.name", "ro.product.vendor.name", "a21s");
    }
    
    std::string device = GetProperty("ro.product.device", "");
    LOG(ERROR) << "Found bootloader id %s setting build properties for %s device\n" << bootloader.c_str() << device.c_str();
}
