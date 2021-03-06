// Auto generated file, don't modify.

#ifndef CPGF_META_GINCUGEVENT_H
#define CPGF_META_GINCUGEVENT_H


#include "cpgf/gmetadefine.h"
#include "cpgf/metadata/gmetadataconfig.h"
#include "cpgf/metadata/private/gmetadata_header.h"
#include "cpgf/gmetapolicy.h"


using namespace gincu;


namespace meta_gincu { 


template <typename D>
void buildMetaClass_Global_gevent(D _d)
{
    (void)_d;
    using namespace cpgf;
    
    _d.CPGF_MD_TEMPLATE _method("isTouchEvent", (bool (*) (const GEventType))&isTouchEvent);
    _d.CPGF_MD_TEMPLATE _enum<GEventType>("GEventType")
        ._element("none", gincu::GEventType::none)
        ._element("render", gincu::GEventType::render)
        ._element("update", gincu::GEventType::update)
        ._element("execute", gincu::GEventType::execute)
        ._element("touchMoved", gincu::GEventType::touchMoved)
        ._element("touchPressed", gincu::GEventType::touchPressed)
        ._element("touchReleased", gincu::GEventType::touchReleased)
        ._element("windowClosed", gincu::GEventType::windowClosed)
        ._element("windowResized", gincu::GEventType::windowResized)
        ._element("windowActivated", gincu::GEventType::windowActivated)
        ._element("windowDeactivated", gincu::GEventType::windowDeactivated)
    ;
}


template <typename D>
void buildMetaClass_GEvent(D _d)
{
    (void)_d;
    using namespace cpgf;
    
    _d.CPGF_MD_TEMPLATE _constructor<void * ()>();
    _d.CPGF_MD_TEMPLATE _constructor<void * (const GEventType)>();
    _d.CPGF_MD_TEMPLATE _constructor<void * (const GEventType, const GTouchEvent &)>();
    _d.CPGF_MD_TEMPLATE _constructor<void * (const GEventType, const GResizeEvent &)>();
    _d.CPGF_MD_TEMPLATE _constructor<void * (const GEventType, GRenderContext *)>();
    _d.CPGF_MD_TEMPLATE _constructor<void * (const GEventType, const std::shared_ptr< void > &)>();
    _d.CPGF_MD_TEMPLATE _constructor<void * (const GEventType, const cpgf::GCallback< void()> &)>();
    _d.CPGF_MD_TEMPLATE _method("getType", &D::ClassType::getType);
    _d.CPGF_MD_TEMPLATE _method("setType", &D::ClassType::setType);
    _d.CPGF_MD_TEMPLATE _method("getTouch", &D::ClassType::getTouch);
    _d.CPGF_MD_TEMPLATE _method("setTouch", &D::ClassType::setTouch);
    _d.CPGF_MD_TEMPLATE _method("getSharedData", &D::ClassType::getSharedData);
    _d.CPGF_MD_TEMPLATE _method("setSharedData", &D::ClassType::setSharedData);
    _d.CPGF_MD_TEMPLATE _method("getCallback", &D::ClassType::getCallback);
    _d.CPGF_MD_TEMPLATE _method("getTag", &D::ClassType::getTag);
    _d.CPGF_MD_TEMPLATE _method("setTag", &D::ClassType::setTag);
    _d.CPGF_MD_TEMPLATE _method("getResize", &D::ClassType::getResize);
    _d.CPGF_MD_TEMPLATE _method("getRenderContext", &D::ClassType::getRenderContext);
    _d.CPGF_MD_TEMPLATE _method("doesAllowPropagate", &D::ClassType::doesAllowPropagate);
    _d.CPGF_MD_TEMPLATE _method("setAllowPropagate", &D::ClassType::setAllowPropagate);
}


inline unsigned int bItFiEldWrapper_GTouchEvent_finger_getter(GTouchEvent * self) {
    return self->finger;
}

inline void bItFiEldWrapper_GTouchEvent_finger_setter(GTouchEvent * self, unsigned int value) {
    self->finger = value;
}
inline unsigned int bItFiEldWrapper_GTouchEvent_down_getter(GTouchEvent * self) {
    return self->down;
}

inline void bItFiEldWrapper_GTouchEvent_down_setter(GTouchEvent * self, unsigned int value) {
    self->down = value;
}


template <typename D>
void buildMetaClass_GTouchEvent(D _d)
{
    (void)_d;
    using namespace cpgf;
    
    _d.CPGF_MD_TEMPLATE _field("screenPosition", &D::ClassType::screenPosition);
    _d.CPGF_MD_TEMPLATE _field("worldPosition", &D::ClassType::worldPosition);
    _d.CPGF_MD_TEMPLATE _field("touchedEntity", &D::ClassType::touchedEntity);
    _d.CPGF_MD_TEMPLATE _property("finger", &bItFiEldWrapper_GTouchEvent_finger_getter, &bItFiEldWrapper_GTouchEvent_finger_setter, cpgf::MakePolicy<cpgf::GMetaRuleGetterExplicitThis, cpgf::GMetaRuleSetterExplicitThis>());
    _d.CPGF_MD_TEMPLATE _property("down", &bItFiEldWrapper_GTouchEvent_down_getter, &bItFiEldWrapper_GTouchEvent_down_setter, cpgf::MakePolicy<cpgf::GMetaRuleGetterExplicitThis, cpgf::GMetaRuleSetterExplicitThis>());
}


} // namespace meta_gincu




#include "cpgf/metadata/private/gmetadata_footer.h"


#endif
