#pragma once

#include "tinyxml2/shared/tinyxml2.h"
#include "BSML/Components/Settings/ListSetting.hpp"
#include "BSML/Components/Settings/ListSliderSetting.hpp"
#include "BSML/Components/Settings/DropdownListSetting.hpp"

namespace BSML {
    class ListSettingData {
        public:
            ListSettingData() {};
            explicit ListSettingData(const tinyxml2::XMLElement& elem);

            auto get_listOptions() const { return listOptions; }
            
            void Apply(BSML::ListSetting* listSetting, Il2CppObject* host) const;
            void Apply(BSML::ListSliderSetting* listSetting, Il2CppObject* host) const;
            void Apply(BSML::DropdownListSetting* listSetting, Il2CppObject* host) const;
        private:
            /// name of field that contains the list of values
            std::string listOptions;
    };
}