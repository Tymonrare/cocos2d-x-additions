test = cc.ComponentJS.extend({
    // add a new enemy every second
    onEnter: function() {
      var verts = this.getOwner().getVertices();
      cc.log(verts);
      var vertices3 = [cc.p(0, 0), cc.p(0, 100)];
      var veg = gm.SplineBasedVegetation.createWithFile(vertices3, 2, "res/images/flowers2.png")
      this.getOwner().addChild(veg);
      veg.growUp(0.1, 0.1, 20);
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
