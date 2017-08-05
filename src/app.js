
var HelloWorldLayer = cc.Layer.extend({
    sprite:null,
    ctor:function () {
        //////////////////////////////
        // 1. super init first
        this._super();

        /////////////////////////////
        // 2. add a menu item with "X" image, which is clicked to quit the program
        //    you may modify it.
        // ask the window size
        var size = cc.winSize;

        /////////////////////////////
        // 3. add your codes below...
        // add a label shows "Hello World"
        // create and initialize a label
        var helloLabel = new cc.LabelTTF("Hello World", "Arial", 38);
        // position the label on the center of the screen
        helloLabel.x = size.width / 2;
        helloLabel.y = size.height / 2 + 200;
        // add the label as a child to this layer
        this.addChild(helloLabel, 5);

        // add "HelloWorld" splash screen"
        this.sprite = new cc.Sprite(res.HelloWorld_png);
        this.sprite.attr({
            x: size.width / 2,
            y: size.height / 2
        });
        this.addChild(this.sprite, 0);

        return true;
    }
});

var HelloWorldScene = cc.Scene.extend({
    onEnter:function () {
        this._super();
        var layer = new HelloWorldLayer();
        this.addChild(layer);

        var sc = gm.GameScene.create("", "sandbox");
        sc.simpleJScallback();
        cc.director.runScene(sc);
        sc.setPosition(640, 360);

        var vertices3 = [cc.p(0, 100), cc.p(100, 0), cc.p(200, -50), cc.p(500, 0)];
        var veg = gm.SplineBasedVegetation.createWithFile(vertices3, 4, "res/images/flowers2.png")
        sc.addChild(veg);
        veg.growUp(0.1, 0.1, 20);
        veg.setScale(20, 20);
    },
});
