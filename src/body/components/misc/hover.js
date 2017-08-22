test = cc.ComponentJS.extend({
    // add a new enemy every second
    onEnter: function() {
    },
    onAdd:function(){
    },
    onInit:function(){
    },
    update: function(dt) {
        var vel = this.getOwner().getLinearVelocity();
        this.getOwner().setLinearVelocity(cc.p(vel.x*0.9, vel.y*0.9));
    },
    onContactPreSolve:function(count){
    },
    onContactBegin:function(count){
    },
    onContactEnd:function(count){
    }
});
