test = cc.ComponentJS.extend({
    // add a new enemy every second
    onEnter: function() {
      var verts = this.getOwner().getVertices();
      var passVerts = [];
      for(var i in verts){
        passVerts.push(cc.p(verts[i].getX(), verts[i].getY()))
      }
      var veg = gm.SplineBasedVegetation.createWithFile(passVerts, passVerts.length, "res/images/flowers2.png")
      this.getOwner().addChild(veg);
      veg.growUp(0.01, 0.1, 20, 5);
      //veg.setScale(20, 20);
    },
    onAdd:function(){
    },
    onInit:function(){
    },
    update: function(dt) {
    },
    onContactPreSolve:function(count){
    },
    onContactBegin:function(count){
    },
    onContactEnd:function(count){
    }
});
