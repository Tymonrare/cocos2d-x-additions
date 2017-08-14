#include "jsb_custom_classes.hpp"
#include "cocos2d_specifics.hpp"
#include "H/b2tojs.h"
#include "H/GameScene.h"
#include "H/SplineBasedContent.h"

template<class T>
static bool dummy_constructor(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS_ReportError(cx, "Constructor for the requested class is not available, please refer to the API reference.");
    return false;
}

static bool empty_constructor(JSContext *cx, uint32_t argc, jsval *vp) {
    return false;
}

static bool js_is_native_obj(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    args.rval().setBoolean(true);
    return true;    
}
JSClass  *jsb_GameScene_class;
JSObject *jsb_GameScene_prototype;

bool js_custom_classes_GameScene_setPhysWorldScale(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    GameScene* cobj = (GameScene *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_custom_classes_GameScene_setPhysWorldScale : Invalid Native Object");
    if (argc == 1) {
        double arg0 = 0;
        ok &= JS::ToNumber( cx, args.get(0), &arg0) && !isnan(arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_custom_classes_GameScene_setPhysWorldScale : Error processing arguments");
        cobj->setPhysWorldScale(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_custom_classes_GameScene_setPhysWorldScale : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_custom_classes_GameScene_simpleJScallback(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    GameScene* cobj = (GameScene *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_custom_classes_GameScene_simpleJScallback : Invalid Native Object");
    if (argc == 0) {
        cobj->simpleJScallback();
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_custom_classes_GameScene_simpleJScallback : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_custom_classes_GameScene_getPhysWorldScale(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    GameScene* cobj = (GameScene *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_custom_classes_GameScene_getPhysWorldScale : Invalid Native Object");
    if (argc == 0) {
        double ret = cobj->getPhysWorldScale();
        jsval jsret = JSVAL_NULL;
        jsret = DOUBLE_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_custom_classes_GameScene_getPhysWorldScale : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_custom_classes_GameScene_create(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    if (argc == 2) {
        std::string arg0;
        std::string arg1;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        ok &= jsval_to_std_string(cx, args.get(1), &arg1);
        JSB_PRECONDITION2(ok, cx, false, "js_custom_classes_GameScene_create : Error processing arguments");

        auto ret = GameScene::create(arg0, arg1);
        js_type_class_t *typeClass = js_get_type_from_native<GameScene>(ret);
        JS::RootedObject jsret(cx, jsb_ref_autoreleased_create_jsobject(cx, ret, typeClass, "GameScene"));
        args.rval().set(OBJECT_TO_JSVAL(jsret));
        return true;
    }
    JS_ReportError(cx, "js_custom_classes_GameScene_create : wrong number of arguments");
    return false;
}

bool js_custom_classes_GameScene_getInstance(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    if (argc == 0) {

        auto ret = GameScene::getInstance();
        js_type_class_t *typeClass = js_get_type_from_native<GameScene>(ret);
        JS::RootedObject jsret(cx, jsb_ref_get_or_create_jsobject(cx, ret, typeClass, "GameScene"));
        args.rval().set(OBJECT_TO_JSVAL(jsret));
        return true;
    }
    JS_ReportError(cx, "js_custom_classes_GameScene_getInstance : wrong number of arguments");
    return false;
}


extern JSObject *jsb_cocos2d_Scene_prototype;

void js_register_custom_classes_GameScene(JSContext *cx, JS::HandleObject global) {
    jsb_GameScene_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_GameScene_class->name = "GameScene";
    jsb_GameScene_class->addProperty = JS_PropertyStub;
    jsb_GameScene_class->delProperty = JS_DeletePropertyStub;
    jsb_GameScene_class->getProperty = JS_PropertyStub;
    jsb_GameScene_class->setProperty = JS_StrictPropertyStub;
    jsb_GameScene_class->enumerate = JS_EnumerateStub;
    jsb_GameScene_class->resolve = JS_ResolveStub;
    jsb_GameScene_class->convert = JS_ConvertStub;
//
//    jsb_GameScene_class->finalize = js_ref_finalize;
//
    jsb_GameScene_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

    static JSPropertySpec properties[] = {
        JS_PSG("__nativeObj", js_is_native_obj, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_PS_END
    };

    static JSFunctionSpec funcs[] = {
        JS_FN("setPhysWorldScale", js_custom_classes_GameScene_setPhysWorldScale, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("simpleJScallback", js_custom_classes_GameScene_simpleJScallback, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getPhysWorldScale", js_custom_classes_GameScene_getPhysWorldScale, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    static JSFunctionSpec st_funcs[] = {
        JS_FN("create", js_custom_classes_GameScene_create, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getInstance", js_custom_classes_GameScene_getInstance, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    JS::RootedObject parent_proto(cx, jsb_cocos2d_Scene_prototype);
    jsb_GameScene_prototype = JS_InitClass(
        cx, global,
        parent_proto,
        jsb_GameScene_class,
        dummy_constructor<GameScene>, 0, // no constructor
        properties,
        funcs,
        NULL, // no static properties
        st_funcs);

    // add the proto and JSClass to the type->js info hash table
    JS::RootedObject proto(cx, jsb_GameScene_prototype);
    jsb_register_class<GameScene>(cx, jsb_GameScene_class, proto, parent_proto);
}
JSClass  *jsb_gm_Body_class;
JSObject *jsb_gm_Body_prototype;

bool js_custom_classes_Body_getVertices(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    gm::Body* cobj = (gm::Body *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_custom_classes_Body_getVertices : Invalid Native Object");
    if (argc == 0) {
        cocos2d::Vector<gm::Vec2Position *> ret = cobj->getVertices();
        jsval jsret = JSVAL_NULL;
        jsret = ccvector_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_custom_classes_Body_getVertices : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_custom_classes_Body_getAngularVelocity(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    gm::Body* cobj = (gm::Body *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_custom_classes_Body_getAngularVelocity : Invalid Native Object");
    if (argc == 0) {
        double ret = cobj->getAngularVelocity();
        jsval jsret = JSVAL_NULL;
        jsret = DOUBLE_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_custom_classes_Body_getAngularVelocity : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_custom_classes_Body_getContacts(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    gm::Body* cobj = (gm::Body *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_custom_classes_Body_getContacts : Invalid Native Object");
    if (argc == 0) {
        cocos2d::Vector<gm::BodyContact *> ret = cobj->getContacts();
        jsval jsret = JSVAL_NULL;
        jsret = ccvector_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_custom_classes_Body_getContacts : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_custom_classes_Body_getComponentJS(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    gm::Body* cobj = (gm::Body *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_custom_classes_Body_getComponentJS : Invalid Native Object");
    if (argc == 0) {
        cocos2d::ComponentJS* ret = cobj->getComponentJS();
        jsval jsret = JSVAL_NULL;
        if (ret) {
            jsret = OBJECT_TO_JSVAL(js_get_or_create_jsobject<cocos2d::ComponentJS>(cx, (cocos2d::ComponentJS*)ret));
        } else {
            jsret = JSVAL_NULL;
        };
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_custom_classes_Body_getComponentJS : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_custom_classes_Body_applyForceToCenter(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    gm::Body* cobj = (gm::Body *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_custom_classes_Body_applyForceToCenter : Invalid Native Object");
    if (argc == 1) {
        cocos2d::Vec2 arg0;
        ok &= jsval_to_vector2(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_custom_classes_Body_applyForceToCenter : Error processing arguments");
        cobj->applyForceToCenter(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_custom_classes_Body_applyForceToCenter : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_custom_classes_Body_setAngularVelocity(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    gm::Body* cobj = (gm::Body *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_custom_classes_Body_setAngularVelocity : Invalid Native Object");
    if (argc == 1) {
        double arg0 = 0;
        ok &= JS::ToNumber( cx, args.get(0), &arg0) && !isnan(arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_custom_classes_Body_setAngularVelocity : Error processing arguments");
        cobj->setAngularVelocity(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_custom_classes_Body_setAngularVelocity : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_custom_classes_Body_applyLinearImpulse(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    gm::Body* cobj = (gm::Body *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_custom_classes_Body_applyLinearImpulse : Invalid Native Object");
    if (argc == 2) {
        cocos2d::Vec2 arg0;
        cocos2d::Vec2 arg1;
        ok &= jsval_to_vector2(cx, args.get(0), &arg0);
        ok &= jsval_to_vector2(cx, args.get(1), &arg1);
        JSB_PRECONDITION2(ok, cx, false, "js_custom_classes_Body_applyLinearImpulse : Error processing arguments");
        cobj->applyLinearImpulse(arg0, arg1);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_custom_classes_Body_applyLinearImpulse : wrong number of arguments: %d, was expecting %d", argc, 2);
    return false;
}
bool js_custom_classes_Body_applyTorque(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    gm::Body* cobj = (gm::Body *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_custom_classes_Body_applyTorque : Invalid Native Object");
    if (argc == 1) {
        double arg0 = 0;
        ok &= JS::ToNumber( cx, args.get(0), &arg0) && !isnan(arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_custom_classes_Body_applyTorque : Error processing arguments");
        cobj->applyTorque(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_custom_classes_Body_applyTorque : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_custom_classes_Body_setDrawPosition(JSContext *cx, uint32_t argc, jsval *vp)
{
    bool ok = true;
    gm::Body* cobj = nullptr;

    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx);
    obj.set(args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cobj = (gm::Body *)(proxy ? proxy->ptr : nullptr);
    JSB_PRECONDITION2( cobj, cx, false, "js_custom_classes_Body_setDrawPosition : Invalid Native Object");
    do {
        if (argc == 2) {
            double arg0 = 0;
            ok &= JS::ToNumber( cx, args.get(0), &arg0) && !isnan(arg0);
            if (!ok) { ok = true; break; }
            double arg1 = 0;
            ok &= JS::ToNumber( cx, args.get(1), &arg1) && !isnan(arg1);
            if (!ok) { ok = true; break; }
            cobj->setDrawPosition(arg0, arg1);
            args.rval().setUndefined();
            return true;
        }
    } while(0);

    do {
        if (argc == 1) {
            cocos2d::Vec2 arg0;
            ok &= jsval_to_vector2(cx, args.get(0), &arg0);
            if (!ok) { ok = true; break; }
            cobj->setDrawPosition(arg0);
            args.rval().setUndefined();
            return true;
        }
    } while(0);

    JS_ReportError(cx, "js_custom_classes_Body_setDrawPosition : wrong number of arguments");
    return false;
}
bool js_custom_classes_Body_onContactEnd(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    gm::Body* cobj = (gm::Body *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_custom_classes_Body_onContactEnd : Invalid Native Object");
    if (argc == 1) {
        b2Contact* arg0 = nullptr;
        do {
            if (args.get(0).isNull()) { arg0 = nullptr; break; }
            if (!args.get(0).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JS::RootedObject tmpObj(cx, args.get(0).toObjectOrNull());
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg0 = (b2Contact*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
        } while (0);
        JSB_PRECONDITION2(ok, cx, false, "js_custom_classes_Body_onContactEnd : Error processing arguments");
        cobj->onContactEnd(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_custom_classes_Body_onContactEnd : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_custom_classes_Body_setFixedRotation(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    gm::Body* cobj = (gm::Body *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_custom_classes_Body_setFixedRotation : Invalid Native Object");
    if (argc == 1) {
        bool arg0;
        arg0 = JS::ToBoolean(args.get(0));
        JSB_PRECONDITION2(ok, cx, false, "js_custom_classes_Body_setFixedRotation : Error processing arguments");
        cobj->setFixedRotation(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_custom_classes_Body_setFixedRotation : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_custom_classes_Body_getB2Body(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    gm::Body* cobj = (gm::Body *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_custom_classes_Body_getB2Body : Invalid Native Object");
    if (argc == 0) {
        b2Body* ret = cobj->getB2Body();
        jsval jsret = JSVAL_NULL;
        if (ret) {
            jsret = OBJECT_TO_JSVAL(js_get_or_create_jsobject<b2Body>(cx, (b2Body*)ret));
        } else {
            jsret = JSVAL_NULL;
        };
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_custom_classes_Body_getB2Body : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_custom_classes_Body_applyForce(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    gm::Body* cobj = (gm::Body *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_custom_classes_Body_applyForce : Invalid Native Object");
    if (argc == 2) {
        cocos2d::Vec2 arg0;
        cocos2d::Vec2 arg1;
        ok &= jsval_to_vector2(cx, args.get(0), &arg0);
        ok &= jsval_to_vector2(cx, args.get(1), &arg1);
        JSB_PRECONDITION2(ok, cx, false, "js_custom_classes_Body_applyForce : Error processing arguments");
        cobj->applyForce(arg0, arg1);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_custom_classes_Body_applyForce : wrong number of arguments: %d, was expecting %d", argc, 2);
    return false;
}
bool js_custom_classes_Body_onContactPreSolve(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    gm::Body* cobj = (gm::Body *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_custom_classes_Body_onContactPreSolve : Invalid Native Object");
    if (argc == 1) {
        b2Contact* arg0 = nullptr;
        do {
            if (args.get(0).isNull()) { arg0 = nullptr; break; }
            if (!args.get(0).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JS::RootedObject tmpObj(cx, args.get(0).toObjectOrNull());
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg0 = (b2Contact*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
        } while (0);
        JSB_PRECONDITION2(ok, cx, false, "js_custom_classes_Body_onContactPreSolve : Error processing arguments");
        cobj->onContactPreSolve(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_custom_classes_Body_onContactPreSolve : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_custom_classes_Body_setLinearVelocity(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    gm::Body* cobj = (gm::Body *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_custom_classes_Body_setLinearVelocity : Invalid Native Object");
    if (argc == 1) {
        cocos2d::Vec2 arg0;
        ok &= jsval_to_vector2(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_custom_classes_Body_setLinearVelocity : Error processing arguments");
        cobj->setLinearVelocity(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_custom_classes_Body_setLinearVelocity : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_custom_classes_Body_applyAngularImpulse(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    gm::Body* cobj = (gm::Body *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_custom_classes_Body_applyAngularImpulse : Invalid Native Object");
    if (argc == 1) {
        double arg0 = 0;
        ok &= JS::ToNumber( cx, args.get(0), &arg0) && !isnan(arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_custom_classes_Body_applyAngularImpulse : Error processing arguments");
        cobj->applyAngularImpulse(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_custom_classes_Body_applyAngularImpulse : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_custom_classes_Body_getLinearVelocity(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    gm::Body* cobj = (gm::Body *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_custom_classes_Body_getLinearVelocity : Invalid Native Object");
    if (argc == 0) {
        cocos2d::Vec2 ret = cobj->getLinearVelocity();
        jsval jsret = JSVAL_NULL;
        jsret = vector2_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_custom_classes_Body_getLinearVelocity : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_custom_classes_Body_onContactBegin(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    gm::Body* cobj = (gm::Body *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_custom_classes_Body_onContactBegin : Invalid Native Object");
    if (argc == 1) {
        b2Contact* arg0 = nullptr;
        do {
            if (args.get(0).isNull()) { arg0 = nullptr; break; }
            if (!args.get(0).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JS::RootedObject tmpObj(cx, args.get(0).toObjectOrNull());
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg0 = (b2Contact*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
        } while (0);
        JSB_PRECONDITION2(ok, cx, false, "js_custom_classes_Body_onContactBegin : Error processing arguments");
        cobj->onContactBegin(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_custom_classes_Body_onContactBegin : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_custom_classes_Body_setDrawRotation(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    gm::Body* cobj = (gm::Body *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_custom_classes_Body_setDrawRotation : Invalid Native Object");
    if (argc == 1) {
        double arg0 = 0;
        ok &= JS::ToNumber( cx, args.get(0), &arg0) && !isnan(arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_custom_classes_Body_setDrawRotation : Error processing arguments");
        cobj->setDrawRotation(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_custom_classes_Body_setDrawRotation : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_custom_classes_Body_create(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    if (argc == 2) {
        b2Body* arg0 = nullptr;
        std::string arg1;
        do {
            if (args.get(0).isNull()) { arg0 = nullptr; break; }
            if (!args.get(0).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JS::RootedObject tmpObj(cx, args.get(0).toObjectOrNull());
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg0 = (b2Body*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
        } while (0);
        ok &= jsval_to_std_string(cx, args.get(1), &arg1);
        JSB_PRECONDITION2(ok, cx, false, "js_custom_classes_Body_create : Error processing arguments");

        auto ret = gm::Body::create(arg0, arg1);
        js_type_class_t *typeClass = js_get_type_from_native<gm::Body>(ret);
        JS::RootedObject jsret(cx, jsb_ref_autoreleased_create_jsobject(cx, ret, typeClass, "gm::Body"));
        args.rval().set(OBJECT_TO_JSVAL(jsret));
        return true;
    }
    JS_ReportError(cx, "js_custom_classes_Body_create : wrong number of arguments");
    return false;
}


extern JSObject *jsb_cocos2d_Node_prototype;

void js_register_custom_classes_Body(JSContext *cx, JS::HandleObject global) {
    jsb_gm_Body_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_gm_Body_class->name = "Body";
    jsb_gm_Body_class->addProperty = JS_PropertyStub;
    jsb_gm_Body_class->delProperty = JS_DeletePropertyStub;
    jsb_gm_Body_class->getProperty = JS_PropertyStub;
    jsb_gm_Body_class->setProperty = JS_StrictPropertyStub;
    jsb_gm_Body_class->enumerate = JS_EnumerateStub;
    jsb_gm_Body_class->resolve = JS_ResolveStub;
    jsb_gm_Body_class->convert = JS_ConvertStub;
//
//    jsb_gm_Body_class->finalize = js_ref_finalize;
//
    jsb_gm_Body_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

    static JSPropertySpec properties[] = {
        JS_PSG("__nativeObj", js_is_native_obj, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_PS_END
    };

    static JSFunctionSpec funcs[] = {
        JS_FN("getVertices", js_custom_classes_Body_getVertices, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getAngularVelocity", js_custom_classes_Body_getAngularVelocity, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getContacts", js_custom_classes_Body_getContacts, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getComponentJS", js_custom_classes_Body_getComponentJS, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("applyForceToCenter", js_custom_classes_Body_applyForceToCenter, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setAngularVelocity", js_custom_classes_Body_setAngularVelocity, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("applyLinearImpulse", js_custom_classes_Body_applyLinearImpulse, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("applyTorque", js_custom_classes_Body_applyTorque, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setDrawPosition", js_custom_classes_Body_setDrawPosition, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("onContactEnd", js_custom_classes_Body_onContactEnd, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setFixedRotation", js_custom_classes_Body_setFixedRotation, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getB2Body", js_custom_classes_Body_getB2Body, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("applyForce", js_custom_classes_Body_applyForce, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("onContactPreSolve", js_custom_classes_Body_onContactPreSolve, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setLinearVelocity", js_custom_classes_Body_setLinearVelocity, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("applyAngularImpulse", js_custom_classes_Body_applyAngularImpulse, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getLinearVelocity", js_custom_classes_Body_getLinearVelocity, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("onContactBegin", js_custom_classes_Body_onContactBegin, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setDrawRotation", js_custom_classes_Body_setDrawRotation, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    static JSFunctionSpec st_funcs[] = {
        JS_FN("create", js_custom_classes_Body_create, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    JS::RootedObject parent_proto(cx, jsb_cocos2d_Node_prototype);
    jsb_gm_Body_prototype = JS_InitClass(
        cx, global,
        parent_proto,
        jsb_gm_Body_class,
        dummy_constructor<gm::Body>, 0, // no constructor
        properties,
        funcs,
        NULL, // no static properties
        st_funcs);

    // add the proto and JSClass to the type->js info hash table
    JS::RootedObject proto(cx, jsb_gm_Body_prototype);
    jsb_register_class<gm::Body>(cx, jsb_gm_Body_class, proto, parent_proto);
}
JSClass  *jsb_gm_Vec2Position_class;
JSObject *jsb_gm_Vec2Position_prototype;

bool js_custom_classes_Vec2Position_getX(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    gm::Vec2Position* cobj = (gm::Vec2Position *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_custom_classes_Vec2Position_getX : Invalid Native Object");
    if (argc == 0) {
        double ret = cobj->getX();
        jsval jsret = JSVAL_NULL;
        jsret = DOUBLE_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_custom_classes_Vec2Position_getX : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_custom_classes_Vec2Position_getY(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    gm::Vec2Position* cobj = (gm::Vec2Position *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_custom_classes_Vec2Position_getY : Invalid Native Object");
    if (argc == 0) {
        double ret = cobj->getY();
        jsval jsret = JSVAL_NULL;
        jsret = DOUBLE_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_custom_classes_Vec2Position_getY : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_custom_classes_Vec2Position_constructor(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    double arg0 = 0;
    double arg1 = 0;
    ok &= JS::ToNumber( cx, args.get(0), &arg0) && !isnan(arg0);
    ok &= JS::ToNumber( cx, args.get(1), &arg1) && !isnan(arg1);
    JSB_PRECONDITION2(ok, cx, false, "js_custom_classes_Vec2Position_constructor : Error processing arguments");
    gm::Vec2Position* cobj = new (std::nothrow) gm::Vec2Position(arg0, arg1);

    js_type_class_t *typeClass = js_get_type_from_native<gm::Vec2Position>(cobj);

    // link the native object with the javascript object
    JS::RootedObject jsobj(cx, jsb_ref_create_jsobject(cx, cobj, typeClass, "gm::Vec2Position"));
    args.rval().set(OBJECT_TO_JSVAL(jsobj));
    if (JS_HasProperty(cx, jsobj, "_ctor", &ok) && ok)
        ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(jsobj), "_ctor", args);
    return true;
}


void js_register_custom_classes_Vec2Position(JSContext *cx, JS::HandleObject global) {
    jsb_gm_Vec2Position_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_gm_Vec2Position_class->name = "Vec2Position";
    jsb_gm_Vec2Position_class->addProperty = JS_PropertyStub;
    jsb_gm_Vec2Position_class->delProperty = JS_DeletePropertyStub;
    jsb_gm_Vec2Position_class->getProperty = JS_PropertyStub;
    jsb_gm_Vec2Position_class->setProperty = JS_StrictPropertyStub;
    jsb_gm_Vec2Position_class->enumerate = JS_EnumerateStub;
    jsb_gm_Vec2Position_class->resolve = JS_ResolveStub;
    jsb_gm_Vec2Position_class->convert = JS_ConvertStub;
//
//    jsb_gm_Vec2Position_class->finalize = js_ref_finalize;
//
    jsb_gm_Vec2Position_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

    static JSPropertySpec properties[] = {
        JS_PSG("__nativeObj", js_is_native_obj, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_PS_END
    };

    static JSFunctionSpec funcs[] = {
        JS_FN("getX", js_custom_classes_Vec2Position_getX, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getY", js_custom_classes_Vec2Position_getY, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    JSFunctionSpec *st_funcs = NULL;

    jsb_gm_Vec2Position_prototype = JS_InitClass(
        cx, global,
        JS::NullPtr(),
        jsb_gm_Vec2Position_class,
        js_custom_classes_Vec2Position_constructor, 0, // constructor
        properties,
        funcs,
        NULL, // no static properties
        st_funcs);

    // add the proto and JSClass to the type->js info hash table
    JS::RootedObject proto(cx, jsb_gm_Vec2Position_prototype);
    jsb_register_class<gm::Vec2Position>(cx, jsb_gm_Vec2Position_class, proto, JS::NullPtr());
}
JSClass  *jsb_gm_ManifoldPoint_class;
JSObject *jsb_gm_ManifoldPoint_prototype;

bool js_custom_classes_ManifoldPoint_getLocalPoint(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    gm::ManifoldPoint* cobj = (gm::ManifoldPoint *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_custom_classes_ManifoldPoint_getLocalPoint : Invalid Native Object");
    if (argc == 0) {
        cocos2d::Vec2 ret = cobj->getLocalPoint();
        jsval jsret = JSVAL_NULL;
        jsret = vector2_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_custom_classes_ManifoldPoint_getLocalPoint : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_custom_classes_ManifoldPoint_getNormalImpulse(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    gm::ManifoldPoint* cobj = (gm::ManifoldPoint *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_custom_classes_ManifoldPoint_getNormalImpulse : Invalid Native Object");
    if (argc == 0) {
        double ret = cobj->getNormalImpulse();
        jsval jsret = JSVAL_NULL;
        jsret = DOUBLE_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_custom_classes_ManifoldPoint_getNormalImpulse : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_custom_classes_ManifoldPoint_getTangentImpulse(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    gm::ManifoldPoint* cobj = (gm::ManifoldPoint *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_custom_classes_ManifoldPoint_getTangentImpulse : Invalid Native Object");
    if (argc == 0) {
        double ret = cobj->getTangentImpulse();
        jsval jsret = JSVAL_NULL;
        jsret = DOUBLE_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_custom_classes_ManifoldPoint_getTangentImpulse : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}

void js_register_custom_classes_ManifoldPoint(JSContext *cx, JS::HandleObject global) {
    jsb_gm_ManifoldPoint_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_gm_ManifoldPoint_class->name = "ManifoldPoint";
    jsb_gm_ManifoldPoint_class->addProperty = JS_PropertyStub;
    jsb_gm_ManifoldPoint_class->delProperty = JS_DeletePropertyStub;
    jsb_gm_ManifoldPoint_class->getProperty = JS_PropertyStub;
    jsb_gm_ManifoldPoint_class->setProperty = JS_StrictPropertyStub;
    jsb_gm_ManifoldPoint_class->enumerate = JS_EnumerateStub;
    jsb_gm_ManifoldPoint_class->resolve = JS_ResolveStub;
    jsb_gm_ManifoldPoint_class->convert = JS_ConvertStub;
//
//    jsb_gm_ManifoldPoint_class->finalize = js_ref_finalize;
//
    jsb_gm_ManifoldPoint_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

    static JSPropertySpec properties[] = {
        JS_PSG("__nativeObj", js_is_native_obj, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_PS_END
    };

    static JSFunctionSpec funcs[] = {
        JS_FN("getLocalPoint", js_custom_classes_ManifoldPoint_getLocalPoint, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getNormalImpulse", js_custom_classes_ManifoldPoint_getNormalImpulse, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getTangentImpulse", js_custom_classes_ManifoldPoint_getTangentImpulse, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    JSFunctionSpec *st_funcs = NULL;

    jsb_gm_ManifoldPoint_prototype = JS_InitClass(
        cx, global,
        JS::NullPtr(),
        jsb_gm_ManifoldPoint_class,
        dummy_constructor<gm::ManifoldPoint>, 0, // no constructor
        properties,
        funcs,
        NULL, // no static properties
        st_funcs);

    // add the proto and JSClass to the type->js info hash table
    JS::RootedObject proto(cx, jsb_gm_ManifoldPoint_prototype);
    jsb_register_class<gm::ManifoldPoint>(cx, jsb_gm_ManifoldPoint_class, proto, JS::NullPtr());
}
JSClass  *jsb_gm_BodyContact_class;
JSObject *jsb_gm_BodyContact_prototype;

bool js_custom_classes_BodyContact_getFriction(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    gm::BodyContact* cobj = (gm::BodyContact *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_custom_classes_BodyContact_getFriction : Invalid Native Object");
    if (argc == 0) {
        double ret = cobj->getFriction();
        jsval jsret = JSVAL_NULL;
        jsret = DOUBLE_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_custom_classes_BodyContact_getFriction : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_custom_classes_BodyContact_getBodyB(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    gm::BodyContact* cobj = (gm::BodyContact *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_custom_classes_BodyContact_getBodyB : Invalid Native Object");
    if (argc == 0) {
        gm::Body* ret = cobj->getBodyB();
        jsval jsret = JSVAL_NULL;
        if (ret) {
            jsret = OBJECT_TO_JSVAL(js_get_or_create_jsobject<gm::Body>(cx, (gm::Body*)ret));
        } else {
            jsret = JSVAL_NULL;
        };
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_custom_classes_BodyContact_getBodyB : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_custom_classes_BodyContact_getBodyA(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    gm::BodyContact* cobj = (gm::BodyContact *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_custom_classes_BodyContact_getBodyA : Invalid Native Object");
    if (argc == 0) {
        gm::Body* ret = cobj->getBodyA();
        jsval jsret = JSVAL_NULL;
        if (ret) {
            jsret = OBJECT_TO_JSVAL(js_get_or_create_jsobject<gm::Body>(cx, (gm::Body*)ret));
        } else {
            jsret = JSVAL_NULL;
        };
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_custom_classes_BodyContact_getBodyA : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_custom_classes_BodyContact_getRestitution(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    gm::BodyContact* cobj = (gm::BodyContact *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_custom_classes_BodyContact_getRestitution : Invalid Native Object");
    if (argc == 0) {
        double ret = cobj->getRestitution();
        jsval jsret = JSVAL_NULL;
        jsret = DOUBLE_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_custom_classes_BodyContact_getRestitution : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_custom_classes_BodyContact_resetFriction(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    gm::BodyContact* cobj = (gm::BodyContact *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_custom_classes_BodyContact_resetFriction : Invalid Native Object");
    if (argc == 0) {
        cobj->resetFriction();
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_custom_classes_BodyContact_resetFriction : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_custom_classes_BodyContact_setEnabled(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    gm::BodyContact* cobj = (gm::BodyContact *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_custom_classes_BodyContact_setEnabled : Invalid Native Object");
    if (argc == 1) {
        bool arg0;
        arg0 = JS::ToBoolean(args.get(0));
        JSB_PRECONDITION2(ok, cx, false, "js_custom_classes_BodyContact_setEnabled : Error processing arguments");
        cobj->setEnabled(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_custom_classes_BodyContact_setEnabled : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_custom_classes_BodyContact_isTouching(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    gm::BodyContact* cobj = (gm::BodyContact *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_custom_classes_BodyContact_isTouching : Invalid Native Object");
    if (argc == 0) {
        bool ret = cobj->isTouching();
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_custom_classes_BodyContact_isTouching : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_custom_classes_BodyContact_isEnabled(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    gm::BodyContact* cobj = (gm::BodyContact *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_custom_classes_BodyContact_isEnabled : Invalid Native Object");
    if (argc == 0) {
        bool ret = cobj->isEnabled();
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_custom_classes_BodyContact_isEnabled : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_custom_classes_BodyContact_setFriction(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    gm::BodyContact* cobj = (gm::BodyContact *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_custom_classes_BodyContact_setFriction : Invalid Native Object");
    if (argc == 1) {
        double arg0 = 0;
        ok &= JS::ToNumber( cx, args.get(0), &arg0) && !isnan(arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_custom_classes_BodyContact_setFriction : Error processing arguments");
        cobj->setFriction(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_custom_classes_BodyContact_setFriction : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_custom_classes_BodyContact_setTangentSpeed(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    gm::BodyContact* cobj = (gm::BodyContact *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_custom_classes_BodyContact_setTangentSpeed : Invalid Native Object");
    if (argc == 1) {
        double arg0 = 0;
        ok &= JS::ToNumber( cx, args.get(0), &arg0) && !isnan(arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_custom_classes_BodyContact_setTangentSpeed : Error processing arguments");
        cobj->setTangentSpeed(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_custom_classes_BodyContact_setTangentSpeed : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_custom_classes_BodyContact_getManifoldPoints(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    gm::BodyContact* cobj = (gm::BodyContact *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_custom_classes_BodyContact_getManifoldPoints : Invalid Native Object");
    if (argc == 0) {
        cocos2d::Vector<gm::ManifoldPoint *> ret = cobj->getManifoldPoints();
        jsval jsret = JSVAL_NULL;
        jsret = ccvector_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_custom_classes_BodyContact_getManifoldPoints : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_custom_classes_BodyContact_getTangentSpeed(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    gm::BodyContact* cobj = (gm::BodyContact *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_custom_classes_BodyContact_getTangentSpeed : Invalid Native Object");
    if (argc == 0) {
        double ret = cobj->getTangentSpeed();
        jsval jsret = JSVAL_NULL;
        jsret = DOUBLE_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_custom_classes_BodyContact_getTangentSpeed : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_custom_classes_BodyContact_getLocalPoint(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    gm::BodyContact* cobj = (gm::BodyContact *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_custom_classes_BodyContact_getLocalPoint : Invalid Native Object");
    if (argc == 0) {
        cocos2d::Vec2 ret = cobj->getLocalPoint();
        jsval jsret = JSVAL_NULL;
        jsret = vector2_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_custom_classes_BodyContact_getLocalPoint : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_custom_classes_BodyContact_setRestitution(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    gm::BodyContact* cobj = (gm::BodyContact *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_custom_classes_BodyContact_setRestitution : Invalid Native Object");
    if (argc == 1) {
        double arg0 = 0;
        ok &= JS::ToNumber( cx, args.get(0), &arg0) && !isnan(arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_custom_classes_BodyContact_setRestitution : Error processing arguments");
        cobj->setRestitution(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_custom_classes_BodyContact_setRestitution : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_custom_classes_BodyContact_getAnotherBody(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    gm::BodyContact* cobj = (gm::BodyContact *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_custom_classes_BodyContact_getAnotherBody : Invalid Native Object");
    if (argc == 1) {
        gm::Body* arg0 = nullptr;
        do {
            if (args.get(0).isNull()) { arg0 = nullptr; break; }
            if (!args.get(0).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JS::RootedObject tmpObj(cx, args.get(0).toObjectOrNull());
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg0 = (gm::Body*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
        } while (0);
        JSB_PRECONDITION2(ok, cx, false, "js_custom_classes_BodyContact_getAnotherBody : Error processing arguments");
        gm::Body* ret = cobj->getAnotherBody(arg0);
        jsval jsret = JSVAL_NULL;
        if (ret) {
            jsret = OBJECT_TO_JSVAL(js_get_or_create_jsobject<gm::Body>(cx, (gm::Body*)ret));
        } else {
            jsret = JSVAL_NULL;
        };
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_custom_classes_BodyContact_getAnotherBody : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_custom_classes_BodyContact_getLocalNormal(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    gm::BodyContact* cobj = (gm::BodyContact *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_custom_classes_BodyContact_getLocalNormal : Invalid Native Object");
    if (argc == 0) {
        cocos2d::Vec2 ret = cobj->getLocalNormal();
        jsval jsret = JSVAL_NULL;
        jsret = vector2_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_custom_classes_BodyContact_getLocalNormal : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_custom_classes_BodyContact_resetRestitution(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    gm::BodyContact* cobj = (gm::BodyContact *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_custom_classes_BodyContact_resetRestitution : Invalid Native Object");
    if (argc == 0) {
        cobj->resetRestitution();
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_custom_classes_BodyContact_resetRestitution : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_custom_classes_BodyContact_create(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    if (argc == 1) {
        b2Contact* arg0 = nullptr;
        do {
            if (args.get(0).isNull()) { arg0 = nullptr; break; }
            if (!args.get(0).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JS::RootedObject tmpObj(cx, args.get(0).toObjectOrNull());
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg0 = (b2Contact*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
        } while (0);
        JSB_PRECONDITION2(ok, cx, false, "js_custom_classes_BodyContact_create : Error processing arguments");

        auto ret = gm::BodyContact::create(arg0);
        js_type_class_t *typeClass = js_get_type_from_native<gm::BodyContact>(ret);
        JS::RootedObject jsret(cx, jsb_ref_autoreleased_create_jsobject(cx, ret, typeClass, "gm::BodyContact"));
        args.rval().set(OBJECT_TO_JSVAL(jsret));
        return true;
    }
    JS_ReportError(cx, "js_custom_classes_BodyContact_create : wrong number of arguments");
    return false;
}


void js_register_custom_classes_BodyContact(JSContext *cx, JS::HandleObject global) {
    jsb_gm_BodyContact_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_gm_BodyContact_class->name = "BodyContact";
    jsb_gm_BodyContact_class->addProperty = JS_PropertyStub;
    jsb_gm_BodyContact_class->delProperty = JS_DeletePropertyStub;
    jsb_gm_BodyContact_class->getProperty = JS_PropertyStub;
    jsb_gm_BodyContact_class->setProperty = JS_StrictPropertyStub;
    jsb_gm_BodyContact_class->enumerate = JS_EnumerateStub;
    jsb_gm_BodyContact_class->resolve = JS_ResolveStub;
    jsb_gm_BodyContact_class->convert = JS_ConvertStub;
//
//    jsb_gm_BodyContact_class->finalize = js_ref_finalize;
//
    jsb_gm_BodyContact_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

    static JSPropertySpec properties[] = {
        JS_PSG("__nativeObj", js_is_native_obj, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_PS_END
    };

    static JSFunctionSpec funcs[] = {
        JS_FN("getFriction", js_custom_classes_BodyContact_getFriction, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getBodyB", js_custom_classes_BodyContact_getBodyB, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getBodyA", js_custom_classes_BodyContact_getBodyA, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getRestitution", js_custom_classes_BodyContact_getRestitution, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("resetFriction", js_custom_classes_BodyContact_resetFriction, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setEnabled", js_custom_classes_BodyContact_setEnabled, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("isTouching", js_custom_classes_BodyContact_isTouching, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("isEnabled", js_custom_classes_BodyContact_isEnabled, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setFriction", js_custom_classes_BodyContact_setFriction, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setTangentSpeed", js_custom_classes_BodyContact_setTangentSpeed, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getManifoldPoints", js_custom_classes_BodyContact_getManifoldPoints, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getTangentSpeed", js_custom_classes_BodyContact_getTangentSpeed, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getLocalPoint", js_custom_classes_BodyContact_getLocalPoint, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setRestitution", js_custom_classes_BodyContact_setRestitution, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getAnotherBody", js_custom_classes_BodyContact_getAnotherBody, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getLocalNormal", js_custom_classes_BodyContact_getLocalNormal, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("resetRestitution", js_custom_classes_BodyContact_resetRestitution, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    static JSFunctionSpec st_funcs[] = {
        JS_FN("create", js_custom_classes_BodyContact_create, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    jsb_gm_BodyContact_prototype = JS_InitClass(
        cx, global,
        JS::NullPtr(),
        jsb_gm_BodyContact_class,
        dummy_constructor<gm::BodyContact>, 0, // no constructor
        properties,
        funcs,
        NULL, // no static properties
        st_funcs);

    // add the proto and JSClass to the type->js info hash table
    JS::RootedObject proto(cx, jsb_gm_BodyContact_prototype);
    jsb_register_class<gm::BodyContact>(cx, jsb_gm_BodyContact_class, proto, JS::NullPtr());
}
JSClass  *jsb_SplineBasedVegetation_class;
JSObject *jsb_SplineBasedVegetation_prototype;

bool js_custom_classes_SplineBasedVegetation_updateSpline(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    SplineBasedVegetation* cobj = (SplineBasedVegetation *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_custom_classes_SplineBasedVegetation_updateSpline : Invalid Native Object");
    if (argc == 0) {
        cobj->updateSpline();
        args.rval().setUndefined();
        return true;
    }
    if (argc == 1) {
        cocos2d::PointArray* arg0 = nullptr;
        do {
            if (args.get(0).isNull()) { arg0 = nullptr; break; }
            if (!args.get(0).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JS::RootedObject tmpObj(cx, args.get(0).toObjectOrNull());
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg0 = (cocos2d::PointArray*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
        } while (0);
        JSB_PRECONDITION2(ok, cx, false, "js_custom_classes_SplineBasedVegetation_updateSpline : Error processing arguments");
        cobj->updateSpline(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_custom_classes_SplineBasedVegetation_updateSpline : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_custom_classes_SplineBasedVegetation_growUp(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    SplineBasedVegetation* cobj = (SplineBasedVegetation *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_custom_classes_SplineBasedVegetation_growUp : Invalid Native Object");
    if (argc == 1) {
        double arg0 = 0;
        ok &= JS::ToNumber( cx, args.get(0), &arg0) && !isnan(arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_custom_classes_SplineBasedVegetation_growUp : Error processing arguments");
        cobj->growUp(arg0);
        args.rval().setUndefined();
        return true;
    }
    if (argc == 2) {
        double arg0 = 0;
        double arg1 = 0;
        ok &= JS::ToNumber( cx, args.get(0), &arg0) && !isnan(arg0);
        ok &= JS::ToNumber( cx, args.get(1), &arg1) && !isnan(arg1);
        JSB_PRECONDITION2(ok, cx, false, "js_custom_classes_SplineBasedVegetation_growUp : Error processing arguments");
        cobj->growUp(arg0, arg1);
        args.rval().setUndefined();
        return true;
    }
    if (argc == 3) {
        double arg0 = 0;
        double arg1 = 0;
        double arg2 = 0;
        ok &= JS::ToNumber( cx, args.get(0), &arg0) && !isnan(arg0);
        ok &= JS::ToNumber( cx, args.get(1), &arg1) && !isnan(arg1);
        ok &= JS::ToNumber( cx, args.get(2), &arg2) && !isnan(arg2);
        JSB_PRECONDITION2(ok, cx, false, "js_custom_classes_SplineBasedVegetation_growUp : Error processing arguments");
        cobj->growUp(arg0, arg1, arg2);
        args.rval().setUndefined();
        return true;
    }
    if (argc == 4) {
        double arg0 = 0;
        double arg1 = 0;
        double arg2 = 0;
        int arg3 = 0;
        ok &= JS::ToNumber( cx, args.get(0), &arg0) && !isnan(arg0);
        ok &= JS::ToNumber( cx, args.get(1), &arg1) && !isnan(arg1);
        ok &= JS::ToNumber( cx, args.get(2), &arg2) && !isnan(arg2);
        ok &= jsval_to_int32(cx, args.get(3), (int32_t *)&arg3);
        JSB_PRECONDITION2(ok, cx, false, "js_custom_classes_SplineBasedVegetation_growUp : Error processing arguments");
        cobj->growUp(arg0, arg1, arg2, arg3);
        args.rval().setUndefined();
        return true;
    }
    if (argc == 5) {
        double arg0 = 0;
        double arg1 = 0;
        double arg2 = 0;
        int arg3 = 0;
        bool arg4;
        ok &= JS::ToNumber( cx, args.get(0), &arg0) && !isnan(arg0);
        ok &= JS::ToNumber( cx, args.get(1), &arg1) && !isnan(arg1);
        ok &= JS::ToNumber( cx, args.get(2), &arg2) && !isnan(arg2);
        ok &= jsval_to_int32(cx, args.get(3), (int32_t *)&arg3);
        arg4 = JS::ToBoolean(args.get(4));
        JSB_PRECONDITION2(ok, cx, false, "js_custom_classes_SplineBasedVegetation_growUp : Error processing arguments");
        cobj->growUp(arg0, arg1, arg2, arg3, arg4);
        args.rval().setUndefined();
        return true;
    }
    if (argc == 6) {
        double arg0 = 0;
        double arg1 = 0;
        double arg2 = 0;
        int arg3 = 0;
        bool arg4;
        bool arg5;
        ok &= JS::ToNumber( cx, args.get(0), &arg0) && !isnan(arg0);
        ok &= JS::ToNumber( cx, args.get(1), &arg1) && !isnan(arg1);
        ok &= JS::ToNumber( cx, args.get(2), &arg2) && !isnan(arg2);
        ok &= jsval_to_int32(cx, args.get(3), (int32_t *)&arg3);
        arg4 = JS::ToBoolean(args.get(4));
        arg5 = JS::ToBoolean(args.get(5));
        JSB_PRECONDITION2(ok, cx, false, "js_custom_classes_SplineBasedVegetation_growUp : Error processing arguments");
        cobj->growUp(arg0, arg1, arg2, arg3, arg4, arg5);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_custom_classes_SplineBasedVegetation_growUp : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_custom_classes_SplineBasedVegetation_initWithFilename(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    SplineBasedVegetation* cobj = (SplineBasedVegetation *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_custom_classes_SplineBasedVegetation_initWithFilename : Invalid Native Object");
    if (argc == 3) {
        cocos2d::PointArray* arg0 = nullptr;
        std::string arg1;
        cocos2d::Vec2 arg2;
        do {
            if (args.get(0).isNull()) { arg0 = nullptr; break; }
            if (!args.get(0).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JS::RootedObject tmpObj(cx, args.get(0).toObjectOrNull());
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg0 = (cocos2d::PointArray*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
        } while (0);
        ok &= jsval_to_std_string(cx, args.get(1), &arg1);
        ok &= jsval_to_vector2(cx, args.get(2), &arg2);
        JSB_PRECONDITION2(ok, cx, false, "js_custom_classes_SplineBasedVegetation_initWithFilename : Error processing arguments");
        bool ret = cobj->initWithFilename(arg0, arg1, arg2);
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_custom_classes_SplineBasedVegetation_initWithFilename : wrong number of arguments: %d, was expecting %d", argc, 3);
    return false;
}
bool js_custom_classes_SplineBasedVegetation_createWithFilename_jsb(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    if (argc == 3) {
        cocos2d::Vec2* arg0 = nullptr;
        int arg1 = 0;
        std::string arg2;
        std::vector<cocos2d::Vec2> tempData;ok &= jsval_to_vector_vec2(cx, args.get(0), &tempData);arg0=tempData.data();
        ok &= jsval_to_int32(cx, args.get(1), (int32_t *)&arg1);
        ok &= jsval_to_std_string(cx, args.get(2), &arg2);
        JSB_PRECONDITION2(ok, cx, false, "js_custom_classes_SplineBasedVegetation_createWithFilename_jsb : Error processing arguments");

        SplineBasedVegetation* ret = SplineBasedVegetation::createWithFilename_jsb(arg0, arg1, arg2);
        jsval jsret = JSVAL_NULL;
        if (ret) {
        jsret = OBJECT_TO_JSVAL(js_get_or_create_jsobject<SplineBasedVegetation>(cx, (SplineBasedVegetation*)ret));
    } else {
        jsret = JSVAL_NULL;
    };
        args.rval().set(jsret);
        return true;
    }
    if (argc == 4) {
        cocos2d::Vec2* arg0 = nullptr;
        int arg1 = 0;
        std::string arg2;
        cocos2d::Vec2 arg3;
        std::vector<cocos2d::Vec2> tempData;ok &= jsval_to_vector_vec2(cx, args.get(0), &tempData);arg0=tempData.data();
        ok &= jsval_to_int32(cx, args.get(1), (int32_t *)&arg1);
        ok &= jsval_to_std_string(cx, args.get(2), &arg2);
        ok &= jsval_to_vector2(cx, args.get(3), &arg3);
        JSB_PRECONDITION2(ok, cx, false, "js_custom_classes_SplineBasedVegetation_createWithFilename_jsb : Error processing arguments");

        SplineBasedVegetation* ret = SplineBasedVegetation::createWithFilename_jsb(arg0, arg1, arg2, arg3);
        jsval jsret = JSVAL_NULL;
        if (ret) {
        jsret = OBJECT_TO_JSVAL(js_get_or_create_jsobject<SplineBasedVegetation>(cx, (SplineBasedVegetation*)ret));
    } else {
        jsret = JSVAL_NULL;
    };
        args.rval().set(jsret);
        return true;
    }
    JS_ReportError(cx, "js_custom_classes_SplineBasedVegetation_createWithFilename_jsb : wrong number of arguments");
    return false;
}


void js_register_custom_classes_SplineBasedVegetation(JSContext *cx, JS::HandleObject global) {
    jsb_SplineBasedVegetation_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_SplineBasedVegetation_class->name = "SplineBasedVegetation";
    jsb_SplineBasedVegetation_class->addProperty = JS_PropertyStub;
    jsb_SplineBasedVegetation_class->delProperty = JS_DeletePropertyStub;
    jsb_SplineBasedVegetation_class->getProperty = JS_PropertyStub;
    jsb_SplineBasedVegetation_class->setProperty = JS_StrictPropertyStub;
    jsb_SplineBasedVegetation_class->enumerate = JS_EnumerateStub;
    jsb_SplineBasedVegetation_class->resolve = JS_ResolveStub;
    jsb_SplineBasedVegetation_class->convert = JS_ConvertStub;
//
//    jsb_SplineBasedVegetation_class->finalize = js_ref_finalize;
//
    jsb_SplineBasedVegetation_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

    static JSPropertySpec properties[] = {
        JS_PSG("__nativeObj", js_is_native_obj, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_PS_END
    };

    static JSFunctionSpec funcs[] = {
        JS_FN("updateSpline", js_custom_classes_SplineBasedVegetation_updateSpline, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("growUp", js_custom_classes_SplineBasedVegetation_growUp, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("initWithFilename", js_custom_classes_SplineBasedVegetation_initWithFilename, 3, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    static JSFunctionSpec st_funcs[] = {
        JS_FN("createWithFile", js_custom_classes_SplineBasedVegetation_createWithFilename_jsb, 3, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    jsb_SplineBasedVegetation_prototype = JS_InitClass(
        cx, global,
        JS::NullPtr(),
        jsb_SplineBasedVegetation_class,
        dummy_constructor<SplineBasedVegetation>, 0, // no constructor
        properties,
        funcs,
        NULL, // no static properties
        st_funcs);

    // add the proto and JSClass to the type->js info hash table
    JS::RootedObject proto(cx, jsb_SplineBasedVegetation_prototype);
    jsb_register_class<SplineBasedVegetation>(cx, jsb_SplineBasedVegetation_class, proto, JS::NullPtr());
}
void register_all_custom_classes(JSContext* cx, JS::HandleObject obj) {
    // Get the ns
    JS::RootedObject ns(cx);
    get_or_create_js_obj(cx, obj, "gm", &ns);

    js_register_custom_classes_Body(cx, ns);
    js_register_custom_classes_ManifoldPoint(cx, ns);
    js_register_custom_classes_SplineBasedVegetation(cx, ns);
    js_register_custom_classes_Vec2Position(cx, ns);
    js_register_custom_classes_BodyContact(cx, ns);
    js_register_custom_classes_GameScene(cx, ns);
}

