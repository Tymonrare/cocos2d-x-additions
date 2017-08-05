test = cc.ComponentJS.extend({
    ctor : function(){
      this._super();
      associateWithNative(this, cc.ComponentJS);
      cc.log("ctor")
    },
    // add a new enemy every second
    onEnter: function() {
        cc.log("enter body component");
  cc.log(this.getOwner());
    },
    onAdd:function(){
      cc.log("add body component");
    },
    onInit:function(){
      cc.log("init body component");
    },

    update: function(dt) {

    },
    test:function(d){
      cc.log("tested: ", d);
    },
    onContactPreSolve:function(c){
      cc.log("contact presolve", c)
    },
    onContactBegin:function(c){
      cc.log("contact begin", c)

    },
    onContactEnd:function(c){
      cc.log("contact end", c)
    }
});
