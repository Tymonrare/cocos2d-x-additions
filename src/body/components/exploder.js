test = cc.ComponentJS.extend({
    // add a new enemy every second
    onEnter: function() {
    },
    onAdd:function(){
    },
    onInit:function(){
    },
    update: function(dt) {
    },
    onContactPreSolve:function(count){
      var cont = this.getOwner().getContacts();
      for(var i in cont){
        var another = cont[i].getAnotherBody(this.getOwner());
        if(another)
          another.applyAngularImpulse(180);
          else {
            this.getOwner().applyTorque(100);
          }
      }
    },
    onContactBegin:function(count){
    },
    onContactEnd:function(count){
    }
});
