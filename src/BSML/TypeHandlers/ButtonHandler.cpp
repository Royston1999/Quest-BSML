#include "BSML/TypeHandlers/ButtonHandler.hpp"
#include "UnityEngine/Events/UnityAction.hpp"
#include "UnityEngine/UI/Button_ButtonClickedEvent.hpp"
#include "logging.hpp"

#include "beatsaber-hook/shared/utils/il2cpp-utils.hpp"

using namespace UnityEngine;
using namespace UnityEngine::Events;
using namespace UnityEngine::UI;

namespace BSML {
    static ButtonHandler buttonHandler;
    ButtonHandler::Base::PropMap ButtonHandler::get_props() const {
        return {
            {"onClick", {"on-click"}},
            {"clickEvent", {"click-event", "event-click"}}
        };
    }

    ButtonHandler::Base::SetterMap ButtonHandler::get_setters() const {
        return {};
    }

    void ButtonHandler::HandleType(const ComponentTypeWithData& componentType, BSMLParserParams& parserParams) {
        auto buttonOpt = il2cpp_utils::try_cast<Button>(componentType.component);
        auto host = parserParams.host;
        if (buttonOpt.has_value()) {
            auto button = buttonOpt.value();
            // it was a button!
            auto onClickItr = componentType.data.find("onClick");
            if (onClickItr != componentType.data.end() && !onClickItr->second.empty()) {
                auto onClickMethodInfo = il2cpp_functions::class_get_method_from_name(host->klass, onClickItr->second.c_str(), 0);
                if (onClickMethodInfo) {
                    std::function<void()> fun = [host, onClickMethodInfo](){ il2cpp_utils::RunMethod(host, onClickMethodInfo); };
                    auto delegate = il2cpp_utils::MakeDelegate<UnityAction*>(fun);
                    button->set_onClick(Button::ButtonClickedEvent::New_ctor());
                    button->get_onClick()->AddListener(delegate);
                } else {
                    ERROR("Method '{}' could not be found in class {}::{}", onClickItr->second, host->klass->namespaze, host->klass->name);
                }
            }

            auto clickEventItr = componentType.data.find("click-event");
            if (clickEventItr != componentType.data.end() && !clickEventItr->second.empty()) {
                auto clickEventMethodInfo = il2cpp_functions::class_get_method_from_name(host->klass, clickEventItr->second.c_str(), 0);
                if (clickEventMethodInfo) {
                    std::function<void()> fun = [host, clickEventMethodInfo](){ il2cpp_utils::RunMethod(host, clickEventMethodInfo); };
                    auto delegate = il2cpp_utils::MakeDelegate<UnityAction*>(fun);
                    button->set_onClick(Button::ButtonClickedEvent::New_ctor());
                    button->get_onClick()->AddListener(delegate);
                } else {
                    ERROR("Method '{}' could not be found in class {}::{}", clickEventItr->second, host->klass->namespaze, host->klass->name);
                }
            }
        }

        Base::HandleType(componentType, parserParams);
    }
}