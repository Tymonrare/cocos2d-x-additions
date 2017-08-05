cd misc
python2 genbindings.py
cd ..
cp frameworks/runtime-src/Classes/JSB/api/*.js frameworks/cocos2d-x/cocos/scripting/js-bindings/script/
cocos run -p linux
