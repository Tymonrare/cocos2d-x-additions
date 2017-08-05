test = cc.ComponentJS.extend({
    // add a new enemy every second
    onEnter: function() {
    },
    onAdd:function(){
    },
    onInit:function(){
    },
    targetUP : 100,
    currProgress : 0,
    currDirection : 1,
    update: function(dt) {
      this.currProgress += 3*this.currDirection;
      if(this.currProgress > this.targetUP || this.currProgress < 0) this.currDirection *= -1;
      this.getOwner().setPositionY(this.getOwner().getPositionY() + 3*this.currDirection);
    },
    onContactPreSolve:function(count){
    },
    onContactBegin:function(count){
    },
    onContactEnd:function(count){
    }
});
