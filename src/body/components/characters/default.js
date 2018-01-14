test = cc.ComponentJS.extend({
    // add a new enemy every second
    onEnter: function() {
      if ('keyboard' in cc.sys.capabilities) {
        self = this;
          cc.eventManager.addListener({
              event: cc.EventListener.KEYBOARD,
              onKeyPressed: function (key, event) {
                  var strTemp = "Key down:" + key;
                  var keyStr = self.getKeyStr(key);
                  if(keyStr == "d"){
                    self.moveDir.x += 1;
                  }
                  if(keyStr == "a"){
                    self.moveDir.x += -1;
                  }
                  if(keyStr == "space"){
                    self.jumping = true;
                    self.moveCharacter(0, 2000);
                  }
              },
              onKeyReleased: function (key, event) {
                var strTemp = "Key down:" + key;
                var keyStr = self.getKeyStr(key);
                if(keyStr == "d"){
                  self.moveDir.x -= 1;
                }
                if(keyStr == "a"){
                  self.moveDir.x -= -1;
                }
                if(keyStr == "space"){
                  self.jumping = false;
                }
              }
          }, this.getOwner());
        }
    },
    moveCharacter:function(x, y){
        this.getOwner().applyLinearImpulse(cc.p(x, y), cc.p(0,0));
    },
    onAdd:function(){
      this.moveDir = cc.p(0,0);
      this.maxXSpeed = 1000;
      this.jumping = false;
      this.onGround = false;
    },
    onInit:function(){
    },
    update: function(dt) {
      var vel = this.getOwner().getLinearVelocity();

      if(this.moveDir.x || this.moveDir.y){
          this.moveCharacter(this.moveDir.x*(this.maxXSpeed-Math.abs(vel.x))*(((Math.abs(vel.x))/this.maxXSpeed)+0.2), this.moveDir.y);
    }


      var p = this.getOwner().getPosition();
      cc.director.getRunningScene().setPosition(-p.x+640,-p.y+360)

      if(!this.jumping)
        this.moveCharacter(0, -100);
      if(!this.moveDir.x || vel.x){
          this.getOwner().applyForceToCenter(cc.p(-vel.x*10, 0));
      }

    },
    onContactPreSolve:function(count){
    },
    onContactBegin:function(count){
      return; //FIXME: Sometimes causes errors
      var contacts = this.getOwner().getContacts();
      for(var i in contacts){
        var mpoints = contacts[i].getManifoldPoints();
        //cc.log(mpoints.length);
        for(var ii in mpoints){
          var v = mpoints[ii].getLocalPoint();
          //cc.log(v.x, v.y);
        }
      }
    },
    onContactEnd:function(count){
      var contacts = this.getOwner().getContacts();
      var allowJump = false;
      for(var i in contacts){
        if(contacts[i].getLocalNormal.y > 0.5){
          allowJump = true;
        }
      }
      this.onGround = allowJump;
    },
    getKeyStr: function (keycode)
    {
        if (keycode == cc.KEY.none)
        {
            return "";
        }

        for (var keyTemp in cc.KEY)
        {
            if (cc.KEY[keyTemp] == keycode)
            {
                return keyTemp;
            }
        }
        return "";
    }
});
