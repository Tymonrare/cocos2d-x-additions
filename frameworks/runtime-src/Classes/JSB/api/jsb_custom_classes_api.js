/**
 * @module custom_classes
 */
var gm = gm || {};

/**
 * @class GameScene
 */
gm.GameScene = {

/**
 * @method setPhysWorldScale
 * @param {float} arg0
 */
setPhysWorldScale : function (
float 
)
{
},

/**
 * @method simpleJScallback
 */
simpleJScallback : function (
)
{
},

/**
 * @method getPhysWorldScale
 * @return {float}
 */
getPhysWorldScale : function (
)
{
    return 0;
},

/**
 * @method create
 * @param {String} arg0
 * @param {String} arg1
 * @return {GameScene}
 */
create : function (
str, 
str 
)
{
    return GameScene;
},

/**
 * @method getInstance
 * @return {GameScene}
 */
getInstance : function (
)
{
    return GameScene;
},

};

/**
 * @class Body
 */
gm.Body = {

/**
 * @method getAngularVelocity
 * @return {float}
 */
getAngularVelocity : function (
)
{
    return 0;
},

/**
 * @method getContacts
 * @return {Array}
 */
getContacts : function (
)
{
    return new Array();
},

/**
 * @method getComponentJS
 * @return {cc.ComponentJS}
 */
getComponentJS : function (
)
{
    return cc.ComponentJS;
},

/**
 * @method applyForceToCenter
 * @param {vec2_object} arg0
 */
applyForceToCenter : function (
vec2 
)
{
},

/**
 * @method setAngularVelocity
 * @param {float} arg0
 */
setAngularVelocity : function (
float 
)
{
},

/**
 * @method applyLinearImpulse
 * @param {vec2_object} arg0
 * @param {vec2_object} arg1
 */
applyLinearImpulse : function (
vec2, 
vec2 
)
{
},

/**
 * @method applyTorque
 * @param {float} arg0
 */
applyTorque : function (
float 
)
{
},

/**
 * @method setDrawPosition
* @param {float|vec2_object} float
* @param {float} float
*/
setDrawPosition : function(
float,
float 
)
{
},

/**
 * @method onContactEnd
 * @param {b2Contact} arg0
 */
onContactEnd : function (
b2contact 
)
{
},

/**
 * @method setFixedRotation
 * @param {bool} arg0
 */
setFixedRotation : function (
bool 
)
{
},

/**
 * @method getB2Body
 * @return {b2Body}
 */
getB2Body : function (
)
{
    return b2Body;
},

/**
 * @method applyForce
 * @param {vec2_object} arg0
 * @param {vec2_object} arg1
 */
applyForce : function (
vec2, 
vec2 
)
{
},

/**
 * @method onContactPreSolve
 * @param {b2Contact} arg0
 */
onContactPreSolve : function (
b2contact 
)
{
},

/**
 * @method setLinearVelocity
 * @param {vec2_object} arg0
 */
setLinearVelocity : function (
vec2 
)
{
},

/**
 * @method applyAngularImpulse
 * @param {float} arg0
 */
applyAngularImpulse : function (
float 
)
{
},

/**
 * @method getLinearVelocity
 * @return {vec2_object}
 */
getLinearVelocity : function (
)
{
    return cc.Vec2;
},

/**
 * @method onContactBegin
 * @param {b2Contact} arg0
 */
onContactBegin : function (
b2contact 
)
{
},

/**
 * @method setDrawRotation
 * @param {float} arg0
 */
setDrawRotation : function (
float 
)
{
},

/**
 * @method create
 * @param {b2Body} arg0
 * @param {String} arg1
 * @return {gm::Body}
 */
create : function (
b2body, 
str 
)
{
    return gm::Body;
},

};

/**
 * @class ManifoldPoint
 */
gm.ManifoldPoint = {

/**
 * @method getLocalPoint
 * @return {vec2_object}
 */
getLocalPoint : function (
)
{
    return cc.Vec2;
},

/**
 * @method getNormalImpulse
 * @return {float}
 */
getNormalImpulse : function (
)
{
    return 0;
},

/**
 * @method getTangentImpulse
 * @return {float}
 */
getTangentImpulse : function (
)
{
    return 0;
},

};

/**
 * @class BodyContact
 */
gm.BodyContact = {

/**
 * @method getFriction
 * @return {float}
 */
getFriction : function (
)
{
    return 0;
},

/**
 * @method getBodyB
 * @return {gm::Body}
 */
getBodyB : function (
)
{
    return gm::Body;
},

/**
 * @method getBodyA
 * @return {gm::Body}
 */
getBodyA : function (
)
{
    return gm::Body;
},

/**
 * @method getRestitution
 * @return {float}
 */
getRestitution : function (
)
{
    return 0;
},

/**
 * @method resetFriction
 */
resetFriction : function (
)
{
},

/**
 * @method setEnabled
 * @param {bool} arg0
 */
setEnabled : function (
bool 
)
{
},

/**
 * @method isTouching
 * @return {bool}
 */
isTouching : function (
)
{
    return false;
},

/**
 * @method isEnabled
 * @return {bool}
 */
isEnabled : function (
)
{
    return false;
},

/**
 * @method setFriction
 * @param {float} arg0
 */
setFriction : function (
float 
)
{
},

/**
 * @method setTangentSpeed
 * @param {float} arg0
 */
setTangentSpeed : function (
float 
)
{
},

/**
 * @method getManifoldPoints
 * @return {Array}
 */
getManifoldPoints : function (
)
{
    return new Array();
},

/**
 * @method getTangentSpeed
 * @return {float}
 */
getTangentSpeed : function (
)
{
    return 0;
},

/**
 * @method getLocalPoint
 * @return {vec2_object}
 */
getLocalPoint : function (
)
{
    return cc.Vec2;
},

/**
 * @method setRestitution
 * @param {float} arg0
 */
setRestitution : function (
float 
)
{
},

/**
 * @method getAnotherBody
 * @param {gm::Body} arg0
 * @return {gm::Body}
 */
getAnotherBody : function (
body 
)
{
    return gm::Body;
},

/**
 * @method getLocalNormal
 * @return {vec2_object}
 */
getLocalNormal : function (
)
{
    return cc.Vec2;
},

/**
 * @method resetRestitution
 */
resetRestitution : function (
)
{
},

/**
 * @method create
 * @param {b2Contact} arg0
 * @return {gm::BodyContact}
 */
create : function (
b2contact 
)
{
    return gm::BodyContact;
},

};

/**
 * @class SplineBasedVegetation
 */
gm.SplineBasedVegetation = {

/**
 * @method updateSpline
 */
updateSpline : function (
)
{
},

/**
 * @method growUp
 * @param {float} arg0
 * @param {float} arg1
 * @param {float} arg2
 * @param {int} arg3
 * @param {bool} arg4
 * @param {bool} arg5
 */
growUp : function (
float, 
float, 
float, 
int, 
bool, 
bool 
)
{
},

/**
 * @method initWithFilename
 * @param {point_object} arg0
 * @param {String} arg1
 * @param {vec2_object} arg2
 * @return {bool}
 */
initWithFilename : function (
pointarray, 
str, 
vec2 
)
{
    return false;
},

/**
 * @method createWithFilename_jsb
 * @param {vec2_object} arg0
 * @param {int} arg1
 * @param {String} arg2
 * @param {vec2_object} arg3
 * @return {SplineBasedVegetation}
 */
createWithFilename_jsb : function (
vec2, 
int, 
str, 
vec2 
)
{
    return SplineBasedVegetation;
},

};
