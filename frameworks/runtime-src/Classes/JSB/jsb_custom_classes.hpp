#include "base/ccConfig.h"
#ifndef __custom_classes_h__
#define __custom_classes_h__

#include "jsapi.h"
#include "jsfriendapi.h"

extern JSClass  *jsb_GameScene_class;
extern JSObject *jsb_GameScene_prototype;

bool js_custom_classes_GameScene_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_custom_classes_GameScene_finalize(JSContext *cx, JSObject *obj);
void js_register_custom_classes_GameScene(JSContext *cx, JS::HandleObject global);
void register_all_custom_classes(JSContext* cx, JS::HandleObject obj);
bool js_custom_classes_GameScene_setPhysWorldScale(JSContext *cx, uint32_t argc, jsval *vp);
bool js_custom_classes_GameScene_simpleJScallback(JSContext *cx, uint32_t argc, jsval *vp);
bool js_custom_classes_GameScene_getPhysWorldScale(JSContext *cx, uint32_t argc, jsval *vp);
bool js_custom_classes_GameScene_create(JSContext *cx, uint32_t argc, jsval *vp);
bool js_custom_classes_GameScene_getInstance(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_gm_Body_class;
extern JSObject *jsb_gm_Body_prototype;

bool js_custom_classes_Body_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_custom_classes_Body_finalize(JSContext *cx, JSObject *obj);
void js_register_custom_classes_Body(JSContext *cx, JS::HandleObject global);
void register_all_custom_classes(JSContext* cx, JS::HandleObject obj);
bool js_custom_classes_Body_getAngularVelocity(JSContext *cx, uint32_t argc, jsval *vp);
bool js_custom_classes_Body_getContacts(JSContext *cx, uint32_t argc, jsval *vp);
bool js_custom_classes_Body_getComponentJS(JSContext *cx, uint32_t argc, jsval *vp);
bool js_custom_classes_Body_applyForceToCenter(JSContext *cx, uint32_t argc, jsval *vp);
bool js_custom_classes_Body_setAngularVelocity(JSContext *cx, uint32_t argc, jsval *vp);
bool js_custom_classes_Body_applyLinearImpulse(JSContext *cx, uint32_t argc, jsval *vp);
bool js_custom_classes_Body_applyTorque(JSContext *cx, uint32_t argc, jsval *vp);
bool js_custom_classes_Body_setDrawPosition(JSContext *cx, uint32_t argc, jsval *vp);
bool js_custom_classes_Body_onContactEnd(JSContext *cx, uint32_t argc, jsval *vp);
bool js_custom_classes_Body_setFixedRotation(JSContext *cx, uint32_t argc, jsval *vp);
bool js_custom_classes_Body_getB2Body(JSContext *cx, uint32_t argc, jsval *vp);
bool js_custom_classes_Body_applyForce(JSContext *cx, uint32_t argc, jsval *vp);
bool js_custom_classes_Body_onContactPreSolve(JSContext *cx, uint32_t argc, jsval *vp);
bool js_custom_classes_Body_setLinearVelocity(JSContext *cx, uint32_t argc, jsval *vp);
bool js_custom_classes_Body_applyAngularImpulse(JSContext *cx, uint32_t argc, jsval *vp);
bool js_custom_classes_Body_getLinearVelocity(JSContext *cx, uint32_t argc, jsval *vp);
bool js_custom_classes_Body_onContactBegin(JSContext *cx, uint32_t argc, jsval *vp);
bool js_custom_classes_Body_setDrawRotation(JSContext *cx, uint32_t argc, jsval *vp);
bool js_custom_classes_Body_create(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_gm_ManifoldPoint_class;
extern JSObject *jsb_gm_ManifoldPoint_prototype;

bool js_custom_classes_ManifoldPoint_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_custom_classes_ManifoldPoint_finalize(JSContext *cx, JSObject *obj);
void js_register_custom_classes_ManifoldPoint(JSContext *cx, JS::HandleObject global);
void register_all_custom_classes(JSContext* cx, JS::HandleObject obj);
bool js_custom_classes_ManifoldPoint_getLocalPoint(JSContext *cx, uint32_t argc, jsval *vp);
bool js_custom_classes_ManifoldPoint_getNormalImpulse(JSContext *cx, uint32_t argc, jsval *vp);
bool js_custom_classes_ManifoldPoint_getTangentImpulse(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_gm_BodyContact_class;
extern JSObject *jsb_gm_BodyContact_prototype;

bool js_custom_classes_BodyContact_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_custom_classes_BodyContact_finalize(JSContext *cx, JSObject *obj);
void js_register_custom_classes_BodyContact(JSContext *cx, JS::HandleObject global);
void register_all_custom_classes(JSContext* cx, JS::HandleObject obj);
bool js_custom_classes_BodyContact_getFriction(JSContext *cx, uint32_t argc, jsval *vp);
bool js_custom_classes_BodyContact_getBodyB(JSContext *cx, uint32_t argc, jsval *vp);
bool js_custom_classes_BodyContact_getBodyA(JSContext *cx, uint32_t argc, jsval *vp);
bool js_custom_classes_BodyContact_getRestitution(JSContext *cx, uint32_t argc, jsval *vp);
bool js_custom_classes_BodyContact_resetFriction(JSContext *cx, uint32_t argc, jsval *vp);
bool js_custom_classes_BodyContact_setEnabled(JSContext *cx, uint32_t argc, jsval *vp);
bool js_custom_classes_BodyContact_isTouching(JSContext *cx, uint32_t argc, jsval *vp);
bool js_custom_classes_BodyContact_isEnabled(JSContext *cx, uint32_t argc, jsval *vp);
bool js_custom_classes_BodyContact_setFriction(JSContext *cx, uint32_t argc, jsval *vp);
bool js_custom_classes_BodyContact_setTangentSpeed(JSContext *cx, uint32_t argc, jsval *vp);
bool js_custom_classes_BodyContact_getManifoldPoints(JSContext *cx, uint32_t argc, jsval *vp);
bool js_custom_classes_BodyContact_getTangentSpeed(JSContext *cx, uint32_t argc, jsval *vp);
bool js_custom_classes_BodyContact_getLocalPoint(JSContext *cx, uint32_t argc, jsval *vp);
bool js_custom_classes_BodyContact_setRestitution(JSContext *cx, uint32_t argc, jsval *vp);
bool js_custom_classes_BodyContact_getAnotherBody(JSContext *cx, uint32_t argc, jsval *vp);
bool js_custom_classes_BodyContact_getLocalNormal(JSContext *cx, uint32_t argc, jsval *vp);
bool js_custom_classes_BodyContact_resetRestitution(JSContext *cx, uint32_t argc, jsval *vp);
bool js_custom_classes_BodyContact_create(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_SplineBasedVegetation_class;
extern JSObject *jsb_SplineBasedVegetation_prototype;

bool js_custom_classes_SplineBasedVegetation_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_custom_classes_SplineBasedVegetation_finalize(JSContext *cx, JSObject *obj);
void js_register_custom_classes_SplineBasedVegetation(JSContext *cx, JS::HandleObject global);
void register_all_custom_classes(JSContext* cx, JS::HandleObject obj);
bool js_custom_classes_SplineBasedVegetation_updateSpline(JSContext *cx, uint32_t argc, jsval *vp);
bool js_custom_classes_SplineBasedVegetation_growUp(JSContext *cx, uint32_t argc, jsval *vp);
bool js_custom_classes_SplineBasedVegetation_initWithFilename(JSContext *cx, uint32_t argc, jsval *vp);
bool js_custom_classes_SplineBasedVegetation_createWithFilename_jsb(JSContext *cx, uint32_t argc, jsval *vp);

#endif // __custom_classes_h__
