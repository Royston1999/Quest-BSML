#include "BSML/Tags/TextFieldTag.hpp"

#include "BSML/Components/ExternalComponents.hpp"
#include "Polyglot/LocalizedTextMeshProUGUI.hpp"
#include "TMPro/TextMeshProUGUI.hpp"
#include "UnityEngine/RectTransform.hpp"
#include "UnityEngine/Resources.hpp"
#include "UnityEngine/UI/LayoutElement.hpp"
using namespace UnityEngine;

namespace BSML {
    BSMLNodeParser<TextFieldTag> textFieldTagParser({"text-field"});

    HMUI::InputFieldView* TextFieldTag::get_fieldViewPrefab() const {
        static SafePtrUnity<HMUI::InputFieldView> fieldViewPrefab;
        if (!fieldViewPrefab) {
            fieldViewPrefab = Resources::FindObjectsOfTypeAll<HMUI::InputFieldView*>().FirstOrDefault([](auto x){ return x->get_name() == "GuestNameInputField"; });
        }
        return fieldViewPrefab.ptr();
    }

    GameObject* TextFieldTag::CreateObject(Transform* parent) const {
        auto go = Object::Instantiate(get_fieldViewPrefab()->get_gameObject(), parent, false);
        static ConstString name("BSMLTextField");
        go->set_name(name);
        auto layoutElement = go->AddComponent<UI::LayoutElement*>();
        layoutElement->set_preferredWidth(90.0f);
        layoutElement->set_preferredHeight(8.0f);
        auto transform = reinterpret_cast<RectTransform*>(go->get_transform());
        transform->set_anchoredPosition({0, 0});

        auto fieldView = go->GetComponent<HMUI::InputFieldView*>();
        fieldView->useGlobalKeyboard = true;
        fieldView->textLengthLimit = 128;
        fieldView->keyboardPositionOffset =  Vector3(1337.0f, 1337.0f, 1337.0f);

        fieldView->Awake();

        Object::Destroy(fieldView->placeholderText->GetComponent<Polyglot::LocalizedTextMeshProUGUI*>());
        auto text = fieldView->placeholderText->GetComponent<TMPro::TextMeshProUGUI*>();
        auto externalComponents = go->AddComponent<ExternalComponents*>();
        externalComponents->Add(text);
        return go;
    }
}
