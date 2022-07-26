#include "BSML/Tags/ScrollIndicatorTag.hpp"
#include "logging.hpp"

#include "UnityEngine/Resources.hpp"
#include "UnityEngine/GameObject.hpp"
#include "UnityEngine/Transform.hpp"
#include "UnityEngine/Object.hpp"
#include "HMUI/VerticalScrollIndicator.hpp"
#include "BSML/Components/ScrollIndicator.hpp"
#include "UnityEngine/RectTransform.hpp"

namespace BSML
{
    HMUI::VerticalScrollIndicator *ScrollIndicator = nullptr;

    void ScrollIndicatorTag::Construct(UnityEngine::Transform *parent, Il2CppObject *host) const
    {
        auto obj = CreateObject(parent);
    }

    UnityEngine::GameObject *ScrollIndicatorTag::CreateObject(UnityEngine::Transform *parent) const
    {
        DEBUG("making ScrollIndicator");
        if (!ScrollIndicator || !UnityEngine::Object::IsNativeObjectAlive(ScrollIndicator))
        {
            ScrollIndicator = UnityEngine::Resources::FindObjectsOfTypeAll<HMUI::VerticalScrollIndicator *>().FirstOrDefault([](auto x)
                                                                                                                             { return x->get_name() == "VerticalScrollIndicator"; });
        }

        auto baseObj = UnityEngine::Object::Instantiate(ScrollIndicator, parent, false);
        auto gameObj = baseObj->get_gameObject();

        gameObj->SetActive(false);
        gameObj->set_name("BSMLVerticalScrollIndicator");

        auto transform = gameObj->GetComponent<UnityEngine::RectTransform *>();
        transform->SetParent(parent, false);

        UnityEngine::Object::DestroyImmediate(gameObj->GetComponent<HMUI::VerticalScrollIndicator*>());
        auto indicator = gameObj->AddComponent<BSML::ScrollIndicator*>();
        indicator->set_Handle(transform->GetChild(0)->GetComponent<UnityEngine::RectTransform*>());

        gameObj->SetActive(true);

        return gameObj;
    }

    void ScrollIndicatorTag::parse(const tinyxml2::XMLElement &elem)
    {
        DEBUG("Parsing ScrollIndicator tag.");
        this->::BSML::BSMLTag::parse(elem);
    }
}